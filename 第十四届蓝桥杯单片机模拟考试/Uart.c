#include <STC15F2K60S2.H>
#include "Distance.h"

unsigned char send_dat1[13] = {0};
unsigned char send_dat2[14] = {0};
unsigned char send_dat3[15] = {0};

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
        SBUF = *p; //发送一个字节
        while(TI == 0); //等待发送完成
        TI = 0; //清除发送完成标志
        p++; 
    }
}

void Uart_Send_dat(){
    if(sound_dat >= 0 && sound_dat < 10){
        send_dat1[0] = 'D'; 
        send_dat1[1] = 'i';
        send_dat1[2] = 's';
        send_dat1[3] = 't';  
        send_dat1[4] = 'a';
        send_dat1[5] = 'n';
        send_dat1[6] = 'c';
        send_dat1[7] = 'e';
        send_dat1[8] = ':';
        send_dat1[9] = sound_dat + '0'; 
        send_dat1[10] = 'c';
        send_dat1[11] = 'm';
        send_dat1[12] = '\0'; //字符串结束标志
        Uart_Sendstring(send_dat1); //发送字符串
    }
    if(sound_dat >= 10 && sound_dat < 100){
        send_dat2[0] = 'D'; 
        send_dat2[1] = 'i';
        send_dat2[2] = 's';
        send_dat2[3] = 't';  
        send_dat2[4] = 'a';
        send_dat2[5] = 'n';
        send_dat2[6] = 'c';
        send_dat2[7] = 'e';
        send_dat2[8] = ':';
        send_dat2[9] = (sound_dat / 10) + '0'; //十位
        send_dat2[10] = (sound_dat % 10) + '0'; //个位
        send_dat2[11] = 'c';     
        send_dat2[12] = 'm';
        send_dat2[13] = '\0'; //字符串结束标志
        Uart_Sendstring(send_dat2); //发送字符串
    }
    if(sound_dat >= 100){
        send_dat3[0] = 'D'; 
        send_dat3[1] = 'i';
        send_dat3[2] = 's';
        send_dat3[3] = 't';  
        send_dat3[4] = 'a';
        send_dat3[5] = 'n';
        send_dat3[6] = 'c';
        send_dat3[7] = 'e';
        send_dat3[8] = ':';
        send_dat3[9] = (sound_dat / 100) + '0'; //百位
        send_dat3[10] = ((sound_dat % 100) / 10) + '0'; //十位
        send_dat3[11] = (sound_dat % 10) + '0'; //个位
        send_dat3[12] = 'c';     
        send_dat3[13] = 'm';
        send_dat3[14] = '\0'; //字符串结束标志
        Uart_Sendstring(send_dat3); //发送字符串
    }
}