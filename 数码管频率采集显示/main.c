#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "NE555.h"
#include "Timer.h"
#include "LED_Display.h"

void Init_MCU(){
    LED(0xFF);
    COM(0xFF);
    BUZ(0x00);
    REY(0x00);
    SEG(0xFF);
    Timer0_Init();
    Timer1_Init();
}

void main(){
    Init_MCU();
    while(1){
        NE555_Display();
        LED_Display_Show();
    }
}