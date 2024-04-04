#include "declaracion.h"

DHT22 dht22(pinDHT22);

unsigned long periodoEspera = 2000; // Definición e inicialización de periodoEspera

String getDatosDHT22(long periodo, float ajustarTemperatura, float ajustarHumedad) {
  float t = dht22.getTemperature() - ajustarTemperatura;
  float h = dht22.getHumidity() - ajustarHumedad;

  String datos = "h=" + String(h, 1) + "\t" + "t=" + String(t, 1);
  delay(periodo); // El período de recolección debería ser > 1.7 segundos

  return datos;
}
