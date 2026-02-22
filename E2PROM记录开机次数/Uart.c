#include <STC15F2K60S2.H>
#include "EEPROM.h"
#include "KEY.h"

unsigned char Send_value[9] = {'0'};

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
}

void Uart_Sendstring(unsigned char *dat){
    unsigned char *ptr;
    ptr = dat;
    while(*ptr != 0){
        SBUF = *ptr;
        while(TI == 0);
        TI = 0;
        ptr++;
    }
}

void Send_EEPROM(){
    Send_value[0] = 'N';
    Send_value[1] = 'u';
    Send_value[2] = 'm';
    Send_value[3] = 'b';
    Send_value[4] = 'e';
    Send_value[5] = 'r';
    Send_value[6] = ':';
    Send_value[7] = num + '0';
    Send_value[8] = '\0';
    Uart_Sendstring(Send_value);
}