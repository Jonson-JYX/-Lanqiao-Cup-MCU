#ifndef DS18B20_H
#define DS18B20_H
extern unsigned char temp_value;   //测量温度值
extern unsigned char temp_dat;    //温度参数
extern bit temp_flag;              //温度标志位
void Temp_login();
#endif // !DS18B20_H