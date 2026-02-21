#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "DS18B20.h"
#include "PCF8591.h"
#include "LED.h"
#include "KEY.h"
#include "Relay.h"
#include "Uart.h"
#include "LED_Display.h"
#include "Timer.h"

void Init_MCU(){
    SEG(0xFF);
    COM(0xFF);
    LED(0xFF);
    BUZ(0x00);
    REY(0x00);
    Timer0_Init();
    Uart1_Init();
}

void main(){
    Init_MCU();
    while(1){
        Recv_login();
        Key_login();
        Temp_login();
        ADC_login();
        LED_login();
        Relay_login();
        LED_Display_Choose();
        LED_Display_Show();
        LED_Display_Show();
        LED_Display_Show();
    }
}