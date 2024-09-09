#include "main.h"
#include "C:\hoc\8051\bai_tap\Library\UartMode1\UartMode1.h"

#if(FREQ_OSC != 11059200)
	#error "thu vien UartMode1 chi ho tro tan so thach anh 11059200"
#endif

void Uart_Init()
{
	// khoi tao UART mode 1, 9600 baud
	SM0 = 0; SM1 = 1; // Khoi tao UART kieu 1
	
	TMOD &= 0x0F;
	TMOD |= 0x20;			// 0010_0000 - Timer 1 hoat dong o che do 8 bit tu dong nap lai
	
	#if(BAUD_RATE == 9600)
	TH1 = 0xFD;				// toc do baud 9600
	#elif(BAUD_RATE == 2400)
	TH1 = 0xF4;			// toc do baud 2400
	#elif(BAUD_RATE == 1200)
	TH1 = 0xE8;				// toc do baud 1200
	#elif(BAUD_RATE == 19200)
	TH1 = 0xFD;
	PCON |= 0x80;			// toc do baud 19200
	#else
		#error "toc do Baud chi co the la 19200, 9600, 2400, 1200"
	#endif
	
	TR1 = 1;					// Timer 1 bat dau chay
	TI = 1;						// san sang gui du lieu
	REN = 1; 					// cho phep nhan du lieu
}

void Uart_Write(char c)
{
	while( TI == 0 ); // cho cho den khi ky tu duoc gui het 
	TI = 0;
	SBUF = c;
}

void Uart_Write_Text(char *str)
{
	unsigned char i=0;
	while( *(str+i) != 0 )
	{
		Uart_Write( *(str+i) );
		i++;
	}

}

char Uart_Data_Ready()
{
	// neu RI bang 1 thi bao hieu da nhan xong 1 ky tu
	return RI;
}

char Uart_Read()
{
	RI = 0; // neu nhan duoc tin hieu da nhan xong 1 ky tu se tat co bao hieu da nhan xong 1 ky tu
	return SBUF; // tra ve ky tu nhan duoc
}