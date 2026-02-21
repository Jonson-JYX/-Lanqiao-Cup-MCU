#include <STC15F2K60S2.H>
#include "KEY.h"
#include "Common.h"

void LED_login(){
    if(S4_cnt % 3 == 0){
        LED(0xFE);
    }
    if(S4_cnt % 3 == 1){
        LED(0xFD);
    }
    if(S4_cnt % 3 == 2){
        LED(0xFB);
    }
}