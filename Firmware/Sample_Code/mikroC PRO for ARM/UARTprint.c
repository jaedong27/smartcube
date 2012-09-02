#include "UARTprint.h"

void UARTDoublePrint(double value)
{
     char temp[30];
     FloatToStr(value, temp);
     UART2_Write_Text(temp);
     UART2_Write(0x0D);
     UART2_Write(0x0A);
}

void UARTIntegerPrint(int value)
{
     char temp[30];
     IntToStr(value, temp);
     UART2_Write_Text(temp);
     //UART2_Write(0x0D);
     //UART2_Write(0x0A);
}

void UARTLongPrint(long value)
{
     char temp[30];
     LongToStr(value, temp);
     UART2_Write_Text(temp);
     //UART2_Write(0x0D);
     //UART2_Write(0x0A);
}

void UARTShortPrint(short value)
{
     char temp[30];
     ShortToStr(value, temp);
     UART2_Write_Text(temp);
     //UART2_Write(0x0D);
     //UART2_Write(0x0A);
}

void UARTLongHexPrint(unsigned long value)
{
     char temp[30];
     //IntToStr((unsigned int)(value>>16) & 0xffff, temp);
     LongIntToHex(value, temp);
     UART2_Write_Text(temp);
     UART2_Write(0x0D);
     UART2_Write(0x0A);
}