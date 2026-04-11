#include <STC15F2K60S2.H>
#include "Delay.h"

sbit S4 = P3^3;
sbit S5 = P3^2;

unsigned char S4_cnt = 0;
unsigned char S5_cnt = 0;
unsigned char key_value = 0;

void Key_Scan(){
    key_value = 0;
    if(S4 == 0){
        Delay100ms();
        if(S4 == 0){
            key_value = 1;
            while(S4 == 0);
        }
    }
    if(S5 == 0){
        Delay100ms();
        if(S5 == 0){
            key_value = 2;
            while(S5 == 0);
        }
    }
}

void Key_login(){
    switch(key_value){
        case 1:
            S4_cnt = (S4_cnt + 1) % 3;
            if(S4_cnt != 1){
                S5_cnt = 0;
            }
            break;
        case 2:
            if(S4_cnt == 1){
                S5_cnt = (S5_cnt + 1) % 2;
            }
            break;
    }
}