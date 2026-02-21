#include <STC15F2K60S2.H>
#include "Common.h"
#include "PCF8591.h"
#include "KEY.h"

unsigned char Relay_value = 0x00;

void Relay_login(){
    if(ADC_value < 300 && S4_flag == 1){
        Relay_value = 0xBF;
    }
    else{
        Relay_value = 0x00;
    }
    REY(Relay_value);
}