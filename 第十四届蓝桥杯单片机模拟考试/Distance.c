#include <STC15F2K60S2.H>
#include "Delay.h"
#include "Timer.h"

sbit TX = P1^0;
sbit RX = P1^1;

int sound_dat = 0;

//超声波测距
unsigned char Distance_Value(){
    int sound = 0;
    unsigned char i;
    CMOD = 0x01;    //PCA使用系统时钟
    CCON = 0x00;    //清除PCA计数器
    CH = 0x00;      //清除PCA计数器
    CL = 0x00;      //清除PCA计数器
    for(i = 0;i < 8;i++){
        TX = 1;
        Delay12us();
        TX = 0;
        Delay12us();
    }
    CR = 1;         //启动PCA计数器
    while((RX == 1) && (CH <= 0x40)); //等待回声开始
    CR = 0;         //停止PCA计数器
    if(CH > 0x40){ //如果等待超时，返回0
        CF = 0; //清除PCA溢出标志
        return 0;
    }
    sound = (CH<<8) | CL; //记录高8位和低8位
    return sound * 0.0172; 
}

void Read_Sound(){
    if(sound_cnt == 199){
         sound_dat = Distance_Value();
    }
}