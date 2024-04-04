#include "declaracion.h"

DHT22 dht22(pinDHT22);

unsigned long periodoEspera = 2000; // Definición e inicialización de periodoEspera

void getDatosDHT22(long periodo){
	float t = dht22.getTemperature();
  	float h = dht22.getHumidity();

  	Serial.print("h=");Serial.print(h,1);Serial.print("\t");
  	Serial.print("t=");Serial.println(t,1);
  	delay(periodo); //Collecting period should be : >1.7 second
}