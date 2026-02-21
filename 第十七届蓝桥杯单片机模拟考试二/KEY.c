#include <STC15F2K60S2.H>
#include "Delay.h"

unsigned char S4_cnt = 0;
unsigned char S5_cnt = 0;
unsigned int Temp_dat = 30;
unsigned int Light_dat = 100;

//按键扫描函数
unsigned char Key_Scan(){
    unsigned char key = 0;
    P32 = 0;P33 = 1;
    if(P44 == 0){
        Delay100ms();
        while(P44 == 0){
            key = 1;
        }
    }
    if(P42 == 0){
        Delay100ms();
        while(P42 == 0){
            key = 2;
        }
    }
    P32 = 1;P33 = 0;
    if(P44 == 0){
        Delay100ms();
        while(P44 == 0){
            key = 3;
        }
    }
    if(P42 == 0){
        Delay100ms();
        while(P42 == 0){
            key = 4;
        }
    }
    return key;
}

//按键逻辑函数
void Key_Logic(){
    unsigned char key = Key_Scan();
    if(key == 1){
        S5_cnt++;
    }
    if(key == 2){
        if(Temp_dat >= 15){
            Temp_dat -= 5;
        }
        if(Light_dat >= 120){
            Light_dat -= 20;
        }
    }
    if(key == 3){
        S4_cnt++;
        if(S4_cnt % 2 == 0){
            S5_cnt = 0;
        }
    }
    if(key == 4){
        if(Temp_dat <= 45){
            Temp_dat += 5;
        }
        if(Light_dat <= 280){
            Light_dat += 20;
        }
    }
}