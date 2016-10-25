/////////////////////////////////////////////////////////////////////////////
//LOCAL NETWORK  SERVER WITH NODEMCU                                      //
//PETRESCU CRISTIAN                                                      //
//////////////////////////////////////////////////////////////////////////
//file system reference:
//http://arduino.esp8266.com/versions/1.6.5-1160-gef26c5f/doc/reference.html#file-system-object-spiffs
//html and java sript reference:
//http://www.w3schools.com/
//check my blog :www.hobbyelectro.blogspot.ro

#include "FS.h"
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>

//#define DEBUG

#include "GlobalVariables.h"
#include "WifiManager.h"
#include "PagesWeb.h"
#include "Aspect.h"


void setup ( void ) {
  pinMode ( led, OUTPUT );
  digitalWrite ( led, 0 );

  strip.begin();
  strip.show();

 hasDebug (initWIFILite);
  hasDebugDelay(15);
  hasDebug (initDNS);
  hasDebugDelay(10);
  hasDebug (initWebServer);
  digitalWrite ( led, 1 );
}
void loop () {
  updateWebServer();
}
