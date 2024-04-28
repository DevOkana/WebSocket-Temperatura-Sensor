#include  "pantalla.h"


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void drawBitmap(int16_t x, int16_t y, const unsigned char bitmap[], int16_t width, int16_t height, uint16_t color) {
    display.drawBitmap(x, y, bitmap, width, height, color);
}

void pantalla(String date,int comenzar, bool serverNTP, String temperatura, String humedad) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(100, 0);
  display.cp437(true);
  
  // Display WiFi icon
  display.setCursor(0, 0);
  if(comenzar == 1){
    drawBitmap(115, 0, wifi, 8, 8, WHITE);  
  }   
  
  //drawBitmap(100, 0, serverntp, 10, 10, WHITE);
  display.print(date);
  if(serverNTP){
    display.print(" ");
    display.write(0x12);
  }

  display.drawLine(1, 10, SCREEN_WIDTH - 1, 10, WHITE);
  display.setCursor(0, SCREEN_HEIGHT / 4);
  display.setTextSize(3);
  
  display.print("H:");
  display.print(humedad);
  display.print("%");
  //display.write(0x18);
  display.println("");
  display.print("T:");
  display.print(temperatura);
  //display.write(0xF8);
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