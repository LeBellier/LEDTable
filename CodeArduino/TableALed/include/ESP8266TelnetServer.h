﻿/*
* ESP8266TelnetServer.h
*
*  Created on: 1 mars 2017
*      Author: Bruno
*
*  This class is a Telnet server which handle the first client connected until its disconnexion.
*
*  Char read go directely to Serial, TODO: add methodes to manage these characters.
*/

#ifndef _ESP8266TELNETSERVER_h
#define _ESP8266TELNETSERVER_h

#include <ESP8266WiFi.h>
#include <string.h>

// Buffers
#define MAX_BUFFER_TELNET 255
#define END_CHAR 'o'

class ESP8266TelnetServer : public Print {

public:
	void begin();
	void handleClient();
	bool hasConnectedClient();
	void stopClient();

	size_t write(uint8_t) override;
	size_t write(const uint8_t *, size_t) override;

	void setDebug(bool);
	//called when read some char ends by \n
	void setReadCallback(void(*func)(char*, uint8_t));

private:
	WiFiClient serverClient;
	void(*readCallBack)(char*, uint8_t) = NULL;

	char artnetPacket[MAX_BUFFER_TELNET];
	uint8_t nbChar = 0;

	bool _debug = true;
	template<typename Generic>
	void DEBUG_SVR_TELNET(Generic text);

};

extern ESP8266TelnetServer esp8266TelnetServer;

#endif
