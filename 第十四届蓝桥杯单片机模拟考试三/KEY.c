#include <STC15F2K60S2.H>
#include "Delay.h"

bit S4_flag = 0;
sbit S4 = P3^3;
sbit S5 = P3^2;

unsigned char S5_cnt = 0;

unsigned char Key_Scan(){
    unsigned char key = 0;
    if(S4 == 0){
        Delay100ms();
        while(S4 == 0){
            key = 1;
        }
    }
    if(S5 == 0){
        Delay100ms();
        while(S5 == 0){
            key = 2;
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    switch(key){
        case 1:
            S4_flag = !S4_flag;
            break;
        case 2:
            S5_cnt = (S5_cnt + 1) % 2;
            break;
    }
}