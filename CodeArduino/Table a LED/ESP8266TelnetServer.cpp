﻿/*
* ESP8266TelnetServer.cpp
*
*  Created on: 1 mars 2017
*      Author: Bruno
*/

#include "ESP8266TelnetServer.h"

WiFiServer telnet_srv(23);


void ESP8266TelnetServer::begin() {

	telnet_srv.begin();
	telnet_srv.setNoDelay(true);
	DEBUG_SVR_TELNET("Please connect Telnet Client.");
}

void ESP8266TelnetServer::handleClient() {

	// look for Client connect trial
	if (telnet_srv.hasClient()) {
		if (!hasConnectedClient()) {
			stopClient();
			serverClient = telnet_srv.available();
			DEBUG_SVR_TELNET("New Telnet client");
			serverClient.flush(); // clear input buffer, else you get strange characters
		}
	}

	while (serverClient.available()) { // get data from Client

		char charRX = serverClient.read();
		if (charRX == 13 || charRX == 10) {
			if (nbChar > 0) {
				readCallBack(artnetPacket, nbChar);
				nbChar = 0;
			}
		}
		else if (nbChar == MAX_BUFFER_TELNET) {
			DEBUG_SVR_TELNET("Too many char in this message");
			nbChar = 0;
		}
		else if (charRX >= 0) {
			artnetPacket[nbChar] = charRX;
			nbChar++;
		}
	}
}
bool ESP8266TelnetServer::hasConnectedClient() {
	return (serverClient && serverClient.connected());
}

void ESP8266TelnetServer::stopClient() {
	if (serverClient) {
		serverClient.stop();
		DEBUG_SVR_TELNET("Telnet Client Stop");
	}
}

size_t ESP8266TelnetServer::write(uint8_t c) {
	if (hasConnectedClient()) {
		serverClient.write(c);
	}
	delay(10);  // to avoid strange characters left in buffer
	return 1;
}

size_t ESP8266TelnetServer::write(const uint8_t* buffer, size_t size) {
	if (hasConnectedClient()) {
		serverClient.write(buffer, size);
	}
	delay(10);  // to avoid strange characters left in buffer
	return size;
}
void ESP8266TelnetServer::setDebug(bool param) {
	_debug = param;
}

//read data callback
void ESP8266TelnetServer::setReadCallback(void(*func)(char*, uint8_t)) {
	readCallBack = func;
}
template<typename Generic>
void ESP8266TelnetServer::DEBUG_SVR_TELNET(Generic text) {
	if (_debug) {
		if (hasConnectedClient()) {
			print("*TelS*: ");
			println(text);
		}
		else {
			Serial.print("*TelS*: ");
			Serial.println(text);
		}
	}
}

ESP8266TelnetServer esp8266TelnetServer;
