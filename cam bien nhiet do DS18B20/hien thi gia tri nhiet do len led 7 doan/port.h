#ifndef _PORT_H_
#define _PORT_H_

//khai bao chan ket noi led 7 doan
#define GPIO_DIG P0

// khai bao chan ket noi cua ic 74hc138
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

// khai bao chan ket noi OneWire
sbit OneWire_PIN = P3^7;

#endif