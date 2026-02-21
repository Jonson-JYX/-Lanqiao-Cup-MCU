#include <stc15f2k60s2.h>
#include "Delay.h"
#include "Common.h"

//LEDÏÔÊ¾º¯Êý
void LED_Show(){
	LED(0xFE);
	Delay2000ms();
	LED(0xFF);
}