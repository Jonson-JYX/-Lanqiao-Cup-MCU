#include <STC15F2K60S2.H>
#include "Common.h"
#include "KEY.h"
#include "PCF8591.h"
#include "NE555.h"

bit LED_flag = 1;
unsigned char xdata LED_value = 0xFF;

void LED_login(){
    if(LED_flag){
        if(S4_cnt == 0){
            LED_value = 0xFB;
        }
        if(S4_cnt == 1){
            LED_value = 0xF7;
        }
        if(S4_cnt == 2){
            LED_value = 0xEF;
        }
        if(RB2_dat < RB2_value){
            LED_value &= 0xFE;
        }
        else{
            LED_value |= 0x01;
        }
        if(NE555_dat < NE555_value){
            LED_value &= 0xFD;
        }
        else{
            LED_value |= 0x02;
        }
    }
    else{
        LED_value = 0xFF;
    }
    LED(LED_value);
}