#include <STC15F2K60S2.H>

unsigned int Sound_cnt = 0;   //声音测量计数器
unsigned int Temp_cnt = 0;    //温度测量计数器
unsigned int RB2_cnt = 0;     //RB2测量计数器
unsigned int Time_cnt = 0;    //时间计数器
unsigned int NE555_cnt = 0;   //NE555测量计数器
unsigned int Tank_cnt = 0;    //容器测量计数器

void Timer1_Isr(void) interrupt 3{
	Sound_cnt++;   //声音测量计数器加1
    Temp_cnt++;    //温度测量计数器加1
    RB2_cnt++;     //RB2测量计数器加1
    Time_cnt++;    //时间计数器加1
    NE555_cnt++;   //NE555测量计数器加1
	Tank_cnt++;    //容器测量计数器加1
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
    EA = 1;					//使能全局中断
}
