#include <stc15f2k60s2.h>
#include "Delay.h"

sbit S16 = P3^3;
sbit GND = P3^4;

//°´¼üÉ¨Ãèº¯Êı
unsigned char Key_Scan(){
	unsigned char key = 0;
	GND = 0;
	if(S16 == 0){
		Delay10ms();
		while(S16 == 0){
			key = 1;
		}
	}
	return key;
}