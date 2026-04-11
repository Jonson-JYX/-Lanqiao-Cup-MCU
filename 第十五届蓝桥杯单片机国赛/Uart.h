#ifndef Uart_H
#define Uart_H

extern unsigned int xdata rx_dat[2];  

void Uart1_Init(void);
void Uart_login(void);
void Uart_Send_Char(unsigned char ch);
void Uart_sendstring(unsigned char *str);
void Uart_Send_Position(void);
void Uart_Rece_Position(void);

#endif