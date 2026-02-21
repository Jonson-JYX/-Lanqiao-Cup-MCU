#include <stc15f2k60s2.h>
#include "keypad.h"
#include "displays.h"
#include "delay.h"
#include "common.h"

//初始化函数
void Init_MCU(){
	LED(0xFF);
	SEG(0xFF);
	COM(0xFF);
	BUZ(0x00);
}

//数码管显示按键函数
void Display_Key(){
	unsigned char Key_Number;
	//调用按键扫描函数
	//获取返回值
	Key_Number = Key_Scan();
	//调用数码管显示函数
	Seg_Display(Key_Number);
}
void main(){
	//初始化
	Init_MCU();
	while(1){
		//数码管显示按键函数
		Display_Key();
	}
}