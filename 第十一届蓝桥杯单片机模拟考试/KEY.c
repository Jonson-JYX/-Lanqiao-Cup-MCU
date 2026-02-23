#include <STC15F2K60S2.H>
#include "Delay.h"
#include "EEPROM.h"
#include "Timer.h"

unsigned char key_password[] = {16,16,16,16,16,16}; // 密码临时数组
unsigned char read_password[] = {16,16,16,16,16,16};
unsigned char key_value = 0;
int num = 0;
bit S12_flag = 0;   //密码修改标志位
bit S16_flag = 0;   //密码输入标志位
bit password = 0;   //密码正确标志位
bit first_flag = 0; //第一次输入密码
bit key_down = 0;   //按键按下检测按键
unsigned char key_num = 0;  //输入密码不同个数累加变量

unsigned char Key_Scan(){
    unsigned char key = 0;
    P30 = 0;P31 = 1;P32 = 1;P33 = 1;
    if(P44 == 0){   //S7
        Delay100ms();
        while(P44 == 0){
            key = 1;
        }
    }
    if(P42 == 0){   //S11
        Delay100ms();
        while(P42 == 0){
            key = 2;
        }
    }
    if(P35 == 0){   //S15
        Delay100ms();
        while(P35 == 0){
            key = 3;
        }
    }
    if(P34 == 0){   //S19
        Delay100ms();
        while(P34 == 0){
            key = 4;
        }
    }
    P30 = 1;P31 = 0;P32 = 1;P33 = 1;
    if(P44 == 0){   //S6
        Delay100ms();
        while(P44 == 0){
            key = 5;
        }
    }
    if(P42 == 0){   //S10
        Delay100ms();
        while(P42 == 0){
            key = 6;
        }
    }
    if(P35 == 0){   //S14
        Delay100ms();
        while(P35 == 0){
            key = 7;
        }
    }
    if(P34 == 0){   //S18
        Delay100ms();
        while(P34 == 0){
            key = 8;
        }
    }
    P30 = 1;P31 = 1;P32 = 0;P33 = 1;
    if(P44 == 0){   //S5
        Delay100ms();
        while(P44 == 0){
            key = 9;
        }
    }
    if(P42 == 0){   //S9
        Delay100ms();
        while(P42 == 0){
            key = 10;
        }
    }
    P30 = 1;P31 = 1;P32 = 1;P33 = 0;
    if(P42 == 0){   //S8
        Delay100ms();
        while(P42 == 0){
            key = 11;
        }
    }
    if(P35 == 0){   //S12
        Delay100ms();
        while(P35 == 0){
            key = 12;
        }
    }
    if(P34 == 0){   //S16
        Delay100ms();
        while(P34 == 0){
            key = 13;
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    unsigned char i;
    switch(key){
        case 1:
            if(S16_flag || S12_flag){
                key_value = 0;
                if(num < 6){
                    key_password[num] = key_value;
                    num++;
                }
            }
            break;
        case 2:
            if(S16_flag || S12_flag){
                key_value = 1;
                if(num < 6){
                    key_password[num] = key_value;
                    num++;
                }
            }
            break;
        case 3:
            if(S16_flag || S12_flag){
                key_value = 2;
                if(num < 6){
                    key_password[num] = key_value;
                    num++;
                }
            }
            break;
        case 4:
            if(S16_flag || S12_flag){
                key_value = 3;
                if(num < 6){
                    key_password[num] = key_value;
                    num++;
                }
            }
            break;
        case 5:
            if(S16_flag || S12_flag){
                key_value = 4;
                if(num < 6){
                    key_password[num] = key_value;
                    num++;
                }
            }
            break;
        case 6:
            if(S16_flag || S12_flag){
                key_value = 5;
                if(num < 6){
                    key_password[num] = key_value;
                    num++;
                }
            }
            break;
        case 7:
            if(S16_flag || S12_flag){
                key_value = 6;
                if(num < 6){
                    key_password[num] = key_value;
                    num++;
                }
            }
            break;
        case 8:
            if(S16_flag || S12_flag){
                key_value = 7;
                if(num < 6){
                    key_password[num] = key_value;
                    num++;
                }
            }
            break;
        case 9:
            if(S16_flag || S12_flag){
                key_value = 8;
                if(num < 6){
                    key_password[num] = key_value;
                    num++;
                }
            }
            break;
        case 10:
            if(S16_flag || S12_flag){
                key_value = 9;
                if(num < 6){
                    key_password[num] = key_value;
                    num++;
                }
            }
            break;
        case 11:
            if(num < 6 && S16_flag){
                key_password[0] = 16;
                key_password[1] = 16;
                key_password[2] = 16;
                key_password[3] = 16;
                key_password[4] = 16;
                key_password[5] = 16;
                num = 0;
            }
            break;
        case 12:
            if(password){
                S12_flag = 1;
            }
            break;
        case 13:
            S16_flag = 1;
            break;
    }
    if(S16_flag){                //密码输入逻辑
        if(num == 6){
            Read_EEPROM(EEPROM_value,0,6);
            for(i = 0;i < 6;i++){
                read_password[i] = EEPROM_value[i]; 
            }
            for(i = 0;i < 6;i++){
                if(key_password[i] != read_password[i]){
                    key_num++;
                }
            }
            if(key == 13){
                if(key_num == 0){
                    password = 1;
                }
                else{
                    password = 0;
                    first_flag = 1;
                }
                key_num = 0;
                num = 0;
                S16_flag = 0;
                for(i = 0;i < 6;i++){
                    key_password[i] = 16;
                }
            }
        }
    }
    if(S12_flag){    //密码修改逻辑
        if(num == 6){
            for(i = 0;i < 6;i++){
                EEPROM_value[i] = key_password[i];
            }
            if(key == 12){
                Write_EEPROM(EEPROM_value,0,6);
                num = 0;
                S12_flag = 0;
                password = 1;
                for(i = 0;i < 6;i++){
                    key_password[i] = 16;
                }
            } 
        }
    }
    if(key == 0){
        Key_flag = 1;
    }
    if(Key_cnt >= 5000){
        key_down = 1;
        password = 0;
        Key_cnt = 0;
    }
    if(key != 0){
        Key_flag = 0;
        key_down = 0;
    }
}