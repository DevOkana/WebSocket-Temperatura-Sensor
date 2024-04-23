#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "pantalla.h"

// WiFi credentials
const char* ssid = "(((Mariola)))";
const char* password = "Resiliencia1*";

// NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.google.com");

void setup() {
  Serial.begin(115200);

  initPantalla();
  
  // Initialize WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to WiFi");

  // Initialize NTP
  timeClient.begin();
  timeClient.setTimeOffset(-18000); // Timezone: Eastern Standard Time (UTC -5 hours)
}

void loop() {
  timeClient.update();
  int hour = timeClient.getHours();
  int minute = timeClient.getMinutes();
  int second = timeClient.getSeconds();
  pantalla(hour, minute,second);
  delay(1000);
}
