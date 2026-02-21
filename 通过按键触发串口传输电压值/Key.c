#include <stc15f2k60s2.h>
#include "Delay.h"
#include "Uart.h"

sbit S4 = P3^3;

//按键扫描函数
unsigned char Key_Scan(){
	unsigned char key = 0;
	if(S4 == 0){
		Delay50ms();
		while(S4 == 0){
			key = 1;
		}
	}
	return key;
}

//按键发送函数
void Key_Send(){
	unsigned char key = Key_Scan();
	if(key == 1){
		Send_RB2();
	}
}