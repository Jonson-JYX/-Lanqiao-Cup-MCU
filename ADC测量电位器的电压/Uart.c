#include <stc15f2k60s2.h>

bit recv_flag = 0;
unsigned int recv_cnt = 0;
unsigned char recv_dat[5];

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
		if(recv_cnt < 5){
			recv_dat[recv_cnt] = SBUF;
			recv_cnt++;
			if(recv_cnt == 5){
				recv_flag = 1;
				recv_cnt = 0;
			}
		}
	}
}

unsigned char *Recv_dat_arr(){
	if(recv_flag){
		return recv_dat;
	}
}