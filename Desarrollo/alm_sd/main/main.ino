#include <SPI.h>
#include <SD.h>
#include <FS.h>
#include <ArduinoJson.h>

#define SD_CS_PIN 5

File file;

void crearConfig() {
  // Abrir un archivo en modo escritura
  file = SD.open("/data.json", FILE_WRITE);
  
  DynamicJsonDocument doc(1024);
  doc["clave"] = "valor";
  if (file) {
    serializeJson(doc, file);
    file.close(); // Cerrar el archivo después de escribir
    Serial.println("Datos escritos en data.json.");
  } else {
      Serial.println("Error al abrir el archivo");
  }
}

void ComprobandoConfig(){
  // Verificar si el archivo existe
  if (!SD.exists("/data.json")) {
    Serial.println("El archivo data.json no existe. Creándolo...");
    crearConfig();
  } else {
    Serial.println("El archivo data.json ya existe.");
  }
}

void setup() {
  Serial.begin(115200);
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("Error al inicializar la tarjeta SD");
    return;
  }  
  Serial.println("Tarjeta SD inicializada correctamente.");
  ComprobandoConfig();
}

void loop() {
  // No es necesario hacer nada en el loop en este ejemplo
}
