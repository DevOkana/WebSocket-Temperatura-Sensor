#ifndef ALM_INTERNO_H
#define ALM_INTERNO_H

#include <Preferences.h>
#include <Arduino.h>


void operacion(Preferences x, String key, bool read);
void borrarClave(Preferences x, String clave);


#endif
