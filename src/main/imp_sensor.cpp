#include "declaracion.h"


//Le pasamos el pin del sensor 
DHT22 dht22(pinDHT22);

// Definición e inicialización de periodoEspera por defecto será de 2 seg
unsigned long periodoEspera = 2000; 

/*
* Función para obtener los datos del sensor
* @param periodo para recibir las actualizaciones
* @param ajustarTemperatura para ajustar la temperatura
* @param ajustarHumedad para ajustar la humedad
* return String con los datos||MODIFICAR LUEGO POR UN JSON
*/

String getDatosDHT22(long periodo, float ajustarTemperatura, float ajustarHumedad) {
  float t = dht22.getTemperature() - ajustarTemperatura;
  float h = dht22.getHumidity() - ajustarHumedad;
  String datos = "h=" + String(h, 1) + "\t" + "t=" + String(t, 1);
  delay(periodo); // El período de recolección debería ser > 1.7 segundos
  return datos;
}

String getDatosDHT22TemperaturaP(float ajustarTemperatura) {
  float t = dht22.getTemperature() - ajustarTemperatura;
  String temperatura = String(t, 1);
  return temperatura;
}
String getDatosDHT22HumedadP(float ajustarHumedad) {
  float h = dht22.getHumidity() - ajustarHumedad;
  String humedad = String(h, 1);
  return humedad;
}

