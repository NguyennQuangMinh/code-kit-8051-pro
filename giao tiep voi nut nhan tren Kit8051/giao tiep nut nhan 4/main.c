// nhan nut K1 vao che do 1: chop tat led
// nhan nut K2 vao che do 2: chop tat xen ke
// nhan nut K3 vao che do 3: chop tat 4 led tren, 4 led duoi
// nhan nut K4 de thoat toan bo cac che do

#include <REGX52.H>

sbit K1 = P3^1;
sbit K2 = P3^0;
sbit K3 = P3^2;
sbit K4 = P3^3;

bit flagPress = 0;

void Delay_ms(unsigned int t) //ham delay
{
	unsigned int x,y;
	for(x=0; x<t; x++)
	{
		for(y=0; y<123; y++);
	}
}

unsigned int checkPress() 
{
	unsigned int i;
	for(i=0; i<50; i++) //check nhan nut 50 lan, moi lan Delay 10ms => mat 500ms de check xem nut nao duoc nhan
	{
		Delay_ms(10);
		if( K1==0 || K2==0 || K3==0 || K4==0)
		{
			if(flagPress==0)
			{
				flagPress = 1;
				return 1;
			}
		}
		else flagPress = 0;
	}
	return 0;
}

void main()
{
	while(1)
	{
		// che do 1
		if(K1 == 0)
		{
			Delay_ms(20);
			while(K1==0);
			P2 = 0x00;
			while(1)
			{
				if(checkPress()) break;
				P2 = ~P2;			
			}

		}
		
		// che do 2
		if(K2 == 0)
		{
			Delay_ms(20);
			while(K2==0);
			P2 = 0x55;
			while(1)
			{
				if(checkPress()) break;
				P2 = ~P2;
			}
		}
		
		// che do 3
		if(K3 == 0)
		{
			Delay_ms(20);
			while(K3==0);
			P2 = 0xF0;
			while(1)
			{
				if(checkPress()) break;
				P2 = ~P2;
			}
		}
		
		// tat toan bo cac led
		if(K4 == 0)
		{
			Delay_ms(20);
			while(K4==0);
			P2 = 0xFF;
			while(1)
			{
				if(checkPress()) break;
			}
		}
	}
}