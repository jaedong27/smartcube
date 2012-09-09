#ifndef __UARTPRINT
#define __UARTPRINT        1

void UART_WRITE_HEX(unsigned int temp);
void UARTDoublePrint(double value);
void UARTIntegerPrint(int value);
void UARTLongPrint(long value);
void UARTShortPrint(short value);
void UARTLongHexPrint(unsigned long value);

#endif