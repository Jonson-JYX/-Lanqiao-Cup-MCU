#include <STC15F2K60S2.H>
#include "Common.h"
#include "IIC.h"
#include "KEY.h"
#include "LED.h"
#include "LED_Display.h"
#include "NE555.h"
#include "PCF8591.h"
#include "Timer.h"
#include "Delay.h"

void Init_MCU(){
    LED(0xFF);
    COM(0xFF);
    SEG(0xFF);
    BUZ(0x00);
    REY(0x00);
    Timer0_Init();
    Timer1_Init();
}

void main(){
    Init_MCU();
    while(1){
        Key_Scan();
        Key_login();
        LED_login();
        NE555_login();
        RB2_login();
        Light_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}