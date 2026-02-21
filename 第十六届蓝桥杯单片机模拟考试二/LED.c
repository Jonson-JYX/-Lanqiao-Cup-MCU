#include <STC15F2K60S2.H>
#include "Common.h"
#include "KEY.h"
#include "PCF8591.h"
#include "Timer.h"

unsigned char LED_value = 0xFF;
bit LED_flag = 1;

void LED_login(){
    unsigned char dat = S4_cnt % 3;
    switch(dat){
        case 0:
            LED_value = 0xFE;
            break;
        case 1:
            LED_value = 0xFD;
            break;
        case 2:
            LED_value = 0xFB;
            break;
    }
    if(ADC_value > light_value){
        if(LED_flag){
            if(LED_cnt >= 3000){
                LED_cnt = 0;
                LED_flag = 0;
            }
            LED_value = 0x7F;
        }
    }
    else{
        LED_flag = 1;
        LED_cnt = 0;
    }
    LED(LED_value);
}