# WebSocket-Temperatura-Sensor

Este es un proyecto creado con un esp32 con un sensor DHT22 para enviar los datos de la temperatura y la humedad a un cliente mediante WebSocket.

## Configuración

1. Crear un archivo `config.h` donde tendrás el SSID y la contraseña por defecto. Aquí tienes un ejemplo de cómo debería verse:

```C
#ifndef CONFIG_H
#define CONFIG_H

char *ssid = "NombreDelaWifi";
char *password = "Contraseña";

#endif
```

2. Define el pin por el cual el ESP32 va a recibir los datos de entrada del sensor de temperatura:

```C
#define pinDHT22 27
```

3. Define el puerto a utilizar, en este caso, el puerto 80:

```C
AsyncWebServer server(80); //Puerto 80
```

