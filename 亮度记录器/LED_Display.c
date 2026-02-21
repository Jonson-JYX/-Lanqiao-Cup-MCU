#include <stc15f2k60s2.h>
#include "Common.h"
#include "Delay.h"
#include "PCF8591.h"

code unsigned char SEG_Table[] = {
	0xC0,	//0
	0xF9,	//1
	0xA4,	//2
	0xB0,	//3
	0x99,	//4
	0x92,	//5
	0x82,	//6
	0xF8,	//7
	0x80,	//8
	0x90,	//9
	0xFF	//全灭
};

//记录当前电压
unsigned char dat_value = 0;
//记录最大电压
unsigned char dat_max = 0;
//记录最小电压
unsigned char dat_min = 100;

//临时存储数组
unsigned char dat_value_arr[] = {10,10,10,10,10,10,10,10};
//电压显示数组
unsigned char dat_show_arr[] = {10,10,10,10,10,10,10,10};

//电压转化函数
void Lighting_Change(){
	float dat = Lighting_Value();
	unsigned char i;
	unsigned int value = (unsigned int)(dat * 50.0);
	if(value > dat_max){
		dat_max = value;
	}
	if(value < dat_min){
		dat_min = value;
	}
	
	if(value >= 10){
		dat_value_arr[0] = value / 10;
		dat_value_arr[1] = value % 10;
	}
	else{
		dat_value_arr[0] = 0;
		dat_value_arr[1] = value % 10;
	}
	
	if(dat_min >= 10){
		dat_value_arr[3] = dat_min / 10;
		dat_value_arr[4] = dat_min % 10;
	}
	else{
		dat_value_arr[3] = 0;
		dat_value_arr[4] = dat_min % 10;
	}
	
	if(dat_max >= 10){
		dat_value_arr[6] = dat_max / 10;
		dat_value_arr[7] = dat_max % 10;
	}
	else{
		dat_value_arr[6] = 0;
		dat_value_arr[7] = dat_max % 10;
	}
	
	for(i = 0;i < 8;i++){
		dat_show_arr[i] = dat_value_arr[i];
	}
}
//数码管显示函数
void LED_Display_Show(){
	unsigned char i;
	unsigned char dat;
	unsigned char com = 0;
	
	for(i = 0;i < 8;i++){
		SEG(0xFF);
		COM(0xFF);
		COM(1<<com);
		dat = SEG_Table[dat_show_arr[i]];
		if(i == 0 || i == 3 || i == 6){
			dat = dat & 0x7F;
		}
		SEG(dat);
		com++;
		Delay50us();
	}
	com = 0;
	SEG(0xFF);
	COM(0xFF);
}