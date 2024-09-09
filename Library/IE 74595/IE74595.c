// mo rong ngo ra su dung IC74HC595
// yeu cau: tao file port.h chua cac ket noi phan cung nhu sau:
//sbit IE74595_SHCP = P2^0;
//sbit IE74595_DS = P2^1;
//sbit IE74595_STCP = P2^2;

#include "main.h"
#include "IE74595.h"
#include "port.h"


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