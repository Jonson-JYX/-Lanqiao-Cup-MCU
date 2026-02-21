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
	0xC1,	//U
	0xFF	//全灭
};

//RB2临时数组
unsigned char RB2_dat_arr[] = {10,11,11,11,11,11,11,11};
//RB2显示数组
unsigned char RB2_show_arr[] = {10,11,11,11,11,11,11,11};

//RB2电压转化函数
void RB2_Change(){
	float RB2 = RB2_Value();
	unsigned int RB2_value = (unsigned int)(RB2 * 500);
	unsigned char i;
	if(RB2_value >= 100){
		RB2_dat_arr[5] = RB2_value / 100;
		RB2_dat_arr[6] = RB2_value % 100 / 10;
		RB2_dat_arr[7] = RB2_value % 10;
	}
	if(RB2_value >= 10 && RB2_value < 100){
		RB2_dat_arr[5] = 0;
		RB2_dat_arr[6] = RB2_value / 10;
		RB2_dat_arr[7] = RB2_value % 10;
	}
	if(RB2_value >= 0 && RB2_value < 10){
		RB2_dat_arr[5] = 0;
		RB2_dat_arr[6] = 0;
		RB2_dat_arr[7] = RB2_value % 10;
	}
	for(i = 0;i < 8;i++){
		RB2_show_arr[i] = RB2_dat_arr[i];
	}
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
		dat = SEG_Table[RB2_show_arr[i]];
		if(i == 5){
			dat = dat & 0x7F;
		}
		SEG(dat);
		com++;
		Delay50us();
		Delay50us();
	}
	com = 0;
	SEG(0xFF);
	COM(0xFF);
}