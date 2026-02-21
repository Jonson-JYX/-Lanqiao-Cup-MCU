#include <STC15F2K60S2.H>
#include "KEY.h"
#include "PCF8591.h"

unsigned char recv_dat[7] = {'R','e','t','u','r','n','\0'};
unsigned char recv_cnt = 0;
bit recv_flag = 0;
unsigned char send_dat[13] = {0};
unsigned char send_cnt = 0;
bit send_flag = 0;

// 串口中断服务函数
void Uart_Isr(void) interrupt 4{
	if (RI)				// 检测串口1接收中断
	{
        RI = 0; 		// 清除接收中断标志
        if(recv_cnt < 6){
            recv_dat[recv_cnt] = SBUF; // 读取接收数据
            recv_cnt++;
            if(recv_cnt == 6){
                recv_flag = 1; // 接收完成标志
                recv_cnt = 0;
            }
        }
	}
	if (TI)	// 检测串口1发送中断
	{
        TI = 0;            // 清除发送中断标志
        if (send_cnt < 13) { 
            SBUF = send_dat[send_cnt]; 
            send_cnt++;
        } else {
            send_flag = 0; // 发送完成，清零标志
            send_cnt = 0;  // 重置发送计数器
        }
	}
}

void Uart_Init(void){
    SCON = 0x50;		// 8位数据,可变波特率
	AUXR |= 0x40;		// 定时器时钟1T模式
	AUXR &= 0xFE;		// 串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		// 设置定时器模式
	TL1 = 0xC7;			// 波特率9600（12MHz）
	TH1 = 0xFE;			// 定时初始值
	ET1 = 0;			// 禁止定时器1中断
	TR1 = 1;			// 定时器1开始计时
	ES = 1;				// 使能串口1中断
    EA = 1;				// 使能总中断
    send_flag = 0;
}

// 串口发送字符串
void Uart_SendString()
{
    if(send_flag == 0){ // 仅当未发送时启动
        send_flag = 1;  // 标记发送中
        send_cnt = 0;   // 重置发送计数器
        TI = 0;         // 清除发送标志
        SBUF = send_dat[send_cnt]; // 启动第一个字节发送
        send_cnt++;
    }
}

// 封装噪声数据并发送
void Sound_Send(){
    send_dat[0] = 'N';
    send_dat[1] = 'o';
    send_dat[2] = 'i';
    send_dat[3] = 's';
    send_dat[4] = 'e';
    send_dat[5] = 's';
    send_dat[6] = ':';
    send_dat[7] = (Sound_value / 100) + '0';
    send_dat[8] = ((Sound_value % 100) / 10) + '0';
    send_dat[9] = '.';
    send_dat[10] = (Sound_value % 10) + '0';
    send_dat[11] = 'd';
    send_dat[12] = 'B';
    Uart_SendString();
}

// 处理接收的数据
void Uart_ProcessRecv(void){
    if(recv_flag){ 
        recv_flag = 0; // 立即清除接收标志
        if(recv_dat[0]=='R' && recv_dat[1]=='e' && recv_dat[2]=='t' && recv_dat[3]=='u' && recv_dat[4]=='r' && recv_dat[5]=='n'){
            Sound_Send(); 
        }
    }
}