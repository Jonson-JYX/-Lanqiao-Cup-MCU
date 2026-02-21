#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "KEY.h"
#include "Timer.h"
#include "Distrance.h"
#include "LED.h"
#include "Beep.h"
#include "LED_Display.h"

void Init_MCU(){
    SEG(0xFF);
    COM(0xFF);
    BUZ(0x00);
    LED(0xFF);
    REY(0x00);
    Timer0_Init();
}

void main(){
    Init_MCU();
    while(1){
        Key_login();
        Distance_login();
        LED_login();
        Beep_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}