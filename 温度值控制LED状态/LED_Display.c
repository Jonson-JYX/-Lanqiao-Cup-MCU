#include <stc15f2k60s2.h>
#include "Common.h"
#include "Delay.h"
#include "LED.h"
#include "LED_Display.h"
#include "DS18B20.h"

code unsigned char LED_Display_Table[] = {
	0xC0,	// 0
	0xF9,	// 1
	0xA4,	// 2
	0xB0,	// 3
	0x99,	// 4
	0x92,	// 5
	0x82,	// 6
	0xF8,	// 7
	0x80,	// 8
	0x90,	// 9
	0xFF	//全灭
};

//温度显示数组
unsigned char Temp_Show_Arr[] = {10,10,10,10,10,10,10,10};

//临时存储数组
unsigned char Temp_Dat_Arr[] = {10,10,10,10,10,10,10,10};

//温度转化函数
void Temp_Change(){
	float temp = Temp_Value();
	unsigned int temp_dat = (unsigned int)(temp * 100);
	unsigned char i;
	if(temp_dat > 2600){
		LED(0xFE);
	}
	else{
		LED(0xFF);
	}
	if(temp_dat >= 10000){
		Temp_Dat_Arr[3] = temp_dat / 10000;
		Temp_Dat_Arr[4] = temp_dat % 10000 / 1000;
		Temp_Dat_Arr[5] = temp_dat % 1000 / 100;
		Temp_Dat_Arr[6] = temp_dat % 100 / 10;
		Temp_Dat_Arr[7] = temp_dat % 10;
	}
	if(temp_dat >= 1000 && temp_dat < 10000){
		Temp_Dat_Arr[3] = 10;
		Temp_Dat_Arr[4] = temp_dat / 1000;
		Temp_Dat_Arr[5] = temp_dat % 1000 / 100;
		Temp_Dat_Arr[6] = temp_dat % 100 / 10;
		Temp_Dat_Arr[7] = temp_dat % 10;
	}
	if(temp_dat >= 100 && temp_dat < 1000){
		Temp_Dat_Arr[3] = 10;
		Temp_Dat_Arr[4] = 10;
		Temp_Dat_Arr[5] = temp_dat / 100;
		Temp_Dat_Arr[6] = temp_dat % 100 / 10;
		Temp_Dat_Arr[7] = temp_dat % 10;
	}
	if(temp_dat >= 10 && temp_dat < 100){
		Temp_Dat_Arr[3] = 10;
		Temp_Dat_Arr[4] = 10;
		Temp_Dat_Arr[5] = 0;
		Temp_Dat_Arr[6] = temp_dat / 10;
		Temp_Dat_Arr[7] = temp_dat % 10;
	}
	if(temp_dat >= 10 && temp_dat < 100){
		Temp_Dat_Arr[3] = 10;
		Temp_Dat_Arr[4] = 10;
		Temp_Dat_Arr[5] = 0;
		Temp_Dat_Arr[6] = temp_dat / 10;
		Temp_Dat_Arr[7] = temp_dat % 10;
	}
	if(temp_dat >= 10 && temp_dat < 100){
		Temp_Dat_Arr[3] = 10;
		Temp_Dat_Arr[4] = 10;
		Temp_Dat_Arr[5] = 0;
		Temp_Dat_Arr[6] = 0;
		Temp_Dat_Arr[7] = temp_dat % 10;
	}
	for(i = 0;i < 8;i++){
		Temp_Show_Arr[i] = Temp_Dat_Arr[i];
	}
}

//数码管显示函数
void LED_Display_Show(){
	unsigned char i;	//循环
	unsigned char com = 0;	//位选
	unsigned char dat;	//缓冲区
	
	for(i = 0;i < 8;i++){
		SEG(0xFF);
		COM(0xFF);
		COM(1<<com);
		dat = LED_Display_Table[Temp_Show_Arr[i]];
		if(i == 5){
			dat = dat & 0x7F;
		}
		SEG(dat);
		com++;
		Delay40us();
	}
	com = 0;
	SEG(0xFF);
	COM(0xFF);
}










