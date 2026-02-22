#include <STC15F2K60S2.H>
#include "KEY.h"
#include "Common.h"
#include "Delay.h"
#include "Timer.h"

unsigned char LED_value = 0xFF;
bit LED2_flag = 1;

void LED_login(){
    if(S9_cnt % 2 == 0){
        LED_value = 0xFE;
    }
    else{
        LED_value = 0xFF;
    }
    if(count > num){
        LED_flag = 1;
        if(LED2_flag){
            LED_value &= 0xFD;
        }
        else{
            LED_value |= 0xFE;
        }
        if(LED_cnt >= 200){
            LED2_flag = !LED2_flag;
            LED_cnt = 0;
        }
    }
    else{
        LED_flag = 0;
        LED_value |= 0xFE;
    }
    LED(LED_value);
}