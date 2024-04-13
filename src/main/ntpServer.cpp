#include "declaracion.h"


ESP32Time rtc(3600);

void startServerNtp(long gmtOffset_sec,int daylightOffset){
    gmtOffset_sec = gmtOffset_sec * 3600;
    
    configTime(gmtOffset_sec,daylightOffset,ntpServer);

    // Actualizar el cliente NTP cada cierto tiempo
    //clientTime.update();
    struct tm timeinfo;
    if(getLocalTime(&timeinfo)){
        rtc.setTimeStruct(timeinfo);
    } 
}
//"%A, %B %d %Y %H:%M:%S"
//https://cplusplus.com/reference/ctime/strftime/
String MostrarHora(String formato, int update){
    delay(update);
    struct tm timeinfo = rtc.getTimeStruct();
    return rtc.getTime(formato);
}



