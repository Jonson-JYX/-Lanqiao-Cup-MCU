#include <STC15F2K60S2.H>
#include "Timer.h"
#include "KEY.h"
#include "Common.h"
#include "Distrance.h"

unsigned char LED_value = 0xFF;
void LED_login(){
    unsigned char dat = S4_cnt % 3;
    switch(dat){
        case 1:
            LED_value = 0xFE;
            break;
        case 2:
            LED_value = 0xFD;
            break;
    }
    if(sound_value >= Distance_max || sound_value <= Distance_min){
        if(LED_cnt == 199){
            if(LED_flag){
                LED_value &= 0xFB;
            }
            else{
                LED_value |= 0xFC;
            }
        }
    }
    LED(LED_value);
}