#include <STC15F2K60S2.H>
#include "Common.h"
#include "Timer.h"

bit L4_blink = 0; // L4闪烁状态（0灭1亮）
bit L5_blink = 0; // L5闪烁状态（0灭1亮）

void LED_login(){
    unsigned char LED_value = 0xFF; // 默认所有LED熄灭（共阴极，FF=灭）
    
    // L1控制：标志有效则点亮（0xFE=第0位L1亮）
    if(L1_flag){
        LED_value &= 0xFE;
    }
    // L2控制：标志有效则点亮（0xFD=第1位L2亮）
    if(L2_flag){
        LED_value &= 0xFD;
    }
    // L4控制：标志有效则0.1秒闪烁（0xF7=第3位L4亮）
    if(L4_flag){
        if(blink4_cnt >= 100){ // 100ms=0.1秒翻转一次
            blink4_cnt = 0;
            L4_blink = !L4_blink;
        }
        if(L4_blink){
            LED_value &= 0xF7;
        }
    }
    else{
        L4_blink = 0; // 标志失效时强制熄灭
    }
    // L5控制：标志有效则0.1秒闪烁（0xEF=第4位L5亮）
    if(L5_flag){
        if(blink5_cnt >= 100){
            blink5_cnt = 0;
            L5_blink = !L5_blink;
        }
        if(L5_blink){
            LED_value &= 0xEF;
        }
    }
    else{
        L5_blink = 0; // 标志失效时强制熄灭
    }
    
    // 输出LED状态
    LED(LED_value);
}