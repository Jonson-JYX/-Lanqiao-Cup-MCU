#include <stc15f2k60s2.h>
#include "Uart.h"
#include "DS1302.h"

#define BAUD	     9600  //波特率
#define SYSTEMCLOCK  12000000L  //系统时钟频率
unsigned char time_send[14];

void Uart_Init(void)	//9600bps@12.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器时钟1T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xC7;			//设置定时初始值
	TH1 = 0xFE;			//设置定时初始值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
}

//通过串口发送字符串
void uart_sendstring(unsigned char *str)
{
    unsigned char *p;
    p = str;
    while(*p != '\0')
    {
        SBUF = *p;
        while(TI == 0);  //等待发送标志位置位
        TI = 0;
        p++;
    }
}

//接收时间转化函数
void Send_Time(){
	unsigned char *p_rtc = ReadRTC();
	unsigned char dat[8];
	unsigned char i;
	for(i = 0;i < 8;i++){
		dat[i] = p_rtc[i];
	}
	time_send[0] = 'T';
    time_send[1] = 'i';
    time_send[2] = 'm';
    time_send[3] = 'e';
    time_send[4] = ':';
    // 小时
    time_send[5] = (p_rtc[0] * 10) / 10 + '0'; // 小时十位
    time_send[6] = (p_rtc[1] % 10) + '0';      // 小时个位
    time_send[7] = ':';
    // 分钟
    time_send[8] = (p_rtc[3] * 10) / 10 + '0'; // 分钟十位
    time_send[9] = (p_rtc[4] % 10) + '0';      // 分钟个位
    time_send[10] = ':';
    // 秒
    time_send[11] = (p_rtc[6] * 10) / 10 + '0'; // 秒十位
    time_send[12] = (p_rtc[7] % 10) + '0';      // 秒个位
    time_send[13] = '\0'; // 字符串结束符
    
	uart_sendstring(time_send);
}
