#include <stc15f2k60s2.h>
#include "Uart.h"
#include "DS1302.h"
#include "KEY.h"

#define BAUD	     9600  //波特率
#define SYSTEMCLOCK  12000000L  //系统时钟频率

unsigned char time_send_Hour[8] = {0};
unsigned char time_send_Minute[10] = {0};
unsigned char time_send_Second[10] = {0};

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

//通过串口发送字符串
void uart_sendstring(unsigned char *str)
{
    unsigned char *p;
    p = str;
    while(*p != '\0')
    {
        SBUF = *p;
        while(TI == 0);  //等待发送标志位置位
        TI = 0;
        p++;
    }
}

//接收时间转化函数
void Change_Time(){
	unsigned char *p_rtc = ReadRTC();
	
	// 时
	time_send_Hour[0] = 'H';
    time_send_Hour[1] = 'o';
    time_send_Hour[2] = 'u';
    time_send_Hour[3] = 'r';
    time_send_Hour[4] = ':';
    time_send_Hour[5] = p_rtc[0] + '0'; // 小时十位
    time_send_Hour[6] = p_rtc[1] + '0';      // 小时个位
    time_send_Hour[7] = '\0';
    // 钟
	time_send_Minute[0] = 'M';
	time_send_Minute[1] = 'i';
	time_send_Minute[2] = 'n';
	time_send_Minute[3] = 'u';
	time_send_Minute[4] = 't';
	time_send_Minute[5] = 'e';
	time_send_Minute[6] = ':';
    time_send_Minute[7] = p_rtc[3] + '0'; // 分钟十位
    time_send_Minute[8] = p_rtc[4] + '0';      // 分钟个位
    time_send_Minute[9] = '\0';
    // 秒
	time_send_Second[0] = 'S';
	time_send_Second[1] = 'e';
	time_send_Second[2] = 'c';
	time_send_Second[3] = 'o';
	time_send_Second[4] = 'n';
	time_send_Second[5] = 'd';
	time_send_Second[6] = ':';
    time_send_Second[7] = p_rtc[6] + '0'; // 秒十位
    time_send_Second[8] = p_rtc[7] + '0';      // 秒个位
	time_send_Second[9] = '\0';
}

void Send_Time(){
	unsigned char key = Key_Scan();
	Change_Time();
	if(key == 1){
		uart_sendstring(time_send_Hour);
	}
	if(key == 2){
		uart_sendstring(time_send_Minute);
	}
	if(key == 3){
		uart_sendstring(time_send_Second);
	}
}
