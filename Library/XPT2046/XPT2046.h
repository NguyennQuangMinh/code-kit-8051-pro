// khai bao chan ket noi cua ic chuyen doi tin hieu adc ET2046(XPT2046)
//sbit DOUT = P3^7;	  
//sbit CLK  = P3^6;	  
//sbit DIN  = P3^4;	  
//sbit CS   = P3^5;	 

#ifndef	  __XPT2046_H_
#define   __XPT2046_H_

#include<intrins.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint  unsigned int
#endif

#ifndef ulong
#define ulong  unsigned long
#endif

uint Read_AD_Data(uchar cmd);
uint SPI_Read(void);
void SPI_Write(uchar dat);

#endif





