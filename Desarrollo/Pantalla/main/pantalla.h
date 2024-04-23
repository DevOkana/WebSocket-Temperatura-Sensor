#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// 'icons8-wifi-20', 20x20px
const unsigned char epd_bitmap_icons8_wifi_20 [20] PROGMEM = {
0xff, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0x8c, 0x40, 0xa1, 0x40, 0xc0, 0xc0, 0xf3, 0xc0, 0xf3, 0xc0, 
0xff, 0xc0, 0xff, 0xc0
};


void drawBitmap(int16_t x, int16_t y, const unsigned char bitmap[], int16_t width, int16_t height, uint16_t color);
void pantalla(String date);
void initPantalla();
