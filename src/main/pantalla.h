#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "declaracion.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// 'icons8-wifi-20', 20x20px
const unsigned char wifi [] PROGMEM = {
 0x00, 0xff, 0x00, 0x7e, 0x00, 0x18, 0x00, 0x00
};

const unsigned char reloj [] PROGMEM = {
 0x00, 0x1c, 0x3e, 0x71, 0x77, 0x77, 0x3e, 0x41,0x00,
};

/*const unsigned char wifi [] PROGMEM = {                   
	0b00000111, 0b11100000, //      ######     
	0b00001111, 0b11110000, //     ########    
	0b00011000, 0b00011000, //    ##      ##   
	0b00000011, 0b11000000, //       ####      
	0b00000111, 0b11100000, //      ######     
	0b00000100, 0b00100000, //      #    #     
	0b00000001, 0b10000000, //        ##       
	0b00000001, 0b10000000, //        ##    
};*/


// 'icons8-17372-0-73111-reproducir-derecha-43-flechas-20 (1)', 20x20px
const unsigned char serverntp [60] PROGMEM = {
	0xff, 0xff, 0xf0, 0xff, 0xff, 0xf0, 0xe0, 0x00, 0xf0, 0xef, 0xff, 0xf0, 0xdf, 0xff, 0xf0, 0xdf, 
	0xff, 0xf0, 0xdf, 0xff, 0x30, 0xdf, 0xfe, 0x10, 0xdf, 0xfd, 0xa0, 0xdf, 0xff, 0xb0, 0xdf, 0xff, 
	0xb0, 0x5b, 0xff, 0xb0, 0x87, 0xff, 0xb0, 0xcf, 0xff, 0xb0, 0xff, 0xff, 0xb0, 0xff, 0xff, 0xb0, 
	0xff, 0xff, 0x70, 0xf0, 0x00, 0x70, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf0
};


void drawBitmap(int16_t x, int16_t y, const unsigned char bitmap[], int16_t width, int16_t height, uint16_t color);
void pantalla(String date,int comenzar, bool serverNTP, String temperatura, String humedad);
void initPantalla();
void pantallaReloj(String hora, String minuto, String segundo, bool* par,int comenzar, String temperatura, String humedad);
