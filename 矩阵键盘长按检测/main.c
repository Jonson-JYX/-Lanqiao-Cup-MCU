#include <STC15F2K60S2.h>
#include "KEY.h"
#include "LED_Display.h"
#include "Common.h"
#include "Timer.h"

void Init_MCU(){
	LED(0xFF);
	COM(0xFF);
	SEG(0xFF);
	BUZ(0x00);
	REY(0x00);
	Timer0_Init();
	KEY_Init();
}

void main(){
	Init_MCU();
	while(1){
		LED_Display_Choose();
		LED_Display_Show();
	}
}