#include <STC15F2K60S2.H>
#include "Common.h"
#include "LED.h"
#include "Delay.h"
#include "KEY.h"
#include "Timer.h"

void Init_MCU(){
    SEG(0xFF);
    COM(0xFF);
    LED(0xFF);
    BUZ(0x00);
    COM(0x00);
    Timer0_Init();
}

void main(){
    Init_MCU();
    while(1){
        Key_login();
        LED_login();
    }
}