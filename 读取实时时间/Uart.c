#include "STC15F2K60S2.h"  
#define BAUD         9600   // 串口波特率
#define SYSTEMCLOCK  12000000L  // 系统时钟频率

// 全局接收缓冲区：存储串口接收的8个字符XX:XX:XX
unsigned char rx_buf[8] = {0};    
unsigned char rx_cnt = 0;         // 接收字符计数
bit rx_complete_flag = 0;        // 接收完成标志

// 函数声明
void system_init(void);                  // 系统初始化(串口+中断)
void uart_sendstring(unsigned char *str); // 串口发送字符串
bit parse_time(unsigned char *time_arr);  // 解析时间，格式正确返回1
void uart_receive_handler(void);         // 串口接收处理逻辑
unsigned char* get_time_array(void);      // 获取时间数组指针

// 全局定时时间：[0]时, [1]分, [2]秒（供蜂鸣器模块使用）
unsigned char g_timer_time[3] = {0};
// 标记定时时间是否已设置（避免未设置时误触发）
bit timer_time_set = 0;

// 系统初始化函数
void system_init(void)
{
    // 串口初始化
    SCON = 0x50;          // 8位数据,可变波特率,REN=1允许接收
    AUXR = 0x40;          // 定时器1使用1T模式(STC15专属)
    TMOD = 0x00;          // 定时器1为16位自动重装模式
    // 计算定时器1初值(9600波特率)
    TL1 = (65536 - (SYSTEMCLOCK / 4 / BAUD));
    TH1 = (65536 - (SYSTEMCLOCK / 4 / BAUD)) >> 8;
    TR1 = 1;              // 启动定时器1
    ES = 1;               // 使能串口中断
    EA = 1;               // 使能总中断
}

// 串口接收处理逻辑
void uart_receive_handler(void)
{
    unsigned char i;
    if(rx_complete_flag == 1)  // 检测到完整的时间字符串
    {
        rx_complete_flag = 0;  // 清空接收完成标志
        
        // 解析时间到全局定时数组
        if(parse_time(g_timer_time) == 1)
        {
            timer_time_set = 1; // 标记定时时间已设置
        }
        // 重置接收缓冲区，准备下次接收
        rx_cnt = 0;
        for(i=0; i<8; i++) rx_buf[i] = 0;
    }
}

// 返回定时时间数组指针
unsigned char* get_time_array(void)
{
    return g_timer_time;
}

// 解析时间字符串：rx_buf的"XX:XX:XX"转为数值存入time_arr
bit parse_time(unsigned char *time_arr)
{
    unsigned char i;
    // 1. 校验格式：第3位和第6位必须是':'
    if(rx_buf[2] != ':' || rx_buf[5] != ':')
    {
        return 0;
    }
    
    // 2. 校验字符是否为数字(0-9)
    for(i=0; i<8; i++)
    {
        if(i == 2 || i == 5) continue; // 跳过冒号
        if(rx_buf[i] < '0' || rx_buf[i] > '9')
        {
            return 0; // 非数字字符，格式错误
        }
    }
    
    // 3. 字符转数值：时、分、秒
    time_arr[0] = (rx_buf[0] - '0') * 10 + (rx_buf[1] - '0');  // 小时
    time_arr[1] = (rx_buf[3] - '0') * 10 + (rx_buf[4] - '0');  // 分钟
    time_arr[2] = (rx_buf[6] - '0') * 10 + (rx_buf[7] - '0');  // 秒
    
    // 4. 校验数值范围
    if(time_arr[0] > 23 || time_arr[1] > 59 || time_arr[2] > 59)
    {
        return 0; // 时间值超出范围
    }
    
    return 1; // 解析成功
}

// 串口中断服务函数
void isr_uart(void) interrupt 4
{
    unsigned char i;
    if(RI)
    {
        RI = 0;  // 清接收中断标志
        if(rx_cnt < 8)  // 只接收8个字符(XX:XX:XX)
        {
            rx_buf[rx_cnt] = SBUF;  // 存储接收字符
            rx_cnt++;               // 计数+1
            if(rx_cnt == 8)         // 8个字符接收完成
            {
                rx_complete_flag = 1;    // 置接收完成标志
            }
        }
        else
        {
            // 超出8个字符，重置缓冲区
            rx_cnt = 0;
            for(i=0; i<8; i++) rx_buf[i] = 0;
        }
    }
}

// 串口发送字符串
void uart_sendstring(unsigned char *str)
{
    unsigned char *p = str;
    while(*p != '\0')  // 遍历字符串直到结束符
    {
        SBUF = *p;     // 写入当前字符到发送寄存器
        while(TI == 0); // 等待发送完成
        TI = 0;        // 清发送中断标志
        p++;           // 指向下一个字符
    }
}