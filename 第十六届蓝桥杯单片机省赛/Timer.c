#include <STC15F2K60S2.H>

unsigned int temp_cnt = 0;    //温度计数值
unsigned int light_cnt = 0;   //光照计数值
unsigned int sound_cnt = 0;   //声音计数值
unsigned int sound_status1_cnt = 0;   //声音状态1计数值
unsigned int sound_status2_cnt = 0;   //声音状态2计数值 
unsigned int sound_status3_cnt = 0;   //声音状态3计数值
unsigned int LED_cnt = 0;     //LED计数值
bit LED_flag = 0;             //LED标志位
bit sound_status1_flag = 0;       //声音状态1标志位
bit sound_status2_flag = 0;       //声音状态2标志位
bit sound_status3_flag = 0;       //声音状态3标志位

void Timer0_Isr(void) interrupt 1
{
    temp_cnt++;
    light_cnt++;
    sound_cnt++;
    if(LED_flag){
        LED_cnt++;
    }
    if(sound_status1_flag){
        sound_status1_cnt++;
    }
    if(sound_status2_flag){
        sound_status2_cnt++;
    }
    if(sound_status3_flag){
        sound_status3_cnt++;
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
    EA = 1;				    //总中断使能
}
