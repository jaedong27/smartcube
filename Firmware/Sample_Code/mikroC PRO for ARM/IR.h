#ifndef __IR
#define __IR        1

#define SOUTH   0x00
#define WEST    0x01
#define NORTH   0x02
#define EAST    0x03


extern struct {
       //현재 IR 통신 중인지 판단하는 Flag
       int CommStatus;
       int intindex;
       //int receiveddata;
       unsigned long pretime;
       unsigned long time[100];
       unsigned long receiveddata;
       unsigned long tdata;
       unsigned long receivedtick;
} strReceievedIRStatus[4];

void SendIR(int direction, unsigned short data1, unsigned short data2);
void SendIRInterruptProcess();


extern void ReceivedIR(int i);
#endif