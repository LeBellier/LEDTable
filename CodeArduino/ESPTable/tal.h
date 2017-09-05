/*
 * tal.h
 *
 *  Created on: 5 sept. 2017
 *      Author: Bruno
 */

#ifndef TAL_H_
#define TAL_H_

//#define FTP_DEBUG
//#define DEBUG_ESP
#define DEBUG_INIT

#include <Aspect.h>

//#include <FS.h>
//#include <ESP8266FtpServer.h>
#include <ESP8266WebServer.h>
//#include <Libs/ESP8266TelnetServer.h>
//#include <ArduinoOTA.h>
//#include <DNSServer.h>
//#include <memory>

/* extern "C" {
 #include "user_interface.h"
 }*/
#include "PersonnalData.h"
#include <MatrixStrip.h>
MatrixStrip strip(pixelPin, nbRows, nbColumns); // il faut les personnalData + MatrixStrip
#include "Animations.h"// besoin de IPAdress
Animation anim;
#include <Libs/ServerManager.h>
#include <Libs/WifiManager.h>
#include "ArtNet.h" // besoin du strip

#endif /* TAL_H_ */
