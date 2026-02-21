#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "Timer.h"
#include "Distrance.h"
#include "LED_Display.h"
#include "LED.h"
#include "KEY.h"
#include "PCF8591.h"

void Init_MCU(){
    LED(0xFF);
    SEG(0xFF);
    COM(0xFF);
    BUZ(0x00);
    REY(0x00);
    Timer0_Init();
}

void main(){
    Init_MCU();
    while(1){
        Key_login();
        Sound_login();
        LED_login();
        ADC_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}