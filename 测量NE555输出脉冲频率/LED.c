#include <STC15F2K60S2.H>
#include "NE555.h"
#include "Timer.h"
#include "KEY.h"
#include "Common.h"

#define L1_BIT 0x01  
#define L2_BIT 0x02

void LED_login(){
    unsigned char led_status = 0xFF;  
    if(S4_cnt % 4 == 0){
        if(LED1_flag == 0){  
            led_status &= ~L1_BIT;  
        }
    }
    if(NE555_now < 0){  
        led_status &= ~L2_BIT;
    }
    else if(NE555_now > NE555_PF){  
        if(LED2_flag == 0){
            led_status &= ~L2_BIT;
        }
    }
    
    LED(led_status);
}