#include <STC15F2K60S2.H>
#include "Common.h"
#include "KEY.h"
#include "Timer.h"
#include "NE555.h"
#include "PCF8591.h"
#include "Ultrasound.h"

unsigned char LED_value = 0xFF;
bit LED1 = 0;
bit LED2 = 0;
bit LED3 = 0;

void LED_login(){
    if(S4_cnt % 4 == 0){
        LED1_flag = 1;
        LED2_flag = 0;
        LED3_flag = 0;
        if(LED1_flag){
            if(LED1_cnt >= 100){
                LED1 = !LED1;
                LED1_cnt = 0;
            }
            if(LED1){
                LED_value = 0xFE;
            }
            else{
                LED_value |= 0xC1;
            }
        }
    }
    else{
        LED1_flag = 0;
        LED1_cnt = 0;
    }

    if(S4_cnt % 4 == 1){
        LED1_flag = 0;
        LED2_flag = 1;
        LED3_flag = 0;
        if(LED2_flag){
            if(LED2_cnt >= 100){
                LED2 = !LED2;
                LED2_cnt = 0;
            }
            if(LED2){
                LED_value = 0xFD;
            }
            else{
                LED_value |= 0xC2;
            }
        }
    }
    else{
        LED2_flag = 0;
        LED2_cnt = 0;
    }

    if(S4_cnt % 4 == 2){
        LED1_flag = 0;
        LED2_flag = 0;
        LED3_flag = 1;
        if(LED3_flag){
            if(LED3_cnt >= 100){
                LED3 = !LED3;
                LED3_cnt = 0;
            }
            if(LED3){
                LED_value = 0xFB;
            }
            else{
                LED_value |= 0xC4;
            }
        }
    }
    else{
        LED3_flag = 0;
        LED3_cnt = 0;
    }

    if(S4_cnt % 4 == 3){
        LED_value |= 0xC7;
        if(NE555_value > NE555_dat * 1000){
            LED_value &= 0xF7;
        }
        else{
            LED_value |= 0xC8;
        }

        if(Humidity_value > Humidity_dat){
            LED_value &= 0xEF;
        }
        else{
            LED_value |= 0xD0;
        }

        if(Sound_value > Sound_dat * 10){
            LED_value &= 0xDF;
        }
        else{
            LED_value |= 0xE0;
        }
    }

    LED(LED_value);
}