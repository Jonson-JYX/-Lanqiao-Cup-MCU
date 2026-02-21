#include <stc15f2k60s2.h>
#include "LED.h"
#include "Delay.h"
#include "PCF8591.h"
#include "IIC.h"
#include "Uart.h"
#include "Common.h"
#include "LED_Display.h"

void Init_MCU(){
	SEG(0xFF);
	LED(0xFF);
	COM(0xFF);
	BUZ(0x00);
	Uart_Init();
	LED_Display_flag = 3;
}

void main(){
	Init_MCU();
	while(1){
		if(recv_flag){
			LED_Display_flag = Uart_Choose();
		}
		LED_Display_Choose();
		LED_Display_Show();
	}
}