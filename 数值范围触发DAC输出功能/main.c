#include <stc15f2k60s2.h>
#include "KEY.h"
#include "LED_Display.h"
#include "IIC.h"
#include "PCF8591.h"
#include "Delay.h"
#include "Common.h"

void Init_MCU(){
	SEG(0xFF);
	COM(0xFF);
	BUZ(0x00);
	LED(0xFF);
}

void main(){
	Init_MCU();
	while(1){
		Key_Sum();
		DA_Cout();
		Key_Change();
		LED_Display_Show();
	}
}