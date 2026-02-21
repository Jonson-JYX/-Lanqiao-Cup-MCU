#include <STC15F2K60S2.H>
#include "NE555.h"
#include "Delay.h"

unsigned char S4_cnt = 0;
unsigned char S5_para_cnt = 0;  //参数
unsigned char S5_echo_cnt = 0;  //回显

unsigned char Key_Scan(){
    unsigned char key = 0;
    P32 = 0;P33 = 1;
    if(P44 == 0){   //S5
        Delay100ms();
        while(P44 == 0){
            key = 1;
        }
    }
    if(P42 == 0){   //S9
        Delay100ms();
        while(P42 == 0){
            key = 2;
        }
    }
    P32 = 1;P33 = 0;
    if(P44 == 0){   //S4
        Delay100ms();
        while(P44 == 0){
            key = 3;
        }
    }
    if(P42 == 0){   //S4
        Delay100ms();
        while(P42 == 0){
            key = 4;
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    if(key == 1){
        if(S4_cnt % 4 == 1){
            S5_para_cnt = (S5_para_cnt + 1) % 2;
        }
        if(S4_cnt % 4 == 3){
            S5_echo_cnt = (S5_echo_cnt + 1) % 2;
        }
    }
    if(key == 2){
        if(S4_cnt % 4 == 1 && S5_para_cnt % 2 == 0){
            if(NE555_PF > 1000){
                NE555_PF -= 1000;
            }
        }
        if(S4_cnt % 4 == 1 && S5_para_cnt % 2 == 1){
            if(NE555_cali > -900){
                NE555_cali -= 100;
            }
        }
    }
    if(key == 3){
        S4_cnt = (S4_cnt + 1) % 4;
		if(S4_cnt % 4 != 1){
			S5_para_cnt = 0;
		}
		if(S4_cnt % 4 != 3){
			S5_echo_cnt = 0;
		}
    }
    if(key == 4){
        if(S4_cnt % 4 == 1 && S5_para_cnt % 2 == 0){
            if(NE555_PF < 9000){
                NE555_PF += 1000;
            }
        }
        if(S4_cnt % 4 == 1 && S5_para_cnt % 2 == 1){
            if(NE555_cali < 900){
                NE555_cali += 100;
            }
        }
    }
}