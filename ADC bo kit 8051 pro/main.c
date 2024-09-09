//doc gia tri ADC hien thi len man hinh LCD
#include "main.h"
#include "C:\hoc\8051\bai_tap\Library\Delay\Delay.h"
#include "Port.h"
#include "C:\hoc\8051\bai_tap\Library\LCD16x2_4bit\LCD4.h"
#include "C:\hoc\8051\bai_tap\Library\XPT2046\XPT2046.h"
#include "String.h"

void main()
{
	unsigned int adc_value, voltage;
	LCD_RW = 0; // khoi tao LCD che do ghi (khai bao dong nay truoc Lcd_Init()
	Lcd_Init(); // khoi tao LCD

	while(1)
	{	
		// doc gia tri ADC
		adc_value = Read_AD_Data(0x94);			//AIN0 doc gia tri tu triet ap AD1 tren bo kit8051 pro
	//	adc_value = Read_AD_Data(0xD4);		//   AIN1
	//	adc_value = Read_AD_Data(0xA4);		//   AIN2 
	//	adc_value = Read_AD_Data(0xE4);		//   AIN3
		Lcd_Out(1,1,"ADC value: ");
		Lcd_Chr_Cp(adc_value/1000 + 0x30);
		Lcd_Chr_Cp(adc_value%1000/100 + 0x30);
		Lcd_Chr_Cp(adc_value%100/10 + 0x30);
		Lcd_Chr_Cp(adc_value%10 + 0x30);
		
		// doc gia tri voltage
		/* do phan giai cua ADC la 2^12 => V = adc_value*(5.0/4095)*1000     */
		
		voltage = (unsigned int)(adc_value*(5.0/4095)*1000);
		Lcd_Out(2,1,"voltage: ");
		Lcd_Chr_Cp(voltage/1000 + 0x30);
		Lcd_Chr_Cp('.');
		Lcd_Chr_Cp(voltage%1000/100 + 0x30);
		Lcd_Chr_Cp(voltage%100/10 + 0x30);
		Lcd_Chr_Cp(voltage%10 + 0x30);
		
		Delay_ms(500); //delay tranh man hinh LCD nhap nhay lien tuc
	
	}
}
