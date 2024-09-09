#include <REGX52.H>

sbit PWM_pin = P2^0;

unsigned int T, Ton, Toff;
unsigned char Ton_TH0_reload, Ton_TL0_reload, Toff_TH0_reload, Toff_TL0_reload;

// ck(us)
void PWM_Init(unsigned int ck) // khoi tao PWM voi chu ky tu chon (us)
{
	PWM_pin = 1;
	// khoi tao T0 mode 1: 16bit
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	EA = 1; //cho phep ngat toan cuc
	ET0 = 1; //cho phep ngat T0
	
	T = ck; //luu gia tri chu ky vao bien T
}

// D tu 0 den 100
void PWM_SetDuty(unsigned char D) // set do rong xung %
{ 
	if(D == 0)
	{
		PWM_pin = 0;
		ET0 = 0; // T0 ngung dem
	}
	else if(D == 100)
	{
		PWM_pin = 1;
		ET0 = 0; // T0 ngung dem
	}
	else
	{
		Ton = T*((unsigned long)D)/100;
		Toff = T - Ton;
		
		// luu gia tri Ton vao bien Ton_TH0_reload va bien Ton_TL0_reload
		Ton_TH0_reload = (65536 - Ton) >> 8; //luu vao 8 bit cao 
		Ton_TL0_reload = (65536 - Ton) & 0x00FF; // luu vao 8 bit thap 
		
		// luu gia tri Toff vao bien Toff_TH0_reload va bien Toff_TL0_reload
		Toff_TH0_reload = (65536 - Toff) >> 8;   // luu vao 8 bit cao
		Toff_TL0_reload = (65536 - Toff) & 0x00FF; // luu vao 8 bit thap
	}

}

void main()
{
	PWM_Init(1000); // khoi tao PWM voi chu ky  1000us <=> 1ms
	PWM_SetDuty(70); // chon do rong xung la x% (x: const)
	TR0 = 1; //cho phep T0 bat dau dem
	while(1)
	{
	
	}
}

void Timer0_overflow() interrupt 1 // chuong trinh ngat T0
{
	PWM_pin = !PWM_pin;
	if( PWM_pin == 0) 
	{
		// luu gia tri Toff vao thanh ghi TH0 va TL0
		TH0 = Toff_TH0_reload; 
		TL0 = Toff_TL0_reload;
	}
	else if(PWM_pin == 1)
	{
		// luu gia tri Ton vao thanh ghi TH0 va TL0
		TH0 = Ton_TH0_reload;
		TL0 = Ton_TL0_reload;
	}
	
}
