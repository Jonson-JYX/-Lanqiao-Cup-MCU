#include <stc15f2k60s2.h>
#include "LED_Display.h"
#include "LED.h"
#include "Delay.h"
#include "Uart.h"
#include "Common.h"

void Init_MCU(){
	system_init();
	SEG(0xFF);
	COM(0xFF);
	BUZ(0x00);
	LED(0xFF);
}

void main(){
	Init_MCU();
	while(1){
		if(rx_complete_flag){ // 仅当串口接收完成时更新显示
            LED_Display_Show();
			rx_complete_flag = 0; // 显示完成后清零，避免重复执行
            rx_cnt = 0;
        }
		LED_Display_Show();
	}
}