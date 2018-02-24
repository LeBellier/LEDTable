#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "TAL.h"

// parse cmd from DMX port
void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence,
	uint8_t* data) {

#ifdef DEBUG_ESP
	DEBUG_PRINT("DMX: Univ: ");
	DEBUG_PRINT(universe, DEC);
	DEBUG_PRINT(", Seq: ");
	DEBUG_PRINT(sequence, DEC);
	DEBUG_PRINT(", Data (");
	DEBUG_PRINT(length, DEC);
	DEBUG_PRINT("): ");

	// send out the buffer
	for (int i = 0; i < length; i++) {
		DEBUG_PRINT(data[i], HEX);
		DEBUG_PRINT(" ");
	}
	DEBUG_PRINT("\n");
#endif

	// read universe and put into the right part of the display buffer
	for (int i = 0; i < length / 3; i++) {
		int led = i;
		if (led < MatrixStrip.numPixels()) {
			MatrixStrip.setMatrixPixelColor(led, data[i * 3], data[i * 3 + 1],
				data[i * 3 + 2]);
		}
	}
	MatrixStrip.show();
}

// To assign one color on one LED and show animation
void pixelRequest() {
	svrs.printDebug(svrs.printRequest());
	if (svrs.httpSvr->hasArg("animation")) {
		anim.showType = svrs.httpSvr->arg("animation").toInt();
		anim.light = svrs.httpSvr->arg("light").toInt();
		anim.cycle = svrs.httpSvr->arg("cycle").toInt();
		anim.animate = true;
		svrs.httpSvr->send(200);
	}
	else if (svrs.httpSvr->hasArg("LEDnb")) {
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
			MatrixStrip.setColor(r, g, b);
		}
		else {
			MatrixStrip.setMatrixPixelColor(ledNb, r, g, b);
			MatrixStrip.show();
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
	}
	else {
		svrs.handleRequestFile();
	}
}

void handleRequestOnFile() {
	svrs.handleRequestFile();
}
void parseTelnet(char* text, uint8_t size) {
	String message = "";
	for (int i = 0; i < size; i++) {
		message += text[i];
	}
	svrs.printDebug(message);
}

#endif
