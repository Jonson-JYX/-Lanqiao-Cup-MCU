#include <STC15F2K60S2.H>
#include "Delay.h"

unsigned char time = 3;
unsigned char ADC_dat = 50;
unsigned char S4_cnt = 0;
bit S5_flag = 0;

unsigned char Key_Scan(){
    unsigned char key = 0;
    P33 = 0;P32 = 1;
    if(P44 == 0){   //S4
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
    if(P42 == 0){   //S9
        Delay100ms();
        while(P42 == 0){
            key = 4;
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    unsigned char dat = S4_cnt % 3;
    switch(key){
        case 1:
            S4_cnt = (S4_cnt + 1) % 3;
            break;
        case 2:
            switch(dat){
                case 1:
                    ADC_dat -= 5;
                    if(ADC_dat < 30){
                        ADC_dat = 90;
                    }
                    break;
                case 2:
                    time -= 1;
                    if(time < 1){
                        time = 10;
                    }
                    break;
            }
            break;
        case 3:
            S5_flag = !S5_flag;
            break;
        case 4:
            switch(dat){
                case 1:
                    ADC_dat += 5;
                    if(ADC_dat > 90){
                        ADC_dat = 30;
                    }
                    break;
                case 2:
                    time += 1;
                    if(time > 10){
                        time = 1;
                    }
                    break;
            }
            break;
    }
}