#include <stc15f2k60s2.h>
#include "KEY.h"
#include "DELAY.h"

//按键键值表
code unsigned char Key_Value[5] = {0,1,2,3,4};

//按键扫描函数
unsigned char Key_Scan(){
	//扫描第一行
	P30 = 0;P31 = 1;P32 = 1;P33 = 1;
	if(P44 == 0){
		Delay(100);
		while(P44 == 0){
			return Key_Value[1];
		}
	}
	//扫描第二行
	P30 = 1;P31 = 0;P32 = 1;P33 = 1;
	if(P44 == 0){
		Delay(100);
		while(P44 == 0){
			return Key_Value[2];
		}
	}
	//扫描第三行
	P30 = 1;P31 = 1;P32 = 0;P33 = 1;
	if(P44 == 0){
		Delay(100);
		while(P44 == 0){
			return Key_Value[3];
		}
	}
	//扫描第四行
	P30 = 1;P31 = 1;P32 = 1;P33 = 0;
	if(P44 == 0){
		Delay(100);
		while(P44 == 0){
			return Key_Value[4];
		}
	}
	return Key_Value[0];
}

