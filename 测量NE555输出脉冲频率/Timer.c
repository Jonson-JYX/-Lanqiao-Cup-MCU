#include <STC15F2K60S2.H>
#include "NE555.h"

unsigned int NE555_cnt = 0;
unsigned int time_cnt = 0;
unsigned int LED1_cnt = 0;
unsigned int LED2_cnt = 0;
bit LED1_flag = 0;
bit LED2_flag = 0;

void Timer1_Isr(void) interrupt 3
{
    if(++NE555_cnt == 1000){
        NE555_cnt = 0;
        NE555_value = (TH0 << 8) | TL0;
        TH0 = 0;
        TL0 = 0;
    }
    if(++LED1_cnt == 200){
        LED1_cnt = 0;
        LED1_flag = !LED1_flag;
    }
    if(++LED2_cnt == 200){
        LED2_cnt = 0;
        LED2_flag = !LED2_flag;
    }
}

void Timer1_Init(void)		//1毫秒@12.000MHz
{
	AUXR &= 0xBF;			//定时器时钟12T模式
	TMOD &= 0x0F;			//设置定时器模式
	TL1 = 0x18;				//设置定时初始值
	TH1 = 0xFC;				//设置定时初始值
	TF1 = 0;				//清除TF1标志
	TR1 = 1;				//定时器1开始计时
	ET1 = 1;				//使能定时器1中断
    EA = 1;
}
