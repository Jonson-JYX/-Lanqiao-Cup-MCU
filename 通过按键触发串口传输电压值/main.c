#include <stc15f2k60s2.h>
#include "LED_Display.h"
#include "Key.h"
#include "PCF8591.h"
#include "IIC.h"
#include "Delay.h"
#include "Uart.h"
#include "Common.h"

void Init_MCU(){
	SEG(0xFF);
	BUZ(0x00);
	LED(0xFF);
	COM(0xFF);
	Uart_Init();
}

void main(){
	Init_MCU();
	while(1){
		Key_Send();
		RB2_Change();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
	}
}