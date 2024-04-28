#include "declaracion.h"
#include "pantalla.h"

#define true 1
#define false 0

int comenzar; // Declaración global de comenzar para almacenar el retorno de conectarse a la wifi

long gmtOffset_sec = 1;// Poner que lo extraiga de la flash del esp32 para recordar el gmt donde esta
int daylightOffset = 0;
bool nptServer = false;

String formatoFecha = "%d/%m/%y-%H:%M";

void setup() {
  Serial.begin(115200);
  comenzar = ConectarWifi(ssid, password); // asignar el valor de retorno de la función a comenzar
  initPantalla();
  //En caso de que sea 0 pues crea un punto de acceso
  if(comenzar == false){
    createHotspot();
  }
  //Inicializa el server-web-socket poniéndole a la escucha
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws); //Pasamos los datos contenido en ws
  server.begin(); 
  nptServer = startServerNtp(gmtOffset_sec,daylightOffset);  
}

void loop() {
  pantalla(MostrarHora(formatoFecha, 1000),comenzar, nptServer,getDatosDHT22TemperaturaP(0), getDatosDHT22HumedadP(0));
  //Serial.println(MostrarHora(formatoFecha, 5000));
  //Serial.println(getDatosDHT22(2000,0,0));
  delay(60000);
}
