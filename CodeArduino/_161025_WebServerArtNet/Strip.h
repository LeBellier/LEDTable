
// Prototypage
void initStrip(); //Call in the setup
void initStripTest(); // Show all Red, Green then Blue
void blinkStrip(); // Show all Blue
// Set color for the whole strip
void setColor(uint32_t color);
void fillChar(char letter, uint32_t color);

int convert1DTo1D( int xCurrent);// convert MatrixCoor in StripCoor



// Déclaration
void initStrip() {
  Serial.println(fileName);
  strip.begin();
  strip.show();
}

void initStripTest() {
setColor(RED);
  delay(500);
setColor(GREEN);
  delay(500);
setColor(BLUE);
  delay(500);
setColor(BLACK);
}
void blinkStrip(uint32_t color) {
setColor(color);
  delay(500);
setColor(BLACK);
  delay(500);
setColor(color);
  delay(500);
setColor(BLACK);
}
void setColor(uint32_t color) {
  int i;
  for (i = 0; i < pixelCount; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
  //Serial.println( "Show color: " );
  //Serial.println(color);
}
void fillChar(char letter, uint32_t color){
  int letter_offset = 0; //The position of the letter in the letters[] array.

  //if (color == 0x25 || color == 0x26)return;

  //if (isalpha(letter))letter = toupper(letter); //Convert to uppercase
  letter_offset = letter - 'A' + 1; //Find the offset in the letters[] array
  letter_offset *= 8;
  if (letter == ' ')letter_offset = 0; //If we get a space or invalid character, display a space
  if (!isalpha(letter))letter_offset = 0;
  //Fill the screen with data from the letters[] array
  for (int column = 0; column < 8; column++)  {
    for (int row = 0; row < 8; row++)    {
      //Strange looking algorithm converts rows to columns and vice versa.
      if (letters[letter_offset + (7 - column)] & (1 << row))strip.setPixelColor(convert1DTo1D(row * 13 + column), color);
      else strip.setPixelColor(convert1DTo1D(row * 13 + column), 0);
    }
  }
  strip.show();
}
int convert1DTo1D( int xCurrent) {
  if (((xCurrent / 13) % 2) == 0) {
    return xCurrent;
  } else {
    return (xCurrent / 13 + 1) * 13 - (xCurrent % 13 + 1);
  }
}
