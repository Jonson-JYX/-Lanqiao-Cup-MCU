#include "stc15f2k60s2.h"
#include "intrins.h"
#include "Delay.h"  
#include "DS1302.h" 
#include "E2PROM.h"

sbit SCL = P1^5;
sbit SDA1 = P1^4;

// 格式：[0]=时十位、[1]=时个位、[2]=分十位、[3]=分个位
unsigned char g_FirstInputTime[TIME_ARRAY_LEN] = {0};

// 标记：是否已记录首次数字键时间（避免重复记录）
static bit g_FirstInputFlag = 0;

// ------------------- I2C底层时序 -------------------
void I2C_Start(void)
{
    SDA1 = 1;
    SCL = 1;
    _nop_();
    SDA1 = 0;
    _nop_();
    SCL = 0;
}

void I2C_Stop(void)
{
    SDA1 = 0;
    SCL = 1;
    _nop_();
    SDA1 = 1;
    _nop_();
}

void I2C_Ack(void)
{
    SDA1 = 0;
    _nop_();
    SCL = 1;
    _nop_();
    SCL = 0;
    SDA1 = 1;
}

bit I2C_WaitAck(void)
{
    bit ack_flag;
    SDA1 = 1;
    _nop_();
    SCL = 1;
    _nop_();
    ack_flag = SDA;
    SCL = 0;
    return ack_flag;
}

void I2C_SendByte(unsigned char dat)
{
    unsigned char i;
    for(i=0; i<8; i++)
    {
        SCL = 0;
        _nop_();
        SDA1 = (dat & 0x80) >> 7;
        dat <<= 1;
        _nop_();
        SCL = 1;
        _nop_();
    }
    SCL = 0;
}

unsigned char I2C_RecvByte(void)
{
    unsigned char i, dat = 0;
    SCL = 0;
    SDA1 = 1;
    for(i=0; i<8; i++)
    {
        _nop_();
        SCL = 1;
        _nop_();
        dat = (dat << 1) | SDA;
        SCL = 0;
        _nop_();
    }
    return dat;
}

// ------------------- E2PROM基础操作 -------------------
void I2C_Init(void)
{
    SCL = 1;
    _nop_();
    SDA1 = 1;
    _nop_();
}

void E2PROM_Write(unsigned char addr, unsigned char dat)
{
    I2C_Start();
    I2C_SendByte(0xA0);
    I2C_WaitAck();
    I2C_SendByte(addr);
    I2C_WaitAck();
    I2C_SendByte(dat);
    I2C_WaitAck();
    I2C_Stop();
    Delay10ms();
}

unsigned char E2PROM_Read(unsigned char addr)
{
    unsigned char dat;
    I2C_Start();
    I2C_SendByte(0xA0);
    I2C_WaitAck();
    I2C_SendByte(addr);
    I2C_WaitAck();

    I2C_Start();
    I2C_SendByte(0xA1);
    I2C_WaitAck();
    dat = I2C_RecvByte();
    I2C_Stop();
    return dat;
}

void Save_Data_To_E2PROM(unsigned char hour, unsigned char min, unsigned int input_data)
{
    unsigned char high_byte = input_data / 100;
    unsigned char low_byte = input_data % 100;
    E2PROM_Write(0, hour);
    E2PROM_Write(1, min);
    E2PROM_Write(2, high_byte);
    E2PROM_Write(3, low_byte);
}

unsigned int Read_Last_Data_From_E2PROM(void)
{
    unsigned char high = E2PROM_Read(2);
    unsigned char low = E2PROM_Read(3);
    return (high * 100) + low;
}

// 记录首次数字键时间 
unsigned char* Record_First_Input_Time(void)
{
    // 仅首次调用时记录时间
    if(g_FirstInputFlag == 0)
    {
        unsigned char *rtc = ReadRTC(); // 读取DS1302实时时间（你的原有函数）
        // 解析时间为四位数组（BCD码直接拆分，无需转十进制）
        g_FirstInputTime[0] = rtc[0]; // 时十位
        g_FirstInputTime[1] = rtc[1]; // 时个位
        g_FirstInputTime[2] = rtc[3]; // 分十位
        g_FirstInputTime[3] = rtc[4]; // 分个位
        
        g_FirstInputFlag = 1; // 标记已记录，后续调用不再更新
    }
    
    // 返回四位临时数组指针
    return g_FirstInputTime;
}

//从E2PROM读取时间并解析为四位数组 
unsigned char* Read_Record_Time_To_4Array(void)
{
    // 从E2PROM读取存储的时、分（十进制）
    unsigned char hour = E2PROM_Read(0);
    unsigned char min = E2PROM_Read(1);
    
    // 解析为四位数组（十进制拆分为十位+个位）
    g_FirstInputTime[0] = hour / 10;  // 时十位
    g_FirstInputTime[1] = hour % 10;  // 时个位
    g_FirstInputTime[2] = min / 10;   // 分十位
    g_FirstInputTime[3] = min % 10;   // 分个位
    
    return g_FirstInputTime;
}

// 重置首次记录标志
void Reset_First_Input_Flag(void)
{
    g_FirstInputFlag = 0;
    g_FirstInputTime[0] = 0;
    g_FirstInputTime[1] = 0;
    g_FirstInputTime[2] = 0;
    g_FirstInputTime[3] = 0;
}