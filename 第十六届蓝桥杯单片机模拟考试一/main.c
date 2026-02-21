#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "DS18B20.h"
#include "KEY.h"
#include "LED_Display.h"
#include "LED.h"
#include "Timer.h"

void Init_MCU(){
    SEG(0xFF);
    COM(0xFF);
    LED(0xFF);
    BUZ(0x00);
    S4_cnt = 0;
    S5_cnt = 0;
    temp_dat = 26;
    cali_dat = 0;
    Timer_Init();
}

void main(){
    Init_MCU();
    while(1){
        if(temp_cnt == 499){
            Read_Temp();
        }
        Key_login();
        LED_login();
        LED_Dislay_Choose();
        LED_Display_Show();
    }
}