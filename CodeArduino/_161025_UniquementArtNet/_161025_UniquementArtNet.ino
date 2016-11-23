#include "FS.h"

#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>
#include <ArtnetWifi.h>
#include "Arduino.h"

//#define DEBUG
String fileName = "Progam: TestArtNet.ino";

#include "GlobalVariables.h"
#include "WifiManager.h"
#include "ArtNet.h"
#include "Strip.h"
#include "Aspect.h"


void setup ( void ) {
  pinMode ( led, OUTPUT );
  digitalWrite ( led, 0 );

  hasDebug (initStrip);
  hasDebug (initWIFILite);
  hasDebugDelay(15);
  hasDebug (initArtNet);
  hasDebugDelay(10);

  initStripTest();
  digitalWrite ( led, 1 );
}

void loop ( void ) {

  updateArtNet();

}
