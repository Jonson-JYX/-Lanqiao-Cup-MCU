#include <STC15F2K60S2.H>
#include "Distrance.h"
#include "KEY.h"
#include "Common.h"

void LED_login(){
    if(sound_value > sound_dat){
        LED(0xFE);
    }
    else{
        LED(0xFF);
    }
}