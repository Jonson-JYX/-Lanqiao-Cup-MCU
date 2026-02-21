#include <STC15F2K60S2.H>
#include "Common.h"
#include "Timer.h"
#include "LED.h"

void Init_MCU(){
    LED(0xFF);
    SEG(0xFF);
    COM(0xFF);
    BUZ(0xFF);
    Timer_Init();
}

void main(){
    Init_MCU();
    while(1){
        LED_login();
    }
}