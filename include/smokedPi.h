//function prototypes


void displayTempOLED(int temp1, int temp2);
void initializeOLED();
void pollThermocouples();
void initializeGPIO();
void printSensorResponse();
int calcFarenheit(int response[]);




#define ever ;;

#include "oled.h"
#include "gfx.h"
#include <stdio.h>
#include <math.h>
#include <wiringPi.h>
#include <unistd.h>
#include <string.h>