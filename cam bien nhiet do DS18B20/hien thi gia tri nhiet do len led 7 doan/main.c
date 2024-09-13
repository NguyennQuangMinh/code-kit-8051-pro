//hien thi gia tri nhiet do tu cam bien DS18B20 len led 7 doan kit 8051 pro

#include "main.h"
#include "C:\hoc\8051\bai_tap\Library\Delay\Delay.h"
#include "C:\hoc\8051\bai_tap\Library\T0_Delay_us\T0_Delay_us.h"
#include "C:\hoc\8051\bai_tap\Library\One Wire\OneWire.h"
#include "port.h"

#define DS18B20_SKIP_ROM  					0xCC //gui lenh den toan bo thiet bi (vi o day co 1 con DS18B20 nen su dung SKIP ROM)
#define DS18B20_CONVERT_T						0x44 // gui lenh chuyen doi nhiet do sang DS18B20
#define DS18B20_READ_SCRATCHPAD			0xBE // gui lenh doc gia tri nhiet do tu trong thanh ghi SCRATCHPAD cua DS18B20 ra

unsigned char code Code7Seg_ko_dau_cham[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
}; // ma led 7 doan tu 0->9 và tu A->F

unsigned char code Code7Seg_co_dau_cham[] = {0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF, 0xF7, 0xFC, 0xB9, 0xDE, 0xF9, 0xF1};

char DisplayData[8]; // mang tao du lieu cua 8 led 7 doan

// quet led bang ic 74hc138
void DigDisplay()
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		switch(i)
		{
			case(0):
					LSA = 0; LSB = 0; LSC = 0; break;
			case(1):
					LSA = 1; LSB = 0; LSC = 0; break;
			case(2):
					LSA = 0; LSB = 1; LSC = 0; break;
			case(3):
					LSA = 1; LSB = 1; LSC = 0; break;
			case(4):
					LSA = 0; LSB = 0; LSC = 1; break;
			case(5):
					LSA = 1; LSB = 0; LSC = 1; break;
			case(6):
					LSA = 0; LSB = 1; LSC = 1; break;
			case(7):
					LSA = 1; LSB = 1; LSC = 1; break;
		}
		//quet led
		GPIO_DIG = DisplayData[i];
		Delay_ms(1);
		GPIO_DIG = 0x00;
	}
}

void main()
{
	unsigned int delay_counter  = 5000;
	unsigned int temp;
	unsigned char int_part, decimal_part;
	//thiet lap timer 0 mode 1 (Mode timer 16 bit)
	TMOD &= 0xF0; //xoa bo nho timer 0
	TMOD |= 0x01; //set cai dat timer 0 chay mode 1
	
	while(1)
	{
		if(++delay_counter > 1000)	//sau moi 1000 lan dem se cap nhat gia tri 1 lan
		{
			// gui lenh chuyen doi sang DS18B20
			while(OneWire_Reset());
			OneWire_Write_Byte(DS18B20_SKIP_ROM);
			OneWire_Write_Byte(DS18B20_CONVERT_T);
			
			Delay_ms(800);
			
			//gui lenh doc gia tri tu DS18B20 ve
			while(OneWire_Reset());
			OneWire_Write_Byte(DS18B20_SKIP_ROM);
			OneWire_Write_Byte(DS18B20_READ_SCRATCHPAD);
			
			//lay gia tri nhiet do luu vao bien temp
			temp = OneWire_Read_Byte();                 // lay 8 bit thap
			temp = (OneWire_Read_Byte()<<8) | temp;		// lay 8 bit cao ghep voi 8 bit thap luu vao bien temp
			
			//lay gia tri nguyen cua nhiet do
			int_part = temp >> 4;					
			//lay gia tri thap phan cua nhiet do
			decimal_part = temp & 0x000F;   
			decimal_part = decimal_part*10/16;		//doi gia tri tu he 2 sang he 10
			
			// doc gia tri nhiet do luu vao mang DisplayData de quet led
			//hien thi do C
			DisplayData[2] = 0x39; //chu C
			DisplayData[3] = 0x63;	// dau nhiet do
			DisplayData[4]	= Code7Seg_ko_dau_cham[decimal_part]; //hien thi gia tri thap phan
			DisplayData[5] = Code7Seg_co_dau_cham[int_part%10]; //hien thi hang donvi
			DisplayData[6] = Code7Seg_ko_dau_cham[int_part/10];	//hien thi hang don vi
			
			delay_counter = 0;	// dat bien dem cap nhat gia tri ve 0
		}

		DigDisplay();// hien thi gia tri nhiet do len led 7 doan
	}
}
	