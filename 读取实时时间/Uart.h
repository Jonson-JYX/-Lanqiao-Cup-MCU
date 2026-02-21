#ifndef _Uart_H_
#define _Uart_H_

void system_init(void);                  // 系统初始化（串口+中断）
void uart_sendstring(unsigned char *str); // 串口发送字符串
bit parse_time(unsigned char *time_arr);  // 解析时间，结果存入传入的数组，返回1=成功
void uart_receive_handler(void);         // 串口接收处理主逻辑
unsigned char* get_time_array(void);      // 获取时间数组的指针（核心需求）

#endif