#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H
// Prototypage

#include <ESP8266mDNS.h>
void initWIFILite(); //Connection if it's possible
String ipToString(IPAddress ip);
void printNumber(int i, String number);


// Déclaration
void initWIFILite() {
  char *ssid;
  char *password;

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
        DEBUG_INIT_PRINTLN("");
        // Wait for connection
        while (WiFi.status() != WL_CONNECTED) {
          delay(500);
        }
        DEBUG_INIT_PRINTLN("");
        DEBUG_INIT_PRINT("Connected to ");
        DEBUG_INIT_PRINTLN(ssid);
        DEBUG_INIT_PRINT("IP address: ");
        DEBUG_INIT_PRINTLN(sIP);
        break;
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
