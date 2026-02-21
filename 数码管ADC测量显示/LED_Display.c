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

//ADC临时数组
unsigned char ADC_dat_arr[] = {10,11,11,11,11,11,11,11};
//ADC显示数组
unsigned char ADC_show_arr[] = {10,11,11,11,11,11,11,11};

//ADC转化函数
void ADC_Change(){
	unsigned char i;
	float ADC_dat = ADC_Value();
	unsigned int dat = (unsigned int)(ADC_dat * 500);
	if(dat >= 100){
		ADC_dat_arr[5] = dat / 100;
		ADC_dat_arr[6] = dat % 100 / 10;
		ADC_dat_arr[7] = dat % 10;
	}
	else if(dat >= 10 && dat < 100){
		ADC_dat_arr[5] = 0;
		ADC_dat_arr[6] = dat / 10;
		ADC_dat_arr[7] = dat % 10;
	}
	else if(dat >= 0 && dat < 10){
		ADC_dat_arr[5] = 0;
		ADC_dat_arr[6] = 0;
		ADC_dat_arr[7] = dat % 10;
	}
	for(i = 0;i < 8;i++){
		ADC_show_arr[i] = ADC_dat_arr[i];
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
		dat =  SEG_Table[ADC_show_arr[i]];
		if(i == 5){
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



