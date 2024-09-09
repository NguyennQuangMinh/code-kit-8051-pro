
// dieu khien led sang dan va tat dan bang PWM

#include "main.h"
#include "C:\hoc\8051\bai_tap\Library\Delay\Delay.h"

unsigned int T, Ton, Toff;
unsigned char Ton_TH0_reload, Ton_TL0_reload, Toff_TH0_reload, Toff_TL0_reload;

// ck(us)
void PWM_Init(unsigned int ck) //khoi tao PWM voi chu ky tu chon (us)
{
	// khoi tao T0 mode 1: 16bit
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	EA = 1; //cho phep ngat toan cuc
	ET0 = 1 ; //cho phep ngat T0
	
	T = ck;
	
	//sau 1us se tran => 65536 - 1000 = 64536 => FC18
	TH0 = 0xFC;
	TL0 = 0x18;
}

// D tu 0 den 100
void PWM_SetDuty(unsigned char D) // do rong xung %
{
	if(D==0)
	{
		P2_0 = 0;
		ET0 = 0; // cam ngat T0
	}
	else if(D==100)
	{
		P2_0 = 1;
		ET0 = 0; // cam ngat T0
	}
	else
	{
		Ton = T * ((unsigned long)D)/100;	
		Toff = T - Ton;
		
		Ton_TH0_reload = (65536 - Ton) >> 8;
		Ton_TL0_reload = (65536 - Ton) &0x00FF;
		
		Toff_TH0_reload = (65536 - Toff) >> 8;
		Toff_TL0_reload = (65536 - Toff) & 0x00FF;
		
		ET0 = 1; //cho phep ngat T0 
	}
}

void main()
{
	unsigned char dir = 0;
  unsigned char	duty = 0;
	
	PWM_Init(1000); // chon chu ky cua xung
	PWM_SetDuty(0); // chon do rong xung x% (x: const)
	TR0 = 1;	// cho phep T0 bat dau dem

	while(1)
	{
		Delay_ms(100);
		//sang dan
		if(dir == 0)
		{
			duty += 2;
			if(duty == 100)
			{
				dir = 1;
			}
		}
		// tat dan
		else
		{
			duty -= 2;
			if(duty == 0)
			{
				dir = 0;
			}
		}
		PWM_SetDuty(duty);
	}
}

void Timer0_Overflow() interrupt 1
{
	P2_0 = !P2_0;
	if(P2_0 == 0)
	{
		TH0 = Toff_TH0_reload;
		TL0 = Toff_TL0_reload;
	}
	else if(P2_0 == 1)
	{
		TH0 = Ton_TH0_reload;
		TL0 = Ton_TL0_reload;
	}
}
