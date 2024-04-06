#ifndef DECLARACION_H
#define DECLARACION_H
#define pinDHT22 27

#include <DHT22.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncWebSocket.h>
#include <Arduino.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <ArduinoJson.h>


extern unsigned long periodoEspera;
extern DHT22 dht22;

void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
String getDatosDHT22(long periodo, float ajustarTemperatura, float ajustarHumedad);

enum WifiConfigState
{
  WAITING_COMMAND,
  WAITING_NAME,
  WAITING_PASSWORD,
  WAITING_CONFIG // Asegúrate de que esta línea esté presente
};

#endif // Cierre del ifndef
