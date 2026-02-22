#include <STC15F2K60S2.H>

unsigned int S8_cnt = 0;
unsigned int LED_cnt = 0;
unsigned int DAC_cnt = 0;
bit S8_flag = 0;
bit LED_flag = 0;

void Timer0_Isr(void) interrupt 1
{
    if(S8_flag){
        S8_cnt++;
    }
    if(LED_flag){
        LED_cnt++;
    }
	DAC_cnt++;
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
