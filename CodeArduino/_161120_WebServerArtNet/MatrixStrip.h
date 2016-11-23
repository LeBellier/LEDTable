/*
   MatrixStrip.h

    Created on: 21 nov. 2016
        Author: bruno
*/

#ifndef MATRIXSTRIP_H_
#define MATRIXSTRIP_H_

#include <Adafruit_NeoPixel.h>

class MatrixStrip: public Adafruit_NeoPixel {
  public:
    MatrixStrip(uint8_t pinStrip, uint8_t nbRows, uint8_t nbColumns);
    virtual ~MatrixStrip() {};
    void setMatrixPixelColor(uint16_t n, uint32_t color);
    void setMatrixPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
    void setColor(uint32_t color);
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void rgbBlink();
    void colorBlink(uint32_t color);
    void fillChar(char letter, uint32_t color);
    void fillNumber(byte positionScreen, char letter, uint32_t color);
    // numpixels(); pour get le nombre de pixels
  private:
    uint8_t nbRows, nbColumns;

};
MatrixStrip strip(D3, 12, 13);

/*
   Strip.cpp

    Created on: 21 nov. 2016
        Author: bruno
*/


MatrixStrip::MatrixStrip(uint8_t pinStrip, uint8_t nbRows, uint8_t nbColumns) :
  Adafruit_NeoPixel(nbRows * nbColumns, pinStrip, NEO_GRB + NEO_KHZ800), nbRows(
    nbRows), nbColumns(nbColumns) {
  begin();
  show();
}

void MatrixStrip::setMatrixPixelColor(uint16_t n, uint32_t c) {
  uint8_t r = (uint8_t) (c >> 16), g = (uint8_t) (c >> 8), b = (uint8_t) c;
  setMatrixPixelColor(n, r, g, b);
}
void MatrixStrip::setMatrixPixelColor(uint16_t n, uint8_t r, uint8_t g,
                                      uint8_t b) {
  uint16_t idLed = 0;
  if (((n / nbColumns) % 2) == 0) {
    idLed = n;
  } else {
    idLed = (n / nbColumns + 1) * nbColumns - (n % nbColumns + 1);
  }
  setPixelColor(idLed, r, g, b);
}
void MatrixStrip::setColor(uint32_t c) {
  uint8_t r = (uint8_t) (c >> 16), g = (uint8_t) (c >> 8), b = (uint8_t) c;
  setColor(r, g, b);
}
void MatrixStrip::setColor(uint8_t r, uint8_t g, uint8_t b) {
  uint16_t i;
  for (i = 0; i < numPixels(); i++) {
    setPixelColor(i, r, g, b);
  }
  show();
}
void MatrixStrip::rgbBlink() {
  setColor(RED);
  delay(500);
  setColor(GREEN);
  delay(500);
  setColor(BLUE);
  delay(500);
  setColor(BLACK);
}
void MatrixStrip::colorBlink(uint32_t color) {
  setColor(color);
  delay(500);
  setColor(BLACK);
  delay(500);
  setColor(color);
  delay(500);
  setColor(BLACK);
}
void MatrixStrip::fillChar(char letter, uint32_t color) {
  int letter_offset = 0; //The position of the letter in the letters[] array.
  if (isalpha(letter))letter = toupper(letter); //Convert to uppercase

  letter_offset = letter - 'A' + 1; //Find the offset in the letters[] array
  letter_offset *= 8;
  if (letter == ' ')
    letter_offset = 0; //If we get a space or invalid character, display a space
  if (!isalpha(letter))
    letter_offset = 0;
  //Fill the screen with data from the letters[] array
  for (int column = 0; column < 8; column++) {
    for (int row = 0; row < 8; row++) {
      //Strange looking algorithm converts rows to columns and vice versa.
      if (letters[letter_offset + column] & (1 << row))
        setMatrixPixelColor(row * 13 + column, color);
      else
        setMatrixPixelColor(row * 13 + column, 0);
    }
  }
  show();
}
void MatrixStrip::fillNumber(byte positionScreen, char letter, uint32_t color) {
  byte charWidth = 4;
  byte charHigth = 6;
  positionScreen %= 6;
  int position_offsetRow = 0;
  int position_offsetColumn = positionScreen * 4 + 1;
  if (positionScreen > 2) {
    position_offsetRow = 6;
    position_offsetColumn = (positionScreen - 3) * 4 + 1;
  }
  int letter_offset = 0; //The position of the letter in the letters[] array.
  if (letter >= '0' && letter <= '9') {
    letter_offset = letter - '0' + 1; //Find the offset in the letters[] array
    letter_offset *= charWidth - 1;
  }
  //Fill the screen with data from the letters[] array
  for (int column = 0; column < charWidth - 1; column++) {
    for (int row = 0; row < charHigth; row++) {
      //Strange looking algorithm converts rows to columns and vice versa.
      int index = (row + position_offsetRow) * nbColumns + column +  position_offsetColumn;
      if (numbers[letter_offset + column] & (1 << (charHigth - 1 - row)))
        setMatrixPixelColor(index, color);
      else
        setMatrixPixelColor(index, 0);
    }
  }
  show();
}

#endif /* MATRIXSTRIP_H_ */
