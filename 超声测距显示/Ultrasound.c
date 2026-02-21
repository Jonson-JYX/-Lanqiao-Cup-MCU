#include <stc15f2k60s2.h>
#include "Delay.h"
sbit TX = P1^0;
sbit RX = P1^1;

unsigned char time = 0;
void Timer_Isr(void) interrupt 1
{
	if(++time == 200){
		time = 0;
	}
}

void Timer_Init(void)		//1毫秒@12.000MHz
{
	AUXR |= 0x80;			//定时器时钟1T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0x20;				//设置定时初始值
	TH0 = 0xD1;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断
	EA = 1;
}

//超声波测距
unsigned char Uitrasound_Value(){
	unsigned int time_dat = 0;
	unsigned char i;
	CMOD = 0x01;
	CCON = 0x00;
	CH = 0x00;
	CL = 0x00;
	for(i = 0;i < 8;i++){
		TX = 1;
		Delay12us();
		TX = 0;
		Delay12us();
	}
	CR = 1;
	while((RX == 1) && (CH <= 0x40));
	CR = 0;
	if(CH > 0x40){
		CF = 0;
		return 0;
	}
	time_dat = (CH<<8) | CL;
	return time_dat * 0.0172 + 2;
}