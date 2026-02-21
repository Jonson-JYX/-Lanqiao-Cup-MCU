#include <STC15F2K60S2.H>
#include "Delay.h"
#include "LED_Display.h"

unsigned char S4_cnt = 0;
unsigned char S5_cnt = 0;

unsigned char Key_Scan(){
    unsigned char key = 0;
    P33 = 0;P32 = 1;
    if(P44 == 0){   //S4;
        Delay100ms();
        while(P44 == 0){
            key = 1;
        }
    }
    if(P42 == 0){   //S8
        Delay100ms();
        while(P42 == 0){
            key = 2;
        }
    }
    P33 = 1;P32 = 0;
    if(P44 == 0){   //S5
        Delay100ms();
        while(P44 == 0){
            key = 3;
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    unsigned char i;
    switch(key){
        case 1:
            S4_cnt = (S4_cnt + 1) % 3;
            break;
        case 2:
            for(i = 2;i < 8;i++){
                History_dat_arr1[i] = 14;
                History_dat_arr2[i] = 14;
                History_dat_arr3[i] = 14;
            }
            break;
        case 3:
            if(S4_cnt % 3 == 2){
                S5_cnt = (S5_cnt + 1) % 3;
            }
            break;
    }
}