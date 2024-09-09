// mo rong ngo ra su dung IC74HC595
// yeu cau: tao file port.h chua cac ket noi phan cung nhu sau:
//sbit IE74595_SHCP = P2^0;
//sbit IE74595_DS = P2^1;
//sbit IE74595_STCP = P2^2;

#ifndef _IE74595_H_
#define _IE74595_H_

void IE74595_Out(unsigned char *p, unsigned char n);

#endif