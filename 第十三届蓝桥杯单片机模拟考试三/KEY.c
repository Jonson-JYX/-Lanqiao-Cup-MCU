#include <STC15F2K60S2.H>
#include "Delay.h"

unsigned char S4_cnt = 0;
int Distance_min = 0;
int Distance_max = 50;

unsigned char Key_Scan(){
    unsigned char key = 0;
    P33 = 0;
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
    if(P35 == 0){
        Delay100ms();
        while(P35 == 0){
            key = 3;
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    switch(key){
        case 1:
            S4_cnt = (S4_cnt + 1) % 3;
            break;
        case 2:
            switch(S4_cnt){
                case 1:
                    Distance_max += 10;
                    break;
                case 2:
                    Distance_min += 10;
                    break;
            }
            break;
        case 3:
            switch(S4_cnt){
                case 1:
                    Distance_max -= 10;
                    break;
                case 2:
                    Distance_min -= 10;
                    break;
            }
            break;
    }
}