#include <STC15F2K60S2.H>
#include "Timer.h"

int NE555_value = 0;
int NE555_Hyperparameter = 2000;    //超限
int NE555_Calibration = 0;          //校准
int NE555_now = 0;
int NE555_max = 0;

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
    if(NE555_cnt >= 1000){
        NE555_value = (TH0 << 8) | TL0;
		NE555_now = NE555_value + NE555_Calibration;
        NE555_cnt = 0;
        TL0 = 0;
        TH0 = 0;
    }
}