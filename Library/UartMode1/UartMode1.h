#ifndef _UARTMODE1_H_
#define _UARTMODE1_H_

//khoi tao UART mode 1
void Uart_Init();

// gui 1 ky tu ra UART
void Uart_Write(char c);

// gui 1 chuoi ky tu ra UART
void Uart_Write_Text(char *str);

//Kiem tra co nhan duoc byte du lieu hay chua
// Tra ve 1: Da nhan duoc
// Tra ve 0: Chua nhan duoc
char Uart_Data_Ready();

// doc byte du lieu nhan duoc
char Uart_Read();

#endif