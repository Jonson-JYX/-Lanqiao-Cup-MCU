#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "DS18B20.h"
#include "KEY.h"
#include "DS1302.h"
#include "LED.h"
#include "Timer.h"
#include "Relay.h"
#include "LED_Display.h"

void Init_MCU(){
    SEG(0xFF);
    COM(0xFF);
    BUZ(0x00);
    REY(0x00);
    LED(0xFF);
    Timer0_Init();
    SetRTC();
}

void main(){
    Init_MCU();
    while(1){
        Key_login();
        Temp_login();
        Time_login();
        LED_login();
        Relay_login();
        LED_Display_Choose();
        LED_Display_Show();
        LED_Display_Show();
        LED_Display_Show();
    }
}