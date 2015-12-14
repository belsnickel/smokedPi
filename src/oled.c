void initOLED(){
	//send command to initialize display ssd1305 chip 128x64
	
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
  	#endif

  	command(SSD1305_DISPLAYON);//--turn on oled panel
	
}