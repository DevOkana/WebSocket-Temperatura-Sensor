#include "declaracion.h"

#define true 1
#define false 0

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
char *ssid = "(((Mariola)))";
char *password = "Resiliencia1*";
const char *hostssid = "HosportTemperatura";      // Nombre del punto de acceso
const char *hostpassword = "";


int comenzar; // Declaración global de comenzar

void createHostport() {
    // Inicializar el modo de punto de acceso
    WiFi.mode(WIFI_AP);

    // Configurar el punto de acceso sin contraseña
    WiFi.softAP(hostssid, hostpassword);

    // Configurar el servidor DHCP
    IPAddress IPaddr(192, 168, 1, 1);
    IPAddress netMask(255, 255, 255, 0);
    WiFi.softAPConfig(IPaddr, IPaddr, netMask);

    
    
    // Obtener la dirección IP del punto de acceso
    IPAddress ip = WiFi.softAPIP();
    Serial.print("Dirección IP del punto de acceso: ");
    Serial.println(ip);
}
int ConectarWifi(char *ssid, char *password) {
WiFi.begin(ssid, password);
int reintentos = 0;
  
  while (WiFi.status() != WL_CONNECTED) {
    if(reintentos > 20){
      createHostport();
      break;
    }
    delay(1000);
    Serial.println("Conectando a WiFi...");
    reintentos = reintentos + 1;
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
