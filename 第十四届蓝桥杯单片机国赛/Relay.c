#include <STC15F2K60S2.H>
#include "Common.h"
#include "Ultrasound.h"
#include "DS18B20.h"

unsigned char Relay_value = 0x00;

void Relay_login(){
    if((Sound_value >= -5 && Sound_value <= Sound_dat + 5) && Temp_value <= Temp_dat * 10){
        Relay_value = 0xBF;
    }
    else{
        Relay_value = 0x00;
    }
    REY(Relay_value);
}