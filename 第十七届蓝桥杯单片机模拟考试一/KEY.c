#include <STC15F2K60S2.H>
#include "Delay.h"
#include "LED_Display.h"

unsigned char S4_cnt = 0;
unsigned char S5_cnt = 0;
bit S9_password = 1;
bit num_flag = 1;

unsigned char Key_Scan(){
    unsigned char key = 0;
    P32 = 1;P33 = 0;
    if(P44 == 0){
        Delay100ms();
        while(P44 == 0){
            key = 1;
        }
    }
    if(P42 == 0){
        Delay100ms();
        while(P42 == 0){
            key = 3;
        }
    }
    P32 = 0;P33 = 1;
    if(P44 == 0){
        Delay100ms();
        while(P44 == 0){
            key = 2;
        }
    }
    if(P42 == 0){
        Delay100ms();
        while(P42 == 0){
            key = 4;
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    unsigned char i;
    if(key == 1){
        S4_cnt = (S4_cnt + 1) % 3;
        if(S4_cnt % 3 == 0 || S4_cnt % 3 == 1){
            S5_cnt = 0;
        }
    }
    if(key == 2){
        S5_cnt = (S5_cnt + 1) % 3;
    }
    if(key == 3){
        for(i = 2;i < 8;i++){
            time1_dat_arr[i] = Clear_dat_arr[i];
            time2_dat_arr[i] = Clear_dat_arr[i];
            time3_dat_arr[i] = Clear_dat_arr[i];
        }
    }
    if(key == 4){
        S9_password = 0;
    }
}