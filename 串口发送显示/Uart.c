#include <stc15f2k60s2.h>

unsigned char rx_buf[1] = {0};    
unsigned char rx_cnt = 0;         // 接收字符计数
bit rx_complete_flag = 0;         // 接收完成标志

void Uart1_Init(void)	//9600bps@12.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器时钟1T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xC7;			//设置定时初始值
	TH1 = 0xFE;			//设置定时初始值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
	ES = 1;				//使能串口1中断
	EA = 1;
}

void Uart_Isr(void) interrupt 4
{
	if (TI)				//检测串口1发送中断
	{
		TI = 0;			//清除串口1发送中断请求位
	}
	if (RI)				//检测串口1接收中断
	{
		 RI = 0;  // 清接收中断标志
        if(rx_cnt < 1)  // 只接收1个字符
        {
            rx_buf[rx_cnt] = SBUF;  // 存储接收字符
            rx_cnt++;               // 计数+1
            if(rx_cnt == 1)         // 1个字符接收完成 
            {
                rx_complete_flag = 1;    // 置接收完成标志
            }
        }
        else
        {
            // 超出1个字符，重置缓冲区
            rx_cnt = 0;
            rx_buf[0] = 0;  
        }
	}
}

unsigned char *Arr_Value(){
	if(rx_complete_flag)
    {
        return rx_buf;  // 接收完成返回缓冲区地址
    }
}