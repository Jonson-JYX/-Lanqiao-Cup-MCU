#ifndef Uart_H
#define Uart_H
void Uart_Init(void);
void Uart_SendString();
extern unsigned char recv_dat[7];
void Sound_Send();
void Uart_Isr(void);
void Uart_ProcessRecv(void);
#endif // !Uart_H