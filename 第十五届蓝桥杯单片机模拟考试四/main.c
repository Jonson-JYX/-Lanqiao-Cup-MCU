#include <STC15F2K60S2.H>
#include "Common.h"
#include "Dealy.h"
#include "DS18B20.h"
#include "LED_Display.h"
#include "LED.h"
#include "Timer.h"
#include "PCF8591.h"
#include "NE555.h"
#include "KEY.h"
#include "Relay.h"

void Init_MCU(){
    LED(0xFF);
    SEG(0xFF);
    COM(0xFF);
    BUZ(0x00);
    REY(0x00);
    Timer0_Init();
    Timer1_Init();
    LED_cnt = 0;
    Temp_cnt = 0;
    NE555_cnt = 0;
    DAC_cnt = 0;
}

void main(){
    Init_MCU();
    while(1){
        Key_login();
        Temp_login();
        NE555_login();
        LED_login();
        Relay_login();
        DAC_login();
        LED_Display_Choose();
        LED_Display_Show();
        LED_Display_Show();
        LED_Display_Show();
    }
}