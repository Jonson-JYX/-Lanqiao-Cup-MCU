#include <STC15F2K60S2.H>
#include "IIC.h"
#include "PCF8591.h"
#include "LED_Display.h"
#include "LED.h"
#include "KEY.h"
#include "Timer.h"
#include "Uart.h"
#include "Common.h"
#include "Delay.h"

void Init_MCU(){
    LED(0xFF);
    SEG(0xFF);
    COM(0xFF);
    BUZ(0x00);
    Uart_Init();
    Timer_Init();
}

void main(){
    Init_MCU();
    while(1){
        ADC_Read();
        Key_login();
        LED_login();
        ADC_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}