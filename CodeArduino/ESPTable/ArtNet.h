#ifndef ARTNET_H
#define ARTNET_H

#include <ArtnetWifi.h>
#include <Aspect.h>
extern ArtnetWifi artnet;

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data) {

#ifdef DEBUG
  DEBUG_PRINT("DMX: Univ: ");
  DEBUG_PRINT(universe, DEC);
  DEBUG_PRINT(", Seq: ");
  DEBUG_PRINT(sequence, DEC);
  DEBUG_PRINT(", Data (");
  DEBUG_PRINT(length, DEC);
  DEBUG_PRINT("): ");

  // send out the buffer
  for (int i = 0; i < length; i++) {
    DEBUG_PRINT(data[i], HEX);
    DEBUG_PRINT(" ");
  }
  DEBUG_PRINTLN();
#endif

  // read universe and put into the right part of the display buffer
  for (int i = 0; i < length / 3; i++) {
    int led = i;
    if (led < strip.numPixels()) {
      strip.setMatrixPixelColor(led, data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
    }
  }
  strip.show();
}

#endif
