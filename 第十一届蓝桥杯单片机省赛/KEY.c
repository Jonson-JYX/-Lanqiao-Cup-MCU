#include <STC15F2K60S2.H>
#include "Delay.h"

unsigned int S4_cnt = 0;
unsigned int S5_cnt = 0;
unsigned char Temp_max = 30;
unsigned char Temp_min = 20;
unsigned char Temporarily_max = 30;
unsigned char Temporarily_min = 20;

//按键扫描函数
unsigned char Key_Scan(){
    unsigned char key = 0;
    if(P30 == 0){
        Delay100ms();
        while(P30 == 0){
            key = 1;
        }
    }
    if(P31 == 0){
        Delay100ms();
        while(P31 == 0){
            key = 2;
        }
    }
    if(P32 == 0){
        Delay100ms();
        while(P32 == 0){
            key = 3;
        }
    }
    if(P33 == 0){
        Delay100ms();
        while(P33 == 0){
            key = 4;
        }
    }
    return key;
}

//按键逻辑函数
void Key_login(){
    unsigned char key = Key_Scan();
    if(key == 1){
        if(S5_cnt % 2 == 0){
            if(Temporarily_min >= 0 && Temporarily_min < 100){
                Temporarily_min--;
            }
        }
        if(S5_cnt % 2 == 1){
            if(Temporarily_min >= 0 && Temporarily_min < 100){
                Temporarily_max--;
            }
        }
    }
    if(key == 2){
        if(S5_cnt % 2 == 0){
            if(Temporarily_min >= 0 && Temporarily_min < 100){
                Temporarily_min++;
            }
        }
        if(S5_cnt % 2 == 1){
            if(Temporarily_min >= 0 && Temporarily_min < 100){
                Temporarily_max++;
            }
        }
    }
    if(key == 3){
        if(S4_cnt % 2 == 1){
            S5_cnt++;
        }  
    }
    if(key == 4){
        S4_cnt++;  
        if(Temporarily_max < Temporarily_min){
            S4_cnt--;
        }
        if(Temporarily_max >= Temporarily_min){
            Temp_max = Temporarily_max;
            Temp_min = Temporarily_min;
        }
        if(S4_cnt % 2 == 1){
            S5_cnt = 0;
        }
    }
}