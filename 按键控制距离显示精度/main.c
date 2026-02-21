#include <STC15F2K60S2.H>
#include "Delay.h"
#include "Distrance.h"
#include "Common.h"
#include "Timer.h"
#include "KEY.h"
#include "LED_Display.h"

void Init_MCU(){
    SEG(0xFF);
    COM(0xFF);
    LED(0xFF);
    BUZ(0x00);
    REY(0x00);
    Timer_Init();
}

void main(){
    Init_MCU();
    while(1){
        Key_login();
        Sound_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}