#ifndef _Uart_H_
#define _Uart_H_

extern bit rx_complete_flag;
extern unsigned char rx_cnt;

void system_init(void);
void uart_sendstring(unsigned char *str);
void isr_uart(void);
unsigned char *Arr_Value();

#endif