#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "DS1302.h"
#include "Timer.h"
#include "PCF8591.h"
#include "KEY.h"
#include "LED.h"
#include "LED_Display.h"

void Init_MCU(){
    SEG(0xFF);
    COM(0xFF);
    LED(0xFF);
    BUZ(0x00);
    REY(0x00);
    SetRTC();
    Timer0_Init();
}

void main(){
    Init_MCU();
    while(1){
        Key_login();
        Time_login();
        ADC_login();
        Light_login();
        LED_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}