#include "IR.h"
#include "Driver.h"

struct {
       //현재 IR 통신하는 중인지 판단하는 Flag
       int Status;
       //현재 보낸 Data Index
       int intindex;
       unsigned int sendeddata;
       unsigned long pretime;
       unsigned long timegap;
} strEmitIRStatus[4];

void InitEmitIR()
{

}

void SendIR(int direction, unsigned short data1, unsigned short data2)
{
     //현재 데이타 보내는 중이면 보내지 아니함.
     if(strEmitIRStatus[direction].Status == 1) return;

     strEmitIRStatus[direction].pretime = tick_10um_time;
     strEmitIRStatus[direction].Status = 1;
     strEmitIRStatus[direction].intindex = 0;
     strEmitIRStatus[direction].sendeddata = ((data1<<8) | data2);
     strEmitIRStatus[direction].timegap = 50;
     GPIO_PORTH_DATA |= (0x1 << direction);

}

#define ZERO_DELAY_TIME    20
#define ONE_DELAY_TIME    50

void SendIRInterruptProcess()
{
     int i;
     for( i = 0 ; i < 4 ; i++ )
     {
          if( strEmitIRStatus[i].Status != 0 )
          {
              //Start Packet IR 전송중
              if(strEmitIRStatus[i].Status == 1)
              {
                   //현재 StartPacket 전송중
                   //emit ON 상태
                   if( tick_10um_time - strEmitIRStatus[i].pretime > 50 )
                   {
                       //UART2_Write('1');
                       //시간을 다 채움

                       //emit off
                       GPIO_PORTH_DATA &= ~(0x1 << i);
                       //status off
                       strEmitIRStatus[i].Status = 2;
                       //시간 초기화
                       strEmitIRStatus[i].pretime = tick_10um_time;
                       /*
                       if( (strEmitIRStatus[i].sendeddata>>15) & 0x01 )
                       {
                           //다음 data가 1임
                           strEmitIRStatus[i].timegap = ONE_DELAY_TIME;
                       }
                       else
                       {
                           //다음 data가 0임
                           strEmitIRStatus[i].timegap = ZERO_DELAY_TIME;
                       }
                       */
                       strEmitIRStatus[i].timegap = 50;
                   }
              }
              else if(strEmitIRStatus[i].Status == 2)
              {
                   //emit Off 상태
                   if( tick_10um_time - strEmitIRStatus[i].pretime > strEmitIRStatus[i].timegap )
                   {

                       //UART2_Write('2');
                       // 시간 다 채움
                       //emit ON
                       GPIO_PORTH_DATA |= (0x1 << i);

                       //status off
                       strEmitIRStatus[i].Status = 3;

                       //시간 초기화
                       strEmitIRStatus[i].pretime = tick_10um_time;
                   }
                   
              }else if(strEmitIRStatus[i].Status == 3)
              {
                   //emit ON 상태 Data 보내는중
                   if( tick_10um_time - strEmitIRStatus[i].pretime > 10 )
                   {
                       //UART2_Write('3');
                       // 시간 다 채움
                       //emit off
                       GPIO_PORTH_DATA &= ~(0x1 << i);

                       //status ON
                       strEmitIRStatus[i].Status = 2;

                       //시간 초기화
                       strEmitIRStatus[i].pretime = tick_10um_time;

                       //if( strEmitIRStatus[i].intindex >= 16 )

                       if( strEmitIRStatus[i].intindex >= 16 )
                       {
                            strEmitIRStatus[i].Status = 0;
                            return;
                       }

                       if( (strEmitIRStatus[i].sendeddata >> (15 - strEmitIRStatus[i].intindex) ) & 0x01 )
                       {
                           //다음 data가 1임
                           strEmitIRStatus[i].timegap = ONE_DELAY_TIME;
                       }
                       else
                       {
                           //다음 data가 0임
                           strEmitIRStatus[i].timegap = ZERO_DELAY_TIME;
                       }
                       
                       strEmitIRStatus[i].intindex++;


                   }
              }
              
          }
     }
}


struct {
       //현재 IR 통신 중인지 판단하는 Flag
       int CommStatus;
       int intindex;
       int receiveddata;
       unsigned long pretime;
       unsigned long time[100];
} strReceievedIRStatus[4];

void InitReceivedIR()
{
     int i;
     for(i = 0 ; i < 4 ; i++)
     {
           strReceievedIRStatus[i].CommStatus = 0;
           strReceievedIRStatus[i].intindex = 0;
           strReceievedIRStatus[i].receiveddata = 0;
           strReceievedIRStatus[i].pretime = 0;
     }
}

void ReceivedIR(int i)
{
     strReceievedIRStatus[i].time[strReceievedIRStatus[i].intindex] = tick_10um_time - strReceievedIRStatus[i].pretime;
     strReceievedIRStatus[i].pretime = tick_10um_time;
     strReceievedIRStatus[i].intindex++;
 /*
     if(strReceievedIRStatus[i].CommStatus == 0)
     {
           //통신 시작함
           strReceievedIRStatus[i].CommStatus = 1;
     }
     */
}
