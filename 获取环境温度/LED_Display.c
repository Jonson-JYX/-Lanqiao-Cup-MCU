#include <stc15f2k60s2.h>
#include "Common.h"
#include "Delay.h"
#include "DS18B20.h"

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
	0xC6,	//C
	0xFF	//全灭
};

//温度临时存储数组
unsigned char Temp_dat_arr[] = {11,11,11,11,11,11,11,10};
//温度显示数组
unsigned char Temp_show_arr[] = {11,11,11,11,11,11,11,10};

//温度转化函数
void Temp_Change(){
	float temp = Temp_Value();
	unsigned char i;
	unsigned int temp_value = (unsigned int)(temp * 100);
	Temp_dat_arr[3] = temp_value / 1000;
	Temp_dat_arr[4] = temp_value % 1000 / 100;
	Temp_dat_arr[5] = temp_value % 100 / 10;
	Temp_dat_arr[6] = temp_value % 10;
	for(i = 0;i < 8;i++){
		Temp_show_arr[i] = Temp_dat_arr[i];
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
		dat = SEG_Table[Temp_show_arr[i]];
		if(i == 4){
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
