/*
 Programme pour table à led
 Bruno Bellier
 */

#include "tal.h"

ServerManager svrs;

void pixelRequest(); // To assign one color on one LED and show animation
void handleRequestOnFile() {
	svrs.handleRequestFile();
}
unsigned long startTime = millis();

void setup(void) {
	Serial.begin(BAUDRATE);

	pinMode( led, OUTPUT);
	digitalWrite( led, 0);
	strip.rgbBlink();

	WiFiManager wifiManager;
	//reset settings - for testing
	//wifiManager.resetSettings();

	//set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
	//wifiManager.setAPCallback(configModeCallback);

	//fetches ssid and pass and tries to connect
	//if it does not connect it starts an access point with the specified name
	//here  "AutoConnectAP"
	//and goes into a blocking loop awaiting configuration
	if (!wifiManager.autoConnect()) {
		Serial.println("failed to connect and hit timeout");
		//reset and try again, or maybe put it to deep sleep
		ESP.reset();
		delay(1000);
	}

#ifdef DEBUG_INIT
	delay(15);
#endif

	artnet.setArtDmxCallback(onDmxFrame);
	artnet.begin();
	svrs.setServersON(0b11111);
#ifdef DEBUG_INIT
	delay(20);
#endif
	svrs.httpSvr->onNotFound(handleRequestOnFile);
	svrs.httpSvr->on("/pixel", HTTP_GET, pixelRequest);

	if (WiFi.getMode() != WIFI_STA) {
		showIP(WiFi.softAPIP());
	} else {
		showIP(WiFi.localIP());
	}

	digitalWrite( led, 1);
}

void loop() {
	svrs.update();
	artnet.read();
	startShow(anim);

}

void pixelRequest() {
	/*	svrs_printlnDebug(svrs_printRequest());
	 if (svrs.httpServer->hasArg("animation")) {
	 anim.showType = svrs.httpServer->arg("animation").toInt();
	 anim.light = svrs.httpServer->arg("light").toInt();
	 anim.cycle = svrs.httpServer->arg("cycle").toInt();
	 anim.animate = true;
	 svrs.httpServer->send(200);
	 } else if (svrs.httpServer->hasArg("LEDnb")) {
	 String chiffres = "0123456789ABCDEF";
	 int ledNb = chiffres.indexOf(svrs.httpServer->arg(0).charAt(0)) * 16
	 + chiffres.indexOf(svrs.httpServer->arg(0).charAt(1));
	 int r = chiffres.indexOf(svrs.httpServer->arg(1).charAt(0)) * 16
	 + chiffres.indexOf(svrs.httpServer->arg(1).charAt(1));
	 int g = chiffres.indexOf(svrs.httpServer->arg(2).charAt(0)) * 16
	 + chiffres.indexOf(svrs.httpServer->arg(2).charAt(1));
	 int b = chiffres.indexOf(svrs.httpServer->arg(3).charAt(0)) * 16
	 + chiffres.indexOf(svrs.httpServer->arg(3).charAt(1));
	 if (ledNb == 156) {
	 strip.setColor(r, g, b);
	 } else {
	 strip.setMatrixPixelColor(ledNb, r, g, b);
	 strip.show();
	 }
	 String response = "";
	 response.concat(svrs.httpServer->arg(0));
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
	 svrs_printDebug("Show color: ");
	 svrs_printDebug((String) r);
	 svrs_printDebug(" ");
	 svrs_printDebug((String) g);
	 svrs_printDebug(" ");
	 svrs_printDebug((String) b);
	 svrs_printDebug(" Response:");
	 svrs_printlnDebug(response);
	 svrs.httpServer->send(200, "text/plain", response);
	 } else {
	 svrs_handleRequestFile();
	 }*/
}
