#ifndef EEPROM_H
#define EEPROM_H
extern unsigned char EEPROM_value[];
void Write_EEPROM(unsigned char *dat,unsigned char addr,unsigned char num);
void Read_EEPROM(unsigned char *dat,unsigned char addr,unsigned char num);
#endif // !EEPROM_H