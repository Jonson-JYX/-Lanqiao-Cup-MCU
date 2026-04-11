#include <STC15F2K60S2.H>
#include "Common.h"
#include "Timer.h"
#include "KEY.h"
#include "DS18B20.h"

unsigned char LED_value = 0xFF;
bit LED = 0;
void LED_login(){
    if(Temp_num == 10){
        LED_flag = 1;
    }
    else{
        LED_flag = 0;
        LED_value = 0xFF;
    }
    if(LED_flag){
        if(LED_cnt >= 200){
            LED_cnt = 0;
            LED = !LED;
        }
        if(LED){
            LED_value = 0xFE;
        }
        else{
            LED_value = 0xFF;
        }
    }
    LED(LED_value);
}