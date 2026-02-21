#include <stc15f2k60s2.h>
#include "Delay.h"

//界面模式锁
bit KEY_Password = 0;
//S4按键模式计数器（初始化为1，确保默认时间界面）
unsigned char S4_Cnt = 1;
unsigned char S4 = 1;  // 初始化默认模式为1（时间界面）
unsigned char S5;

//按键键值存储表
code unsigned char KEY_Value[12] = {
    0,1,2,3,4,5,6,7,8,9,10,11
};

//按键扫描函数
unsigned char KEY_Scan(){
    // 新增：默认返回无按键（0xFF），避免返回随机值
    unsigned char key = 0xFF;
    //第二行扫描
    P31 = 0;P32 = 1;P33 = 1;
    if(P44 == 0){
        Delay10ms();
        while(P44 == 0); // 等待按键释放，避免重复触发
        key = KEY_Value[0];
    }else if(P42 == 0){
        Delay10ms();
        while(P42 == 0);
        key = KEY_Value[1];
    }else if(P35 == 0){
        Delay10ms();
        while(P35 == 0);
        key = KEY_Value[2];
    }else if(P34 == 0){
        Delay10ms();
        while(P34 == 0);
        key = KEY_Value[3];
    }
    //第三行扫描
    P31 = 1;P32 = 0;P33 = 1;
    if(P44 == 0){
        Delay10ms();
        while(P44 == 0);
        key = KEY_Value[10];
    }else if(P42 == 0){
        Delay10ms();
        while(P42 == 0);
        key = KEY_Value[4];
    }else if(P35 == 0){
        Delay10ms();
        while(P35 == 0);
        key = KEY_Value[5];
    }else if(P34 == 0){
        Delay10ms();
        while(P34 == 0);
        key = KEY_Value[6];
    }
    //第四行扫描
    P31 = 1;P32 = 1;P33 = 0;
    if(P44 == 0){
        Delay10ms();
        while(P44 == 0);
        key = KEY_Value[11];
    }else if(P42 == 0){
        Delay10ms();
        while(P42 == 0);
        key = KEY_Value[7];
    }else if(P35 == 0){
        Delay10ms();
        while(P35 == 0);
        key = KEY_Value[8];
    }else if(P34 == 0){
        Delay10ms();
        while(P34 == 0);
        key = KEY_Value[9];
    }
    return key;
}

//按键S4函数
unsigned char KEY_S4(){
    if(S4_Cnt > 3){
        S4_Cnt = 1;
    }
    // 返回当前界面模式
    return S4_Cnt;
}

//按键S5函数
unsigned char KEY_S5(){
    return 4;
}

//按键综合函数
unsigned char KEY_ALL(){
    unsigned char num = KEY_Scan();
    if(num == 11){ // S4按键（切换界面）
        S4_Cnt++;
        S4 = KEY_S4();
        if(S4 == 2){
            KEY_Password = 1; // 输入界面解锁
        }else{
            KEY_Password = 0; // 其他界面锁定输入
        }
        return S4;
    }else if(num == 10){ // S5按键（清除输入）
        S5 = KEY_S5();
        return S5;
    }
    // 无按键时返回当前默认模式（确保初始界面为时间界面）
    return S4;
}