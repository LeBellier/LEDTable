
// Prototypage
void initStrip(); //Call in the setup
void initStripTest(); // Show all Red, Green then Blue

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
