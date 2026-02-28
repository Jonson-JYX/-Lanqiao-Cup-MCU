#include <STC15F2K60S2.H>

unsigned int Time_cnt = 0;
unsigned int NE555_cnt = 0;
unsigned int LED1_cnt = 0;
unsigned int LED2_cnt = 0;
bit LED1_flag = 0;
bit LED2_flag = 0;

void Timer1_Isr(void) interrupt 3
{
	Time_cnt++;
    NE555_cnt++;
    if(LED1_flag){
        LED1_cnt++;
    }
    if(LED2_flag){
        LED2_cnt++;
    }
}

void Timer1_Init(void)		//1毫秒@12.000MHz
{
	AUXR &= 0xBF;			//定时器时钟12T模式
	TMOD &= 0x0F;			//设置定时器模式
	TMOD |= 0x10;			//设置定时器模式
	TL1 = 0x18;				//设置定时初始值
	TH1 = 0xFC;				//设置定时初始值
	TF1 = 0;				//清除TF1标志
	TR1 = 1;				//定时器1开始计时
	ET1 = 1;				//使能定时器1中断
    EA = 1;
}
