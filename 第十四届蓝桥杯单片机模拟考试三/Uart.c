#include <STC15F2K60S2.H>
#include "DS18B20.h"
#include "PCF8591.h"
#include "KEY.h"
#include "Timer.h"

unsigned char Send_Over[6] = {'0'};
unsigned char Send_Temp[7] = {'0'};
unsigned char Send_ADC[10] = {'0'};
unsigned char Recv_dat[10];
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
        Recv_dat[recv_cnt] = SBUF;
        if((Recv_dat[recv_cnt] == '\n' || (recv_cnt == 0 && (Recv_dat[recv_cnt] == '1' || Recv_dat[recv_cnt] == '2'))) && S4_flag == 1){
            recv_flag = 1;
            recv_cnt = 0;
        }
        else{
            recv_cnt++;
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
    unsigned char *ptr;
    ptr = str;
    while(*ptr != '\0'){
        SBUF = *ptr;
        while(TI == 0);
        TI = 0;
        ptr++;
    }
}

void Send_Over_login(){
    Send_Over[0] = 'O';
    Send_Over[1] = 'v';
    Send_Over[2] = 'e';
    Send_Over[3] = 'r';
    Send_Over[4] = '!';
    Send_Over[5] = '\0';
    Uart_Sendstring(Send_Over);
}

void Send_Temp_login(){
    Send_Temp[0] = 'C';
    Send_Temp[1] = ':';
    Send_Temp[2] = Temp_value / 100 + '0';
    Send_Temp[3] = Temp_value % 100 / 10 + '0';
    Send_Temp[4] = '.';
    Send_Temp[5] = Temp_value % 10 + '0';
    Send_Temp[6] = '\0';
    Uart_Sendstring(Send_Temp);
}

void Send_ADC_login(){
    Send_ADC[0] = 'D';
    Send_ADC[1] = ':';
    Send_ADC[2] = ADC_value / 100 + '0';
    Send_ADC[3] = '.';
    Send_ADC[4] = ADC_value % 100 / 10 + '0';
    Send_ADC[5] = ADC_value % 10 + '0';
    Send_ADC[6] = 'p';
    Send_ADC[7] = 'p';
    Send_ADC[8] = 'm';
    Send_ADC[9] = '\0';
    Uart_Sendstring(Send_ADC);
}

void Recv_login(){
    if(recv_flag){
        recv_flag = 0;
        if(Recv_dat[0] == '1'){
            Send_Temp_login();
        }
        else if(Recv_dat[0] == '2'){
            Send_ADC_login();
        }
        else{
            if(Uart_flag == 0){
                Uart_flag = 1;
                Uart_cnt = 0; 
            }
        }
    }
    if(Uart_flag && Uart_cnt >= 3000){
        Uart_cnt = 0;
        Uart_flag = 0;
        Send_Over_login();
    }
}