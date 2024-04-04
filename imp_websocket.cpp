#include "declaracion.h"

void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.println("Cliente conectado");
  } else if (type == WS_EVT_DISCONNECT) {
    Serial.println("Cliente desconectado");
  } else if (type == WS_EVT_DATA) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->opcode == WS_TEXT) {
      String msg = "";
      for (size_t i = 0; i < info->len; i++) {
        msg += (char)data[i];
      }
      Serial.print("Mensaje recibido: ");
      Serial.println(msg);
      
      // Verificar el comando recibido
      if (msg == "tmp") {
        // Obtener los datos del sensor DHT22
        String datosDHT22 = getDatosDHT22(periodoEspera, 0, 0);
        client->text(datosDHT22);
      } else {
        // Comando no reconocido, enviar un mensaje de error al cliente
        client->text("Comando no reconocido");
      }
    }
  }
}
