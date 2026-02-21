#include <stc15f2k60s2.h>
#include "Uart.h"
#include "Common.h"
#include "LED.h"
#include "Delay.h"

code unsigned char LED_Display_Value[4] = {
	0xFF,
	0x88,
	0x92,
	0x86
};
unsigned char Value[8] = {0,0,0,0,0,0,0,0};
//定义全局变量，持久化存储当前显示值
unsigned char current_display_num = 0;

unsigned char Update_Display_Num(){
	unsigned char *num = Arr_Value();
	if(*num == 'A'){
		current_display_num = 1;
	}
	else if(*num == 'S'){
		current_display_num = 2;
	}
	else if(*num != 'A'&&*num == 'S'&&*num != '\0'){
		current_display_num = 3;
	}
	else{
		current_display_num = 0;
	}
	return current_display_num;
}

// 使用全局变量current_display_num
void LED_Display_Show(){
	unsigned char i;
	unsigned char com = 0;
	unsigned char dat;
	unsigned char num = Update_Display_Num(); // 读取全局变量
	
	Value[7] = num;
	for(i = 0;i < 8;i++){
		SEG(0xFF); // 消影
		COM(0x00);
		COM(1<<com);
		dat = LED_Display_Value[Value[i]];
		SEG(dat);
		com++;
	}
	
	// LED逻辑保持不变
	if(num == 1){
		LED(LED_Value[0]);
	}else if(num == 2){
		LED(LED_Value[1]);
	}else{
		LED(0xFF);
	}
	
	// 消影
	com = 0;
	SEG(0xFF);
	COM(0x00);
}