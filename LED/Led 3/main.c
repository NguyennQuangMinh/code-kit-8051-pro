
// sang dan va tat dan tu led 0 den led 8 bang phuong phap dich bit

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
	unsigned int i;
	while(1)
	{
		//sang dan tu led 0 den led 8
		for(i=0; i<8;i++){
			P2 <<=1; //dich trai 1 lan
			P2 &= 0xFE; // moi lan dich bit se keo bit thap nhat xuong muc 0 de bat led
			Delay_ms(500);
		}
		//tat dan cac led tu led 8 -> led 0
		for(i=0;i<8;i++)
		{
			P2 >>=1; //dich phai 1 lan
			P2 |= 0x80; // moi lan dich bit se keo bit cao nhat len muc 1 de tat led
			Delay_ms(500);
		}
	}

}