/*
 * tal.h
 *
 *  Created on: 5 sept. 2017
 *      Author: Bruno
 */

#ifndef TAL_H_
#define TAL_H_

 /* Lib used under some other  */
 //#include <FS.h>
 //#include <ESP8266FtpServer.h>
 //#include <ESP8266TelnetServer.h>
 //#include <ArduinoOTA.h>
 //#include <DNSServer.h>
 //#include <memory>
extern "C" {
	//#include "user_interface.h"
}
#include <ESP8266WebServer.h>
#include <MatrixStrip.h>
#include <ServerManager.h>
#include <WifiManager.h>
#include <ArtnetWifi.h>

#include "GlobalVars.h"

#include "Animations.h"// besoin de IPAdress
#include "Callbacks.h" // besoin du strip

#endif /* TAL_H_ */
