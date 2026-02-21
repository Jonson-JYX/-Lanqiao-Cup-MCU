#include <stc15f2k60s2.h>

unsigned char recv_dat[8];
unsigned char rece_cnt = 0;
bit rece_flag = 0;

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
		RI = 0;			//清除串口1接收中断请求位
		if(rece_cnt < 8){
			recv_dat[rece_cnt] = SBUF;
			rece_cnt++;
			if(rece_cnt == 8){
				rece_flag = 1;
				rece_cnt = 0;
			}
		}
	}
}

unsigned char *Arr_Value(){
	if(rece_flag){
		return recv_dat;
	}
}