#include "alm_interno.h"

void operacion(Preferences x, String key, bool read) {
  // Convertir key a const char* para begin() y remove()
  const char* key_cstr = key.c_str();

  x.begin(key_cstr, read);

  if (read) {
    // Almacenar un valor
    x.putString(key_cstr, key_cstr); // Se guarda la clave como valor
    Serial.println("Valor almacenado: " + key);
  } else {
    // Leer un valor
    String retrievedValue = x.getString(key_cstr);
    Serial.println("Valor: " + retrievedValue);
  }

  x.end(); // Cierra el objeto Preferences
}

void borrarClave(Preferences x, String clave) {
  // Convertir clave a const char* para remove()
  const char* clave_cstr = clave.c_str();

  x.remove(clave_cstr);
  Serial.println("Clave '" + clave + "' eliminada");
}



