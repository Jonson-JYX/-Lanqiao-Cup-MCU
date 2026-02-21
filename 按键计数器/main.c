#include <stc15f2k60s2.h>
#include "LED_Display.h"
#include "Key.h"
#include "Delay.h"
#include "LED.h"
#include "Common.h"

// 定义初始化函数
void Init_MCU(){
	LED(0xFF);
	SEG(0xFF);
	COM(0xFF);
	BUZ(0x00);
	Timer0_Init();
}

void main(){
	Init_MCU();
	while(1){
		LED_Display_Show();
	}
}