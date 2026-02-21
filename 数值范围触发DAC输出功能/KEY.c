#include <stc15f2k60s2.h>
#include "Delay.h"

sbit S4 = P3^3;
sbit S5 = P3^2;

unsigned char count = 0;

//按键扫描函数
unsigned char Key_Scan(){
	unsigned char key = 0;
	if(S4 == 0){
		Delay100ms();
		while(S4 == 0){
			key = 1;
		}
	}
	if(S5 == 0){
		Delay100ms();
		while(S5 == 0){
			key = 2;
		}
	}
	return key;
}

//按键累加器函数
void Key_Sum(){
	unsigned char key = Key_Scan();
	if(key == 1){
		if(count < 99){
			count++;
		}
	}
	if(key == 2){
		if(count > 0){
			count--;
		}
	}
}