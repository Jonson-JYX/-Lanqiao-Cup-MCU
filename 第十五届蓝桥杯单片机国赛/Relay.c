#include <STC15F2K60S2.H>
#include "Common.h"
#include "KEY.h"

unsigned char Relay_value = 0x00;

void Relay_login(){
    if(Run_flag){
        Relay_value = 0xBF;
    }
    else{
        Relay_value = 0x00;
    }
    REY(Relay_value);
}