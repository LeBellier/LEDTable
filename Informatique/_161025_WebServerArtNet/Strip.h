
// Prototypage
void initStrip(); //Call in the setup
void initStripTest(); // Show all Red, Green then Blue
// Set color for the whole strip
void setColor(uint32_t color);

// Déclaration
void initStrip() {
  Serial.println(fileName);
  strip.begin();
  strip.show();
}

void initStripTest() {
  for (int i = 0 ; i < pixelCount ; i++)
    strip.setPixelColor(i, 127, 0, 0);
  strip.show();
  delay(500);
  for (int i = 0 ; i < pixelCount ; i++)
    strip.setPixelColor(i, 0, 127, 0);
  strip.show();
  delay(500);
  for (int i = 0 ; i < pixelCount ; i++)
    strip.setPixelColor(i, 0, 0, 127);
  strip.show();
  delay(500);
  for (int i = 0 ; i < pixelCount ; i++)
    strip.setPixelColor(i, 0, 0, 0);
  strip.show();
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
