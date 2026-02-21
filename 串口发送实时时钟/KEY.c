#include <stc15f2k60s2.h>
#include "KEY.h"
#include "Uart.h"
#include "Delay.h"

sbit GND = P4^2;
sbit S9 = P3^2;

//按键扫描函数
unsigned char Key_Scan(){
	GND = 0;
	if(S9 == 0){
		Delay500ms();
		while(S9 == 0){
			return 1;
		}
	}
	return 0;
}

//按键实现函数
void Key_Show(){
	if(Key_Scan() == 1){
		Send_Time();
	}
}