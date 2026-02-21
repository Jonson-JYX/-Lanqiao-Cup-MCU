#include <stc15f2k60s2.h>
#include "Delay.h"
#include "UItrasound.h"
#include "LED_Display.h"

sbit GND = P4^2;
sbit S9 = P3^2;

unsigned char value = 1000;
unsigned char Key_Scan(){
	unsigned char key = 0;
	GND = 0;
	if(S9 == 0){
		Delay100ms();
		while(S9 == 0){
			key = 1;
		}
	}
	return key;
}

void Key_login(){
	unsigned char key = Key_Scan();
	if(key == 1){
		value = dat1;
	}
}