#include <stc15f2k60s2.h>
#include "LED_Display.h"
#include "Delay.h"
#include "IIC.h"
#include "PCF8591.h"
#include "Common.h"

void Init_MCU(){
	SEG(0xFF);
	COM(0xFF);
	LED(0xFF);
	BUZ(0x00);
}

void main(){
	Init_MCU();
	while(1){
		Lighting_Change();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
	}
}