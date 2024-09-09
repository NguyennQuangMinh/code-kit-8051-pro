
// su dung thu vien LCD 4 bit 2 hang

#include "main.h"
#include "port.h"
#include "C:\hoc\8051\bai_tap\Library\Delay\Delay.h"
#include "C:\hoc\8051\bai_tap\Library\LCD16x2_4bit\LCD4.h"


void main()
{
	LCD_RW = 0; //KHOI TAO LCD CHE DO GHI

	Lcd_Init();// khoi tao LCD
	
	Lcd_Chr(1, 2, 'A'); //xuat ra ky tu 'A' tai vi tri hang 1 cot 2
	Lcd_Chr_Cp('B'); 		// xuat ky tu 'B' tai vi tri cua con tro tren man hinh dang chi toi
	
	Delay_ms(5000);
	Lcd_Cmd(_LCD_CLEAR);//sau 5 giay se xoa trang man hinh va dat con tro ve vi tri ban dau
	
	Delay_ms(2000);
	Lcd_Out_Cp("HELLO"); // xuat chuoi "HELLO" tai vi tri con tro tren man hinh dang chi toi sau 2 giay
	Lcd_Out(2, 1, "WORLD");//xuat chuoi "WORLD" ra vi tri hang 2 cot 1

	while(1)
	{
	
	}
}
