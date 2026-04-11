#include <STC15F2K60S2.H>
#include "Delay.h"
#include "PCF8591.h"

unsigned char Key_value = 0;   //按键值
unsigned char S4_cnt = 0;     //S4按键计数器
unsigned char S5_cnt1 = 0;     //S5按键计数器
unsigned char S5_cnt2 = 0;     //S5按键计数器
unsigned char S5_cnt3 = 0;     //S5按键计数器

void Key_Scan(){
    P44 = 0;P42 = 1;
    if(P33 == 0){   //S4
        Delay50us();
        if(P33 == 0){
            Key_value = 1;
            while(P33 == 0);
        }
    }
    if(P32 == 0){   //S5
        Delay50us();
        if(P32 == 0){
            Key_value = 2;
            while(P32 == 0);
        }
    }
    P44 = 1;P42 = 0;
    if(P33 == 0){   //S8
        Delay50us();
        if(P33 == 0){
            Key_value = 3;
            while(P33 == 0);
        }
    }
    if(P32 == 0){   //S9
        Delay50us();
        if(P32 == 0){
            Key_value = 4;
            while(P32 == 0);
        }
    }
}

void Key_login(){
    switch(Key_value){
        case 1:     //S4
            S4_cnt += (S4_cnt + 1) % 3;
            S5_cnt1 = 0;
            S5_cnt2 = 0;
            S5_cnt3 = 0;
            break;
        case 2:     //S5
            switch(S4_cnt){
                case 0:
                    S5_cnt1 += (S5_cnt1 + 1) % 4;
                    S5_cnt2 = 0;
                    S5_cnt3 = 0;
                    break;
                case 1:
                    S5_cnt2 += (S5_cnt2 + 1) % 8;
                    S5_cnt1 = 0;
                    S5_cnt3 = 0;
                    break;
                case 2:
                    S5_cnt3 += (S5_cnt3 + 1) % 5;
                    S5_cnt1 = 0;
                    S5_cnt2 = 0;
                    break;
            }
            break;
        case 3:     //S8
            if(S4_cnt == 2){
                RB2_value += 1;
            }
            break;
        case 4:     //S9
            if(S4_cnt == 2){
                RB2_value -= 1;
            }
            break;
        default:
            break;
    }
}