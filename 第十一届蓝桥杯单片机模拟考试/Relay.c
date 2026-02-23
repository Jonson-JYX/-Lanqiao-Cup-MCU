#include <STC15F2K60S2.H>
#include "KEY.h"
#include "Common.h"

unsigned char Relay_value = 0x00;

void Relay_login(){
    if(key_down == 0){
        if(password){
            Relay_value = 0xBF;
        }
        else{
            Relay_value = 0x00;
        }
    }
    else{
        Relay_value = 0x00;
    }
    REY(Relay_value);
}