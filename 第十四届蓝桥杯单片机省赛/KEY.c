#include <STC15F2K60S2.H>
#include "Delay.h"
#include "DS18B20.h"
#include "DS1302.h"
#include "NE555.h"
#include "Timer.h"

unsigned char xdata S4_cnt = 0;
unsigned char xdata S5_cnt = 0;

unsigned char Key_Scan(){
    unsigned char key = 0;
    P33 = 0;P32 = 1;
    if(P44 == 0){   //S4
        Delay100ms();
        if(P44 == 0){
            key = 1;
            while(P44 == 0);
        }
    }
    if(P42 == 0){   //S8
        Delay100ms();
        if(P42 == 0){   
            key = 2;
            while(P42 == 0);
        }
    }
    P33 = 1;P32 = 0;
    if(P44 == 0){   //S5
        Delay100ms();
        if(P44 == 0){
            key = 3;
            while(P44 == 0);
        }
    }
    if(P42 == 0){   //S9
        Delay100ms();
        if(P44 == 0){
            S9_flag = 1;
            S9_cnt = 0;
        }
        else{
            S9_flag = 0;
        }
        while(P42 == 0);
        if(S9_cnt >= 2000){
            key = 4;
            S9_flag = 0;
            S9_cnt = 0;
        }
        else{
            key = 5;
        }
    }
    return key;
}

void Key_login(){
    unsigned char xdata key = Key_Scan();
    unsigned char xdata S4 = S4_cnt % 3;
    unsigned char xdata S5 = S5_cnt % 3;
    switch(key){
        case 1:
            S4_cnt = (S4_cnt + 1) % 3;
            break;
        case 2:
            if(S4_cnt % 3 == 2){
                Temp_dat += 1;
            }
            break;
        case 3:
            if(S4_cnt % 3 == 1){
                S5_cnt = (S5_cnt + 1) % 3;
            }
            break;
        case 4:
            Temp_max = 0;
            Temp_Average = 0;
            NE555_max = 0;
            NE555_Average = 0;
            Time_dat[0] = 0;
            Time_dat[1] = 0;
            Time_dat[2] = 0;
            Time_dat[3] = 0;
            break;
        case 5:
            if(S4_cnt % 3 == 2){
                Temp_dat -= 1;
            }
            break;
    }
}