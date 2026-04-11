#include <STC15F2K60S2.H>
#include "Common.h"
#include "Timer.h"
#include "KEY.h"
#include "PCF8591.h"
#include "Uart.h"

unsigned char LED_value = 0xFF;
bit LED = 0;

void LED_login(){
    if(Free_flag){
        LED_value |= 0xF9;
    }
    if(Run_flag){
        LED_value &= 0xFE;
    }
    if(Wait_flag){
        LED1_flag = 1;
        if(LED1_cnt >= 100){
            LED = !LED;
            LED1_cnt = 0;
        }
        if(LED){
            LED_value |= 0xF9;
        }
        else{
            LED_value &= 0xFE;
        }
    }
    else{
        LED1_cnt = 0;
        LED1_flag = 0;
    }
    if(Light_flag){
        LED_value &= 0xFD;
    }
    else{
        LED_value |= 0xFA;
    }
    if(Position_value[0] >= rx_dat[0] && Position_value[1] >= rx_dat[1]){
        LED3_flag = 1;
        LED_value &= 0xFB;
        if(LED3_cnt >= 3000){
            LED_value |= 0xFC;
            LED3_flag = 0;
            LED3_cnt  =0;
        }
    }
    LED(LED_value);
}