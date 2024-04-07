# WebSocket-Temperatura-Sensor
Este es un proyecto creado con un esp32 con un sensor DHT22 para enviar los datos de la temperatura y la húmeda a un cliente mediante WebSocket.

## Crear un archivo config.h donde tendremos el ssid y el password por defecto, ejemplo de ello en config_template.h


```C
#ifndef CONFIG_H
#define CONFIG_H

char *ssid = "NombreDelaWIfi";
char *password = "Contraseña";

#endif
```


### Definir el pin por el cual el esp32 va a recibir los datos de entrada del sensor de temperatura

```C
#define pinDHT22 27
```

### Definir el puerto a utilizar en este caso el puerto 80

```C
AsyncWebServer server(80); //Puerto 80
```
