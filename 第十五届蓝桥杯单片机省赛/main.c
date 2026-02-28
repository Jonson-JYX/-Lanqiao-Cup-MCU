#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "KEY.h"
#include "LED.h"
#include "LED_Display.h"
#include "Timer.h"
#include "DS1302.h"
#include "PCF8591.h"
#include "NE555.h"

void Init_MCU(){
    LED(0xFF);
    SEG(0xFF);
    COM(0xFF);
    BUZ(0x00);
    REY(0x00);
    SetRTC();
    Timer0_Init();
    Timer1_Init();
}

void main(){
    Init_MCU();
    while(1){
        NE555_login();
        Key_login();
        LED_login();
        Time_login();
        DAC_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}