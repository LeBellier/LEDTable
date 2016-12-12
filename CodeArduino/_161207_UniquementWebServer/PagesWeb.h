// Prototypage
void initDNS();
void initWebServer();
void updateWebServer();

// Set color for the whole strip
void setColor(uint32_t color);
//send the html page to client
void printPage(WiFiClient k);


void handleNotFound();
bool loadAnimation(String sPath);
bool loadFromSpiffs(String path);
//trait the request
void checkRequest();

MDNSResponder mdns;
ESP8266WebServer server(80);

// Déclaration
void initDNS() {
  if ( mdns.begin ( "esp8266", WiFi.localIP() ) ) {
    Serial.println ( "MDNS responder started" );
    Serial.println ( "You can use the name: http://esp8266.local/" );
  }
}
void initWebServer() {
  SPIFFS.begin();//start spiffs (spi file system)
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println ( "HTTP server started" );
}
void updateWebServer() {
  mdns.update();
  // Check if a client has connected
  server.handleClient();
}
void setColor(uint32_t color) {
  int i;
  for (i = 0; i < pixelCount; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
  Serial.println( "Show color: " );
  Serial.println(color);
}
/////////////////////////////////////////////////////////////////////////////////
//send the "ok" response to client                                            //
//if it's the first conection or reload then send page, if not check request //
//////////////////////////////////////////////////////////////////////////////

void handleNotFound() {
  String uriAsked = server.uri();
#ifdef DEBUG
  Serial.println(uriAsked);
#endif

  //check the request
  if ((uriAsked.indexOf("/c") !=- 1) || uriAsked.indexOf("/r") != -1) {
    checkRequest();
  } else if (!loadFromSpiffs(server.uri()) && ! loadAnimation(server.uri())) { // no file at the uri found
    String message = "File Not Detected  ";
    message += "URI: ";
    message += server.uri();
    message += "  Method: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "  Arguments: ";
    message += server.args();
    for (uint8_t i = 0; i < server.args(); i++) {
      message += " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
#ifdef DEBUG
    Serial.println(message);
#endif
  }
}
////////////////////////////////////////////////////////////////////////////
//send the html page to client                                           //
//////////////////////////////////////////////////////////////////////////

bool loadAnimation(String sPath) {

  if (sPath.startsWith("/pixel_inputs&LED")) {
    if (sPath.startsWith("/pixel_inputs&LED3=0")) {
      showType = 0;
      animate = true;
    }
    else if (sPath.startsWith("/pixel_inputs&LED3=1")) {
      showType = 1;
      animate = true;
    }
    else if (sPath.startsWith("/pixel_inputs&LED3=2")) {
      showType = 2;
      animate = true;
    }
    else if (sPath.startsWith("/pixel_inputs&LED3=3")) {
      showType = 3;
      animate = true;
    }
    else if (sPath.startsWith("/pixel_inputs&LED3=4")) {
      showType = 4;
      animate = true;
    }
    else if (sPath.startsWith("/pixel_inputs&LED3=5")) {
      showType = 5;
      animate = true;
    }
    else if (sPath.startsWith("/pixel_inputs&LED3=6")) {
      showType = 6;
      animate = true;
    }
    else if (sPath.startsWith("/pixel_inputs&LED3=7")) {
      showType = 7;
      animate = true;
    }
    else if (sPath.startsWith("/pixel_inputs&LED3=8")) {
      showType = 8;
      animate = true;
    }
    else if (sPath.startsWith("/pixel_inputs&LED3=9")) {
      showType = 9;
      animate = true;
    }
    return true;
  } else {
    return false;
  }
}
bool loadFromSpiffs(String path) {

  String dataType = "text/plain";
  if (path.endsWith("/")) path += "index.html";

  if (path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));
  else if (path.endsWith(".html")) dataType = "text/html";
  else if (path.endsWith(".css")) dataType = "text/css";
  else if (path.endsWith(".js"))  dataType = "application/javascript";
  else if (path.endsWith(".png")) dataType = "image/png";
  else if (path.endsWith(".gif")) dataType = "image/gif";
  else if (path.endsWith(".jpg")) dataType = "image/jpeg";
  else if (path.endsWith(".ico")) dataType = "image/x-icon";
  else if (path.endsWith(".xml")) dataType = "text/xml";
  else if (path.endsWith(".pdf")) dataType = "application/pdf";
  else if (path.endsWith(".zip")) dataType = "application/zip";

  File dataFile = SPIFFS.open(path.c_str(), "r");
  if (!dataFile) {
    return false;
  }

  if (server.hasArg("download")) dataType = "application/octet-stream";
  if (server.streamFile(dataFile, dataType) != dataFile.size()) {
#ifdef DEBUG
    //Serial.println("Sent less data than expected!");
#endif
    return false;
  }
  dataFile.close();
  return true;
}

////////////////////////////////////////////////////////////////////////////
//check if client wants to read the states of leds or want to change them//
//////////////////////////////////////////////////////////////////////////
void checkRequest() {
  String uriAsked = server.uri();
  int i = 0;
  String response = "/";// add the first char of the response string
  //check if request it's a command
  if (uriAsked.indexOf("c") != -1) {
    String chiffres = "0123456789ABCDEF";

    int ledNb = chiffres.indexOf(uriAsked.charAt(1)) * 16 + chiffres.indexOf(uriAsked.charAt(2));
    int r = chiffres.indexOf(uriAsked.charAt(3)) * 16 + chiffres.indexOf(uriAsked.charAt(4));
    int g = chiffres.indexOf(uriAsked.charAt(5)) * 16 + chiffres.indexOf(uriAsked.charAt(6));
    int b = chiffres.indexOf(uriAsked.charAt(7)) * 16 + chiffres.indexOf(uriAsked.charAt(8));
    uint32_t color = strip.Color(r, g, b);
    if (ledNb == 156) {
      setColor( color);
    } else {
      strip.setPixelColor(ledNb, color);
      strip.show();
    }
    response.concat(uriAsked.substring(1, 3));
    response.concat('#');
    response.concat(uriAsked.substring(3, 9));

#ifdef DEBUG
    Serial.print( "Show color: " );
    Serial.print(r); Serial.print( " " );
    Serial.print(g); Serial.print( " " );
    Serial.println(b);
    Serial.println(response);
#endif
    server.send(200, "text/plain", response); // send response to client
    return;
  }
  if (uriAsked.indexOf("r") != -1) {//check if client wants to read the state of leds
  }
}
