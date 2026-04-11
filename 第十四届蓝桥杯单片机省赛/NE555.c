#include <STC15F2K60S2.H>
#include "Timer.h"

unsigned int NE555_value = 0;
unsigned int NE555_max = 0;
unsigned int xdata NE555_Average = 0;
unsigned int xdata NE555_num = 0;
unsigned int xdata NE555_sum = 0;

void Timer0_Init(void)		//1毫秒@12.000MHz
{
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x05;			//设置定时器模式
	TL0 = 0x00;				//设置定时初始值
	TH0 = 0x00;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
}

void NE555_login(){
    unsigned int value = 0;
    if(NE555_flag && Collect_Flag == 0){
        value = (TH0 << 8) | TL0;
        TH0 = 0;
        TL0 = 0;
        if(value <= 200){
            NE555_value = 100;
        }
        else if(value >= 2000){
            NE555_value = 900;
        }
        else{
            NE555_value = (4.0 / 9.0) * value + (100.0 / 9.0);
        }
        if(NE555_max < NE555_value){
            NE555_max = NE555_value;
        }
        NE555_sum += NE555_value;
        NE555_num++;
        NE555_Average = NE555_sum / NE555_num / 10;
        NE555_cnt = 0;
        NE555_flag = 0;
    }
}