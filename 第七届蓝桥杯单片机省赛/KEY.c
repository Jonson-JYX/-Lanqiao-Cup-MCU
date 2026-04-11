#include <STC15F2K60S2.H>
#include "Delay.h"
#include "DS18B20.h"
#include "DS1302.h"
#include "Timer.h"

sbit S4 = P3^3;
sbit S5 = P3^2;
sbit S6 = P3^1;
sbit S7 = P3^0;

bit Setting_flag = 1;
bit Timeing_flag = 0;
bit Collect_flag = 0;

unsigned char Time_setting = 0;
unsigned char Time_fixed = 0;
unsigned char Temp_setting = 0;
unsigned char S4_cnt = 0;
unsigned char S6_cnt = 0;

unsigned char Key_Scan(){
    unsigned char key = 0;
    if(S4 == 0){
        Delay100ms();
        if(S4 == 0){
            key = 1;
            while(S4 == 0);
        }
    }
    if(S5 == 0){
        Delay100ms();
        if(S5 == 0){
            key = 2;
            while(S5 == 0);
        }
    }
    if(S6 == 0){
        Delay100ms();
        if(S6 == 0){
            key = 3;
            while(S6 == 0);
        }
    }
    if(S7 == 0){
        Delay100ms();
        if(S7 == 0){
            key = 4;
            while(S7 == 0);
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    unsigned char i;
    if(Setting_flag){
        Time_setting = Time_dat[S4_cnt]; 
    }
    if(Timeing_flag){
        Temp_flag = 1;
    }
    else{
        Temp_flag = 0;
    }
    if(Collect_flag){
        Temp_setting = Temp_dat[S6_cnt];
    }
    if(Temp_num == 10){
        Collect_flag = 1;
        Timeing_flag = 0;
    }
    switch(key){
        case 1:
            if(Setting_flag){
                S4_cnt = (S4_cnt + 1) % 4;
            }
            break;
        case 2:
            Timeing_flag = 1;
            Setting_flag = 0;
            Time_fixed = Time_setting;
            break;
        case 3:
            if(Collect_flag){
                S6_cnt = (S6_cnt + 1) % 10;
            }
            break;
        case 4:
            Setting_flag = 1;
            Collect_flag = 0;
            Temp_num = 0;
            S6_cnt = 0;
            S4_cnt = 0;
            for(i = 0;i < 8;i++){
                Temp_dat[i] = 0;
            }
            break;
    }
}