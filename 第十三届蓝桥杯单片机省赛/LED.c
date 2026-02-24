#include <STC15F2K60S2.H>
#include "Common.h"
#include "DS1302.h"
#include "DS18B20.h"
#include "Timer.h"
#include "KEY.h"
#include "Relay.h"

unsigned char LED_value = 0xFF;
bit LED3_light = 0;

void LED_login(){
    if(S13_flag){
        if(Time_value[2] == 0 && Time_value[3] == 0 && Time_value[4] == 0 && Time_value[5] == 0){
            LED_value &= 0xFE;
            LED1_flag = 1;
        }
        if(LED1_cnt >= 5000){
            LED_value |= 0xF9;
            LED1_flag = 0;
            LED1_cnt = 0;
        }
    }
    if(!S13_flag){
        LED_value &= 0xFD;
    }
    else{
        LED_value |= 0xFA;
    }
    if(Relay_value == 0xBF){
        LED3_flag = 1;
        if(LED3_cnt >= 100){
            LED3_cnt = 0;
            LED3_light = !LED3_light;
        }
        if(LED3_light){
            LED_value &= 0xFB;
        }
        else{
            LED_value |= 0xFC;
        }
    }
    else{
        LED3_flag = 0;
        LED3_cnt = 0;
        LED_value |= 0xFC;
    }
    LED(LED_value);
}