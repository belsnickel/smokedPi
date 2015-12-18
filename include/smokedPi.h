//function prototypes

void pollThermocouples();
void initializeGPIO();
void printSensorResponse();
int calcFarenheit(int response[]);

#define ever ;;

#include "oled.c"
#include "gfx.h"
#include <stdio.h>
#include <math.h>
#include <wiringPi.h>
#include <unistd.h>