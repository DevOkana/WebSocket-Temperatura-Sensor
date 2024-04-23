#include  "pantalla.h"


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void drawBitmap(int16_t x, int16_t y, const unsigned char bitmap[], int16_t width, int16_t height, uint16_t color) {
    display.drawBitmap(x, y, bitmap, width, height, color);
}

void pantalla(String date) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(120, 0);
  
  // Display WiFi icon
  display.setCursor(0, 0);
  drawBitmap(110, 0, epd_bitmap_icons8_wifi_20, 10, 10, WHITE);
  display.print(date);
/*
  // Formatear la hora y el minuto con dos dígitos
  String hourStr = (hour < 10 ? "0" : "") + String(hour);
  String minuteStr = (minute < 10 ? "0" : "") + String(minute);
  String secondsStr = (seconds < 10 ? "0" : "") + String(seconds);

  // Imprimir hora y minuto
  display.print(hourStr);
  display.print(":");
  display.print(minuteStr);
  display.print(":");
  display.print(secondsStr);*/

  display.drawLine(1, 10, SCREEN_WIDTH - 1, 10, WHITE);
  display.setCursor(0, SCREEN_HEIGHT / 4);
  display.setTextSize(3);
  display.cp437(true);
  display.print("H:");
  display.print("80 %");
  display.write(0x18);
  display.println("");
  display.print("T:");
  display.print("40");
  display.write(0xF8);
  display.write("C");
  display.write(0x19);

  display.display(); 
}

void initPantalla(){
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
}