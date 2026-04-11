#ifndef PCF8591_H
#define PCF8591_H
extern unsigned int xdata RB2_value;
extern unsigned int xdata Light_value;
extern unsigned int xdata RB2_dat;
void Read_RB2();
void Read_Light();
void RB2_login();
void Light_login();
#endif // !PCF8591_H