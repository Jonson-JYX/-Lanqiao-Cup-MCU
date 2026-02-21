#include <stc15f2k60s2.h>
#include "Common.h"
#include "KEY.h"
#include "LED.h"
#include "DS18B20.h"
#include "PCF8591.h"

// 段码表
code unsigned char Seg_Table[] = {
    0xc0,	//0
    0xf9,	//1
    0xa4,	//2
    0xb0,	//3
    0x99,	//4
    0x92,	//5
    0x82,	//6
    0xf8,	//7
    0x80,	//8
    0x90,	//9
    0xc1,	//U
    0xff,	//全灭
};

// 显示数组初始化
unsigned char Temperature_Show_Arr[] = {1,11,11,11,11,11,11,11};  // 模式一（温度）
unsigned char Lighting_Show_Arr[]   = {2,11,11,11,11,11,11,11};  // 模式二（光照）
unsigned char Temperature_DAC_Arr[] = {10,11,11,11,11,11,11,11};  // DAC-温度
unsigned char Lighting_DAC_Arr[]   = {10,11,11,11,11,11,11,11};  // DAC-光照
unsigned char dat_arr[]             = {11,11,11,11,11,11,11,11};  // 最终显示数组

// 温度数据解析（
void Temperature_dat_Receive(){
    float temp_float = DS18B20_Read();
    unsigned int dat_receive = temp_float * 10;
    if(dat_receive >= 100){
        Temperature_Show_Arr[5] = dat_receive/100;
        Temperature_Show_Arr[6] = dat_receive%100/10;
        Temperature_Show_Arr[7] = dat_receive%10;
    }
    else if(dat_receive >= 10 && dat_receive < 100){
        Temperature_Show_Arr[5] = 11;
        Temperature_Show_Arr[6] = dat_receive%100/10;
        Temperature_Show_Arr[7] = dat_receive%10;
    }
    else if(dat_receive >= 0 && dat_receive < 10){
        Temperature_Show_Arr[5] = 11;
        Temperature_Show_Arr[6] = 0;
        Temperature_Show_Arr[7] = dat_receive%10;
    }
}

// 光照数据解析
void Lighting_dat_Receive(){
    unsigned char dat_receive = Photoresistor_Read();
    if(dat_receive >= 100){
        Lighting_Show_Arr[5] = dat_receive/100;
        Lighting_Show_Arr[6] = dat_receive%100/10;
        Lighting_Show_Arr[7] = dat_receive%10;
    }
    else if(dat_receive >= 10 && dat_receive < 100){
        Lighting_Show_Arr[5] = 11;
        Lighting_Show_Arr[6] = dat_receive%100/10;
        Lighting_Show_Arr[7] = dat_receive%10;
    }
    else if(dat_receive >= 0 && dat_receive < 10){
        Lighting_Show_Arr[5] = 11;
        Lighting_Show_Arr[6] = 11;
        Lighting_Show_Arr[7] = dat_receive%10;
    }
}

// 温度DAC解析（
void Temperature_DAC_Receive(){
    float temp_original = DS18B20_Read();
    float dac_voltage = 1.0 + (temp_original / 40.0) * 4.0;
    unsigned int dac_scaled = (unsigned int)(dac_voltage * 10);
    
    if(temp_original <= 10){
        Temperature_DAC_Arr[6] = 1;  // 十位：1（对应1.0V）
        Temperature_DAC_Arr[7] = 0;  // 个位：0（仅≤10℃时固定0）
    }
    else if(temp_original >= 40){
        Temperature_DAC_Arr[6] = 5;  // 十位：5（对应5.0V）
        Temperature_DAC_Arr[7] = 0;  // 个位：0（仅≥40℃时固定0）
    }
    else{
        Temperature_DAC_Arr[6] = dac_scaled / 10;  // 十位（如25→2）
        Temperature_DAC_Arr[7] = dac_scaled % 10;  // 个位（如25→5）
    }
}

// 光照DAC解析
void Lighting_DAC_Receive(){
    unsigned char light_original = Photoresistor_Read();
    float dac_voltage = 1.0 + (light_original / 255.0) * 4.0;
    unsigned int dac_scaled = (unsigned int)(dac_voltage * 10);
    
    if(light_original <= 10){
        Lighting_DAC_Arr[6] = 1;  // 十位：1（对应1.0V）
        Lighting_DAC_Arr[7] = 0;  // 个位：0（仅≤10时固定0）
    }
    else if(light_original >= 240){
        Lighting_DAC_Arr[6] = 5;  // 十位：5（对应5.0V）
        Lighting_DAC_Arr[7] = 0;  // 个位：0（仅≥240时固定0）
    }
    else{
        Lighting_DAC_Arr[6] = dac_scaled / 10;  // 十位（实时值）
        Lighting_DAC_Arr[7] = dac_scaled % 10;  // 个位（实时值）
    }
}

// 选择显示数组
void LED_Display_Arr(){
    unsigned char key_state = Key_Work();
    unsigned char is_mode_interface = (key_state >> 4) & 0x01;  // 1=MODE界面，0=DAC界面
    unsigned char current_mode = key_state & 0x0F;             // 1=温度，2=光照
	unsigned char i;

    // 根据界面+模式选择显示数组
    if(is_mode_interface == 1){  // MODE界面
        if(current_mode == 1){   // 模式一：温度
            for(i=0; i<8; i++) dat_arr[i] = Temperature_Show_Arr[i];
            LED(LED_Table[0]);   // 指示灯1亮（温度模式）
        }
		else{                   // 模式二：光照
            for(i=0; i<8; i++) dat_arr[i] = Lighting_Show_Arr[i];
            LED(LED_Table[1]);   // 指示灯2亮（光照模式）
        }
    }
	else{                       // DAC界面
        if(current_mode == 1){   // 模式一→温度DAC
            for(i=0; i<8; i++) dat_arr[i] = Temperature_DAC_Arr[i];
			LED(LED_Table[0]); 
        }
		else{                   // 模式二→光照DAC
            for(i=0; i<8; i++) dat_arr[i] = Lighting_DAC_Arr[i];
			LED(LED_Table[1]);
        }
    }
}

// 数码管显示驱动（
void LED_Display_Show(){
    unsigned char com = 0;
	unsigned char dat;
	unsigned char i;
    LED_Display_Arr();  // 先更新显示数组

    for(i = 0;i < 8;i++){
        COM(0xFF);
        SEG(0xFF);
        COM(1<<com);
        dat = Seg_Table[dat_arr[i]];
        if(i == 6){  
            if(cur_mode == 1){
                dat &= 0x7F;
            }
            else if(cur_mode == 2 && S4_Password == 0){
                dat &= 0x7F;
            }
        }
        SEG(dat);
        Delay1ms();
        com++;
    }
    COM(0xFF);
    SEG(0xFF);
}