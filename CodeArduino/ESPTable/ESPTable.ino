/*
 Programme pour table à led
 Bruno Bellier
 */

#define FTP_DEBUG
#define DEBUG_ESP
#define DEBUG_INIT
#include <Aspect.h>

#include "PersonnalData.h"
#include <MatrixStrip.h>
//MatrixStrip strip(pixelPin, nbRows, nbColumns); // il faut les personnalData + MatrixStrip
#include "Animations.h"// besoin de IPAdress
#include <ServersWeb.h> // personnalData
#include <WifiManager.h> // personnalData
#include "ArtNet.h" // besoin du strip
#include "PagesWeb.h"

unsigned long startTime = millis();

void setup(void) {
	Serial.begin(BAUDRATE);

	pinMode( led, OUTPUT);
	digitalWrite( led, 0);
	strip.rgbBlink();

	initWIFI(nbSSID, SSIDs, passewords);
#ifdef DEBUG_INIT
	delay(15);
#endif

	artnet.setArtDmxCallback(onDmxFrame);
	artnet.begin();
	initDnsHttpFtpOtaTelnetServers(dnsName, ftpUser, ftpPasseWord, otaHostName,
			otaPasseWord);
#ifdef DEBUG_INIT
	delay(20);
#endif
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

	if (millis() - startTime > 5000) { // run every 5000 ms
		startTime = millis();
		telnetServeur.send("Telnet Test, millis: \r\n");
	}

}

