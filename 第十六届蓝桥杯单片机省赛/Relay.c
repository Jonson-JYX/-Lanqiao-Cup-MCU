#include <STC15F2K60S2.H>
#include "Common.h"
#include "DS18B20.h"
#include "Sound.h"

unsigned char relay_value = 0x00;    //继电器状态值
unsigned char relay_cnt = 0;         //继电器计数值
bit relay_flag = 0;                 //继电器标志位

void Relay_login(){
    if(temp_flag && sound_flag){
        relay_value = 0xBF;
        if(relay_flag){
            relay_cnt++;
            relay_flag = 0;
        }
    }
    else{
        relay_value = 0x00;
        relay_flag = 1;
    }
    REY(relay_value);
}