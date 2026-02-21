#include <stc15f2k60s2.h>
#include "Delay.h"

sbit S9 = P3^2;
sbit GND = P4^2;

//模式判断位
bit key_password = 0;

//按键扫描函数
unsigned char Key_Scan(){
	unsigned char key = 0;
	GND = 0;
	if(S9 == 0){
		Delay10ms();
		while(S9 == 0){
			key = 1; 
		}
	}
	return key;
}

//按键模式切换函数
void Key_Modle(){
	unsigned char key = Key_Scan();
	if(key == 1){
		key_password = ~key_password;
	}
}