#include <stc15f2k60s2.h>
#include "LED_Display.h"
#include "DS18B20.h"
#include "Delay.h"
#include "Onewire.h"
#include "Uart.h"
#include "Key.h"
#include "Common.h"

void Init_MCU(){
	LED(0xFF);
	COM(0xFF);
	BUZ(0x00);
	SEG(0xFF);
}

void main(){
	Init_MCU();
	Uart_Init();
	while(1){
		Key();
		Temp_Change();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
		LED_Display_Show();
	}
}