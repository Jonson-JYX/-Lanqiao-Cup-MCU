#include <STC15F2K60S2.H>
#include "PCF8591.h"

unsigned char send_dat[10] = {0};

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

void Uart_Sendstring(unsigned char *str){
    unsigned char *p = str;
    while(*p != '\0'){
        SBUF = *p;
        while(TI == 0);
        TI = 0;
        p++;
    }
}

void Uart_send_dat(){
    send_dat[0] = 'U';
    send_dat[1] = ':';
    send_dat[2] = Vol_value1 / 100 + '0';
    send_dat[3] = '.';
    send_dat[4] = Vol_value1 % 100 / 10 + '0';
    send_dat[5] = Vol_value1 % 10 + '0';
    send_dat[6] = 'V';
    send_dat[7] = '\r';
    send_dat[8] = '\n';
    send_dat[9] = '\0';
    Uart_Sendstring(send_dat);
}