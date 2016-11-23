#include "FS.h"
#include "Pins.h"

#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>
#include <ArtnetWifi.h>

//#define DEBUG
#define DEBUG_INIT
String fileName = "Progam: TestWebServerArtNet.ino";

#include "GlobalVariables.h"
#include "Strip.h"
#include "WifiManager.h"
#include "PagesWeb.h"
#include "ArtNet.h"
#include "Aspect.h"


void setup ( void ) {


  pinMode ( led, OUTPUT );
  digitalWrite ( led, 0 );
  hasDebug (initStrip);
  initStripTest();

  // fillChar('A', MAGENTA);
  // delay(10000);

  hasDebug (initWIFILite);
  hasDebugDelay(15);
  hasDebug (initArtNet);//
  hasDebugDelay(10);//
  hasDebug (initDNS);
  hasDebugDelay(10);
  hasDebug (initWebServer);

  initStripTest();
  digitalWrite ( led, 1 );
}
void loop () {
  updateWebServer();

  updateArtNet();
}
