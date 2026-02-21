#include <STC15F2K60S2.H>
#include "KEY.h"

unsigned char send_arr[5] = {'0'};

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
    unsigned char *ptr = str;
    while(*ptr != '\0'){
        SBUF = *ptr;
        while(TI == 0);
        TI = 0;
        ptr++;
    }
}

void Read_Uart(){
    send_arr[0] = (S4_flag ? 1 : 0) + '0';
    send_arr[1] = (S5_flag ? 1 : 0) + '0';
    send_arr[2] = (S8_flag ? 1 : 0) + '0';
    send_arr[3] = (S9_flag ? 1 : 0) + '0';
    send_arr[4] = '\0';
    Uart_Sendstring(send_arr);
}