#ifndef PAGESWEB_H
#define PAGESWEB_H

#include <ESP8266WebServer.h>
#include <Aspect.h>

// Prototypage
void pixelRequest(); // To assign one color on one LED and show animation

// Déclaration
void pixelRequest() {
	if (httpServer.hasArg("animation")) {
		showType = httpServer.arg(0).toInt();
		animate = true;
		httpServer.send(200);
	} else if (httpServer.hasArg("LEDnb")) {
		String chiffres = "0123456789ABCDEF";
		int ledNb = chiffres.indexOf(httpServer.arg(0).charAt(0)) * 16
				+ chiffres.indexOf(httpServer.arg(0).charAt(1));
		int r = chiffres.indexOf(httpServer.arg(1).charAt(0)) * 16
				+ chiffres.indexOf(httpServer.arg(1).charAt(1));
		int g = chiffres.indexOf(httpServer.arg(2).charAt(0)) * 16
				+ chiffres.indexOf(httpServer.arg(2).charAt(1));
		int b = chiffres.indexOf(httpServer.arg(3).charAt(0)) * 16
				+ chiffres.indexOf(httpServer.arg(3).charAt(1));
		if (ledNb == 156) {
			strip.setColor(r, g, b);
		} else {
			strip.setMatrixPixelColor(ledNb, r, g, b);
			strip.show();
		}
		String response = "";
		response.concat(httpServer.arg(0));
		response.concat('#');
		response.concat(httpServer.arg(1));
		response.concat(httpServer.arg(2));
		response.concat(httpServer.arg(3));

		telnetServeur.send("Show color: ");
		telnetServeur.send((String) r);
		telnetServeur.send(" ");
		telnetServeur.send((String) g);
		telnetServeur.send(" ");
		telnetServeur.send((String) b);
		telnetServeur.send(" Response:");
		telnetServeur.send(response);
		telnetServeur.send("\n\r");
		httpServer.send(200, "text/plain", response);
	} else {
		handleRequestOnFile();
	}
}

#endif
