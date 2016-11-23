
// Prototypage
void initWIFILite(); //Connection if it's possible


// Déclaration
void initWIFILite() {
  char *ssid;
  char *password;
  byte nbSSID=4;

  char * SSIDs[nbSSID] = {"Box-anous",  "LAppart", "freebox_fanny", "Zipo"};
  char * passewords[nbSSID] = {"EEA6E591357C24A8EF92697C2A", "LaCiteDeLaPeur", "locura2016", "0645905188"};

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
        WiFi.begin ( ssid, password );
        Serial.println ( "" );
        // Wait for connection
        while ( WiFi.status() != WL_CONNECTED ) {
          delay ( 500 );
          Serial.print ( "." );
        }
        IPAddress ip = WiFi.localIP();
        Serial.println ( "" );
        Serial.print ( "Connected to " );
        Serial.println ( ssid );
        Serial.print ( "IP address: " );
        Serial.println(ip);
        break;
      }
    }
  }
}
// Prototypage
void initWIFILite(); //Connection if it's possible

#define nbSSID 4

// Déclaration
void initWIFILite() {
  char *ssid;
  char *password;

  char * SSIDs[nbSSID] = {"Box-anous",  "LAppart", "freebox_fanny", "Zipo"};
  char * passewords[nbSSID] = {"EEA6E591357C24A8EF92697C2A", "LaCiteDeLaPeur", "locura2016", "0645905188"};

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
        WiFi.begin ( ssid, password );
        Serial.println ( "" );
        // Wait for connection
        while ( WiFi.status() != WL_CONNECTED ) {
          delay ( 500 );
          Serial.print ( "." );
        }
        IPAddress ip = WiFi.localIP();
        Serial.println ( "" );
        Serial.print ( "Connected to " );
        Serial.println ( ssid );
        Serial.print ( "IP address: " );
        Serial.println(ip);
        break;
      }
    }
  }
}
