#include "declaracion.h"



// Variable para almacenar el nombre de la WiFi
String wifiName;

void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
  static WifiConfigState configState = WAITING_COMMAND;
  
  if (type == WS_EVT_CONNECT)
  {
    Serial.println("Cliente conectado");
  }
  else if (type == WS_EVT_DISCONNECT)
  {
    Serial.println("Cliente desconectado");
    configState = WAITING_COMMAND;
  }
  else if (type == WS_EVT_DATA)
  {
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->opcode == WS_TEXT)
    {
      String msg = "";
      for (size_t i = 0; i < info->len; i++)
      {
        msg += (char)data[i];
      }

      DynamicJsonDocument msg_json(256); // Tamaño del documento en bytes
      DeserializationError error = deserializeJson(msg_json, msg);
      Serial.print("Mensaje recibido: ");
      Serial.println(msg);
      
      
      // Verificar si hubo un error al parsear el JSON
      if (error) {
        Serial.print("Error al parsear JSON: ");
        Serial.println(error.c_str());
        client->text(error.c_str());
        return;
      }    
      

      const char* comm = msg_json["command"];
      //Comando para configurar la wifi que se guardará en la memoria del esp32
      if (strcmp(comm,"config_wifi") == 0)
      {
        String ssid = msg_json["data"]["ssid"];
        String password = msg_json["data"]["password"];
        client->text("Datos de contraseña recibidos");
        // Imprimir las variables obtenidas -- Borra luego solo sirve para debug
        Serial.print("Comando: ");
        Serial.println(comm);
        Serial.print("SSID: ");
        Serial.println(ssid);
        Serial.print("Contraseña: ");
        Serial.println(password);
      }
      //Enviar en los datos del sensor al cliente que lo solicita
      else if (strcmp(comm,"tmp") == 0)
      {
        Serial.println("Enviando Temperatura");
        String enviar = getDatosDHT22(2000, 0, 0); 
        client->text(enviar);
        Serial.println(enviar);

      //Este comando es para encontrar el server web en una red
      //Petición que se implementara con un scrip para buscar entre todo los equipos de la red y el que responda ok es el correcto
      //Implementar un sistema de claves unicas para casa sensor en caso de crear mucho
      }else if (strcmp(comm,"test") == 0)
      {
          client->text("okay");
      /* 
      * Comando para ajustar el sensor en caso de que querramos quitarle temperatura o humedad
      * sincronizarlo con un sensor que ya tenemos en casa
      * los datos que recibe son en estructura json
      * Ejemplo {
                "command": "config_tmp",
                "data": {
                  "temperatura": "5",
                  "humedad": "-5"
                    }
                }
      */
      }else if(strcmp(comm,"config_tmp") == 0){
          double ajusteTemperatura = msg_json["data"]["temperatura"].as<double>();
          double ajusteHumedad = msg_json["data"]["humedad"].as<double>();

          Serial.print("Ajusta Datos de Temperatura");
          Serial.print("Comando: ");
          Serial.println(comm);
          Serial.print("AjusteT: ");
          Serial.println(ajusteTemperatura);
          Serial.print("AjusteH: ");
          Serial.println(ajusteHumedad);
          client->text("Temperatura ajustada");
      }else{
        client->text("Comando no Encontrado");
      }
    }
  }
}


