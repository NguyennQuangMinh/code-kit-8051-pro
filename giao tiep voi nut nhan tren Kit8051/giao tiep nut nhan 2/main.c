
// nhan nut K1 se nhap nhay led xen ke, nhan them lan nua se tat

#include <REGX52.H>

sbit K1 = P3^1;
bit flagBTN = 0;

void Delay_ms(unsigned int t)
{
	unsigned int x,y;
	for(x =0; x<t; x++)
	{
		for(y=0; y<123; y++);
	}
}

unsigned int pressBTN()
{
	unsigned int i;
	for(i=0; i<50; i++)
	{	// quet kiem tra lien tuc 50 lan => tong thoi gian quet 1 la 500ms
		Delay_ms(10);
		if( K1==0 )
		{
			if(flagBTN == 0)
			{
				flagBTN = 1;
				return 1;
			}
		}
		else
		{
			flagBTN = 0;
		}
	}
	return 0;
}

void main()
{
	unsigned int cnt=0;
	while(1)
	{
		if(K1 == 0)
		{
			if(pressBTN())
			{
				cnt++;
				if(cnt%2!=0)
				{
					P2 = 0x55;
					while(1)
					{
						if(pressBTN())
						{
							cnt++;
							P2 = 0xFF;
							break;
						}
						P2 = ~P2;
					}				
				}
			}
		}
		
	}
}
