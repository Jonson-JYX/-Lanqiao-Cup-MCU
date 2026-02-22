#include <STC15F2K60S2.H>
#include "Delay.h"
#include "Timer.h"
#include "EEPROM.h"

unsigned char S9_cnt = 0;
unsigned char num = 0;
unsigned char count = 0;

unsigned char Key_Scan(){
    unsigned char key = 0;
    P33 = 0;P32 = 1;
    if(P44 == 0){   //S4
        Delay100ms();
        while(P44 == 0){
            key = 1;
        }
    }
    if(P42 == 0){   
        Delay100ms();  
        S8_flag = 1; 
        S8_cnt = 0;    
        while(P42 == 0){
            if(S8_cnt >= 2000){ 
                key = 2; 
				S8_flag = 0;	
                break;          
            }
        }
        if(S8_flag && key != 2){
            key = 3; 
        }
        S8_flag = 0;
        S8_cnt = 0;
    }
    P33 = 1;P32 = 0;
    if(P44 == 0){   //S5
        Delay100ms();
        while(P44 == 0){
            key = 4;
        }
    }
    if(P42 == 0){   //S9
        Delay100ms();
        while(P42 == 0){
            key = 5;
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    switch(key){
        case 1:
            if(S9_cnt % 2 == 0){
                count ++;
            }
            break;
        case 2:
            if(S9_cnt % 2 == 0){
                count = 0;
            }
            break;
        case 3:
            if(S9_cnt % 2 == 0){
                EEPROM_value[0] = count;
                Write_EEPROM(EEPROM_value,0,1);
				if(EEPROM_value[0] == count){
					num++; // 仅当写入成功时，num累加
				}
            }
            break;
        case 4:
            if(S9_cnt % 2 == 0){
                count --;
            }
            break;
        case 5:
            S9_cnt = (S9_cnt + 1) % 2;
            break;
    }
}