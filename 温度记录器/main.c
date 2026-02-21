#include <stc15f2k60s2.h>
#include "LED_Display.h"
#include "Onewire.h"
#include "DS18B20.h"
#include "Delay.h"
#include "Common.h"

void Init_MCU(){
	SEG(0xFF);
	COM(0xFF);
	BUZ(0x00);
	LED(0xFF);
	Temp_Now = 0;
	Temp_Min = 99;
	Temp_Max = 0;
}

void main(){
	Init_MCU();
	while(1){
		Temp_Change();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
	}
}