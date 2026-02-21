#include <STC15F2K60S2.H>
#include "Common.h"
#include "KEY.h"
#include "PCF8591.h"
#include "LED.h"
#include "LED_Display.h"
#include "Timer.h"
#include "Uart.h"

void Init_MCU(){
    SEG(0xFF);
    LED(0xFF);
    BUZ(0x00);
    COM(0xFF);
    Uart_Init();
    Timer_Init();
}

void main(){
    Init_MCU();
    while(1){
        Read_Sound();
        Key_logic();
        Uart_ProcessRecv();
        LED_logic();
        LED_Choose();
        LED_Display_Show();
    }
}