#include <stc15f2k60s2.h>
#include "Common.h"
#include "LED_Display.h"
#include "Delay.h"
#include "UItrasound.h"
#include "KEY.h"
#include "LED.h"

void Init_MCU(){
	SEG(0xFF);
	COM(0xFF);
	LED(0xFF);
	BUZ(0x00);
}

void main(){
	Init_MCU();
	Timer_Init();
	while(1){
		Key_login();
		LED_login();
		dat_Change();
		LED_Display_Show();
	}
}