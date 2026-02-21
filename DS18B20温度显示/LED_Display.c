#include <stc15f2k60s2.h>
#include "KEY.h"
#include "DS18B20.h"
#include "Delay.h"
#include "Common.h"


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
	0xC6,	// C
	0xFF,	// 全灭
};

//模式一温度显示数组
unsigned char Temp_modle1_Arr[] = {11,11,11,11,11,11,11,10};

//模式二温度显示数组
unsigned char Temp_modle2_Arr[] = {11,11,11,11,11,11,11,10};

//温度存储显示数组
unsigned char Temp_dat[] = {11,11,11,11,11,11,11,10};

//转换温度函数
void Temp_Change(){
	float temp = Temp_Value();
	unsigned int temp_modle1 = (unsigned int)(temp * 10);
	unsigned int temp_modle2 = (unsigned int)(temp * 100);
	
	//模式一存储
	if(temp_modle1 >= 1000){
		Temp_modle1_Arr[3] = temp_modle1 / 1000;
		Temp_modle1_Arr[4] = temp_modle1 % 1000 / 100;
		Temp_modle1_Arr[5] = temp_modle1 % 100 / 10;
		Temp_modle1_Arr[6] = temp_modle1 % 10;
	}
	else if(temp_modle1 >= 100 && temp_modle1 < 1000){
		Temp_modle1_Arr[3] = 11;
		Temp_modle1_Arr[4] = temp_modle1 / 100;
		Temp_modle1_Arr[5] = temp_modle1 % 100 / 10;
		Temp_modle1_Arr[6] = temp_modle1 % 10;
	}
	else if(temp_modle1 >= 10 && temp_modle1 < 100){
		Temp_modle1_Arr[3] = 11;
		Temp_modle1_Arr[4] = 11;
		Temp_modle1_Arr[5] = temp_modle1 / 10;
		Temp_modle1_Arr[6] = temp_modle1 % 10;
	}
	else if(temp_modle1 < 10){
		Temp_modle1_Arr[3] = 11;
		Temp_modle1_Arr[4] = 11;
		Temp_modle1_Arr[5] = 0;
		Temp_modle1_Arr[6] = temp_modle1 % 10;
	}
	
	//模式二存储
	if(temp_modle2 >= 10000){
		Temp_modle2_Arr[2] = temp_modle2 / 10000;
		Temp_modle2_Arr[3] = temp_modle2 % 10000 / 1000;
		Temp_modle2_Arr[4] = temp_modle2 % 1000 / 100;
		Temp_modle2_Arr[5] = temp_modle2 % 100 / 10;
		Temp_modle2_Arr[6] = temp_modle2 % 10;
	}
	else if(temp_modle2 >= 1000 && temp_modle2 < 10000){
		Temp_modle2_Arr[2] = 11;
		Temp_modle2_Arr[3] = temp_modle2 / 1000;
		Temp_modle2_Arr[4] = temp_modle2 % 1000 / 100;
		Temp_modle2_Arr[5] = temp_modle2 % 100 / 10;
		Temp_modle2_Arr[6] = temp_modle2 % 10;
	}
	else if(temp_modle2 >= 100 && temp_modle2 < 1000){
		Temp_modle2_Arr[2] = 11;
		Temp_modle2_Arr[3] = 11;
		Temp_modle2_Arr[4] = temp_modle2 / 100;
		Temp_modle2_Arr[5] = temp_modle2 % 100 / 10;
		Temp_modle2_Arr[6] = temp_modle2 % 10;
	}
	else if(temp_modle2 >= 10 && temp_modle2 < 100){
		Temp_modle2_Arr[2] = 11;
		Temp_modle2_Arr[3] = 11;
		Temp_modle2_Arr[4] = 0;
		Temp_modle2_Arr[5] = temp_modle2 / 10;
		Temp_modle2_Arr[6] = temp_modle2 % 10;
	}
	else if(temp_modle2 < 10){
		Temp_modle2_Arr[2] = 11;
		Temp_modle2_Arr[3] = 11;
		Temp_modle2_Arr[4] = 0;
		Temp_modle2_Arr[5] = 0;
		Temp_modle2_Arr[6] = temp_modle2 % 10;
	}
}

//数码管显示函数
void LED_Display_Show(){
	unsigned char i;
	unsigned char dat;
	unsigned char com = 0;
	
	for(i = 0;i < 8;i++){
		COM(0xff);
		SEG(0xff);
		COM(1<<com);
		dat = LED_Display_Table[Temp_dat[i]];
		if(key_password == 0 && i == 5){
			dat = (LED_Display_Table[Temp_dat[i]]) & 0x7F;
		}
		if(key_password == 1 && i == 4){
			dat = (LED_Display_Table[Temp_dat[i]]) & 0x7F;
		}
		SEG(dat);
		com++;
		Delay40us();
	}
	com = 0;
	COM(0xff);
	SEG(0xff);
}

//数码管模式选择函数
void LED_Display_Choose(){
	unsigned char i;
	if(key_password == 0){
		for(i = 0;i < 8;i++){
			Temp_dat[i] = Temp_modle1_Arr[i];
		}
	}
	if(key_password == 1){
		for(i = 0;i < 8;i++){
			Temp_dat[i] = Temp_modle2_Arr[i];
		}
	}
}