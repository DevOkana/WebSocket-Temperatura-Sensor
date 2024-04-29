#include "declaracion.h"
#include "pantalla.h"

#define true 1
#define false 0

int comenzar; // Declaración global de comenzar para almacenar el retorno de conectarse a la wifi
String dia_semana[] = {"Lunes", "martes", "Miercoles", "Jueves", "Viernes", "Sabado","Domingo"};
long gmtOffset_sec = +2;// Poner que lo extraiga de la flash del esp32 para recordar el gmt donde esta
int daylightOffset = 0;
bool nptServer;

//String formatoFecha = "%d/%m/%y-%H:%M";
String formatoFecha = "%H:%M";
String hora = "%H";
String minuto = "%M";
String segundo = "%S";
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
  nptServer = false;
  nptServer = startServerNtp(gmtOffset_sec,daylightOffset);  
}


void loop() {
  //pantalla(MostrarHora(formatoFecha, 1000),comenzar, nptServer,getDatosDHT22TemperaturaP(0), getDatosDHT22HumedadP(0));
  //Serial.println(MostrarHora(formatoFecha, 5000));
  //Serial.println(getDatosDHT22(2000,0,0));
  String h = MostrarHoraPantalla(hora);
  String m = MostrarHoraPantalla(minuto);
  String s = MostrarHoraPantalla(segundo);
  verificarConexionNTP(gmtOffset_sec,daylightOffset,&nptServer);
  pantallaReloj(h,m,s,&nptServer,comenzar,getDatosDHT22TemperaturaP(0), getDatosDHT22HumedadP(0));
  delay(1000);
}
