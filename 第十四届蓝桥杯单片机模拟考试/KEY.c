#include <STC15F2K60S2.H>
#include "Delay.h"
#include "Uart.h"
#include "Distance.h"

unsigned char S4_cnt = 0;
int sound_value = 30;

unsigned char Key_Scan(){
    unsigned char key = 0;
    P32 = 0;P33 = 1;
    if(P42 == 0){
        Delay100ms();
        while(P42 == 0){
            key = 1;
        }
    }
    P32 = 1;P33 = 0;
    if(P44 == 0){
        Delay100ms();
        while(P44 == 0){
            key = 2;
        }
    }
    if(P42 == 0){
        Delay100ms();
        while(P42 == 0){
            key = 3;
        }
    }
    if(P35 == 0){
        Delay100ms();
        while(P35 == 0){
            key = 4;
        }
    }
    if(P34 == 0){
        Delay100ms();
        while(P34 == 0){
            key = 5;
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    if(key == 1){
        if(S4_cnt % 2 == 0){
            Uart_Send_dat();
        }
    }
    if(key == 2){
        S4_cnt = (S4_cnt + 1) % 2;
    }
    if(key == 3){
        if(S4_cnt % 2== 0){
            sound_value = sound_dat; 
        } 
    }
    if(key == 4){
        if(S4_cnt % 2 == 1){
            sound_value += 10;
        }
    }
    if(key == 5){
        if(S4_cnt % 2 == 0){
            if(sound_value >= 10){
                sound_value -= 10;
            }
        }
    }
}