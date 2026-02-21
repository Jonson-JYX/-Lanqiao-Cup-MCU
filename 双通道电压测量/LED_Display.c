#include <stc15f2k60s2.h>
#include "Common.h"
#include "Delay.h"
#include "PCF8591.h"

//数码管段码表
code unsigned char SEG_Table[] = {
	0xC0, 	//0
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

//光敏电阻电压临时数组
unsigned char Lighting_dat_Arr[] = {10,10,10};
//RB2电压数值临时数组
unsigned char RB2_dat_Arr[] = {10,10,10};
//数码管显示数组
unsigned char dat_arr[] = {10,10,10,10,10,10,10,10};

//光敏电阻电压转化函数
void Lighting_Change(){
	float dat = Lighting_Value();
	unsigned int value = (unsigned int)(dat * 500);
	if(value >= 100){
		Lighting_dat_Arr[0] = value / 100;
		Lighting_dat_Arr[1] = value % 100 /10;
		Lighting_dat_Arr[2] = value % 10;
	}
	else{
		Lighting_dat_Arr[0] = 0;
		Lighting_dat_Arr[1] = value % 100 /10;
		Lighting_dat_Arr[2] = value % 10;
	}
}

//RB2电阻电压转化函数
void RB2_Change(){
	float dat = RB2_Value();
	unsigned int value = (unsigned int)(dat * 500);
	if(value >= 100){
		RB2_dat_Arr[0] = value / 100;
		RB2_dat_Arr[1] = value % 100 /10;
		RB2_dat_Arr[2] = value % 10;
	}
	else{
		RB2_dat_Arr[0] = 0;
		RB2_dat_Arr[1] = value % 100 /10;
		RB2_dat_Arr[2] = value % 10;
	}
}

//数码管显示数组存储
void dat_arr_change(){
	dat_arr[0] = Lighting_dat_Arr[0];
	dat_arr[1] = Lighting_dat_Arr[1];
	dat_arr[2] = Lighting_dat_Arr[2];
	
	dat_arr[5] = RB2_dat_Arr[0];
	dat_arr[6] = RB2_dat_Arr[1];
	dat_arr[7] = RB2_dat_Arr[2];
}

//数码管显示数组
void LED_Display_Show(){
	unsigned char i;
	unsigned char dat;
	unsigned char com = 0;
	
	for(i = 0;i < 8;i++){
		SEG(0xFF);
		COM(0xFF);
		COM(1<<com);
		dat = SEG_Table[dat_arr[i]];
		if(i == 0 || i == 5){
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


