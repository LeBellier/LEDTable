
// Prototypage
void initArtNet(); // call in the setUp
void updateArtNet(); // call in the loop
int convert1DTo1D( int xCurrent);// convert MatrixCoor in StripCoor
void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data);

ArtnetWifi artnet;

// Déclaration
void initArtNet() {
  // this will be called for each packet received
  artnet.setArtDmxCallback(onDmxFrame);
  artnet.begin();
}
void updateArtNet() {
  // we call the read function inside the loop
  artnet.read();
}
int convert1DTo1D( int xCurrent) {
  if (((xCurrent / 13) % 2) == 0) {
    return xCurrent;
  } else {
    return (xCurrent / 13 + 1) * 13 - (xCurrent % 13 + 1);
  }
}
void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data) {

#ifdef DEBUG
  Serial.print("DMX: Univ: ");
  Serial.print(universe, DEC);
  Serial.print(", Seq: ");
  Serial.print(sequence, DEC);
  Serial.print(", Data (");
  Serial.print(length, DEC);
  Serial.print("): ");

  // send out the buffer
  for (int i = 0; i < length; i++)  {
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
#endif

  // read universe and put into the right part of the display buffer
  for (int i = 0; i < length / 3; i++) {
    int led = i ;
    if (led < pixelCount) {
      strip.setPixelColor(convert1DTo1D(led), data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
    }
  }
  strip.show();
}


