#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "TAL.h"
// Prototypage

struct Animation {
	bool animate;
	int showType, light, cycle;
};
Animation anim;

// Show the selected animation
void startShow(Animation);
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait);
void rainbow(uint8_t wait, uint8_t cycle, uint8_t light);
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait, uint8_t cycle, uint8_t light);
//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait);
//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait, uint8_t light);
uint32_t Wheel(uint8_t wheelPos, uint8_t light);
void showIP(IPAddress ip);

const char spirale[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 38, 39,
64, 65, 90, 91, 116, 117, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151,
152, 153, 154, 155, 130, 129, 104, 103, 78, 77, 52, 51, 26, 25, 24, 23, 22,
21, 20, 19, 18, 17, 16, 15, 14, 37, 40, 63, 66, 89, 92, 115, 118, 141, 140,
139, 138, 137, 136, 135, 134, 133, 132, 131, 128, 105, 102, 79, 76, 53, 50,
27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 41, 62, 67, 88, 93, 114, 119, 120,
121, 122, 123, 124, 125, 126, 127, 106, 101, 80, 75, 54, 49, 48, 47, 46, 45,
44, 43, 42, 61, 68, 87, 94, 113, 112, 111, 110, 109, 108, 107, 100, 81, 74,
55, 56, 57, 58, 59, 60, 69, 86, 95, 96, 97, 98, 99, 82, 73, 72, 71, 70, 85,
84, 83 };
const char spirale2[] = { 12, 13, 38, 39, 64, 65, 90, 91, 116, 117, 142, 143,
144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 130, 129, 104,
103, 78, 77, 52, 51, 26, 25, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 14, 37,
40, 63, 66, 89, 92, 115, 118, 141, 140, 139, 138, 137, 136, 135, 134, 133,
132, 131, 128, 105, 102, 79, 76, 53, 50, 27, 24, 23, 22, 21, 20, 19, 18, 17,
16, 15, 36, 41, 62, 67, 88, 93, 114, 119, 120, 121, 122, 123, 124, 125, 126,
127, 106, 101, 80, 75, 54, 49, 28, 29, 30, 31, 32, 33, 34, 35, 42, 61, 68,
87, 94, 113, 112, 111, 110, 109, 108, 107, 100, 81, 74, 55, 48, 47, 46, 45,
44, 43, 60, 69, 86, 95, 96, 97, 98, 99, 82, 73, 56, 57, 58, 59, 70, 85, 84,
83, 72, 71 };

// Déclaration

void startShow(Animation anim) {
	if (anim.animate == true) {
		switch (anim.showType) {
		case 0:
			colorWipe(MatrixStrip.Color(0, 0, 0), 50);    // Black/off
			break;
		case 1:
			colorWipe(MatrixStrip.Color(255 * anim.light / 100, 0, 0), 50);  // Red
			break;
		case 2:
			colorWipe(MatrixStrip.Color(0, 255 * anim.light / 100, 0), 50);  // Green
			break;
		case 3:
			colorWipe(MatrixStrip.Color(0, 0, 255 * anim.light / 100), 50);  // Blue
			break;
		case 4:
			theaterChase(
				MatrixStrip.Color(255 * anim.light / 100, 255 * anim.light / 100,
					255 * anim.light / 100), 50); // White
			break;
		case 5:
			theaterChase(MatrixStrip.Color(255 * anim.light / 100, 0, 0), 50); // Red
			break;
		case 6:
			theaterChase(MatrixStrip.Color(0, 0, 255 * anim.light / 100), 50); // Blue
			break;
		case 7:
			rainbow(20, anim.cycle, anim.light);
			break;
		case 8:
			rainbowCycle(20, anim.cycle, anim.light);
			break;
		case 9:
			theaterChaseRainbow(50, anim.light);
			break;
		}
		anim.animate = false;
	}
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
	for (uint16_t i = 0; i < MatrixStrip.numPixels(); i++) {
		MatrixStrip.setPixelColor(spirale2[i], c);
		MatrixStrip.show();
		delay(wait);
	}
}

void rainbow(uint8_t wait, uint8_t cycle, uint8_t light) {
	uint16_t i, j;

	for (j = 0; j < 256 * cycle; j++) {
		for (i = 0; i < MatrixStrip.numPixels(); i++) {
			MatrixStrip.setPixelColor(i, Wheel((i + j) & 255, light));
		}
		MatrixStrip.show();
		delay(wait);
	}
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait, uint8_t cycle, uint8_t light) {
	uint16_t i, j;

	for (j = 0; j < 256 * cycle; j++) { // 5 cycles of all colors on wheel
		for (i = 0; i < MatrixStrip.numPixels(); i++) {
			MatrixStrip.setPixelColor(spirale2[i],
				Wheel(((i * 256 / MatrixStrip.numPixels()) + j) & 255, light));
		}
		MatrixStrip.show();
		delay(wait);
	}
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
	for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
		for (int q = 0; q < 3; q++) {
			for (int i = 0; i < MatrixStrip.numPixels(); i = i + 3) {
				MatrixStrip.setPixelColor(i + q, c);  //turn every third pixel on
			}
			MatrixStrip.show();

			delay(wait);

			for (int i = 0; i < MatrixStrip.numPixels(); i = i + 3) {
				MatrixStrip.setPixelColor(i + q, 0);      //turn every third pixel off
			}
		}
	}
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait, uint8_t light) {
	for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
		for (int q = 0; q < 3; q++) {
			for (int i = 0; i < MatrixStrip.numPixels(); i = i + 3) {
				MatrixStrip.setPixelColor(i + q, Wheel((i + j) % 255, light)); //turn every third pixel on
			}
			MatrixStrip.show();

			delay(wait);

			for (int i = 0; i < MatrixStrip.numPixels(); i = i + 3) {
				MatrixStrip.setPixelColor(i + q, 0);      //turn every third pixel off
			}
		}
	}
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint8_t calcWheel(uint8_t wheelPos, uint8_t light) {
	return wheelPos * 3 * light / 100;
}
uint8_t calc255Wheel(uint8_t wheelPos, uint8_t light) {
	return (255 - wheelPos * 3) * light / 100;
}
uint32_t Wheel(uint8_t wheelPos, uint8_t light) {
	wheelPos = 255 - wheelPos;
	if (wheelPos < 85) {
		return MatrixStrip.Color(calc255Wheel(wheelPos, light), 0,
			calcWheel(wheelPos, light));
	}
	if (wheelPos < 170) {
		wheelPos -= 85;
		return MatrixStrip.Color(0, calcWheel(wheelPos, light),
			calc255Wheel(wheelPos, light));
	}
	wheelPos -= 170;
	return MatrixStrip.Color(calcWheel(wheelPos, light), calc255Wheel(wheelPos, light),
		0);
}

void showIP(IPAddress ip) {
	for (int i = 0; i < 3; i++) {
		String number = (String)(ip[i]);
		MatrixStrip.printNumber(i, number);
	}
	String number = (String)(ip[3]);
	MatrixStrip.printNumber(3, number);
}
#endif
