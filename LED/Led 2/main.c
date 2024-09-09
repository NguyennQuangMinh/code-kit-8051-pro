//nhap nhay toan bo led

#include <REGX52.H>

void Delay_ms(unsigned int t)
{
	unsigned int x,y;
	for(x=0; x<t; x++)
	{
		for(y=0;y<123;y++);
	}
}
void main()
{
	while(1)
	{
		P2 = ~P2;     // dao trang thai led o port 2
		Delay_ms(500);// Delay 500ms
	}
}