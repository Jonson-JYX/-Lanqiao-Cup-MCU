#ifndef PCF8591_H
#define PCF8591_H
extern unsigned char Light_dat;   //设置光线临界值
extern unsigned char Light_value;  //实时光线
extern bit Light_flag;
void Light_login();
#endif // !PCF8591_H