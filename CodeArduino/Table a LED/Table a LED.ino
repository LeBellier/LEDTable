#include "TAL.h"

void setup(void) {
	Serial.begin(BAUDRATE);
	Serial.println("");
	Serial.println("Nouvelle version 3");
	pinMode(led, OUTPUT);
	digitalWrite(led, 0);
	MatrixStrip.init(pixelPin, nbRows, nbColumns);
	MatrixStrip.rgbBlink();

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
	svrs.setReadTelnetCallback(parseTelnet);

	if (WiFi.getMode() != WIFI_STA) {
		showIP(WiFi.softAPIP());
	}
	else {
		showIP(WiFi.localIP());
	}
	digitalWrite(led, 1);
}

void loop() {
	svrs.update();
	artnet.read();
	startShow(anim);
}
