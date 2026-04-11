#include <STC15F2K60S2.H>
#include "Delay.h"
#include "PCF8591.h"
#include "LED.h"
#include "Timer.h"
#include "NE555.h"

sbit S4 = P3^3;
sbit S5 = P3^2;
sbit S6 = P3^1;
sbit S7 = P3^0;

unsigned char xdata key_value = 0;
unsigned char xdata S4_cnt = 0;
unsigned char xdata S5_cnt = 0;

void Key_Scan(){
    key_value = 0;
    if(S4 == 0){
        Delay100ms();
        if(S4 == 0){
            key_value = 1;
        }
    }
    if(S5 == 0){
        Delay100ms();
        if(S5 == 0){
            key_value = 2;
        }
    }
    if(S6 == 0){
        Delay100ms();
        if(S6 == 0){
            key_value = 3;
        }
    }
    if(S7 == 0){
        Delay100ms();
        if(S7 == 0){
            S7_flag = 1;
            while(1){
                if(S7 == 0){
                    if(S7_cnt >= 1000){
                        if(S7 == 0){
                            Delay100ms();
                            if(S7 == 0){
                                S7_flag = 0;
                                key_value = 5;
                                break;
                            }
                            else{
                                key_value = 4;
                                break;
                            }
                        }
                        else{
                            key_value = 4;
                            break;
                        }
                    }
                }
                else{
                    key_value = 4;
                    break;
                }
            }
        }
    }
}

void Key_login(){
    switch(key_value){
        case 1: 
            S4_cnt = (S4_cnt + 1) % 3;
            if(S4_cnt != 2){
                S5_cnt = 0;
            }
            break;
        case 2: 
            if(S4_cnt == 2){
                S5_cnt = (S5_cnt + 1) % 2;
            }
        case 3:
            RB2_dat = RB2_value;
            break;
        case 4:
            NE555_dat = NE555_value;
            break;
        case 5:
            LED_flag = !LED_flag;
            break;
    }
}