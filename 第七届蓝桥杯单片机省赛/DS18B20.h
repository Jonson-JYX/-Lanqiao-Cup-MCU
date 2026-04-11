#ifndef DS18B20_H
#define DS18B20_H
extern unsigned char Temp_value;
extern unsigned char Temp_dat[];
extern unsigned char Temp_num;
float Read_Temp();
void Temp_login();
#endif // !DS18B20_H