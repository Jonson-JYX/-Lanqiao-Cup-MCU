#include <STC15F2K60S2.H>
#include "Common.h"
#include "KEY.h"
#include "Timer.h"

unsigned char LED_value = 0xFF;

void LED_login(){
    if(key_down == 0){
        if(S16_flag){
            LED_value = 0xBF;
        }
        if(S12_flag){
            LED_value = 0x7F;
        }
        if(password == 0 && first_flag == 1){
            LED_flag = 1;
            LED_value = 0xFE;
        }
        if(LED_cnt >= 5000){
            LED_value = 0xFF;
            LED_cnt = 0;
            LED_flag = 0;
        }
    }
    if(key_down == 1 && S16_flag == 0 && S12_flag == 0){
        LED_value = 0xFF;
        LED_cnt = 0;
        LED_flag = 0;
    }
    LED(LED_value);
}
