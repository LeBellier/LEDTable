/*
   Programme pour table à led
   Bruno Bellier
*/

//#define FTP_DEBUG
//#define DEBUG_ESP
//#define DEBUG_INIT

#include "PersonnalData.h"
#include <Aspect.h>
#include <MatrixStrip.h>
MatrixStrip strip(pixelPin, nbRows, nbColumns); // il faut les personnalData + MatrixStrip
#include <ServersWeb.h> // personnalData
#include <WifiManager.h> // personnalData
#include "ArtNet.h" // besoin du strip
#include "PagesWeb.h"
#include "Animations.h"// besoin de IPAdress

void setup(void) {
  Serial.begin(BAUDRATE);

  pinMode( led, OUTPUT);
  digitalWrite( led, 0);
  strip.rgbBlink();

  initWIFI();
  hasDebugDelay(15);
  artnet.setArtDmxCallback(onDmxFrame);
  artnet.begin();
  initDnsHttpFtpServers();
  httpServer.on("/pixel", HTTP_GET, pixelRequest);
  hasDebugDelay(20);

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

