#include"main.h"
#include "C:\hoc\8051\bai_tap\Library\Delay\Delay.h"

sbit K1 = P3^1;

void main()
{
	unsigned int cnt = 0;
	while(1)
	{
		if(K1 == 0 )
		{
			Delay_ms(20);
			while(K1==0); //cho cho den khi nguoi dung nha phim ra
			cnt++;
			if(cnt%2==0)
			{
				P2_0 = 1;
			}
			else
			{
				P2_0 = 0;
			}
		}
	}
}
