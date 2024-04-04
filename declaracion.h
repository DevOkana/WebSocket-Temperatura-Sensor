#ifndef declaracion
#define declaracion
#include <DHT22.h>

#define pinDHT22 27 //Declaración del pin de datos del sensor

extern unsigned long periodoEspera; //Declaración del tiempo de actualizacion
extern DHT22 dht22; //Declaracion externa del obejto DHT22

void getDatosDHT22(long periodo);

#endif // Cierre del ifndef