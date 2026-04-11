#include <stc15f2k60s2.h>
#include "KEY.h"


unsigned int timer_cnt = 0;  // 10ms计数器

void Timer0_Isr(void) interrupt 1
{
	timer_cnt++;
	if(timer_cnt >= 10)
	{
		timer_cnt = 0;
		KEY_Scan();
	}
}

void Timer0_Init(void)		//1毫秒@12.000MHz
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