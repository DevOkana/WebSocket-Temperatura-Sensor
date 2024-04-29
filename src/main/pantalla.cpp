#include  "pantalla.h"


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void drawBitmap(int16_t x, int16_t y, const unsigned char bitmap[], int16_t width, int16_t height, uint16_t color) {
    display.drawBitmap(x, y, bitmap, width, height, color);
}

char *dias_semana[] = {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"};

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
    drawBitmap(100, 0, reloj, 8, 8, WHITE);  
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
  /*display.fillRoundRect(0, 0, 128, 12, 3, SSD1306_WHITE);
  display.setCursor(8, 2);
  display.setTextSize(1);
  display.setTextColor(SSD1306_BLACK);
  
  display.print("  ");
  display.print(timeInfo->tm_mday);
  display.print("/");
  display.print(timeInfo->tm_mon + 1);
  display.print("/");
  display.println(timeInfo->tm_year + 1900);*/
void pantallaReloj(String hora, String minuto, String segundo, bool* par, int comenzar, String temperatura, String humedad) {
  display.clearDisplay();
  display.setCursor(0,0);
  display.print(MostrarHoraPantalla("%Z %z"));
  display.setCursor(60,0);
  display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
  display.setTextSize(1);
  display.print(dias_semana[MostrarHoraPantalla("%u").toInt()-1]);
  
  display.setTextSize(3);
  if(par){
    display.print(" ");
    drawBitmap(100, 0, reloj, 8, 8, WHITE);  
  }
  if(comenzar == 1){
    drawBitmap(115, 0, wifi, 8, 8, WHITE);  
  }  
  display.setCursor(15, 20);

  display.print(hora);
  int contador = segundo.toInt() % 2;
  if (contador == 0) {
    display.print(":");
  } else {
    display.print(" ");
  }
  /*if (minuto.toInt() < 10) {
    display.print("0");
  }*/
  display.print(minuto);

  display.drawCircle(117, 48, 10, SSD1306_WHITE);
  display.setCursor(112, 45);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  /*if (segundo.toInt() < 10) {
    display.print("0");
  }*/
  display.println(segundo);
  int load = map(segundo.toInt(), 0, 59, 15, 106);
  display.drawLine(15, 50, load, 50, SSD1306_WHITE);
  display.setCursor(0, 55);
  display.setTextSize(1);
  display.print("H:");
  display.print(humedad);
  display.print("%");
  //display.write(0x18);
  display.print(" ");
  display.print("T:");
  display.print(temperatura);
  //display.write(0xF8);
  display.write("C");
  display.write(0x19); 
  display.display();
  //delay(1000);
}


void initPantalla(){
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
}