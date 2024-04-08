# WebSocket-Temperatura-Sensor

Este es una aplicación desarrollada para un dispositivo basado en ESP32 que permite medir la temperatura y la humedad utilizando un sensor DHT22, y proporciona una interfaz web para acceder a los datos y configurar la conexión Wi-Fi del dispositivo. El proyecto está estructurado en diferentes módulos para facilitar la organización y el mantenimiento del código.


## Funcionalidades
1. **Medición de Temperatura y Humedad**
   - Utiliza el sensor DHT22 para medir la temperatura y la humedad del entorno.
   - La función `getDatosDHT22` proporciona la temperatura y la humedad actual, ajustada opcionalmente con valores personalizados.

2. **Conexión Wi-Fi**
   - Permite al dispositivo
   - `int ConectarWifi(char *ssid, char *password)` te permite conectar con una wifi 
   - `void createHostport()` te permite crear un hosport con server dhcp con el nombre por defecto **HosportTemperatura**
   - Tener en cuen que en caso de que el dispositivo se valla a conectar a una red wifi y no la encuentre tendrá una x cantidad de reitentos para crear automaticamente el Hosport

3. **ServerWebSocket**
   - Es el que contendrá los comando admitidos por el dispositivos que serán recibidos en formato json
   - Los comando serás enviado como clave primaria.
        - Algunos comando disponibles 
            - `config_wifi` este comando le enviará al dispositivo una configuración de wifi para cambiar
               - Ejemplo:
               ```json
                {
                "command": "config_wifi",
                "data": {
                  "ssid": "nombreWifi",
                  "password": "12345678"
                    }
                }
               ```
            - `config_tmp` este comando es para ajustar los datos recibidos, para reducir la temperatura o húmedad en caso de que queremos sincronizarlo con algún otro sensor de casa.
                - Ejemplo 
                ```json 
                {
                "command": "config_tmp",
                "data": {
                  "temperatura": "nombreWifi",
                  "humedad": "12345678"
                    }
                }
                ```
                - En caso de que querramos reducirla en -5 grados pues es tan simple como indicarle en la clave de temperatura -5.
            - `test` este comando aún esta en desarrollo, su funcionalidad es para detectar el dispositivo en una red para que el cliente le envie este comando y el le responda pero aún falta algunos detalles -> AÚN POR DESARROLLAR

## Configuración

1. Crear un archivo `config.cpp` donde tendrás el SSID y la contraseña por defecto. Aquí tienes un ejemplo de cómo debería verse:

```C
#include "declaracion.h"

char *ssid = "NombreDelaWifi";
char *password = "Contraseña";

```

2. Define el pin por el cual el ESP32 va a recibir los datos de entrada del sensor de temperatura:

```C
#define pinDHT22 27
```

3. Define el puerto a utilizar, en este caso, el puerto 80:

```C
AsyncWebServer server(80); //Puerto 80
```

