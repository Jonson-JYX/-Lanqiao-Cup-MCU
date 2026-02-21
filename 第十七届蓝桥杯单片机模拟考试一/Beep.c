#include <STC15F2K60S2.H>
#include "Distance.h"
#include "KEY.h"
#include "Common.h"

void Beep_login(){
    if(sound_dat <= 30 && S9_password == 1){
        BUZ(0xEF);
    }
    if(sound_dat > 30 || S9_password == 0){
        BUZ(0x00);
    }
    if(sound_dat > 30){
        S9_password = 1;
    }
}