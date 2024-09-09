#include <REGX52.H>

void Delay_ms(unsigned int t)
{
	unsigned int x, y;
	for(x =0; x<t; x++)
	{
		for(y=0; y<123; y++);
	}
}

void main()
{
	unsigned char i;
//	P0 = 0x52;
//	Delay_ms(3000);
//	P0 = P0 | (1<<5);  // P0 |= (1<<5) <=> P0 = P0 | 0x20
	while(1)
	{
		P0 = 0x00;
		Delay_ms(500);
		// sang 2 led 1 va giu nguyen trang thai nhung led da sang truoc do tu phai sang trai
		P0 = 0x03;
		for(i=0; i<4; i++)
		{
			Delay_ms(500);
			P0 = P0 << 2;
			P0 = P0 | 0x03;
		}
		Delay_ms(500);
		
		// sang led tu trai qua phai
		P0 = 0x00;
		for(i=0; i<8; i++)
		{
			Delay_ms(500);
			P0 = P0 >> 1;
			P0 = P0 | (1<<7);
		}
		Delay_ms(500);
	}
}
// sua P0 thanh P2 de su dung tren bo kit 8051 pro
