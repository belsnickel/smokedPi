
#include "smokedPi.h"
//#include "oled.c"

	int heartBeatPin = 6;
	int temp1Clk = 14; //gpio 11 for temp sensor 1 clk
	int temp1Data = 13; // gpio 9 for receiving sensor data
	int temp1CS = 10; //Chip select for temp sensor 1
	int temp2CS = 11;
	int error = -1;

	int tempSensor1Response[32]; //response from max31855 chip stored here
	int tempSensor2Response[32];
	
	int meatTemp = -1;
	int grillTemp = -1;

int main()
{
	//setup gpio pins and set initial state
	initializeGPIO();
	initializeOLED();
	
	//set initial state for each pin
	digitalWrite(temp1CS,HIGH);
	digitalWrite(temp1Clk,LOW);
	digitalWrite(temp2CS,HIGH);
	
	
	for(ever){
		
		//pollThermocouples();
		//displayTempOLED(meatTemp, grillTemp);
		//display();
       // command(0xA5);
      //  command(0xA4);
        
		usleep(1000000);
		digitalWrite(heartBeatPin,LOW);
        
		usleep(1000000);
        digitalWrite(displayClk,HIGH);
        usleep(1000000);
        digitalWrite(displayClk,LOW);
        
        usleep(1000000);
        digitalWrite(displayCS,HIGH);
        usleep(1000000);
        digitalWrite(displayCS,LOW);
        
        usleep(1000000);
        digitalWrite(displayDC,HIGH);
        usleep(1000000);
        digitalWrite(displayDC,LOW);
        
         usleep(1000000);
        digitalWrite(displayRst,HIGH);
        usleep(1000000);
        digitalWrite(displayRst,LOW);
        
        usleep(1000000);
        digitalWrite(displayData,HIGH);
        usleep(1000000);
        digitalWrite(displayData,LOW);
        usleep(1000000);
        
        
	}
	return 0;
}

void displayTempOLED(int temp1, int temp2) {
	//send display data?

  drawPixel(10,10);
	
}

void initializeOLED() {
	//send command to turn on and configure oled
	initOLED();
}
void pollThermocouples(){
	
	int i;
	digitalWrite(heartBeatPin,HIGH);
	digitalWrite(temp1CS,LOW); //chip select
	usleep(500);
	for(i = 0; i<32; i++)
	{
		digitalWrite(temp1Clk,HIGH);
		usleep(500);

		//read input pin and store
		tempSensor1Response[i] = digitalRead(temp1Data);
		digitalWrite(temp1Clk,LOW);
		usleep(500);
	}

	digitalWrite(temp1CS,HIGH);
	digitalWrite(temp2CS,LOW);
	usleep(500);
	
	for(i=0; i<32; i++)
	{
		digitalWrite(temp1Clk,HIGH);
		usleep(500);
		tempSensor2Response[i] = digitalRead(temp1Data);
		digitalWrite(temp1Clk,LOW);
		usleep(500);
	}
	
	digitalWrite(temp2CS,HIGH);

	//printSensorResponse(tempSensorResponse);
	grillTemp = calcFarenheit(tempSensor1Response);
	meatTemp = calcFarenheit(tempSensor2Response);
	
	printf("Temp in farenheit is %d and %d",calcFarenheit(tempSensor1Response),calcFarenheit(tempSensor2Response)); 
	printf("\n");
	//usleep(1000000);
}

void initializeGPIO(){
	
	error = wiringPiSetup();
	if (error == -1)
	{
		printf("Error in wiringPiSetup \n");
	}
	
	pinMode(heartBeatPin,OUTPUT);
	pinMode(temp1CS,OUTPUT); //chip select 1
	pinMode(temp1Data,INPUT);
	pinMode(temp1Clk,OUTPUT);
	pinMode(temp2CS,OUTPUT);
    
    pinMode(displayCS,OUTPUT);
    pinMode(displayClk,OUTPUT);
    pinMode(displayData,OUTPUT);
    pinMode(displayDC,OUTPUT);
    pinMode(displayRst,OUTPUT);
    
    digitalWrite(displayClk,LOW);
    digitalWrite(displayData,LOW);
    digitalWrite(displayDC,LOW);
    digitalWrite(displayRst,LOW);
    digitalWrite(displayCS,LOW);
    printf("GPIO pin initialized...\n");
    usleep(10000000);
}

void printSensorResponse(int response[])
{	
	printf("Printing raw temp data...  "); 
	int j;

	for(j=0; j<32; j++)
	{
		printf("%d",response[j]);
	} 
}

int calcFarenheit(int response[])
{
	int k=0;
	int result = 0;
	int temp[14];
	if(response[0] == 1)//number is negative
	{
		for(k=0;k<14;k++)
		{
			if(response[k]==1)
				temp[k]=0;
			else
				temp[k]=1;
		}
	}
	else
	{
		for(k=0;k<14;k++)
		{
			temp[k]=response[k];
			//printf("%d",response[k]);	
		}
	}
	for(k=14;k>0;k--)
	{
		result += (temp[14-k]*(pow(2,k-1)));
	}
	return ((result*9)/20)+32;
}
