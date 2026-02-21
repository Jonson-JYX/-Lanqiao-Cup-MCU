#include <STC15F2K60S2.H>
#include "Delay.h"

sbit S4 = P3^3;
unsigned char S4_cnt = 0;

unsigned char Key_Scan(){
    unsigned char key = 0;
    if(S4 == 0){
        Delay100ms();
        while(S4 == 0){
            key = 1;
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    if(key == 1){
        S4_cnt = (S4_cnt + 1) % 2;
    }
}