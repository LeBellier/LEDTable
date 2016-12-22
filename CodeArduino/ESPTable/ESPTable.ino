/*
   Programme pour table à led
   Bruno Bellier
*/

//#define DEBUG
//#define DEBUG_INIT
String fileName = "Progam: ESPTable.ino";

#include "FS.h"
#include "PersonnalData.h"
#include "GlobalVariables.h"
#include "MatrixStrip.h"
#include "ArtNet.h"
#include "WifiManager.h"
#include "PagesWeb.h"
#include "Aspect.h"
#include "Animations.h"

void setup(void) {

  pinMode( led, OUTPUT);
  digitalWrite( led, 0);
  strip.rgbBlink();

  hasDebug(initWIFILite);
  hasDebugDelay(15);
  artnet.setArtDmxCallback(onDmxFrame);
  artnet.begin();
  hasDebug(initDNS);
  hasDebugDelay(10);
  hasDebug(initWebServer);

  digitalWrite( led, 1);
}
void loop() {
  updateWebServer();
  artnet.read();
  if (animate == true) {
    startShow(showType);
    animate = false;
  }
}

