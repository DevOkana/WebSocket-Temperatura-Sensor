#include "alm_interno.h"


Preferences p;


void setup() {
  Serial.begin(115200);  
  
}

void loop() {

    operacion(p,"WIFICASA",false);
    


}
