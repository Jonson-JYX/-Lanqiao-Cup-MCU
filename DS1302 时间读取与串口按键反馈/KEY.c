#include <stc15f2k60s2.h>
#include "KEY.h"
#include "Uart.h"
#include "Delay.h"


//按键扫描函数
unsigned char Key_Scan(){
	P30 = 1;P31 = 1;P32 = 1;P33 = 0;
	// S4按键（P44）
	if(P44 == 0){
		Delay500ms(); // 消抖
		if(P44 == 0){ // 确认按键按下
			while(P44 == 0); // 等待按键释放
			return 1;
		}
	}
	
	// S8按键（P42）
	if(P42 == 0){
		Delay500ms();
		if(P42 == 0){
			while(P42 == 0);
			return 2;
		}
	}
	
	// S12按键（P35）
	if(P35 == 0){
		Delay500ms();
		if(P35 == 0){
			while(P35 == 0);
			return 3;
		}
	}
	return 0;
}
