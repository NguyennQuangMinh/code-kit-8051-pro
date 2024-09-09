// khai bao chan ket noi cua ic chuyen doi tin hieu adc ET2046(XPT2046)
//sbit DOUT = P3^7;	  
//sbit CLK  = P3^6;	  
//sbit DIN  = P3^4;	  
//sbit CS   = P3^5;	 

#include "C:\hoc\8051\bai_tap\Library\XPT2046\XPT2046.h"
#include "Main.h"
#include "Port.h"

void SPI_Start(void)
{
	CLK = 0;
	CS  = 1;
	DIN = 1;
	CLK = 1;
	CS  = 0;		
}


void SPI_Write(uchar dat)
{
	uchar i;
	CLK = 0;
	for(i=0; i<8; i++)
	{
		DIN = dat >> 7;  	
		dat <<= 1;
		CLK = 0;			
		CLK = 1;

	}
}

uint SPI_Read(void)
{
	uint i, dat=0;
	CLK = 0;
	for(i=0; i<12; i++)	
	{
		dat <<= 1;

		CLK = 1;
		CLK = 0;

		dat |= DOUT;

	}
	return dat;	
}

uint Read_AD_Data(uchar cmd)
{
	uchar i;
	uint AD_Value;
	CLK = 0;
	CS  = 0;
	SPI_Write(cmd);
	for(i=6; i>0; i--); 
	CLK = 1;	
	_nop_();
	_nop_();
	CLK = 0;
	_nop_();
	_nop_();
	AD_Value=SPI_Read();
	CS = 1;
	return AD_Value;	
}
