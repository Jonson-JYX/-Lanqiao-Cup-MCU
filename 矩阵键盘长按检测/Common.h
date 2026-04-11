#ifndef Common_H
#define Common_H
#define LED(X) {P0 = X;P2 = (P2 & 0x1F) | 0X80;P2 &= 0x1F;}
#define SEG(X) {P0 = X;P2 = (P2 & 0x1F) | 0XE0;P2 &= 0x1F;}
#define COM(X) {P0 = X;P2 = (P2 & 0x1F) | 0XC0;P2 &= 0x1F;}
#define BUZ(X) {P0 = X;P2 = (P2 & 0x1F) | 0XA0;P2 &= 0x1F;}
#define REY(X) {P0 = X;P2 = (P2 & 0x1F) | 0XA0;P2 &= 0x1F;}
#endif