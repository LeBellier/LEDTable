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
void parseTelnet(String text) {
	svrs.printDebug(text);
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
	svrs.setServersON(B11111);

#ifdef DEBUG_INIT
	delay(20);
#endif
	svrs.httpSvr->onNotFound(handleRequestOnFile);
	svrs.httpSvr->on("/pixel", HTTP_GET, pixelRequest);
	svrs.setReadCallback(parseTelnet);

	if (WiFi.getMode() != WIFI_STA) {
		showIP(WiFi.softAPIP());
	} else {
		showIP(WiFi.localIP());
	}

	digitalWrite( led, 1);
}

void loop() {
	svrs.update();
	//artnet.read();
	//startShow(anim);

}

void pixelRequest() {
	svrs.printDebug(svrs.printRequest());
	if (svrs.httpSvr->hasArg("animation")) {
		anim.showType = svrs.httpSvr->arg("animation").toInt();
		anim.light = svrs.httpSvr->arg("light").toInt();
		anim.cycle = svrs.httpSvr->arg("cycle").toInt();
		anim.animate = true;
		svrs.httpSvr->send(200);
	} else if (svrs.httpSvr->hasArg("LEDnb")) {
		String chiffres = "0123456789ABCDEF";
		int ledNb = chiffres.indexOf(svrs.httpSvr->arg(0).charAt(0)) * 16
				+ chiffres.indexOf(svrs.httpSvr->arg(0).charAt(1));
		int r = chiffres.indexOf(svrs.httpSvr->arg(1).charAt(0)) * 16
				+ chiffres.indexOf(svrs.httpSvr->arg(1).charAt(1));
		int g = chiffres.indexOf(svrs.httpSvr->arg(2).charAt(0)) * 16
				+ chiffres.indexOf(svrs.httpSvr->arg(2).charAt(1));
		int b = chiffres.indexOf(svrs.httpSvr->arg(3).charAt(0)) * 16
				+ chiffres.indexOf(svrs.httpSvr->arg(3).charAt(1));
		if (ledNb == 156) {
			strip.setColor(r, g, b);
		} else {
			strip.setMatrixPixelColor(ledNb, r, g, b);
			strip.show();
		}
		String response = "";
		response.concat(svrs.httpSvr->arg(0));
		response.concat('#');
		response.concat(svrs.httpSvr->arg(1));
		response.concat(svrs.httpSvr->arg(2));
		response.concat(svrs.httpSvr->arg(3));

//		svrs.printDebug("Show color: ");
//		svrs.printDebug((String) r);
//		svrs.printDebug(" ");
//		svrs.printDebug((String) g);
//		svrs.printDebug(" ");
//		svrs.printDebug((String) b);
//		svrs.printDebug(" Response:");
		//svrs.printDebug(response);
		svrs.httpSvr->send(200, "text/plain", response);
	} else {
		svrs.handleRequestFile();
	}
}
