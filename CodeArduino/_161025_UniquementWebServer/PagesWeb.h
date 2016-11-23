// Prototypage
void initDNS();
void initWebServer();
void updateWebServer();

// Set color for the whole strip
void setColor(uint32_t color);

//send the "ok" response to client
//if it's the first conection or reload then send page, if not check request
void response(WiFiClient k);

//send the html page to client
void printPage(WiFiClient k);
//trait the request
void checkRequest(WiFiClient k, String request) ;

MDNSResponder mdns;
WiFiServer server(80);

// Déclaration
void initDNS() {
  if ( mdns.begin ( "esp8266", WiFi.localIP() ) ) {
    Serial.println ( "MDNS responder started" );
    Serial.println ( "You can use the name: http://esp8266.local/" );
  }
}
void initWebServer() {
  SPIFFS.begin();//start spiffs (spi file system)
  server.begin();
  Serial.println ( "HTTP server started" );
}
void updateWebServer() {
  mdns.update();
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  //analyze data received from client
  response(client);
  client.flush();
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

void response(WiFiClient k) {
  k.println("HTTP/1.1 200 OK");
  k.println("Content-Type: text/html");
  k.println(""); //  do not forget this one
  String request = k.readStringUntil('\n');//read request
#ifdef DEBUG
  Serial.println(request);
#endif
  //check if request
  if ((request.indexOf("/c") == 4) || request.indexOf("/r") == 4) {
    request.remove(0, 5);
    checkRequest(k, request);
    return;
  }
  printPage(k);
}
////////////////////////////////////////////////////////////////////////////
//send the html page to client                                           //
//////////////////////////////////////////////////////////////////////////
void printPage(WiFiClient k) {
  String buff;
  File f = SPIFFS.open("/4LEDS.html", "r");//open html page for reading
  if (!f) {
    Serial.println("file open failed");// check if file exists
    return;
  }
  buff = f.readString();// read all file at once
  int fileSize = f.size();
  f.close();// close the file
  // send data to browser in packets of 2KB each
  for (int i = 0; i < ((fileSize / 2000) + 1); i++) {
    k.print(buff.substring(i * 2000, (1 + i) * 2000));
  }
}
////////////////////////////////////////////////////////////////////////////
//check if client wants to read the states of leds or want to change them//
//////////////////////////////////////////////////////////////////////////
void checkRequest(WiFiClient k, String request) {
  int i = 0;
  String response = "/";// add the first char of the response string
  //check if request it's a command
  if (request.indexOf("c") != -1) {
    String chiffres = "0123456789ABCDEF";

    int ledNb = chiffres.indexOf(request.charAt(1)) * 16 + chiffres.indexOf(request.charAt(2));
    int r = chiffres.indexOf(request.charAt(3)) * 16 + chiffres.indexOf(request.charAt(4));
    int g = chiffres.indexOf(request.charAt(5)) * 16 + chiffres.indexOf(request.charAt(6));
    int b = chiffres.indexOf(request.charAt(7)) * 16 + chiffres.indexOf(request.charAt(8));
    uint32_t color = strip.Color(r, g, b);
    if (ledNb == 156) {
      setColor( color);
    } else {
      strip.setPixelColor(ledNb, color);
      strip.show();
    }
    response.concat(request.substring(1, 3));
    response.concat('#');
    response.concat(request.substring(3, 9));

#ifdef DEBUG
    Serial.print( "Show color: " );
    Serial.print(r); Serial.print( " " );
    Serial.print(g); Serial.print( " " );
    Serial.println(b);
    Serial.println(response);
#endif
    k.println(response);// send response to client
    return;
  }
  if (request.indexOf("r") != -1) {//check if client wants to read the state of leds
  }
}





