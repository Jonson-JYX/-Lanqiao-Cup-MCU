#include <STC15F2K60S2.H>
#include "KEY.h"
#include "Common.h"
#include "Distrance.h"

bit Beep_flag = 1;

void Beep_login(){
    if((sound_value >= Distance_max || sound_value <= Distance_min) && Beep_flag == 1){
        BUZ(0xEF);
        Beep_flag = 0;
    }
    else{
        BUZ(0x00);
        Beep_flag = 1;
    }
}