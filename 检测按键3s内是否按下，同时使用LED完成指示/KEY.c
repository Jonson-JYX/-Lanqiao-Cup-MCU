#include <STC15F2K60S2.H>
#include "Delay.h"
#include "Timer.h"

unsigned char Key_Scan(){
    unsigned char key = 0;
    // 扫描S4（P33=0，P44检测）
    P33 = 0;P32 = 1;P31 = 1;P30 = 1;
    if(P44 == 0){   
        Delay100ms(); // 消抖
        if(P44 == 0){ // 确认按键按下
            key = 1;
            while(P44 == 0); // 等待按键释放
        }
    }
    // 扫描S9（P32=0，P42检测）
    P33 = 1;P32 = 0;P31 = 1;P30 = 1;
    if(P42 == 0){   
        Delay100ms();
        if(P42 == 0){
            key = 2;
            while(P42 == 0);
        }
    }
    // 扫描S14（P31=0，P35检测）
    P33 = 1;P32 = 1;P31 = 0;P30 = 1;
    if(P35 == 0){   
        Delay100ms();
        if(P35 == 0){
            key = 3;
            while(P35 == 0);
        }
    }
    // 扫描S19（P30=0，P34检测）
    P33 = 1;P32 = 1;P31 = 1;P30 = 0;
    if(P34 == 0){   
        Delay100ms();
        if(P34 == 0){
            key = 4;
            while(P34 == 0);
        }
    }
    return key;
}

// 按键处理：按下按键时触发对应LED标志，重置计时
void Key_login(){
    unsigned char key = Key_Scan();
    switch(key){
        case 1: // S4按下：触发L1，重置3秒计时
            L1_flag = 1;
            L1_cnt = 0;
            break;
        case 2: // S9按下：触发L2，重置3秒计时
            L2_flag = 1;
            L2_cnt = 0;
            break;
        case 3: // S14按下：触发L4，重置3秒计时
            L4_flag = 1;
            L4_cnt = 0;
            blink4_cnt = 0;
            break;
        case 4: // S19按下：触发L5，重置3秒计时
            L5_flag = 1;
            L5_cnt = 0;
            blink5_cnt = 0;
            break;
    }
}