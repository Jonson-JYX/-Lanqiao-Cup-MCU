#include <STC15F2K60S2.H>
#include "Delay.h"
#include "Distrance.h"

sbit S5 = P3^2;
unsigned int sound_dat = 900;

unsigned char Key_Scan(){
    unsigned char key = 0;
    if(S5 == 0){
        Delay100ms();
        while(S5 == 0){
            key = 1;
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    if(key == 1){
        sound_dat = sound_value;
    }
}