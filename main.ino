#include "declaracion.h"

#define true 1
#define false 0

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
char *ssid = "(((Mariola)))";
char *password = "Resiliencia1*";
int comenzar; // Declaración global de comenzar

int ConectarWifi(char *ssid, char *password) {
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conexión WiFi establecida");

  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);
  server.begin(); 
  
  return true;
}

void setup() {
  Serial.begin(115200);
  comenzar = ConectarWifi(ssid, password); // asignar el valor de retorno de la función a comenzar
}

void loop() {
}
