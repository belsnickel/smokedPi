#include <stdio.h>
#include <math.h>
#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <unistd.h>
#include <smokedPi.h>


	int temp1Clk = 14; //gpio 11 for temp sensor 1 clk
	int temp1Data = 13; // gpio 9 for receiving sensor data
	int temp1CS = 10; //Chip select for temp sensor 1
	int temp2CS = 11;
	int error = -1;

	int tempSensor1Response[32]; //response from max31855 chip stored here
	int tempSensor2Response[32];

int main()
{
	//setup gpio pins and set initial state
	initializeGPIO();
	
	//set initial state for each pin
	digitalWrite(temp1CS,HIGH);
	digitalWrite(temp1Clk,LOW);
	digitalWrite(temp2CS,HIGH);
	
	
	for(ever){
		
		pollThermocouples();
	
	}
	return 0;
}

void pollThermocouples(){
	
	int i;
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
	printf("Temp in farenheit is %d and %d",calcFarenheit(tempSensor1Response),calcFarenheit(tempSensor2Response)); 
	printf("\n");
	usleep(100000);
}

void initializeGPIO(){
	
		error = wiringPiSetup();
	if (error == -1)
	{
		printf("Error in wiringPiSetup \n");
	}
	
	pinMode(temp1CS,OUTPUT); //chip select 1
	pinMode(temp1Data,INPUT);
	pinMode(temp1Clk,OUTPUT);
	pinMode(temp2CS,OUTPUT);
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
