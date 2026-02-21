#include <stc15f2k60s2.h>
#include "DS18B20.h"

//温度发送数组
unsigned char temp_send [12];
unsigned char temp_dat[] = {'0','1','2','3','4','5','6','7','8','9'};

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

//串口发送字符串函数
void uart_sendstring(unsigned char *str){
	unsigned char *p;
	p = str;
	while(*p != '\0'){
		SBUF = *p;
		while(TI == 0);
		TI = 0;
		p++;
	}
}

//接收温度转化函数
void Send_Temp(){
	float temp = Temp_Value();
	unsigned int temp_value = (unsigned int)(temp * 100);
	temp_send [0] = 'T';
	temp_send [1] = 'e';
	temp_send [2] = 'm';
	temp_send [3] = 'p';
	temp_send [4] = ':';
	temp_send [5] = temp_dat[temp_value / 1000];
	temp_send [6] = temp_dat[temp_value % 1000 / 100];
	temp_send [7] = '.';
	temp_send [8] = temp_dat[temp_value % 100 / 10];
	temp_send [9] = temp_dat[temp_value % 10];
	temp_send [10] = 'C';
	temp_send [11] = '\0';
	uart_sendstring(temp_send);
}