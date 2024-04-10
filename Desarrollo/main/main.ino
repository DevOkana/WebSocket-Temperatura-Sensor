#include <Preferences.h>
#include <Arduino.h>

Preferences p;
Preferences q;

void guardar() {
  p.begin("ssid", false);
  q.begin("password", false);

  String ssid = "WIFICASA";
  String password = "WIFICASA";

  p.putString("ssid", ssid);
  q.putString("password", password);
  Serial.println("Almacenado");
  cerra();
}

void leer() {
  p.begin("ssid", true);
  q.begin("password", true);

  String ssid = p.getString("ssid"); // Corrected: Use getString for String data
  String password = q.getString("password"); // Corrected: Use getString for String data

  Serial.println("ssid: " + ssid);
  Serial.println("Password: " + password);

  cerra();
}

void cerra() {
  p.end();
  q.end();
}

void setup() {
  Serial.begin(115200);
  //guardar();
  
}

void loop() {
  leer();
}
