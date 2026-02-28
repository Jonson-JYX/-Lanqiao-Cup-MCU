#include <STC15F2K60S2.H>
#include "Common.h"
#include "Timer.h"
#include "NE555.h"
#include "KEY.h"

unsigned char LED_value = 0xFF;
bit LED1 = 0;
bit LED2 = 0;

void LED_login(){
    if(S4_cnt % 4 == 0){
        LED1_flag = 1;
    }
    else{
        LED1_flag = 0;
    }
    if(LED1_flag){
        if(LED1_cnt >= 200){
            LED1_cnt = 0;
            LED1 = !LED1;
        }
        if(LED1){
            LED_value &= 0xFE;
        }
        else{
            LED_value |= 0x01;
        }
    }
    else{
        LED_value |= 0x01;
    }

    if(NE555_now < 0){
        LED2_flag = 1;
    }
    else{
        LED2_flag = 0;
    }
    if(LED2_flag){
        if(LED2_cnt >= 200){
            LED2_cnt = 0;
            LED2 = !LED2;
        }
        if(LED2){
            LED_value &= 0xFD;
        }
        else{
            LED_value |= 0x02;
        }
    }
    else{
        LED_value |= 0x02;
    }
    LED(LED_value);
}