#ifndef _E2PROM_H_
#define _E2PROM_H_

#include <stc15f2k60s2.h>

// 定义四位临时数组长度（时十位、时个位、分十位、分个位）
#define TIME_ARRAY_LEN 4

// I2C初始化
void I2C_Init(void);                 

// E2PROM单字节读写
void E2PROM_Write(unsigned char addr, unsigned char dat); 
unsigned char E2PROM_Read(unsigned char addr);           

// 保存数据到E2PROM（时、分、4位输入数据）
void Save_Data_To_E2PROM(unsigned char hour, unsigned char min, unsigned int input_data); 

// 读取上一次存储的4位输入数据
unsigned int Read_Last_Data_From_E2PROM(void);           

//记录首次数字键按下的时间到四位数组，并返回数组指针
unsigned char* Record_First_Input_Time(void);           

//从E2PROM读取存储的时间，解析为四位数组并返回
unsigned char* Read_Record_Time_To_4Array(void);           

#endif