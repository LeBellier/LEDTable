#ifndef ANIMATIONS_H
#define ANIMATIONS_H

// Prototypage

// Show the selected animation
void startShow(int i);

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait);
void rainbow(uint8_t wait);
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait);
//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait);
//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait);

uint32_t Wheel(byte WheelPos);

const char spirale[] = {000, 001, 002, 003, 004, 005, 006, 007, 008, 009, 010, 011, 012,
                        013, 038, 039, 064, 065, 090, 091, 116, 117, 142, 143,
                        144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155,
                        130, 129, 104, 103, 078, 077, 052, 051, 026, 025,
                        024, 023, 022, 021, 020, 019, 018, 017, 016, 015, 014,
                        037, 040, 063, 066, 089, 092, 115, 118, 141,
                        140, 139, 138, 137, 136, 135, 134, 133, 132, 131,
                        128, 105, 105, 079, 076, 053, 050, 027,
                        028, 029, 030, 031, 032, 033, 034, 035, 036,
                        041, 062, 067, 088, 093, 114, 119,
                        120, 121, 122, 123, 124, 125, 126, 127,
                        106, 101, 080, 075, 054, 049,
                        048, 047, 046, 045, 044, 043, 042,
                        061, 068, 087, 094, 113,
                        112, 111, 110, 109, 108, 107,
                        100, 081, 074, 055,
                        056, 057, 058, 059, 060,
                        069, 086, 095,
                        096, 097, 098, 099,
                        082, 073,
                        072, 071, 070,
                        085, 084, 083
                       };
const char spirale2[] = {012, 013, 038, 039, 064, 065, 090, 091, 116, 117, 142, 143,
                         144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155,
                         130, 129, 104, 103, 078, 077, 052, 051, 026, 025, 000,
                         001, 002, 003, 004, 005, 006, 007, 008, 009, 010, 011,
                         014, 037, 040, 063, 066, 089, 092, 115, 118, 141,
                         140, 139, 138, 137, 136, 135, 134, 133, 132, 131,
                         128, 105, 105, 079, 076, 053, 050, 027, 024,
                         023, 022, 021, 020, 019, 018, 017, 016, 015,
                         036, 041, 062, 067, 088, 093, 114, 119,
                         120, 121, 122, 123, 124, 125, 126, 127,
                         106, 101, 080, 075, 054, 049, 028,
                         029, 030, 031, 032, 033, 034, 035,
                         042, 061, 068, 087, 094, 113,
                         112, 111, 110, 109, 108, 107,
                         100, 081, 074, 055, 048,
                         047, 046, 045, 044, 043,
                         060, 069, 086, 095,
                         096, 097, 098, 099,
                         082, 073, 056,
                         057, 058, 059,
                         070, 085,
                         084, 083,
                         072,
                         071
                        };


// Déclaration

void startShow(int i) {
  switch (i) {
    case 0: colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
      animate = false;
      break;
    case 1: colorWipe(strip.Color(255, 0, 0), 50);  // Red
      break;
    case 2: colorWipe(strip.Color(0, 255, 0), 50);  // Green
      break;
    case 3: colorWipe(strip.Color(0, 0, 255), 50);  // Blue
      break;
    case 4: theaterChase(strip.Color(127, 127, 127), 50); // White
      break;
    case 5: theaterChase(strip.Color(127,   0,   0), 50); // Red
      break;
    case 6: theaterChase(strip.Color(  0,   0, 127), 50); // Blue
      break;
    case 7: rainbow(20);
      break;
    case 8: rainbowCycle(20);
      break;
    case 9: theaterChaseRainbow(50);
      break;
  }
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(spirale[i], Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
#endif
