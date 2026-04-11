#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "Timer.h"
#include "DS18B20.h"
#include "KEY.h"
#include "LED.h"
#include "LED_Display.h"
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
    Light_Standard = Read_Light();
    while(1){
        Key_login();
        Temp_login();
        NE555_login();
        Time_login();
        LED_login();
        Light_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}