#include <stc15f2k60s2.h>
#define BAUD         9600   // 串口波特率
#define SYSTEMCLOCK  12000000L  // 系统时钟频率

unsigned char rx_buf[1] = {0};    
unsigned char rx_cnt = 0;         // 接收字符计数
bit rx_complete_flag = 0;         // 接收完成标志


// 系统初始化函数
void system_init(void)
{
    // 串口初始化
    SCON = 0x50;          // 8位数据,可变波特率,REN=1允许接收
    AUXR = 0x40;          // 定时器1使用1T模式(STC15专属)
    TMOD = 0x00;          // 定时器1为16位自动重装模式
    // 计算定时器1初值(9600波特率)
    TL1 = (65536 - (SYSTEMCLOCK / 4 / BAUD));
    TH1 = (65536 - (SYSTEMCLOCK / 4 / BAUD)) >> 8;
    TR1 = 1;              // 启动定时器1
    ES = 1;               // 使能串口中断
    EA = 1;               // 使能总中断
}


// 串口发送字符串
void uart_sendstring(unsigned char *str)
{
    unsigned char *p = str;
    while(*p != '\0')  // 遍历字符串直到结束符
    {
        SBUF = *p;     // 写入当前字符到发送寄存器
        while(TI == 0); // 等待发送完成
        TI = 0;        // 清发送中断标志
        p++;           // 指向下一个字符
    }
}

void isr_uart(void) interrupt 4
{
    if(RI)
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
    // 增加发送中断标志清零，避免干扰
    if(TI)
    {
        TI = 0;
    }
}

unsigned char *Arr_Value(){
    if(rx_complete_flag)
    {
        return rx_buf;  // 接收完成返回缓冲区地址
    }
}
	



