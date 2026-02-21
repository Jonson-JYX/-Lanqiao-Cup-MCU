#include <STC15F2K60S2.H>
#include "Common.h"
#include "KEY.h"
#include "DS1302.h"
#include "Timer.h"

bit LED_flag = 0;
unsigned char LED_value = 0xFF;

void LED_login(){
    unsigned char dat = S4_cnt % 2;
    switch(dat){
        case 0:
            LED_value = 0xFE;
            break;
        case 1:
            LED_value = 0xFD;
            break;
    }
    if(time_now[5] == 0 && time_now[4] == 0 && time_now[3] == 0 && time_now[2] == 0){
        LED_flag = 1;
        LED_cnt = 0;
    }
    if(LED_flag){
        LED_value &= 0x7F;
        if(LED_cnt >= 3000){
            LED_cnt = 0;
            LED_flag = 0;
            LED_value |= 0x80;
        }
    }
    LED(LED_value);
}