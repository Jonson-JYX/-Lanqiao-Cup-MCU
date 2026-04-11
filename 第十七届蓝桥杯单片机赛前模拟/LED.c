#include <STC15F2K60S2.H>
#include "Common.h"
#include "KEY.h"

unsigned char LED_value = 0xFF;

void LED_login(){
    if(S4_cnt == 0){
        LED_value = 0xFE;
    }
    if(S4_cnt == 1){
        if(S5_cnt == 0){
            LED_value = 0xF5;
        }
        if(S5_cnt == 1){
            LED_value = 0xED;
        }
    }
    if(S4_cnt == 2){
        LED_value = 0xFB;
    }
    LED(LED_value);
}