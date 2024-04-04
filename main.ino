#include <DHT22.h>
//define pin data
#include "declaracion.h"


 
void setup() {
  Serial.begin(115200);   
}

void loop() {
  getDatosDHT22(periodoEspera);
  
}