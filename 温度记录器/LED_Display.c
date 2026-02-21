#include <stc15f2k60s2.h>
#include "Delay.h"
#include "Common.h"
#include "DS18B20.h"

//数码管段码表
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
	0xFF,	//全灭
};

//记录当前温度
unsigned char Temp_Now = 0;
//记录最小温度
unsigned char Temp_Min = 99;
//记录最大温度
unsigned char Temp_Max = 0;

//温度临时存储数组
unsigned char Temp_Value_Arr[] = {10,10,10,10,10,10,10,10};
//温度显示数组
unsigned char Temp_Dat_Arr[] = {10,10,10,10,10,10,10,10};

//温度转化函数
void Temp_Change(){
	float temp = Temp_Value();
	unsigned int temp_value = (unsigned int)(temp);
	unsigned char i;
	if(temp_value > Temp_Max){
		Temp_Max = temp_value;
	}
	if(temp_value < Temp_Min){
		Temp_Min = temp_value;
	}
	if(temp_value >= 10){
		Temp_Value_Arr[0] = temp_value / 10;
		Temp_Value_Arr[1] = temp_value % 10;
	}
	if(temp_value < 10){
		Temp_Value_Arr[0] = 10;
		Temp_Value_Arr[1] = temp_value % 10;
	}
	if(Temp_Min >= 10){
		Temp_Value_Arr[3] = Temp_Min / 10;
		Temp_Value_Arr[4] = Temp_Min % 10;
	}
	if(Temp_Min < 10){
		Temp_Value_Arr[3] = 10;
		Temp_Value_Arr[4] = Temp_Min % 10;
	}
	if(Temp_Max >= 10){
		Temp_Value_Arr[6] = Temp_Max / 10;
		Temp_Value_Arr[7] = Temp_Max % 10;
	}
	if(Temp_Max < 10){
		Temp_Value_Arr[6] = 10;
		Temp_Value_Arr[7] = Temp_Max % 10;
	}
	
	for(i = 0;i < 8;i++){
		Temp_Dat_Arr[i] = Temp_Value_Arr[i];
	}
}

//数码管显示函数
void LED_Display_Show(){
	unsigned char i;
	unsigned char com;
	unsigned char dat;
	
	for(i = 0;i < 8;i++){
		SEG(0xFF);
		COM(0xFF);
		COM(1<<com);
		dat = SEG_Table[Temp_Dat_Arr[i]];
		SEG(dat);
		com++;
		Delay10us();
		Delay10us();
		Delay10us();
		Delay10us();
		Delay10us();
		Delay10us();
		Delay10us();
	}
	com = 0;
	SEG(0xFF);
	COM(0xFF);
}
