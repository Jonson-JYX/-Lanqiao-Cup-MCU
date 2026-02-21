#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "IIC.h"
#include "PCF8591.h"
#include "Timer.h"
#include "NE555.h"
#include "LED.h"
#include "KEY.h"
#include "LED_Display.h"
#include "DS1302.h"

void Init_MCU(){
    SEG(0xFF);
    LED(0xFF);
    COM(0xFF);
    BUZ(0x00);
    REY(0x00);
    Timer0_Init();
    Timer1_Init();
    SetRTC();
}

void main(){
    Init_MCU();
    while(1){
        NE555_now = NE555_cali + NE555_value;
        Time_login();
        DAC_login();
        LED_login();
        Key_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}