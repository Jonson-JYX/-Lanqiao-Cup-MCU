#include "stc15f2k60s2.h"
#include "LED.h"
#include "LED_Display.h"
#include "Uart.h"
#include "Delay.h"
#include "Common.h"

void Init_MCU(){
	SEG(0xFF);
	COM(0xFF);
	BUZ(0x00);
	LED(0xFF);
	Uart_Init();
	LED_value = 0xFF;
}

void main(){
	Init_MCU();
	while(1){
		if(rece_flag){
			LED_Show();
			LED_Change();
			rece_flag = 0;
		}
		LED_Display_Show();
		LED(LED_value);
	}
}