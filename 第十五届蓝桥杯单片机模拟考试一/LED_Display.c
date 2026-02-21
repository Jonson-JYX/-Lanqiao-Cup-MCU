#include <stc15f2k60s2.h>
#include "KEY.h"
#include "Common.h"
#include "DS1302.h"
#include "LED.h"
#include "E2PROM.h"

bit LED4_Password = 0;
unsigned char max = 0;

code unsigned char LED_Display_Value[14] = {
    0xC0,   // 0
    0xF9,   // 1
    0xA4,   // 2
    0xB0,   // 3
    0x99,   // 4
    0x92,   // 5
    0x82,   // 6
    0xF8,   // 7
    0x80,   // 8
    0x90,   // 9
    0xBF,   // -
    0xC6,   // C
    0x86,   // E
    0xFF    // 全灭
};
unsigned char Scanf_Cnt = 0;
//时间界面存储数组
unsigned char Time_Arr[8] = {13,13,13,13,13,13,13,13};
//输入界面存储数组
unsigned char Scanf_Arr[8] = {11,13,13,13,13,13,13,13};
//记录界面存储数组
unsigned char Record_Arr[8] = {12,13,13,13,13,10,13,13};

//输入界面清除函数
void Scanf_Delete(){
	unsigned char i;
    Scanf_Arr[0] = 11;
    for(i=1; i<8; i++){ // 简化清空逻辑
        Scanf_Arr[i] = 13;
    }
    Scanf_Cnt = 0; //清空输入计数
}

//时间界面显示函数
void Time_Show(){
	unsigned char i;
    unsigned char *time = ReadRTC(); // 每次调用都读取最新时间
    for(i=0; i<8; i++){
        Time_Arr[i] = time[i];
    }
}

//输入界面显示函数（数字输入逻辑）
void Scanf_Show(){
    unsigned char num = KEY_Scan();
    unsigned int value = 0;
	unsigned char *rtc;
	unsigned char hour;
	unsigned char min;
	unsigned char i;
    if(KEY_Password == 1){ // 仅输入界面解锁时处理输入
        if((num >= 0 && num <= 9) && (Scanf_Cnt < 4)){ 
            for(i = 4; i < 8; i++){ 
                Scanf_Arr[i] = Scanf_Arr[i+1];
            }
            Scanf_Arr[7] = num; // 
            Scanf_Cnt++;
        }
        if(Scanf_Cnt == 4){ // 4位输入完成
            value = Scanf_Arr[4]*1000 + Scanf_Arr[5]*100 + Scanf_Arr[6]*10 + Scanf_Arr[7];
            if(value > max){
                LED4_Password = 1;
                // 存储输入数据到E2PROM
                *rtc = ReadRTC();
				hour = rtc[0]*10 + rtc[1];
                min = rtc[3]*10 + rtc[4];
                Save_Data_To_E2PROM(hour, min, value);
                max = value; // 更新最大值
            }
        }
    }
}

//记录界面显示函数
void Record_Show(){
    unsigned char *record = Read_Record_Time_To_4Array(); //读取E2PROM存储的时间
    Record_Arr[3] = record[0];
    Record_Arr[4] = record[1];
    Record_Arr[5] = 10; // 分隔符'-'
    Record_Arr[6] = record[2];
    Record_Arr[7] = record[3];
}

//数码管显示函数
void LED_Display_Show(){
    unsigned char com = 0;  // 位选存储
    unsigned char dat = 0;  // 数据缓存区
    unsigned char dat_Arr[8];   //存储不同界面的数组
    unsigned char i;    // 循环显示值
    unsigned char modle = KEY_ALL(); // 获取当前界面模式（含默认值）
    
    // 初始化显示数组为全灭，避免乱码
    for(i=0; i<8; i++){
        dat_Arr[i] = 13;
    }

    if(modle == 1){ // 时间界面
        Time_Show(); // 每次都读取最新时间
        for(i=0; i<8; i++){
            dat_Arr[i] = Time_Arr[i];
        }
        LED(LED4_Password ? LED_Value[3] : LED_Value[0]);
    } 
	else if(modle == 2){ // 输入界面
        Scanf_Show();
        for(i=0; i<8; i++){
            dat_Arr[i] = Scanf_Arr[i];
        }
        LED(LED4_Password ? LED_Value[4] : LED_Value[1]);
    } 
	else if(modle == 3){ // 记录界面
        Record_Show();
        for(i=0; i<8; i++){
            dat_Arr[i] = Record_Arr[i];
        }
        LED(LED4_Password ? LED_Value[5] : LED_Value[2]);
    } 
	else if(modle == 4){ // 清除界面
        Scanf_Delete();
        for(i=0; i<8; i++){
            dat_Arr[i] = Scanf_Arr[i];
        }
        LED(LED_Value[1]);
        LED4_Password = 0; // 清除后重置标志
    }

    // 数码管扫描显示
    for(i=0; i<8; i++){
        SEG(0xFF); // 消影
        COM(0x00); // 关闭所有位
        COM(1 << com); // 选通当前位
        dat = LED_Display_Value[dat_Arr[i]];
        SEG(dat); // 输出段码
        com++;
    }
    // 显示完成后关闭所有位和段，消影
	com = 0;
    SEG(0xFF);
    COM(0x00);
}