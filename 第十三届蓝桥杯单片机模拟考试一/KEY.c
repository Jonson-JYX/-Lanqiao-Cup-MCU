#include <STC15F2K60S2.H>
#include "Delay.h"
#include "DS1302.h"

sbit S4 = P3^3;
sbit S5 = P3^2;
sbit S6 = P3^1;
sbit S7 = P3^0;

unsigned char hour = 0;
unsigned char minutes = 0;
unsigned char second = 0;
unsigned char S4_cnt = 0;

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
    if(S6 == 0){
        Delay100ms();
        while(S6 == 0){
            key = 3;
        }
    }
    if(S7 == 0){
        Delay100ms();
        while(S7 == 0){
            key = 4;
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    switch(key){
        case 1:
            S4_cnt = (S4_cnt + 1) % 2;
            break;
        case 2:
            if(S4_cnt % 2 == 0){
                hour++;
            }
            break;
        case 3:
            if(S4_cnt % 2 == 0){
                minutes++;
            }
            break;
        case 4:
            if(S4_cnt % 2 == 0){
                second = time_value[4] * 10 + time_value[5];
            }
            break;
    }
}