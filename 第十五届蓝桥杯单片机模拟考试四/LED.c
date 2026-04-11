#include <STC15F2K60S2.H>
#include "Timer.h"
#include "DS18B20.h"
#include "Common.h"
#include "KEY.h"

unsigned char LED_value = 0xFF;
unsigned int Temp = 300;
bit flag = 0;

void LED_login(){
    if(S4_cnt % 3 == 0){
        LED_value = 0xFE;
    }
    if(S4_cnt % 3 == 1){
        LED_value = 0xFD;
    }
    if(S4_cnt % 3 == 2){
        LED_value = 0xFF;
    }
    if(Temp_value > Temp){
        LED_flag = 1;
    }
    else{
        LED_flag = 0;
        LED_cnt = 0;
    }
    if(LED_flag){
        if(LED_cnt >= 100){
            flag = !flag;
            LED_cnt = 0;
        }
        if(flag){
            LED_value &= 0x7F; 
        }
        else{
            LED_value |= 0x80;
        }
    }
    LED(LED_value);
}