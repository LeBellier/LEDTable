/*
  Programme pour table à led
  Bruno Bellier
*/

//#define FTP_DEBUG
//#define DEBUG_ESP
//#define DEBUG_INIT
#include <Aspect.h>

#include "PersonnalData.h"
#include <MatrixStrip.h>
// MatrixStrip strip(pixelPin, nbRows, nbColumns); // il faut les personnalData + MatrixStrip
#include "Animations.h"// besoin de IPAdress
#include <ServersWeb.h> // personnalData
#include <WifiManager.h> // personnalData
#include "ArtNet.h" // besoin du strip
#include "PagesWeb.h"

void setup(void) {
  Serial.begin(BAUDRATE);

  pinMode( led, OUTPUT);
  digitalWrite( led, 0);
  strip.rgbBlink();

  initWIFI();
  delayIfDebug(15);

  artnet.setArtDmxCallback(onDmxFrame);
  artnet.begin();
  initDnsHttpFtpOtaServers();
  delayIfDebug(20);
  httpServer.on("/pixel", HTTP_GET, pixelRequest);

  if (WiFi.getMode() != WIFI_STA) {
    showIP(WiFi.softAPIP());
  } else {
    showIP(WiFi.localIP());
  }

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

