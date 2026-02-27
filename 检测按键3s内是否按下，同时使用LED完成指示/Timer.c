#include <STC15F2K60S2.H>

// 初始化各计时变量和标志位
unsigned int L1_cnt = 0;
bit L1_flag = 0;
unsigned int L2_cnt = 0;
bit L2_flag = 0;
unsigned int L4_cnt = 0;
bit L4_flag = 0;
unsigned int L5_cnt = 0;
bit L5_flag = 0;
unsigned int blink4_cnt = 0;
unsigned int blink5_cnt = 0;

void Timer0_Isr(void) interrupt 1
{
    // 定时器0为1ms中断，所有计时基于1ms累加
    // L1：3秒计时
    if(L1_flag){
        L1_cnt++;
        if(L1_cnt >= 3000){ // 3000ms=3秒
            L1_flag = 0;
            L1_cnt = 0;
        }
    }
    // L2：3秒计时
    if(L2_flag){
        L2_cnt++;
        if(L2_cnt >= 3000){
            L2_flag = 0;
            L2_cnt = 0;
        }
    }
    // L4：3秒计时 + 0.1秒闪烁计时
    if(L4_flag){
        L4_cnt++;
        blink4_cnt++;
        if(L4_cnt >= 3000){
            L4_flag = 0;
            L4_cnt = 0;
            blink4_cnt = 0;
        }
    }
    // L5：3秒计时 + 0.1秒闪烁计时
    if(L5_flag){
        L5_cnt++;
        blink5_cnt++;
        if(L5_cnt >= 3000){
            L5_flag = 0;
            L5_cnt = 0;
            blink5_cnt = 0;
        }
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
    EA = 1;                 // 开总中断
}