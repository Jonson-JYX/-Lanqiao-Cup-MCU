#include <STC15F2K60S2.H>
#include "Delay.h"
#include "Uart.h"

bit S4_flag = 0;
bit S5_flag = 0;
bit S8_flag = 0;
bit S9_flag = 0;

unsigned char Key_Scan(){
    unsigned char key = 0;
    P33 = 0;P32 = 1;
    if(P44 == 0){   //s4
        Delay100ms();
        while(P44 == 0){
            key = 1;
        }
    }
    if(P42 == 0){   //s8
        Delay100ms();
        while(P42 == 0){
            key = 2;
        }
    }
    if(P35 == 0){   //s12
        Delay100ms();
        while(P35 == 0){
            key = 3;
        }
    }
    P33 = 1;P32 = 0;
    if(P44 == 0){   //s5
        Delay100ms();
        while(P44 == 0){
            key = 4;
        }
    }
    if(P42 == 0){   //s9
        Delay100ms();
        while(P42 == 0){
            key = 5;
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    if(key == 1){
        S4_flag = !S4_flag;
    }
    if(key == 2){
        S8_flag = !S8_flag;
    }
    if(key == 3){
        Read_Uart();
    }
    if(key == 4){
        S5_flag = !S5_flag;
    }
    if(key == 5){
        S9_flag = !S9_flag;
    }
}