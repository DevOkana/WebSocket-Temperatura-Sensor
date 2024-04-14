#ifndef CONFOR_TMP_HUM_H
#define CONFOR_TMP_HUM_H


/*
* Tener en cuento que esto va dentro del config
* Es para definir los maximos y los minimos de temperatura y de humedad para establecer un confort
* Mostrar por pantalla
*/
#define MAXTEMP 21
#define MINTEMP 17
#define MAXHUME 60
#define MINHUME 40

enum Confor{
    DRY,
    CONFORT,
    WEET
};



String EvaluateConfor(double tmp, double hum);



#endif