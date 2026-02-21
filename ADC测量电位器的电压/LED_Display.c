#include <stc15f2k60s2.h>
#include "LED.h"
#include "Delay.h"
#include "PCF8591.h"
#include "IIC.h"
#include "Uart.h"
#include "Common.h"

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
	0xC1	//U
};

//RB2存储数组1
unsigned char RB2_dat_arr1[] = {11,10,10,10,10,10,10,10};
//RB2存储数组2
unsigned char RB2_dat_arr2[] = {11,10,10,10,10,10,10,10};
//RB2存储数组3
unsigned char RB2_dat_arr3[] = {11,10,10,10,10,10,10,10};
//RB2显示数组
unsigned char RB2_dat[] = {11,10,10,10,10,10,10,10};
//数码管显示选择变量
unsigned char LED_Display_flag = 0;

//RB2存储数组1转化函数
void RB2_arr1_Change(){
	float RB2_value = RB2_Value();
	unsigned int RB2 = (unsigned int)(RB2_value * 50);
	unsigned char i;
	if(RB2 >= 10){
		RB2_dat_arr1[6] = RB2 / 10;
		RB2_dat_arr1[7] = RB2 % 10;
	}
	else if(RB2 < 10 && RB2 >= 0){
		RB2_dat_arr1[6] = 0;
		RB2_dat_arr1[7] = RB2 % 10;
	}
	for(i = 0;i < 8;i++){
		RB2_dat[i] = RB2_dat_arr1[i];
	}
}

//RB2存储数组2转化函数
void RB2_arr2_Change(){
	float RB2_value = RB2_Value();
	unsigned int RB2 = (unsigned int)(RB2_value * 500);
	unsigned char i;
	if(RB2 >= 100){
		RB2_dat_arr2[5] = RB2 / 100;
		RB2_dat_arr2[6] = RB2 % 100 / 10;
		RB2_dat_arr2[7] = RB2 % 10;
	}
	else if(RB2 < 100 && RB2 >= 10){
		RB2_dat_arr2[5] = 0;
		RB2_dat_arr2[6] = RB2 / 10;
		RB2_dat_arr2[7] = RB2 % 10;
	}
	else if(RB2 < 10 && RB2 >= 0){
		RB2_dat_arr2[5] = 0;
		RB2_dat_arr2[6] = 0;
		RB2_dat_arr2[7] = RB2 % 10;
	}
	for(i = 0;i < 8;i++){
		RB2_dat[i] = RB2_dat_arr2[i];
	}
}

//RB2存储数组3转化函数
void RB2_arr3_Change(){
	float RB2_value = RB2_Value();
	unsigned int RB2 = (unsigned int)(RB2_value * 5);
	unsigned char i;
	RB2_dat_arr3[7] = RB2;
	for(i = 0;i < 8;i++){
		RB2_dat[i] = RB2_dat_arr3[i];
	}
}

//串口数据处理函数
unsigned char Uart_Choose(){
	unsigned char *recv_dat = Recv_dat_arr();
	unsigned char i;
	unsigned char dat = 3;
	for(i = 0;i < 6;i++){
		if(recv_dat[i] == 'a' || recv_dat[i] == 'A'){
			dat = 1;
			break;
		}
		if(recv_dat[i] == '1' || recv_dat[i] == '#'){
			dat = 2;
			break;
		}
	}
	return dat;
}

//数码管显示选择数组
void LED_Display_Choose(){
	if(LED_Display_flag == 1){
		RB2_arr1_Change();
		LED(LED_Table[0]);
	}	
	if(LED_Display_flag == 2){
		RB2_arr2_Change();
		LED(LED_Table[1]);
	}		
	if(LED_Display_flag == 3){
		RB2_arr3_Change();
		LED(LED_Table[2]);
	}	
}

//数码管显示数组
void LED_Display_Show(){
	unsigned char com;
	unsigned char dat;
	for(com = 0;com < 8;com++){
		SEG(0xFF);
		COM(1<<com);
		dat = SEG_Table[RB2_dat[com]];
		if(LED_Display_flag == 1 && com == 6){
			dat = dat & 0x7F;
		}
		if(LED_Display_flag == 2 && com == 5){
			dat = dat & 0x7F;
		}
		SEG(dat);
		Delay50us();
	}
	COM(0xFF);
	SEG(0xFF);
}