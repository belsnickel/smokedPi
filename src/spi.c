//msb first and mode 0? = clock polarity = 0, clock idle is low and 
//according to data sheet looks like mode 1..so thats what ill use
#include "smokedPi.h"

void transfer(unsigned char data) {
	//define pin numbers in header
	int bitpos, bitvalue;
	
	//chip select low
	digitalWrite(displayCS, LOW);
	usleep(10);
	//clock low, data shifted in on rising edge
	digitalWrite(displayClk,LOW);
    usleep(10);
    
	for(bitpos = 0; bitpos < 8; bitpos++) {
		bitvalue = ((data >> (bitpos - 1)) & 0x01);
		
		if(bitvalue) {
			digitalWrite(displayData, HIGH);
		}
		else {
			digitalWrite(displayData, LOW);
		}
		usleep(10);
		//clock high shift data in
		digitalWrite(displayClk, HIGH);
		
		//clock low
		usleep(10);
		digitalWrite(displayClk, LOW);
	}
	usleep(10);
	digitalWrite(displayCS, HIGH);
}