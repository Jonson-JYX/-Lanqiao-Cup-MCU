#include <stc15f2k60s2.h>
#include "LED_Display.h"
#include "PCF8591.h"
#include "IIC.h"
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
		ADC_Change();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
	}
}