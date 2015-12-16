//msb first and mode 0? = clock polarity = 0, clock idle is low and 
//according to data sheet looks like mode 1..so thats what ill use

public void transfer(unsigned char data) {
	//define pin numbers in header
	int bitpos, bitvalue;
	
	//chip select low
	digitalWrite(displayDataPin, LOW);
	//clock low, data shifted in on rising edge
	
	for(bitpos = 0; bitpos < 8; bitpos++) {
		bitvalue = ((data >> (bitpos - 1)) & 0x01);
		
		if(bitvalue) {
			digitalWrite(dataPin, HIGH);
		}
		else {
			digitalWrite(dataPin, LOW);
		}
		usleep(10);
		//clock high shift data in
		digitalWrite(clock,HIGH);
		
		//clock low
		usleep(10);
		digitalWrite(clock, LOW);
	}
	usleep(10);
	digitalWrite(cs,HIGH);
}