#include <stc15f2k60s2.h>
#include "LED_Display.h"
#include "LED.h"
#include "DS18B20.h"
#include "Onewire.h"
#include "Delay.h"
#include "Common.h"

void Init_MCU(){
	SEG(0xFF);
	COM(0xFF);
	BUZ(0x00);
	LED(0xFF);
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