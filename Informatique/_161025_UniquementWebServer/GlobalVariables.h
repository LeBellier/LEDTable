#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#define BAUDRATE 74880

// Pins
#define pixelPin D3
#define led D4

// Strip
#define pixelCount 156
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelCount, pixelPin, NEO_GRB + NEO_KHZ800);


#endif







