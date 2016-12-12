#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H
// Prototypage
#include <ESP8266mDNS.h>
void initWIFILite(); //Connection if it's possible
String ipToString(IPAddress ip);
void printNumber(int i, String number);

#define nbSSID 4

// Déclaration
void initWIFILite() {
  char *ssid;
  char *password;

  char * SSIDs[nbSSID] = { "Box-anous", "LAppart", "SFR_8820", "Zipo" };
  char * passewords[nbSSID] = { "5A631D27C1F411A4CCD6D1C6FC", "LaCiteDeLaPeur", "poweroffrenchdiamonds2017", "0645905188"};

  boolean wifiFounded = false;
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  if (n != 0) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < nbSSID; ++j) {
        if (WiFi.SSID(i) == SSIDs[j]) {
          ssid = SSIDs[j];
          password = passewords[j];
          wifiFounded = true;
          break;
        }
      }
      if (wifiFounded) {
        WiFi.begin(ssid, password);
        Serial.println("");
        // Wait for connection
        while (WiFi.status() != WL_CONNECTED) {
          delay(500);
          //Serial.print(".");
        }
        IPAddress ip = WiFi.localIP();
        Serial.println("");
        Serial.print("Connected to ");
        Serial.println(ssid);
        Serial.print("IP address: ");
        Serial.println(ipToString(ip));
        strip.colorBlink(GREEN);
        break;
      } else {
        strip.colorBlink(RED);
      }
    }
  }
}

String ipToString(IPAddress ip) {
  String n = "";
  for (int i = 0; i < 3; i++) {
    String number = (String) (ip[i]);
    printNumber(i, number);
    n += (ip[i]);
    n += '.';
  }
  String number = (String) (ip[3]);
  printNumber(3, number);

  n += ip[3];
  return n;
}
void printNumber(int i, String number) {
  int len = number.length();
  for (int j = 0; j < 3 - len; j++) {
    strip.fillNumber(j + (i % 2) * 3, ' ', MAGENTA);
  }
  for (int j = 3 - len; j < 3; j++) {
    strip.fillNumber(j + (i % 2) * 3, number.charAt(j - 3 + len), MAGENTA);
  }
  delay(1000);
}
#endif
