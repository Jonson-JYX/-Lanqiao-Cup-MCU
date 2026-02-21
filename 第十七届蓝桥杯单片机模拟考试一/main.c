#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "DS1302.h"
#include "KEY.h"
#include "LED.h"
#include "Timer.h"
#include "Distance.h"
#include "Beep.h"
#include "LED_Display.h"

void Init_MCU(){
    LED(0xFF);
    BUZ(0x00);
    COM(0xFF);
    SEG(0xFF);
    Timer_Init();
    SetRTC();
}

void main(){
    Init_MCU();
    while(1){
        Key_login();
        LED_login();
        Time_login();
        Distance_login();
        Beep_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}