#include <STC15F2K60S2.H>
#include "DS1302.h"
#include "DS18B20.h"
#include "KEY.h"
#include "Common.h"
#include "Timer.h"

unsigned char Relay_value = 0x00;
void Relay_login(){
    if(Relay_value == 0xBF){
        Relay_value = 0x00;
    }
    if(S13_flag){
        if(Time_value[2] == 0 && Time_value[3] == 0 && Time_value[4] == 0 && Time_value[5] == 0){
            Relay_value = 0xBF;
            Relay_flag = 1;
        }
        if(Relay_cnt >= 5000){
            Relay_flag = 0;
            Relay_cnt = 0;
            Relay_value = 0x00;
        }
    }
    else{
        if(Temp_value > Temp_dat * 10){
            Relay_value = 0xBF;
        }
        else{
            Relay_value = 0x00;
        }
    }
    REY(Relay_value);
}