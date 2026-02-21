#include <STC15F2K60S2.H>
#include "Common.h"
#include "Distance.h"
#include "KEY.h"
#include "Timer.h"
#include "LED_Display.h"
#include "Delay.h"
#include "Uart.h"
#include "LED.h"

void Init_MCU(){
    SEG(0xFF);
    COM(0xFF);
    LED(0xFF);
    BUZ(0x00);
    S4_cnt = 0;
    Uart_Init();
    Timer_Init();
}

void main(){
    Init_MCU();
    while(1){
       Read_Sound();
       Key_login();
       LED_login();
       LED_Display_Choose();
       LED_Display_Show();
    }
}