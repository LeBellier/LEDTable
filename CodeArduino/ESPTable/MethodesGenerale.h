#ifndef METHODESGENERALE_H
#define METHODESGENERALE_H

#include <ESP8266WiFi.h>
// Prototypage
void showIP(IPAddress ip);


// Déclaration
void showIP(IPAddress ip) {
  for (int i = 0; i < 3; i++) {
    String number = (String) (ip[i]);
    strip.printNumber(i, number);
  }
  String number = (String) (ip[3]);
  strip.printNumber(3, number);
}
#endif
