// nhan nut K1 de doi che do, nhan nut K2 de tat toan bo cac che do led

#include <REGX52.H>

sbit K1 = P3^1;
sbit K2 = P3^0;
bit flagPress = 0;

void Delay_ms(unsigned int t)
{
	unsigned int x,y;
	for(x=0;x<t;x++)
	{
		for(y=0;y<123;y++);
	}
}

unsigned int check_press()
{
	unsigned int i;
	for(i=0; i<50;i++)
	{
		Delay_ms(10);
		if(K1==0)
		{
			if(flagPress==0)
			{
				flagPress = 1;
				return 1;
			}
		}
		else
		{
			flagPress = 0;
		}
	}
	return 0;
}

void main()
{
	unsigned int i;
	while(1)
	{	
		if(K1==0)
		{
			Delay_ms(20);
			while(K1==0);
			while(1)
			{
				//che do 1: chop tat led o port 2 - 10 lan
				P2 = 0xFF;
				for(i=0; i<10;i++)
				{
					if(K2 == 0)
					{
						Delay_ms(20);
						break;
					}
					if(check_press()) break;
					P2 = ~P2;
				}
				
				//che do 2: chop tat led xen ke - 10 lan
				P2 = 0x55;
				for(i=0;i<10;i++)
				{
					if(K2 == 0)
					{
						Delay_ms(20);
						break;
					}
					if(check_press()) break;
					P2 = ~P2;
				}
				
				P2 = 0xF0;
				for(i=0; i<10; i++)
				{
					if(K2 == 0)
					{
						Delay_ms(20);
						break;
					}
					if(check_press()) break;
					P2=~P2;
				}
				if(K2==0)
				{
					Delay_ms(20);
					break;
				}
			}
		}
		P2 = 0xFF;
	}
}
