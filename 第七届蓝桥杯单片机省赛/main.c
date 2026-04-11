#include <STC15F2K60S2.H>
#include "Common.h"
#include "DS1302.h"
#include "DS18B20.h"
#include "LED.h"
#include "LED_Display.h"
#include "Timer.h"
#include "KEY.h"

void Init_MCU(){
    LED(0xFF);
    COM(0xFF);
    SEG(0xFF);
    BUZ(0x00);
    REY(0x00);
    Timer0_Init();
    SetRTC();
    LED_cnt = 0;
}

void main(){
    Init_MCU();
    while(1){
        Key_login();
        LED_login();
        Temp_login();
        Time_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}