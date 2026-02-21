#include <stc15f2k60s2.h>
#include "Common.h"
#include "Delay.h"
#include "DS1302.h"
#include "PCF8591.h"
#include "DS18B20.h"
#include "KEY.h"

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
	0xBF,	//-
	0xFF	//全灭
};

//时间界面存储数组
unsigned char Time_dat_arr[] = {12,12,11,12,12,11,12,12};
//数据界面存储数组
unsigned char Value_dat_arr[] = {12,12,12,12,12,12,12,12};
//查询界面存储数组
unsigned char Select_dat_arr[] = {10,12,12,12,12,12,12,12};
//数码管显示数组
unsigned char dat_arr[] = {12,12,12,12,12,12,12,12};

//时间界面转化函数
void Time_Change(){
	unsigned char *time = ReadRTC();
	Time_dat_arr[0] = time[0];
	Time_dat_arr[1] = time[1];
	Time_dat_arr[3] = time[2];
	Time_dat_arr[4] = time[3];
	Time_dat_arr[6] = time[4];
	Time_dat_arr[7] = time[5];
}

//数据界面转化函数
void Value_Change(){
	float lighting_value = Lighting_Value();
	float temp_value = Temp_Value();
	unsigned int light_dat = (unsigned int)(lighting_value * 500);
	unsigned int temp_dat = (unsigned int)(temp_value * 100);
	//处理光敏数据
	if(light_dat >= 100){
		Value_dat_arr[0] = light_dat / 100;
		Value_dat_arr[1] = light_dat % 100 /10;
		Value_dat_arr[2] = light_dat % 10;
	}
	else if(light_dat < 100 && light_dat >= 10){
		Value_dat_arr[0] = 0;
		Value_dat_arr[1] = light_dat /10;
		Value_dat_arr[2] = light_dat % 10;
	}
	else if(light_dat < 10 && light_dat >= 0){
		Value_dat_arr[0] = 0;
		Value_dat_arr[1] = 0;
		Value_dat_arr[2] = light_dat % 10;
	}
	
	//处理温度数据
	if(temp_dat >= 1000){
		Value_dat_arr[4] = temp_dat / 1000;
		Value_dat_arr[5] = temp_dat % 1000 / 100;
		Value_dat_arr[6] = temp_dat % 100 / 10;
		Value_dat_arr[7] = temp_dat % 10;
	}
	else if(temp_dat >= 100 && temp_dat < 1000){
		Value_dat_arr[4] = 12;
		Value_dat_arr[5] = temp_dat / 100;
		Value_dat_arr[6] = temp_dat % 100 / 10;
		Value_dat_arr[7] = temp_dat % 10;
	}
	else if(temp_dat >= 10 && temp_dat < 100){
		Value_dat_arr[4] = 12;
		Value_dat_arr[5] = 0;
		Value_dat_arr[6] = temp_dat / 10;
		Value_dat_arr[7] = temp_dat % 10;
	}
	else if(temp_dat >= 0 && temp_dat < 10){
		Value_dat_arr[4] = 12;
		Value_dat_arr[5] = 0;
		Value_dat_arr[6] = 0;
		Value_dat_arr[7] = temp_dat % 10;
	}
}

//查询界面转化函数
void Select_Change(){
	unsigned char *time = ReadRTC();
	float lighting_value = Lighting_Value();
	float temp_value = Temp_Value();
	unsigned int light_dat = (unsigned int)(lighting_value * 50);
	unsigned int temp_dat = (unsigned int)(temp_value * 10);
	if((time[4] == 0 && time[5] == 0) || S8_password == 1){
		if(light_dat >= 10 && light_dat < 100){
			Select_dat_arr[2] = light_dat / 10;
			Select_dat_arr[3] = light_dat % 10;
		}
		else if(light_dat >= 0 && light_dat < 10){
			Select_dat_arr[2] = 0;
			Select_dat_arr[3] = light_dat % 10;
		}
		if(temp_dat >= 100 && temp_dat < 1000){
			Select_dat_arr[5] = temp_dat / 100;
			Select_dat_arr[6] = temp_dat % 100 / 10;
			Select_dat_arr[7] = temp_dat % 10;
		}
		else if(temp_dat >= 10 && temp_dat < 100){
			Select_dat_arr[5] = 12;
			Select_dat_arr[6] = temp_dat / 10;
			Select_dat_arr[7] = temp_dat % 10;
		}
		else if(temp_dat >= 0 && temp_dat < 10){
			Select_dat_arr[5] = 12;
			Select_dat_arr[6] = 0;
			Select_dat_arr[7] = temp_dat % 10;
		}
		if(S8_password == 1){
			S8_password = 0;
		}
	}
}

//数码管筛选函数
void LED_Display_Choose(){
	unsigned char i;
	if(S4_cnt % 3 == 1){
		for(i = 0 ;i < 8;i++){
			dat_arr[i] = Time_dat_arr[i];
		}
	}
	if(S4_cnt % 3 == 2){
		for(i = 0 ;i < 8;i++){
			dat_arr[i] = Value_dat_arr[i];
		}
	}
	if(S4_cnt % 3 == 0){
		for(i = 0 ;i < 8;i++){
			dat_arr[i] = Select_dat_arr[i];
		}
	}
}

//数码管显示函数
void LED_Display_Show(){
	unsigned char i;
	unsigned char dat;
	for(i = 0;i < 8;i++){
		SEG(0xFF);
		COM(1<<i);
		dat = SEG_Table[dat_arr[i]];
		if(S4_cnt % 3 == 2){
			if(i == 0 || i == 5){
				dat = dat & 0x7F;
			}
		}
		if(S4_cnt % 3 == 0){
			if(i == 2 || i == 6){
				dat = dat & 0x7F;
			}
		}
		SEG(dat);
		Delay50us();
	}
	SEG(0xFF);
	COM(0xFF);
}