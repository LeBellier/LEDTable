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
#include "Animations.h"// besoin de IPAdress
#include <ServerManager.h> // personnalData
ServerManager serverManager;
#include <WifiManager.h> // personnalData
#include "ArtNet.h" // besoin du strip

void pixelRequest(); // To assign one color on one LED and show animation
void handleRequestOnFile() {
	serverManager.handleRequestFile();
}

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
	serverManager.initDnsHttpFtpOtaTelnetServers(dnsName, ftpUser, ftpPasseWord,
			otaHostName, otaPasseWord);
#ifdef DEBUG_INIT
	delay(20);
#endif
	serverManager.getHttpServer().onNotFound(handleRequestOnFile);
	serverManager.getHttpServer().on("/pixel", HTTP_GET, pixelRequest);

	if (WiFi.getMode() != WIFI_STA) {
		showIP(WiFi.softAPIP());
	} else {
		showIP(WiFi.localIP());
	}

	digitalWrite( led, 1);
}

void loop() {
	serverManager.updateServers();
	artnet.read();
	if (animate == true) {
		startShow(showType);
		animate = false;
	}

	if (millis() - startTime > 5000) { // run every 5000 ms
		startTime = millis();
		serverManager.printDebug("Telnet Test, millis:");
		serverManager.printlnDebug((String) startTime);
	}

}

void pixelRequest() {
	ESP8266WebServer httpServer = serverManager.getHttpServer();

	if (httpServer.hasArg("animation")) {
		showType = httpServer.arg(0).toInt();
		animate = true;
		httpServer.send(200);
	} else if (httpServer.hasArg("LEDnb")) {
		String chiffres = "0123456789ABCDEF";
		int ledNb = chiffres.indexOf(httpServer.arg(0).charAt(0)) * 16
				+ chiffres.indexOf(httpServer.arg(0).charAt(1));
		int r = chiffres.indexOf(httpServer.arg(1).charAt(0)) * 16
				+ chiffres.indexOf(httpServer.arg(1).charAt(1));
		int g = chiffres.indexOf(httpServer.arg(2).charAt(0)) * 16
				+ chiffres.indexOf(httpServer.arg(2).charAt(1));
		int b = chiffres.indexOf(httpServer.arg(3).charAt(0)) * 16
				+ chiffres.indexOf(httpServer.arg(3).charAt(1));
		if (ledNb == 156) {
			strip.setColor(r, g, b);
		} else {
			strip.setMatrixPixelColor(ledNb, r, g, b);
			strip.show();
		}
		String response = "";
		response.concat(httpServer.arg(0));
		response.concat('#');
		response.concat(httpServer.arg(1));
		response.concat(httpServer.arg(2));
		response.concat(httpServer.arg(3));

		serverManager.printDebug("Show color: ");
		serverManager.printDebug((String) r);
		serverManager.printDebug(" ");
		serverManager.printDebug((String) g);
		serverManager.printDebug(" ");
		serverManager.printDebug((String) b);
		serverManager.printDebug(" Response:");
		serverManager.printlnDebug(response);
		httpServer.send(200, "text/plain", response);
	} else {
		serverManager.handleRequestFile();
	}
}
