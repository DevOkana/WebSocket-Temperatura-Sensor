#ifndef DECLARACION_H
#define DECLARACION_H

#define pinDHT22 17

#include <DHT22.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncWebSocket.h>
#include <Arduino.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <ESP32Time.h>


/*
* Declaración de tiempo de espera que se usará para que el cliente le diga al sensor
* cada cuanto tiempo quiere recibir la actualización del sensor
*/

extern AsyncWebSocket ws;
extern AsyncWebServer server;
extern const char *hostssid;
extern const char *hostpassword;
extern ESP32Time rtc;

extern char *ssid;
extern char *password;
extern char *ntpServer;

extern ESP32Time rtc;
extern struct tm timeinfo;
extern long gmtOffset_se;
extern int daylightOffset;



void createHotspot();
int ConectarWifi(char *ssid, char *password);
void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
String getDatosDHT22(long periodo, float ajustarTemperatura, float ajustarHumedad);
String MostrarHora(String formato, int update);
bool startServerNtp(long gmtOffset_sec,int daylightOffset);
String getDatosDHT22HumedadP(float ajustarHumedad);
String getDatosDHT22TemperaturaP(float ajustarTemperatura);

enum WifiConfigState
{
  WAITING_COMMAND,
  WAITING_NAME,
  WAITING_PASSWORD,
  WAITING_CONFIG 
};

#endif // Cierre del ifndef
