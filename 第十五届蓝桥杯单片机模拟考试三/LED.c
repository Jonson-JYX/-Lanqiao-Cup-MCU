#include <STC15F2K60S2.H>
#include "Common.h"
#include "KEY.h"
#include "Timer.h"
#include "Distrance.h"

unsigned char LED_dat = 0xFF;

void LED_login(){
    switch(S4_cnt){
        case 0:
            LED_dat = 0xFE;
            break;
        case 1:
            LED_dat = 0xFD;
            break;
        case 2:
            LED_dat = 0xFB;
    }
    if(sound_value <= Parameter_max && sound_value >= Parameter_min){
        LED_dat &= 0x7F;
        LED_flash_flag = 0;
    }
    else{
        if(LED_cnt == 0){
            if(LED_flag){
                LED_dat &= 0x7F;
            }
            else{
                LED_dat |= 0x80;
            }
            LED_flash_flag = 0;
        }
    }
    LED(LED_dat);
}