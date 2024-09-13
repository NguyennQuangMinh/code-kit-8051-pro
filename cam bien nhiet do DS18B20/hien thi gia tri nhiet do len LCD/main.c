// hien thi gia tri nhiet do tu cam bien DS18B20 len LCD

#include "main.h"
#include "C:\hoc\8051\bai_tap\Library\Delay\Delay.h"
#include "C:\hoc\8051\bai_tap\Library\T0_Delay_us\T0_Delay_us.h"
#include "C:\hoc\8051\bai_tap\Library\One Wire\OneWire.h"
#include "C:\hoc\8051\bai_tap\Library\LCD16x2_4bit\LCD4.h"
#include "port.h"

// tap lenh cua cam bien DS18B20
#define DS18B20_SKIP_ROM  					0xCC //gui lenh den toan bo thiet bi (vi o day co 1 con DS18B20 nen su dung SKIP ROM)
#define DS18B20_CONVERT_T						0x44 // gui lenh chuyen doi nhiet do sang DS18B20
#define DS18B20_READ_SCRATCHPAD			0xBE // gui lenh doc gia tri nhiet do tu trong thanh ghi SCRATCHPAD cua DS18B20 ra

void main()
{
	unsigned int temp;
	unsigned int int_part, decimal_part;
	
	// khoi tao LCD
	LCD_RW = 0;
	Lcd_Init();
	
	//thiet lap timer 0 mode 1 (Mode timer 16 bit) (phuc vu giao tiep One Wire)
	TMOD &= 0xF0; //xoa bo nho timer 0
	TMOD |= 0x01; //set cai dat timer 0 chay mode 1
	
	while(1)
	{
		// gui lenh chuyen doi nhiet do sang 
		while(OneWire_Reset());
		OneWire_Write_Byte(DS18B20_SKIP_ROM);
		OneWire_Write_Byte(DS18B20_CONVERT_T);
		
		Delay_ms(800); // thoi gian cho toi da de cam bien DS18B20 chuyen doi
		
		// doc ve gia tri nhiet do
		while(OneWire_Reset());
		OneWire_Write_Byte(DS18B20_SKIP_ROM);
		OneWire_Write_Byte(DS18B20_READ_SCRATCHPAD);
		
		//luu gia tri nhiet do vao bien temp
		temp = OneWire_Read_Byte();						// luu 8 bit thap vao bien temp
		temp = (OneWire_Read_Byte()<<8)|temp;	// luu 8 bit cao va gop voi 8 bit thap de tao thanh bien 16 bit luu gia tri nhiet do
		
		//doc gia tri phan nguyen gia tri nhiet do
		int_part = temp >> 4;
		//doc gia tri thap phan cua nhiet do
		decimal_part = temp & 0x000F;				//lay gia tri thap phan dang nhi phan
		decimal_part = decimal_part*10/16;	// chuyen tu nhi phan sang thap phan
		
		
		//hien thi gia tri nhiet do len man hinh lcd
		Lcd_Out(1,1,"Nhiet do:");
		Lcd_Chr(1,11,int_part/10+0x30);
		Lcd_Chr_Cp(int_part%10+0x30);
		Lcd_Chr_Cp('.');
		Lcd_Chr_Cp(decimal_part+0x30);
		
		Delay_ms(500); // tao mot khoang delay de man hinh LCD khong bi chop tat lien tuc
	}
}
