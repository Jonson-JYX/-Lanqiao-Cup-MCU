#include <STC15F2K60S2.H>

int LED_cnt = 0;
bit LED1 = 1;
bit LED2 = 0;
bit LED8 = 0;  // L8初始熄灭

void Timer_Isr(void) interrupt 1
{
    LED_cnt++;
    // 100ms（0.1秒）：切换L8状态
    if(LED_cnt % 100 == 0){
        LED8 = ~LED8;  // 取反切换亮灭
    }
    // 1000ms（1秒）：切换L1/L2状态
    if(LED_cnt == 1000){
        LED_cnt = 0;   // 重置计数器
        // L1亮 → 切L2亮；L2亮 → 切L1亮
        if(LED1 == 1){
            LED1 = 0;
            LED2 = 1;
        }else{
            LED1 = 1;
            LED2 = 0;
        }
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
    EA = 1;					//开启总中断
}