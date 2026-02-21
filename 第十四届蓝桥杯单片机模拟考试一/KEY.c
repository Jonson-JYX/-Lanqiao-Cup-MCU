#include <STC15F2K60S2.H>
#include "Delay.h"

unsigned char S12_cnt = 0;
unsigned char Decibel_value = 65;

//按键扫描函数
unsigned char Key_Scan(){
    unsigned char key = 0;
    P32 = 0;P33 = 1;
    if(P34 == 0){
        Delay100ms();
        while(P34 == 0){
            key = 1;
        }
    }
    P32 = 1;P33 = 0;
    if(P34 == 0){
        Delay100ms();
        while(P34 == 0){
            key = 2;
        }
    }
    if(P35 == 0){
        Delay100ms();
        while(P35 == 0){
            key = 3;
        }
    }
    return key; 
}

//按键逻辑函数
void Key_logic(){
    unsigned char key = Key_Scan();
    switch(key){
        case 1:
            if(S12_cnt % 2 == 1){
                if(Decibel_value >= 5){
                    Decibel_value -= 5;
                }
            }
            break;
        case 2:
            if(S12_cnt % 2 == 1){
                if (Decibel_value <= 85){
                    Decibel_value += 5;
                }
            }
            break;
        case 3:
            S12_cnt = (S12_cnt + 1) % 2;
            break;
    }
}