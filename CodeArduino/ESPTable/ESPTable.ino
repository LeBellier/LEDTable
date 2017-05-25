/*
 Programme pour table à led
 Bruno Bellier
 */

//#define FTP_DEBUG
//#define DEBUG_ESP
#define DEBUG_INIT
#include <Aspect.h>

#include "PersonnalData.h"
#include <MatrixStrip.h>
#include "Animations.h"// besoin de IPAdress
Animation anim;
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
	serverManager.initDnsHttpFtpOtaTelnetServers(hostName, hostName, passeWord,
			hostName, passeWord);
#ifdef DEBUG_INIT
	delay(20);
#endif
	serverManager.httpServer.onNotFound(handleRequestOnFile);
	serverManager.httpServer.on("/pixel", HTTP_GET, pixelRequest);

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
		startShow(anim);
		animate = false;
	}
}

void pixelRequest() {
	serverManager.printlnDebug(serverManager.printRequest());
	if (serverManager.httpServer.hasArg("animation")) {
		anim.showType = serverManager.httpServer.arg("animation").toInt();
		anim.light = serverManager.httpServer.arg("light").toInt();
		anim.cycle = serverManager.httpServer.arg("cycle").toInt();
		animate = true;
		serverManager.httpServer.send(200);
	} else if (serverManager.httpServer.hasArg("LEDnb")) {
		String chiffres = "0123456789ABCDEF";
		int ledNb = chiffres.indexOf(serverManager.httpServer.arg(0).charAt(0)) * 16
				+ chiffres.indexOf(serverManager.httpServer.arg(0).charAt(1));
		int r = chiffres.indexOf(serverManager.httpServer.arg(1).charAt(0)) * 16
				+ chiffres.indexOf(serverManager.httpServer.arg(1).charAt(1));
		int g = chiffres.indexOf(serverManager.httpServer.arg(2).charAt(0)) * 16
				+ chiffres.indexOf(serverManager.httpServer.arg(2).charAt(1));
		int b = chiffres.indexOf(serverManager.httpServer.arg(3).charAt(0)) * 16
				+ chiffres.indexOf(serverManager.httpServer.arg(3).charAt(1));
		if (ledNb == 156) {
			strip.setColor(r, g, b);
		} else {
			strip.setMatrixPixelColor(ledNb, r, g, b);
			strip.show();
		}
		String response = "";
		response.concat(serverManager.httpServer.arg(0));
		response.concat('#');
		response.concat(serverManager.httpServer.arg(1));
		response.concat(serverManager.httpServer.arg(2));
		response.concat(serverManager.httpServer.arg(3));

		serverManager.printDebug("Show color: ");
		serverManager.printDebug((String) r);
		serverManager.printDebug(" ");
		serverManager.printDebug((String) g);
		serverManager.printDebug(" ");
		serverManager.printDebug((String) b);
		serverManager.printDebug(" Response:");
		serverManager.printlnDebug(response);
		serverManager.httpServer.send(200, "text/plain", response);
	} else {
		serverManager.handleRequestFile();
	}
}
