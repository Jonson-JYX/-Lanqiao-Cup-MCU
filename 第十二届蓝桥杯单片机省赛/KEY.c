#include <STC15F2K60S2.H>
#include "Delay.h"

unsigned char S4_cnt = 0;
unsigned char S5_cnt = 0;
unsigned char Temp_dat = 25;
unsigned char Temporary_dat = 25;

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
void Key_Login(){
    unsigned char key = Key_Scan();
    if(key == 1){
        S5_cnt++;
    }
    if(key == 2){
        if(S4_cnt % 3 == 1){
            Temporary_dat++;
        }
    }
    if(key == 3){
        S4_cnt++;
        Temp_dat = Temporary_dat;
    }
    if(key == 4){
        if(S4_cnt % 3 == 1){
            Temporary_dat--;
        }
    }
}