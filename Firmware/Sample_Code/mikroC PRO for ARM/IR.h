#ifndef __IR
#define __IR        1

#define NORTH   0x00
#define EAST    0x01
#define SOUTH   0x02
#define WEST    0x03


void SendIR(int direction, unsigned short data1, unsigned short data2);
void SendIRInterruptProcess();


extern void ReceivedIR(int i);
#endif