#include <STC15F2K60S2.H>
#include "Delay.h"
#include "IIC.h"
#include "PCF8591.h"
#include "Timer.h"
#include "KEY.h"
#include "LED.h"
#include "LED_Display.h"
#include "Timer.h"
#include "Common.h"

void Init_MCU(){
    SEG(0xFF);
    COM(0xFF);
    BUZ(0x00);
    REY(0x00);
    LED(0xFF);
    Timer0_Init();
}

void main(){
    Init_MCU();
    while(1){
        Key_login();
        Light_login();
        ADC_login();
        LED_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}