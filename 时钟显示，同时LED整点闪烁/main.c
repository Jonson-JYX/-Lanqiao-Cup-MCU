#include <stc15f2k60s2.h>
#include "Common.h"
#include "LED_Display.h"
#include "DS1302.h"
#include "Delay.h"
#include "intrins.h"

// 定义初始化函数
void Init_MCU(){
	LED(0xFF);
	SEG(0xFF);
	COM(0xFF);
	BUZ(0x00);
	SetRTC();
}

// 主函数
void main(){
	Init_MCU();
	while(1){
		LED_Dispaly_Show();
	}
}