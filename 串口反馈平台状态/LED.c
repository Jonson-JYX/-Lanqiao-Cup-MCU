#include <STC15F2K60S2.H>
#include "Common.h"
#include "KEY.h"

unsigned char LED_dat = 0xFF;
void LED_login(){
    if(S4_flag == 1){
        LED_dat &= 0xFE;
    }
    if(S4_flag == 0){
        LED_dat |= 0x01;
    }
    if(S5_flag == 1){
        LED_dat &= 0xFD;
    }
    if(S5_flag == 0){
        LED_dat |= 0x02;
    }
    if(S8_flag == 1){
        LED_dat &= 0xFB;
    }
    if(S8_flag == 0){
        LED_dat |= 0x04;
    }
    if(S9_flag == 1){
        LED_dat &= 0xF7;
    }
    if(S9_flag == 0){
        LED_dat |= 0x08;
    }
	LED(LED_dat);
}