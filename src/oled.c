#include "smokedPi.h"

#define _BV(x)   (1 << x) 

extern const unsigned char font[];

static unsigned char buffer[SSD1305_LCDHEIGHT * SSD1305_LCDWIDTH / 8] = { 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xC0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x0C, 0x3E, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC, 0xFC, 0xF8, 0xF0,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xE0, 0xE0, 0xE0,
0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x1F, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xFD,
0xFB, 0x7B, 0xBF, 0xFF, 0xFF, 0xFC, 0x7F, 0xFF, 0xF7, 0xF7, 0xF7, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x3F, 0x1F, 0x0F, 0x0F, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD,
0xFE, 0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0xFF, 0xFC, 0xF3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xF1,
0xC1, 0x01, 0x00, 0x00, 0x70, 0x78, 0x7C, 0x7C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0xFC, 0xF8,
0xF0, 0x00, 0x00, 0xF0, 0xF8, 0xFC, 0xFC, 0x3C, 0x3C, 0x3C, 0x3C, 0x78, 0xFF, 0xFF, 0xFF, 0xFF,
0x00, 0x00, 0x70, 0x78, 0x7C, 0x7C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0xFC, 0xF8, 0xF0, 0x00,
0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x3D, 0x3D, 0x3D, 0x00, 0x00, 0xFC, 0xFC, 0xFC, 0xFC, 0x70, 0x38,
0x3C, 0x3C, 0x3C, 0x00, 0xFC, 0xFC, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0xFC,
0xFC, 0x00, 0x00, 0xFC, 0xFC, 0xFC, 0xFC, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x3C, 0x3C, 0x3C,
0x00, 0x00, 0x00, 0x00, 0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x0F, 0x0F, 0x07, 0x07, 0x03,
0x03, 0x01, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x3F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF,
0xFF, 0x00, 0x00, 0x00, 0xFC, 0xFE, 0xFF, 0xFF, 0xE7, 0xE7, 0xE7, 0xE7, 0xF7, 0xFF, 0xFF, 0xFF,
0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xE0, 0xE0, 0xE0, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF,
0x00, 0x00, 0xFC, 0xFE, 0xFF, 0xFF, 0xE7, 0xE7, 0xE7, 0xE7, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xE0, 0xE0, 0xE0, 0xE0, 0xF0, 0xFF, 0xFF, 0xFF,
0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xE0, 0xE0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xF8, 0xF9, 0xF9, 0xF9, 0xF9, 0xF9, 0xF9, 0xF9, 0xF8, 0xF9, 0xF9, 0xF9,
0xF9, 0xF8, 0xF8, 0xF8, 0xF9, 0xF9, 0xF9, 0xF9, 0xF9, 0xF9, 0xF9, 0xF8, 0xF9, 0xF9, 0xF9, 0xF9,
0xF8, 0xF8, 0xF8, 0xF9, 0xF9, 0xF9, 0xF9, 0xF9, 0xF9, 0xF9, 0xF8, 0xF9, 0xF9, 0xF9, 0xF9, 0xF8,
0xF8, 0xF9, 0x09, 0xF9, 0x09, 0xD8, 0xB8, 0x78, 0x08, 0xF8, 0x09, 0xE9, 0xE9, 0x19, 0xF8, 0x08,
0xF8, 0xF8, 0x08, 0xF8, 0xD8, 0xA8, 0xA9, 0x69, 0xF9, 0xE9, 0x09, 0xE9, 0xF8, 0x09, 0xA9, 0x29,
0xD9, 0xF8, 0x08, 0xF9, 0x09, 0xA9, 0xA9, 0xF8, 0xD8, 0xA8, 0xA9, 0x69, 0xF9, 0xF9, 0xF9, 0xF9,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01,
0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01,
0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01
};

void initOLED(){
	//send command to initialize display ssd1305 chip 128x64
	digitalWrite(displayRst, HIGH);
	usleep(1000);
	digitalWrite(displayRst,LOW);
	usleep(10000);
	digitalWrite(displayRst, HIGH);
	usleep(1000);
	
	command(SSD1305_DISPLAYOFF);                    // 0xAE
	command(SSD1305_SETLOWCOLUMN | 0x4);  // low col = 0
	command(SSD1305_SETHIGHCOLUMN | 0x4);  // hi col = 0
  	command(SSD1305_SETSTARTLINE | 0x0); // line #0
  	command(0x2E); //??
	command(SSD1305_SETCONTRAST);                   // 0x81
  	command(0x32);
  	command(SSD1305_SETBRIGHTNESS);                 // 0x82
  	command(0x80);
  	command(SSD1305_SEGREMAP | 0x01);
  	command(SSD1305_NORMALDISPLAY);                 // 0xA6
  	command(SSD1305_SETMULTIPLEX);                  // 0xA8
  	command(0x3F); // 1/64
  	command(SSD1305_MASTERCONFIG);
  	command(0x8e); /* external vcc supply */
  	command(SSD1305_COMSCANDEC);
  	command(SSD1305_SETDISPLAYOFFSET);              // 0xD3
  	command(0x40); 
  	command(SSD1305_SETDISPLAYCLOCKDIV);            // 0xD5
  	command(0xf0); 
  	command(SSD1305_SETAREACOLOR);  
  	command(0x05);
  	command(SSD1305_SETPRECHARGE);                  // 0xd9
  	command(0xF1);
  	command(SSD1305_SETCOMPINS);                    // 0xDA
  	command(0x12);
	
	command(SSD1305_SETLUT);
 	command(0x3F);
  	command(0x3F);
  	command(0x3F);
  	command(0x3F);
  

  	command(SSD1305_DISPLAYON);//--turn on oled panel
	
}

void command(unsigned char c) {
	//DC is LOW for command
	digitalWrite(displayDC,LOW);
	usleep(10);
	transfer(c);
	digitalWrite(displayDC,HIGH);
	usleep(10);
}

void data(unsigned char c) {
	//DC is HiGH for data 
	digitalWrite(displayDC, HIGH);
	usleep(10);
	transfer(c);
	usleep(10);
}

void display() {
	int i = 0;
  	unsigned char page = 0;

    for(; page<8; page++) {
    
		command(SSD1305_SETPAGESTART + page);
		command(0x00);
		command(0x10);
		
      	digitalWrite(displayCS, HIGH);
      	digitalWrite(displayDC, HIGH);
      	digitalWrite(displayCS, LOW);
		  
      	int x;
			for(x = 0; x < 128; x++) {
				transfer(buffer[i++]);
				//printf("%d",i);
			}
      
		digitalWrite(displayCS, HIGH);	
		usleep(10);
	}
}

void clearDisplay() {
	memset(buffer, 0, (SSD1305_LCDWIDTH*SSD1305_LCDHEIGHT/8));
}

void invertDisplay(unsigned char i) {
	if(i) {
		command(SSD1305_INVERTDISPLAY);
	}
	else {
		command(SSD1305_NORMALDISPLAY);
	}
	
}

void drawPixel(int x, int y) {
	if ((x >= 128) || (y >= 64) || (x < 0) || (y < 0))
    return;

  // x is which column
 // if (color == WHITE) 
    buffer[x+ (y/8)*SSD1305_LCDWIDTH] |= _BV((y%8));  
//  else
//    buffer[x+ (y/8)*SSD1305_LCDWIDTH] &= ~_BV((y%8)); 
}