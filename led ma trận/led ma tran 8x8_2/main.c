#include "main.h"
#include "C:\hoc\8051\bai_tap\Library\Delay\Delay.h"

#define COMMONPORTS P0

sbit IE74595_STCP = P3^5;     // RCK
sbit IE74595_SHCP = P3^6;     // SRCLK
sbit IE74595_DS = P3^4;       // SER

unsigned char code LedMatrix_8x8_0[10][8] = { {0x00,0x00,0x7C,0xA2,0x92,0x8A,0x7C,0x00,}, // ma so 0 tren led ma tran
																							{0x00,0x00,0x00,0x02,0xFE,0x42,0x00,0x00,}, // ma so 1 tren led ma tran
																							{0x00,0x00,0x62,0x92,0x92,0x8A,0x46,0x00,},	// ma so 2 tren led ma tran
																							{0x00,0x00,0x6C,0x92,0x92,0x92,0x44,0x00,},	// ma so 3 tren led ma tran
																							{0x00,0x00,0x08,0xFE,0x48,0x28,0x18,0x00,},	// ma so 4 tren led ma tran
																							{0x00,0x00,0x8C,0x92,0x92,0x92,0xF4,0x00,},	// ma so 5 tren led ma tran
																							{0x00,0x00,0x0C,0x92,0x92,0x52,0x3C,0x00,},	// ma so 6 tren led ma tran
																							{0x00,0x00,0xC0,0xA0,0x90,0x8E,0x80,0x00,},	// ma so 7 tren led ma tran
																							{0x00,0x00,0x6C,0x92,0x92,0x92,0x6C,0x00,},	// ma so 8 tren led ma tran
																							{0x00,0x00,0x78,0x94,0x92,0x92,0x60,0x00,},	// ma so 9 tren led ma tran
																						};

void IE74595_Out(unsigned char *p, unsigned char n)
{
	unsigned int i, j, b;
	for(j = 0; j<n; j++)
	{
		b = *(p + n - j - 1); //Lay tu byte cao nhat den byte thap nhat
		for(i=0; i<8; i++)
		{
			IE74595_DS = b & (0x80>>i); // lay tung bit cua byte b gui ra DS, lay tu bit cao xuong bit thap
			
			// tao xung nhan du lieu
			IE74595_SHCP = 0;
			IE74595_SHCP = 1;
		}
	}

	// tao xung xuat du lieu
	IE74595_STCP = 0;
	IE74595_STCP = 1;
}

// dem so tu 0 den 9 va lap lai
void main() 
{
    unsigned int cnt,i,j;
    while (1) 
    {
			for(cnt = 0; cnt < 10; cnt++)
			{
				for(j=0 ; j<125; j++)			// sau 1 giay tang 1 so
				{
					for (i = 0; i < 8; i++) //quet led 
					{
						IE74595_Out( &LedMatrix_8x8_0[cnt][i], 1); // Xuat du lieu cot cho hang i
						P0 = ~(0x01 << i); // Kich hoat hang tuong ung (neu su dung common anode thi dung P0 = 0x01 << j)
						Delay_ms(1); // Thay doi thoi gian delay neu can
						P0 = 0xFF; // Tat het cac hang de tranh hien tuong ghosting
					}				
				}
			}
    }
}


