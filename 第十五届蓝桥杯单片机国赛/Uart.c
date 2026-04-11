#include <STC15F2K60S2.H>
#include "KEY.h"
#include <string.h>

// 将大数组定义到 xdata 区域
unsigned char xdata rx_buff[20] = {0};     // 接收缓冲区
unsigned int xdata rx_dat[2] = {0};        // PC发送的坐标
unsigned char xdata rx_count = 0;          // 接收计数器
unsigned char xdata temp_buff[20] = {0};   // 单片机发送的坐标
bit rx_flag = 0;                           // bit类型不需要改

// 串口1中断服务函数
void Uart1_Isr(void) interrupt 4
{
    unsigned char recv;
    if (RI)
    {
        RI = 0;
        recv = SBUF;
        
        if (recv == '\r' || recv == '\n')
        {
            if (rx_count > 0)
            {
                rx_buff[rx_count] = '\0';
                rx_flag = 1;
                rx_count = 0;
            }
        }
        else if (rx_count < 19)
        {
            rx_buff[rx_count] = recv;
            rx_count++;
        }
        else
        {
            rx_count = 0;
        }
    }
    
    if (TI)
    {
        TI = 0;
    }
}

void Uart1_Init(void)	//9600bps@12.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器时钟1T模式
	T2L = 0xC7;			//设置定时初始值
	T2H = 0xFE;			//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时
	ES = 1;				//使能串口1中断
    EA = 1;
}


// 串口发送单个字符
void Uart_Send_Char(unsigned char ch)
{
    SBUF = ch;
    while (!TI);
    TI = 0;
}

// 串口发送字符串
void Uart_sendstring(unsigned char *str)
{
    unsigned char *p = str;
    while (*p != '\0')
    {
        SBUF = *p;
        while (TI == 0);
        TI = 0;
        p++;
    }
}

// 坐标发送函数
void Uart_Send_Position(void)
{
    unsigned char i = 0;
    
    temp_buff[i++] = '(';
    
    if (Position_value[0] >= 100)
    {
        temp_buff[i++] = Position_value[0] / 100 + '0';
        temp_buff[i++] = Position_value[0] % 100 / 10 + '0';
        temp_buff[i++] = Position_value[0] % 10 + '0';
    }
    else if (Position_value[0] >= 10)
    {
        temp_buff[i++] = Position_value[0] / 10 + '0';
        temp_buff[i++] = Position_value[0] % 10 + '0';
    }
    else
    {
        temp_buff[i++] = Position_value[0] + '0';
    }
    
    temp_buff[i++] = ',';
    
    if (Position_value[1] >= 100)
    {
        temp_buff[i++] = Position_value[1] / 100 + '0';
        temp_buff[i++] = Position_value[1] % 100 / 10 + '0';
        temp_buff[i++] = Position_value[1] % 10 + '0';
    }
    else if (Position_value[1] >= 10)
    {
        temp_buff[i++] = Position_value[1] / 10 + '0';
        temp_buff[i++] = Position_value[1] % 10 + '0';
    }
    else
    {
        temp_buff[i++] = Position_value[1] + '0';
    }
    
    temp_buff[i++] = ')';
    temp_buff[i] = '\0';
    
    Uart_sendstring(temp_buff);
}

// 坐标接收函数
void Uart_Rece_Position(void)
{
    unsigned char i = 0;
    unsigned char comma_pos = 0;
    
    // 找到逗号的位置
    while (rx_buff[i] != '\0' && rx_buff[i] != ',')
    {
        if (rx_buff[i] == '(')
        {
            i++;
            continue;
        }
        i++;
    }
    comma_pos = i;
    
    // 解析X坐标
    rx_dat[0] = 0;
    for (i = 1; i < comma_pos; i++)
    {
        if (rx_buff[i] >= '0' && rx_buff[i] <= '9')
        {
            rx_dat[0] = rx_dat[0] * 10 + (rx_buff[i] - '0');
        }
    }
    
    // 解析Y坐标
    rx_dat[1] = 0;
    for (i = comma_pos + 1; i < 20; i++)
    {
        if (rx_buff[i] >= '0' && rx_buff[i] <= '9')
        {
            rx_dat[1] = rx_dat[1] * 10 + (rx_buff[i] - '0');
        }
        else if (rx_buff[i] == ')' || rx_buff[i] == '\0')
        {
            break;
        }
    }
}

// 串口主逻辑处理函数
void Uart_login(void)
{
    if (rx_flag)
    {
        if (rx_buff[0] == '?')
        {
            if (Free_flag)
            {
                Uart_sendstring("Idle\r\n");
            }
            else if (Wait_flag)
            {
                Uart_sendstring("Wait\r\n");
            }
            else if (Run_flag)
            {
                Uart_sendstring("Busy\r\n");
            }
        }
        else if (rx_buff[0] == '#')
        {
            Uart_Send_Position();
            Uart_sendstring("\r\n");
        }
        else if (rx_buff[0] == '(')
        {
            Uart_Rece_Position();
            Uart_sendstring("Got it\r\n");
            coordinate_flag = 1;
        }
        else
        {
            Uart_sendstring("Error\r\n");
        }
        
        rx_flag = 0;
        rx_count = 0;
        memset(rx_buff, 0, sizeof(rx_buff));
    }
}