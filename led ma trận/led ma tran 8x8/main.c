#include "main.h"
#include "C:\hoc\8051\bai_tap\Library\Delay\Delay.h"

#define COMMONPORTS P0

sbit IE74595_STCP = P3^5;     // RCK
sbit IE74595_SHCP = P3^6;     // SRCLK
sbit IE74595_DS = P3^4;       // SER

unsigned char code LedMatrix_8x8_0[] = {0x00,0x7C,0x8A,0x92,0xA2,0x7C,0x00,0x00,}; // ma so 0 tren led ma tran



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

void main() 
{
    unsigned char i;
    while (1) 
    {
        for (i = 0; i < 8; i++) 
        {
            IE74595_Out(&LedMatrix_8x8_0[i], 1); // Output column data
            P0 = ~(0x01<<i);
            Delay_ms(2); 
            P0 = 0xFF; // Clear all rows to prevent ghosting
        }
    }
}
