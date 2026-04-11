#include <STC15F2K60S2.H>
#include "Common.h"
#include "DS18B20.h"

unsigned char Relay_value = 0x00;

void Relay_login(){
    if(Temp_value >= Temp_dat * 10){
        Relay_value = 0xBF;
    }
    else{
        Relay_value = 0x00;
    }
    REY(Relay_value);
}