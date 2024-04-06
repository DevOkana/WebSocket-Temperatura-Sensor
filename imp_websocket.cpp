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
      
      if (strcmp(comm,"config_wifi") == 0)
      {
        const char* ssid = msg_json["data"]["ssid"];
        const char* password = msg_json["data"]["password"];
        client->text("Datos de contraseña recibidos");
        // Imprimir las variables obtenidas
        Serial.print("Comando: ");
        Serial.println(comm);
        Serial.print("SSID: ");
        Serial.println(ssid);
        Serial.print("Contraseña: ");
        Serial.println(password);
      }
      else if (strcmp(comm,"tmp") == 0)
      {
        Serial.println("Enviando Temperatura");
        String enviar = getDatosDHT22(2000, 0, 0); 
        client->text(enviar);
        Serial.println(enviar);
      }else if (strcmp(comm,"test") == 0)
      {
          client->text("okay");
      }else{
        client->text("Comando no Encontrado");
      }
    }
  }
}


