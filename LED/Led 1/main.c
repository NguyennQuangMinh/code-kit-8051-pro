// nhap nhay 1 led o chan bat ky 

#include <REGX52.H>

void Delay_ms(unsigned int t) //tao ham delay_ms
{
	unsigned int x, y;
	for(x=0; x<t; x++)
	{
		for(y=0; y<123; y++);
	}
}

void main()
{
	while(1)
	{
		P2_1=!P2_1; // dao trang thai led o chan P2_1
		Delay_ms(500); // Delay 500ms 
	}
	
}