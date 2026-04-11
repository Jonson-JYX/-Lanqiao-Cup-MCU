#ifndef PCF8591_H
#define PCF8591_H
extern unsigned char Light_value;
extern unsigned char xdata Light_Standard;
void Light_login();
unsigned char Read_Light();
#endif // !PCF8591_H