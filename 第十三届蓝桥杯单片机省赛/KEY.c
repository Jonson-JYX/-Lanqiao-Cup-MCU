#include <STC15F2K60S2.H>
#include "Delay.h"

bit Time_flag = 0;
bit S13_flag = 0;
unsigned char S12_cnt = 0;
unsigned int Temp_dat = 23;

unsigned char Key_Scan(){
    unsigned char key = 0;
    P33 = 0;P32 = 1;
    if(P35 == 0){   //S12
        Delay100ms();
        if(P35 == 0){
            key = 1;
            while(P35 == 0);
        }
    }
    if(P34 == 0){   //S16
        Delay100ms();
        if(P34 == 0){
            key = 2;
            while(P34 == 0);
        }
    }
    P33 = 1;P32 = 0;
    if(P35 == 0){   //S13
        Delay100ms();
        if(P35 == 0){
            key = 3;
            while(P35 == 0);
        }
    }
    if(P34 == 0){   //S17
        Delay100ms();
        if(P34 == 0){
            key = 4;
            while(P34 == 0);
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    switch(key){
        case 1:
            S12_cnt = (S12_cnt + 1) % 3;
            break;
        case 2:
            if(S12_cnt % 3 == 2){
                if(Temp_dat < 99){
                    Temp_dat++;
                }
            }
            break;
        case 3:
            S13_flag = !S13_flag;
            break;
        case 4:
            if(S12_cnt % 3 == 2){
                if(Temp_dat > 10){
                    Temp_dat--;
                }
            }
            if(S12_cnt % 3 == 1){
                Time_flag = !Time_flag;
            }
            break;
    }
}