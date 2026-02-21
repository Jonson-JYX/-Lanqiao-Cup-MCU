#include <stc15f2k60s2.h>
#include "LED_Display.h"
#include "LED.h"
#include "KEY.h"
#include "PCF8591.h"
#include "Delay.h"
#include "IIC.h"
#include "OneWire.h"
#include "Common.h"

//初始化函数
void Init_MCU(){
	SEG(0xFF);
	COM(0xFF);
	LED(0xFF);
	BUZ(0x00);
}

void main(){
	Init_MCU();
	while(1){
		// 循环更新温度/光照数据
		Temperature_dat_Receive();
		Lighting_dat_Receive();
		// 循环更新DAC转换数据
		Temperature_DAC_Receive();
		Lighting_DAC_Receive();
		
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
	}
}



