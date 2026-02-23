#include <STC15F2K60S2.H>
#include "Delay.h"

unsigned char S12_cnt = 0;
unsigned char key_value = 0;

unsigned char Key_Scan(){
    unsigned char key = 0;
    P32 = 0;P33 = 1;
    if(P42 == 0){   //S9
        Delay100ms();
        while(P42 == 0){
            key = 1;
        }
    }
    if(P35 == 0){   //S13
        Delay100ms();
        while(P35 == 0){
            key = 2;
        }
    }
    P32 = 1;P33 = 0;
    if(P42 == 0){   //S8
        Delay100ms();
        while(P42 == 0){
            key = 3;
        }
    }
    if(P35 == 0){   //S12
        Delay100ms();
        while(P35 == 0){
            key = 4;
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    switch(key){
        case 1:
            key_value = 9;
            break;
        case 2:
            key_value = 13;
            break;
        case 3:
            key_value = 8;
            break;
        case 4:
            S12_cnt = (S12_cnt + 1) % 2;
            key_value = 12;
            break;
    }
}