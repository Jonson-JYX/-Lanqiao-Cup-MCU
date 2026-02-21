#include "stc15f2k60s2.h"
#include "Uart.h"

unsigned char LED_value;
//二进制字符转换为8位数值
unsigned char bin_str(unsigned char *value){
    unsigned char result = 0;
    unsigned char i;
    for (i = 0; i < 8; i++) {
        if (value[i] == '1') {
            result |= (1 << i); // 1灭→置1
        }
    }
    return result;
}
//LED转化函数
void LED_Show(){
	unsigned char *value = Arr_Value();
	LED_value = bin_str(value);
}
