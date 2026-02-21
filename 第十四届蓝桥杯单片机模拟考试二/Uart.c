#include <STC15F2K60S2.H>
#include "PCF8591.h"
#include "DS18B20.h"
#include "KEY.h"

unsigned char Send_Temp[11] = {'0'};
unsigned char Send_Voltage[14] = {'0'};
unsigned char Recv_dat[1] = {'0'};
unsigned char recv_value = 'A';
unsigned char recv_cnt = 0;
bit recv_flag = 0;

void Uart1_Isr(void) interrupt 4
{
	if (TI)				//检测串口1发送中断
	{
		TI = 0;			//清除串口1发送中断请求位
	}
	if (RI)				//检测串口1接收中断
	{
		RI = 0;			//清除串口1接收中断请求位
        if(recv_cnt < 1 && password == 0){
            Recv_dat[recv_cnt] = SBUF;
            recv_cnt++;
            if(recv_cnt == 1){
                recv_flag = 1;
                recv_cnt = 0;
            }
        }
	}
}

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

void Uart_Sendstring(unsigned char *str){
    unsigned char *dat;
    dat = str;
    while(*dat != '\0'){
        SBUF = *dat;
        while(TI == 0);
        TI = 0;
        dat++;
    }
}

void Send_Temp_login(){
    Send_Temp[0] = 'T';
    Send_Temp[1] = 'E';
    Send_Temp[2] = 'M';
    Send_Temp[3] = 'P';
    Send_Temp[4] = ':';
    Send_Temp[5] = temp_value / 100 + '0';
    Send_Temp[6] = temp_value % 100 / 10 + '0';
    Send_Temp[7] = '.';
    Send_Temp[8] = temp_value % 10 + '0';
    Send_Temp[9] = 'C';
    Send_Temp[10] = '\0';
    Uart_Sendstring(Send_Temp);
}

void Send_Voltage_login(){
    Send_Voltage[0] = 'V';
    Send_Voltage[1] = 'o';
    Send_Voltage[2] = 'l';
    Send_Voltage[3] = 't';
    Send_Voltage[4] = 'a';
    Send_Voltage[5] = 'g';
    Send_Voltage[6] = 'e';
    Send_Voltage[7] = ':';
    Send_Voltage[8] = ADC_value / 100 + '0';
    Send_Voltage[9] = '.';
    Send_Voltage[10] = ADC_value % 100 / 10 + '0';
    Send_Voltage[11] = ADC_value % 10 + '0';
    Send_Voltage[12] = 'V';
    Send_Voltage[13] = '\0';
    Uart_Sendstring(Send_Voltage);
}

void Recv_login(){
    if(recv_flag){
        recv_value = Recv_dat[0];
    }
}