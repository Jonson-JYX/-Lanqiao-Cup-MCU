#include "stc15f2k60s2.h"
#include "Common.h"
#include "LED_Display.h"
#include "DS1302.h"
#include "DS18B20.h"
#include "PCF8591.h"
#include "Onewire.h"
#include "IIC.h"
#include "Delay.h"
#include "KEY.h"

void Init_MCU(){
	SetRTC();
	SEG(0xFF);
	COM(0xFF);
	LED(0xFF);
	BUZ(0x00);
	S4_cnt = 1;
	S8_password = 0;
}

void main(){
	Init_MCU();
	while(1){
		Key_logic();
		Time_Change();
		Value_Change();
		Select_Change();
		LED_Display_Choose();
		LED_Display_Show();
		LED_Display_Show();
	}
}