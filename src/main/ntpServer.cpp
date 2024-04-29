#include "declaracion.h"


ESP32Time rtc;

//Llevar el control de la temperatura y humedad según el horario en caso de que se quiera almacenar en un dispositivo.
unsigned long ultimaVerificacion = 0; // Variable para almacenar el tiempo de la última verificación
const unsigned long intervaloVerificacion = 3600000; // Intervalo de verificación en milisegundos (1 hora)
struct tm timeinfo;


bool startServerNtp(long gmtOffset_sec,int daylightOffset){
    gmtOffset_sec = gmtOffset_sec * 3600;    
    configTime(gmtOffset_sec,daylightOffset,ntpServer);
    // Actualizar el cliente NTP cada cierto tiempo
    //clientTime.update();
    
    if(getLocalTime(&timeinfo)){
        rtc.setTimeStruct(timeinfo);
        Serial.println("Se ha establecido conexion");
        return true;
    } 
    Serial.println("No se ha establecido conexion");
    return false;
}
//"%A, %B %d %Y %H:%M:%S"
//https://www.ibm.com/docs/en/workload-automation/10.2.0?topic=troubleshooting-date-time-format-reference-strftime
String MostrarHora(String formato, int update){
    delay(update);
    struct tm timeinfo = rtc.getTimeStruct();
    return rtc.getTime(formato);
}
String MostrarHoraPantalla(String formato){
    struct tm timeinfo = rtc.getTimeStruct();
    return rtc.getTime(formato);
}
// Función para verificar la conexión al servidor NTP
void verificarConexionNTP(long gmtOffset_sec,int daylightOffset, bool* nptServer) {
    unsigned long ahora = millis();
    // Verificar si ha pasado el tiempo suficiente desde la última verificación
    if (ahora - ultimaVerificacion >= intervaloVerificacion) {
        // Realizar la verificación de conexión al servidor NTP
        if (!getLocalTime(&timeinfo)) {
            Serial.println("Volviendo a sincronizar el tiempo con el servidor NTP...");
            *nptServer = startServerNtp(gmtOffset_sec, daylightOffset); // Ajustar los valores según sea necesario
        }
        ultimaVerificacion = ahora; // Actualizar el tiempo de la última verificación
    } 
}


