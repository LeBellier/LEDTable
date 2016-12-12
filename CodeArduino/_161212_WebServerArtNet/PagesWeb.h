#ifndef PAGESWEB_H
#define PAGESWEB_H

// Prototypage
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
void initDNS();
void initWebServer();
void updateWebServer();

void handleNotFound();
bool loadAnimation(String sPath);
bool loadFromSpiffs(String path);

MDNSResponder mdns;
ESP8266WebServer server(80);
int showType = 0;
bool animate = false;  // Web Button

// Déclaration
void initDNS() {
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
    Serial.println("You can use the name: http://esp8266.local/");
  }
}
void initWebServer() {
  SPIFFS.begin(); //start spiffs (spi file system)
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}
void updateWebServer() {
  mdns.update();
  // Check if a client has connected
  server.handleClient();
}

void handleNotFound() {
  String uriAsked = server.uri();
#ifdef DEBUG
  Serial.println(uriAsked);
#endif

  //check the request
  if (!loadFromSpiffs(server.uri()) && ! loadAnimation(server.uri())) { // no file at the uri found
    String message = "File Not Detected  ";
    message += "URI: ";
    message += server.uri();
    message += "\n  Method: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\n  Arguments: ";
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
bool loadAnimation(String sPath) {
  if (sPath.startsWith("/pixel_animation=")) {
    showType = sPath.substring(17).toInt();
    animate = true;
    server.send(200);
    return true;
  } else if (sPath.startsWith("/pixel_random=")) {
    String chiffres = "0123456789ABCDEF";
    sPath = sPath.substring(14);
    int ledNb = chiffres.indexOf(sPath.charAt(0)) * 16 + chiffres.indexOf(sPath.charAt(1));
    int r = chiffres.indexOf(sPath.charAt(2)) * 16 + chiffres.indexOf(sPath.charAt(3));
    int g = chiffres.indexOf(sPath.charAt(4)) * 16 + chiffres.indexOf(sPath.charAt(5));
    int b = chiffres.indexOf(sPath.charAt(6)) * 16 + chiffres.indexOf(sPath.charAt(7));
    if (ledNb == 156) {
      strip.setColor(r, g, b);
    } else {
      strip.setMatrixPixelColor(ledNb, r, g, b);
      strip.show();
    }
    String response = "";
    response.concat(sPath.substring(0, 2));
    response.concat('#');
    response.concat(sPath.substring(2, 8));

#ifdef DEBUG
    Serial.print( "Show color: " );
    Serial.print(r); Serial.print( " " );
    Serial.print(g); Serial.print( " " );
    Serial.println(b);
    Serial.println(response);
#endif
    server.send(200,"text/plain",response);
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
#endif
