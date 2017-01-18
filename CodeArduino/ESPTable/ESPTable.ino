/*
   Programme pour table à led
   Bruno Bellier
*/

//#define FTP_DEBUG
//#define DEBUG_ESP
//#define DEBUG_INIT
#include <Aspect.h>
String fileName = "Progam: ESPTable.ino";

#include "FS.h"

#include "PersonnalData.h"
//#include "ConstCharColor.h"
#include <MatrixStrip.h>
MatrixStrip strip(pixelPin, nbRows, nbColumns); // il faut les personnalData+GlobaleVariables+MatrixStrip

#include "ArtNet.h"
#include <WifiManager.h> // Aspect + espWIFI 
#include "PagesWeb.h"

#include "Animations.h"
#include "MethodesGenerale.h" // besoin de IPAdress



void setup(void) {
  Serial.begin(BAUDRATE);
  Serial.print("Coucou");

  pinMode( led, OUTPUT);
  digitalWrite( led, 0);
  strip.rgbBlink();

  initWIFI();
  hasDebugDelay(15);
  artnet.setArtDmxCallback(onDmxFrame);
  artnet.begin();
  initDNS();
  hasDebugDelay(10);
  initHttpServer();
  hasDebugDelay(10);
  initFtpServer();

  showIP(WiFi.localIP());

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

