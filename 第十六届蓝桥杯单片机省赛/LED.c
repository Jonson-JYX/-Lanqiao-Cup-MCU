#include <STC15F2K60S2.H>
#include "Common.h"
#include "Timer.h"
#include "Sound.h"
#include "PCF8591.h"

unsigned char LED_value = 0xFF;    //LED显示值
bit LED8 = 0;                      //LED8状态值

void LED_login(){
    //灯光控制功能
    if(light_level == 1){
        LED_value = 0xFE;
    }
    else if(light_level == 2){
        LED_value = 0xFC;
    }
    else if(light_level == 3){
        LED_value = 0xF8;
    }
    else if(light_level == 4){
        LED_value = 0xF0;
    }
    //运动状态指示功能
    if(sound_status == 1){
        LED_value &= 0xFF;
    }
    if(sound_status == 2){
        LED_value &= 0x7F;
    }
    if(sound_status == 3){
        LED_flag = 1;
        if(LED_cnt >= 100){
            LED_cnt = 0;
            LED8 = ~LED8;   
        }
        if(LED8){
            LED_value &= 0xFF;
        }
        else{
            LED_value &= 0x7F;
        }
    }
    else{
        LED_flag = 0;
        LED8 = 0;
        LED_cnt = 0;
    }
    LED(LED_value);
}