/*
MatrixStrip.h

Created on: 21 nov. 2016
Author: bruno
*/

#ifndef _MATRIXSTRIP_h
#define _MATRIXSTRIP_h

#include <Adafruit_NeoPixel.h>
#include "CharAndColor.h"

class MatrixStripClass : public Adafruit_NeoPixel
{
public:
	void init(uint8_t pinStrip, uint8_t nbRows, uint8_t nbColumns);
	void setMatrixPixelColor(uint16_t n, uint32_t color);
	void setMatrixPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
	void setColor(uint32_t color);
	void setColor(uint8_t r, uint8_t g, uint8_t b);
	void rgbBlink();
	void colorBlink(uint32_t color);
	void fillChar(char letter, uint32_t color);
	void fillNumber(byte positionScreen, char letter, uint32_t color);
	void printNumber(int i, String number);
	// numpixels(); pour get le nombre de pixels
private:
	uint8_t nbRows, nbColumns;
	bool isInit;
};

extern MatrixStripClass MatrixStrip;

#endif
