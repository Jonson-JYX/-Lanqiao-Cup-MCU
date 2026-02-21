#include <stc15f2k60s2.h>
#include "PCF8591.h"

//电阻电压存储数组
unsigned char RB2_send[10];
//电阻电压转化数组
unsigned char RB2_dat[] = {'0','1','2','3','4','5','6','7','8','9'};

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

//串口发送字符函数
void uart_sendstring(unsigned char *str){
	unsigned char *dat;
	dat = str;
	while(*dat != '\0'){
		SBUF = *dat;
		while(TI == 0);
		TI = 0;
		dat++;
	}
}

//接收电压转化函数
void Send_RB2(){
	float RB2 = RB2_Value(); 
	unsigned int RB2_value = (unsigned int)(RB2 * 500);
	if(RB2_value >= 100){
		RB2_send[0] = 'U';
		RB2_send[1] = ':';
		RB2_send[2] = RB2_dat[RB2_value / 100];
		RB2_send[3] = '.';
		RB2_send[4] = RB2_dat[RB2_value % 100 / 10];
		RB2_send[5] = RB2_dat[RB2_value % 10];
		RB2_send[6] = 'V';
		RB2_send[7] = '\r';
		RB2_send[8] = '\n';
		RB2_send[9] = '\0';
	}
	if(RB2_value >= 10 && RB2_value < 100){
		RB2_send[0] = 'U';
		RB2_send[1] = ':';
		RB2_send[2] = RB2_dat[0];
		RB2_send[3] = '.';
		RB2_send[4] = RB2_dat[RB2_value / 10];
		RB2_send[5] = RB2_dat[RB2_value % 10];
		RB2_send[6] = 'V';
		RB2_send[7] = '\r';
		RB2_send[8] = '\n';
		RB2_send[9] = '\0';
	}
	if(RB2_value >= 0 && RB2_value < 10){
		RB2_send[0] = 'U';
		RB2_send[1] = ':';
		RB2_send[2] = RB2_dat[0];
		RB2_send[3] = '.';
		RB2_send[4] = RB2_dat[0];
		RB2_send[5] = RB2_dat[RB2_value % 10];
		RB2_send[6] = 'V';
		RB2_send[7] = '\r';
		RB2_send[8] = '\n';
		RB2_send[9] = '\0';
	}
	uart_sendstring(RB2_send);
}