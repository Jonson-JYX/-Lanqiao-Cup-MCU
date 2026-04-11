#include <STC15F2K60S2.H>
#include "Sound.h"
#include "NE555.h"
#include "Timer.h"

float H1 = 1.0; //液位上限
float H2 = 0.1; //液位下限
unsigned char S = 2; //容器类型
float R = 1.0; //半径
float L = 1.0; //长度
float W = 1.0; //宽度
float H = 1.0; //高度

unsigned int Wainning = 0; //报警标志
bit Wainning_flag1 = 0; //报警状态标志
bit Wainning_flag2 = 0; //报警状态标志
bit Wainning_flag3 = 0; //报警状态标志
bit Wainning_flag4 = 0; //报警状态标志
bit Wainning_flag5 = 0; //报警状态标志

void S_Scan(){
    float h;
    switch(S){
        case 0: 
            h = (unsigned int)((2.0 * R * 100.0) - (float)Sound_value); //计算液位高度
            break;
        case 1: 
            h = (unsigned int)(H * 100.0 - (float)Sound_value); //计算液位高度
            break;
        case 2: 
            h = (unsigned int)(H * 100.0 - (float)Sound_value); //计算液位高度
            break;
    }
    
    if(h > H1 * 100.0){
        Wainning = 500;
        Wainning_flag1 = 1;
        Wainning_flag2 = 0;
        Wainning_flag3 = 0;
        Wainning_flag4 = 0;
        Wainning_flag5 = 0;
    }
    if(h < H2 * 100.0){
        Wainning = 501;
        Wainning_flag1 = 0;
        Wainning_flag2 = 1;
        Wainning_flag3 = 0;
        Wainning_flag4 = 0;
        Wainning_flag5 = 0;
    }
    if(NE555_value > NE555_dat){
        Wainning = 502;
        Wainning_flag1 = 0;
        Wainning_flag2 = 0;
        Wainning_flag3 = 1;
        Wainning_flag4 = 0;
        Wainning_flag5 = 0;
    }
    if(NE555_waining_flag != 0){
        Wainning = 503;
        Wainning_flag1 = 0;
        Wainning_flag2 = 0;
        Wainning_flag3 = 0;
        Wainning_flag4 = 1;
        Wainning_flag5 = 0;
    }
    if(NE555_change_dat > 1000){
        Wainning = 504;
        Wainning_flag1 = 0;
        Wainning_flag2 = 0;
        Wainning_flag3 = 0;
        Wainning_flag4 = 0;
        Wainning_flag5 = 1;
    }
}

void Tank_login(){
    if(Tank_cnt >= 200){
        Tank_cnt = 0;
        S_Scan();
    }
}