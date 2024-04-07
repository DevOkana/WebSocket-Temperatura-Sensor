#include "declaracion.h"
#include "config.h"

#define true 1
#define false 0

//Definición de serverWeb
AsyncWebServer server(80); //Puerto 80
AsyncWebSocket ws("/ws"); //Ruta en la que va escuchar

//--------Declaración del Hosport ------------
const char *hostssid = "HosportTemperatura";
const char *hostpassword = "";
//--------END ------------


int comenzar; // Declaración global de comenzar para almacenar el retorno de conectarse a la wifi


//Funcion para crear un punto de acceso wifi
void createHostport() {
    // Inicializar el modo de punto de acceso
    WiFi.mode(WIFI_AP);

    // Configurar el punto de acceso
    WiFi.softAP(hostssid, hostpassword);

    // Configurar el servidor DHCP
    IPAddress IPaddr(192, 168, 1, 10);
    IPAddress netMask(255, 255, 255, 0);
    WiFi.softAPConfig(IPaddr, IPaddr, netMask);    
    
    // Obtener la dirección IP del punto de acceso
    IPAddress ip = WiFi.softAPIP();
    Serial.print("Dirección IP del punto de acceso: ");
    Serial.println(ip);
}


//Funcion para conectar a una wifi
int ConectarWifi(char *ssid, char *password) {
  WiFi.begin(ssid, password); // Inicializar para conectarse a la wifi
  int reintentos = 0; //Variable que lleva el reintento de veces para conectarse
    //Bucle en caso de que la constante WL_CONNECTED se distinta de 3
    while (WiFi.status() != WL_CONNECTED) {
      if(reintentos > 20){//Reintentos maximos antes de devolver false
        return false;
      }
      delay(1000);//Espera 1 segundo para reintentar
      Serial.println("Conectando a WiFi...");
      reintentos = reintentos + 1;//Aumenta la variable reintento en 1
    }

    Serial.println("Conexión WiFi establecida");   
    
    return true;
}

void setup() {
  Serial.begin(115200);
  comenzar = ConectarWifi(ssid, password); // asignar el valor de retorno de la función a comenzar
  //En caso de que sea 0 pues crea un punto de acceso
  if(comenzar == false){
    createHostport();
  }

  //Inicializa el serverwebsocker poniendolo a la escucha
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws); //Pasamos los datos contenido en ws
  server.begin(); 
}

void loop() {
}
