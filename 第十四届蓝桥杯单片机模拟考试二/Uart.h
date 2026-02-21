#ifndef Uart_H
#define Uart_H
extern unsigned char recv_value;
extern bit recv_flag;
void Uart1_Init(void);
void Send_Temp_login();
void Send_Voltage_login();
void Recv_login();
#endif // !Uart_H