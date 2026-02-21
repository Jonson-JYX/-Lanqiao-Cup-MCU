#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "IIC.h"
#include "PCF8591.h"
#include "KEY.h"
#include "Timer.h"
#include "Relay.h"
#include "LED.h"
#include "LED_Display.h"

void Init_MCU(){
    SEG(0xFF);
    LED(0xFF);
    COM(0xFF);
    BUZ(0x00);
    REY(0x00);
    Timer0_Init();
}

void main(){
    Init_MCU();
    while(1){
        Key_login();
        ADC_login();
        Relay_login();
        LED_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}