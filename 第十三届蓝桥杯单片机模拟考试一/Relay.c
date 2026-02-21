#include <STC15F2K60S2.H>
#include "Common.h"
#include "Timer.h"
#include "DS1302.h"

bit Relay_flag = 0;

void Relay_login(){
    if(time_now[5] == 0 && time_now[4] == 0 && time_now[3] == 0 && time_now[2] == 0){
        Relay_flag = 1;
        realy_cnt = 0;
    }
    if(Relay_flag){
        REY(0xBF);
        if(realy_cnt >= 3000){
            realy_cnt = 0;
            Relay_flag = 0;
            REY(0x00);
        }
    }
}