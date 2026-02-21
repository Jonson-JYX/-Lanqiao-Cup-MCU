#include <STC15F2K60S2.H>
#include "Common.h"
#include "PCF8591.h"

unsigned char Beep_value = 0x00;

void Beep_login(){
    if(ADC_value >= 360){
        Beep_value = 0xBF;
    }
    else{
        Beep_value = 0x00;
    }
    BUZ(Beep_value);
}