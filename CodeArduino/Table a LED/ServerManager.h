﻿/*
* ServerManager.h
*
*  Created on: 8 mars 2017
*      Author: Bruno
*
*  This class manager all servers usefull. TODO: optionnal server, now it's everythings or nothings
*/

#ifndef _SERVERMANAGER_h
#define _SERVERMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <ESP8266FtpServer.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>
#include <FS.h>

//#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include "ESP8266TelnetServer.h"
#include <memory>

extern "C" {
#include "user_interface.h"
}

// Define bit flag masks for the boolean settings in settings.flag.
#define SERVER_DNS         bit(0)
#define SERVER_HTTP        bit(1)
#define SERVER_FTP   	   bit(2)
#define SERVER_OTA         bit(3)
#define SERVER_TELNET      bit(4)
#define RESERVE1           bit(5)
#define RESERVE2           bit(6)
#define RESERVE3           bit(7)

class ServerManagerClass
{
protected:


public:
	void init();

	void setServersON(uint8_t);
	void update();
	String printRequest();

	// methodes to handle http requests on file in SPIFFS
	void handleRequestFile();bool loadFromSpiffs(String path);

	uint8_t isServersON();

	void setDnsName(char*);
	void setUserName(char*);
	void setPasseword(char*);

	void setDebug(bool);
	//read data callback
	void setReadTelnetCallback(void(*func)(char*, uint8_t));

	void printDebug(String text);

	template<typename Generic>
	void DEBUG_SVR_M(Generic text);

	std::unique_ptr<ESP8266WebServer> httpSvr;

private:
	// DNS server
	//const byte DNS_PORT = 53;
	uint8_t serversON = 0;

	char* dnsName = "ESP8266";
	char* userName = "ESP8266"; // OTA and FTP
	char* passeword = "ESP8266"; // OTA and FTP

	std::unique_ptr<MDNSResponder> dnsSvr;
	std::unique_ptr<FtpServer> ftpSvr;
	std::unique_ptr<ESP8266TelnetServer> telnetSvr;

	bool _debug = true;
};

extern ServerManagerClass svrs;

#endif
