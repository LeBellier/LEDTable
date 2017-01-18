/*
   Programme pour table à led
   Bruno Bellier
*/

//#define FTP_DEBUG
//#define DEBUG_ESP
//#define DEBUG_INIT
#include "Aspect.h"
String fileName = "Progam: ESPTable.ino";

#include "FS.h"

#include "PersonnalData.h"
#include "GlobalVariables.h"
#include "MatrixStrip.h"
#include "ArtNet.h"
#include "WifiManager.h"
#include "PagesWeb.h"

#include "Animations.h"

void setup(void) {
  Serial.begin(BAUDRATE);
  Serial.print("Coucou");

  pinMode( led, OUTPUT);
  digitalWrite( led, 0);
  strip.rgbBlink();

  initWIFILite();
  hasDebugDelay(15);
  artnet.setArtDmxCallback(onDmxFrame);
  artnet.begin();
  initDNS();
  hasDebugDelay(10);
  initWebServer();
  hasDebugDelay(10);
  initFtpServer();

  digitalWrite( led, 1);
}
void loop() {
  updateServers();
  artnet.read();
  if (animate == true) {
    startShow(showType);
    animate = false;
  }
}

