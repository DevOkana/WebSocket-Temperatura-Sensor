#ifndef DECLARACION_H
#define DECLARACION_H
#define pinDHT22 27

#include <DHT22.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncWebSocket.h>


extern unsigned long periodoEspera;
extern DHT22 dht22;

void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
void getDatosDHT22(long periodo, float ajustarTemperatura, float ajustarHumedad);
#endif // Cierre del ifndef
