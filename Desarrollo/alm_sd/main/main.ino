#include <SPI.h>
#include <SD.h>
#include <FS.h>
#include <ArduinoJson.h>

#define SD_CS_PIN 5

File file;
const char* nomFileConfig = "/config.json";
const char* rutaConfig = "/config";

void crearConfig(String ruta) {
  // Abrir un archivo en modo escritura
  file = SD.open(ruta, FILE_WRITE);
  
  if (file) {
    // Crear el objeto JSON con la estructura requerida
    DynamicJsonDocument doc(1024);
    JsonObject config = doc.createNestedObject("config");
    
    JsonObject wifi = config.createNestedObject("wifi");
    JsonObject client = wifi.createNestedObject("client");

    client["reintentos"] = 10;
    client["nombre"] = "";
    client["password"] = "";

    JsonObject hotspot = wifi.createNestedObject("hotspot");
    hotspot["nombre"] = "HosportTemperatura";
    hotspot["password"] = "";
    
    JsonObject webSocket = config.createNestedObject("webSocket");
    webSocket["puerto"] = 80;
    webSocket["rutaEscucha"] = "/ws";
    
    JsonObject medidas = config.createNestedObject("medidas");
    medidas["delay"] = 1000;

    JsonObject temperatura = medidas.createNestedObject("temperatura");
    temperatura["ajuste"] = 0;
    temperatura["unidad"] = "celsius(C) or fahrenheit(F)";

    JsonObject humedad = medidas.createNestedObject("humedad");
    humedad["ajuste"] = 0;
    humedad["unidad"] = "relativeHumidity(HR) or absoluteHumidity(HA)";
    
    JsonObject ntp = config.createNestedObject("NTP");
    ntp["delay"] = 1000;
    ntp["server"] = "time.google.com";
    ntp["formato"] = "%d/%m/%y-%H:%M:%S";
    
    // Serializar el objeto JSON y escribirlo en el archivo
    serializeJson(doc, file);
    file.close(); // Cerrar el archivo después de escribir
    Serial.println("Datos escritos en config.json.");
  } else {
    Serial.println("Error al abrir el archivo");
  }
}

DynamicJsonDocument leerConfig(String ruta) {
  // Abrir el archivo en modo lectura
  file = SD.open(ruta);
  
  if (file) {
    // Leer todo el contenido del archivo en una cadena
    String jsonStr = "";
    while (file.available()) {
      jsonStr += (char)file.read();
    }
    file.close(); // Cerrar el archivo después de leer
    
    // Deserializar la cadena JSON en un objeto JSON
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, jsonStr);
    
    if (error) {
      Serial.print("Error al deserializar JSON: ");
      Serial.println(error.c_str());
    } else {
      // Mostrar los datos del objeto JSON
      Serial.println("Contenido del archivo JSON:");
      //serializeJsonPretty(doc, Serial);
      return doc; // Devolver el objeto JSON leído
    }
  } else {
    Serial.println("Error al abrir el archivo para lectura.");
  }

  // Si ocurre un error, devolver un objeto JSON vacío
  DynamicJsonDocument emptyDoc(1);
  return emptyDoc;
}

void entorno(const char* nomFileConfig, const char* rutaConfig) {
  int longitudTotal = strlen(rutaConfig) + strlen(nomFileConfig) + 1; // +1 para el carácter nulo terminador
  if (SD.exists(rutaConfig)) {
    Serial.println("La carpeta ya existe.");
  } else {
    if (SD.mkdir(rutaConfig)) {
      Serial.println("Carpeta creada correctamente.");
    } else {
      Serial.println("Error al crear la carpeta.");
      return;
    }
  }
  
  // Crear un buffer para contener la ruta completa
  char rutaCompleta[longitudTotal];
  // Copiar la ruta de la carpeta al buffer
  strcpy(rutaCompleta, rutaConfig);
  // Concatenar el nombre del archivo al buffer
  strcat(rutaCompleta, nomFileConfig);

  crearConfig(rutaCompleta);
}

void ComprobandoConfig() {
  // Verificar si el archivo existe
  if (!SD.exists(rutaConfig)) {
    Serial.println("El archivo no existe. Creándolo...");
    entorno(nomFileConfig, rutaConfig);
  } else {
    Serial.println("El archivo config.json ya existe.");
    Serial.println("Leyendo configuración...");
    DynamicJsonDocument config = leerConfig(String(rutaConfig) + nomFileConfig);
    String nombreWifi = config["config"]["wifi"]["hotspot"]["nombre"];
    Serial.print("Nombre de la red WiFi: ");
    Serial.println(nombreWifi);
    // Utilizar el objeto JSON según sea necesario
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
