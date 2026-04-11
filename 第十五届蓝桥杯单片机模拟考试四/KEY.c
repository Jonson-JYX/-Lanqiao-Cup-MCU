#include <STC15F2K60S2.H>
#include "Dealy.h"
#include "DS18B20.h"

unsigned char S4_cnt = 0;

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
    if(P42 == 0){   //S9
        Delay100ms();
        if(P42 == 0){
            key = 3;
            while(P42 == 0);
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
            if(S4_cnt % 3 == 2){
                Temp_dat--;
            }
            break;
        case 3:
            if(S4_cnt % 3 == 2){
                Temp_dat++;
            }
            break;
    }
}