#include <STC15F2K60S2.H>
#include "Delay.h"

unsigned char S4_cnt = 0;
unsigned char S5_cnt = 0;
int cali_dat = 0;
int temp_dat = 26;

//按键扫描函数
unsigned char Key_Scan(){
    unsigned char key = 0;
    P33 = 0;P32 = 1;
    if(P44 == 0){
        Delay100ms();
        while(P44 == 0){
            key = 1;
        }
    }
    if(P42 == 0){
        Delay100ms();
        while (P42 == 0){
            key = 2;
        }
    }
    P33 = 1;P32 = 0;
    if(P44 == 0){
        Delay100ms();
        while(P44 == 0){
            key = 3;
        }
    }
    if(P42 == 0){
        Delay100ms();
        while (P42 == 0){
            key = 4;
        }
    }
    return key;
}

//按键逻辑函数
void Key_login(){
    unsigned char key = Key_Scan();
    if(key == 1){
        S4_cnt = (S4_cnt + 1) % 3;
    }
    if(key == 2){
        if(S4_cnt % 3 == 1){
            if(cali_dat > -99){
                cali_dat--;
            } 
        }
        if(S4_cnt % 3 == 2){
            if(temp_dat > -99){
                temp_dat--;
            } 
        }
    }
    if(key == 3){
        S5_cnt = (S5_cnt + 1) % 2;
    }
    if(key == 4){
        if(S4_cnt % 3 == 1){
            if(cali_dat < 99){
                cali_dat++;
            }
        }
        if(S4_cnt % 3 == 2){
            if(temp_dat < 99){
                temp_dat++;
            }
        }
    }
}