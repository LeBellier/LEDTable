/*
 Programme pour table à led
 Bruno Bellier
 */

#define FTP_DEBUG
#define DEBUG_ESP
#define DEBUG_INIT
#include "Logger.h"
Logger* logger;

#include "PersonnalData.h"
#include <MatrixStrip.h>
//MatrixStrip strip(pixelPin, nbRows, nbColumns); // il faut les personnalData + MatrixStrip
#include "Animations.h"// besoin de IPAdress
#include <ServerManager.h>
ServerManager serverM(logger);
#include <WifiManager.h>
#include "ArtNet.h" // besoin du strip

// Prototypage
void pixelRequest(); // To assign one color on one LED and show animation

unsigned long startTime = millis();

void setup(void) {
	Serial.begin(BAUDRATE);
	logger->setPrinter(&Serial);

	pinMode( led, OUTPUT);
	digitalWrite( led, 0);
	strip.rgbBlink();

	initWIFI(nbSSID, SSIDs, passewords);
#ifdef DEBUG_INIT
	delay(15);
#endif

	artnet.setArtDmxCallback(onDmxFrame);
	artnet.begin();
	serverM.initDnsHttpFtpOtaTelnetServers(dnsName, ftpUser, ftpPasseWord,
			otaHostName, otaPasseWord);
#ifdef DEBUG_INIT
	delay(20);
#endif
	serverM.httpServer.on("/pixel", HTTP_GET, pixelRequest);

	if (WiFi.getMode() != WIFI_STA) {
		showIP(WiFi.softAPIP());
	} else {
		showIP(WiFi.localIP());
	}

	digitalWrite( led, 1);
}

void loop() {
	serverM.updateServers();
	artnet.read();
	if (animate == true) {
		startShow(showType);
		animate = false;
	}

	if (millis() - startTime > 5000) { // run every 5000 ms
		startTime = millis();
		//telnetServeur.send("Telnet Test, millis: \r\n");
	}

}

void pixelRequest() {
	if (serverM.httpServer.hasArg("animation")) {
		showType = serverM.httpServer.arg(0).toInt();
		animate = true;
		serverM.httpServer.send(200);
	} else if (serverM.httpServer.hasArg("LEDnb")) {
		String chiffres = "0123456789ABCDEF";
		int ledNb = chiffres.indexOf(serverM.httpServer.arg(0).charAt(0)) * 16
				+ chiffres.indexOf(serverM.httpServer.arg(0).charAt(1));
		int r = chiffres.indexOf(serverM.httpServer.arg(1).charAt(0)) * 16
				+ chiffres.indexOf(serverM.httpServer.arg(1).charAt(1));
		int g = chiffres.indexOf(serverM.httpServer.arg(2).charAt(0)) * 16
				+ chiffres.indexOf(serverM.httpServer.arg(2).charAt(1));
		int b = chiffres.indexOf(serverM.httpServer.arg(3).charAt(0)) * 16
				+ chiffres.indexOf(serverM.httpServer.arg(3).charAt(1));
		if (ledNb == 156) {
			strip.setColor(r, g, b);
		} else {
			strip.setMatrixPixelColor(ledNb, r, g, b);
			strip.show();
		}
		String response = "";
		response.concat(serverM.httpServer.arg(0));
		response.concat('#');
		response.concat(serverM.httpServer.arg(1));
		response.concat(serverM.httpServer.arg(2));
		response.concat(serverM.httpServer.arg(3));

//		telnetServeur.send("Show color: ");
//		telnetServeur.send((String) r);
//		telnetServeur.send(" ");
//		telnetServeur.send((String) g);
//		telnetServeur.send(" ");
//		telnetServeur.send((String) b);
//		telnetServeur.send(" Response:");
//		telnetServeur.send(response);
//		telnetServeur.send("\n\r");
		serverM.httpServer.send(200, "text/plain", response);
	} else {
		serverM.handleRequestFile();
	}
}

