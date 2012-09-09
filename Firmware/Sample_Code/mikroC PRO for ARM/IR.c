#include "IR.h"
#include "Driver.h"
#include "UARTprint.h"

struct {
       //���� IR ����ϴ� ������ �Ǵ��ϴ� Flag
       int Status;
       //���� ���� Data Index
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
     //���� ����Ÿ ������ ���̸� ������ �ƴ���.
     if(strEmitIRStatus[direction].Status == 1) return;

     strEmitIRStatus[direction].pretime = tick_10u_time;
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
              //Start Packet IR ������
              if(strEmitIRStatus[i].Status == 1)
              {
                   //���� StartPacket ������
                   //emit ON ����
                   if( tick_10u_time - strEmitIRStatus[i].pretime > 50 )
                   {
                       //UART2_Write('1');
                       //�ð��� �� ä��

                       //emit off
                       GPIO_PORTH_DATA &= ~(0x1 << i);
                       //status off
                       strEmitIRStatus[i].Status = 2;
                       //�ð� �ʱ�ȭ
                       strEmitIRStatus[i].pretime = tick_10u_time;
                       /*
                       if( (strEmitIRStatus[i].sendeddata>>15) & 0x01 )
                       {
                           //���� data�� 1��
                           strEmitIRStatus[i].timegap = ONE_DELAY_TIME;
                       }
                       else
                       {
                           //���� data�� 0��
                           strEmitIRStatus[i].timegap = ZERO_DELAY_TIME;
                       }
                       */
                       strEmitIRStatus[i].timegap = 50;
                   }
              }
              else if(strEmitIRStatus[i].Status == 2)
              {
                   //emit Off ����
                   if( tick_10u_time - strEmitIRStatus[i].pretime > strEmitIRStatus[i].timegap )
                   {

                       //UART2_Write('2');
                       // �ð� �� ä��
                       //emit ON
                       GPIO_PORTH_DATA |= (0x1 << i);

                       //status off
                       strEmitIRStatus[i].Status = 3;

                       //�ð� �ʱ�ȭ
                       strEmitIRStatus[i].pretime = tick_10u_time;
                   }
                   
              }else if(strEmitIRStatus[i].Status == 3)
              {
                   //emit ON ���� Data ��������
                   if( tick_10u_time - strEmitIRStatus[i].pretime > 10 )
                   {
                       //UART2_Write('3');
                       // �ð� �� ä��
                       //emit off
                       GPIO_PORTH_DATA &= ~(0x1 << i);

                       //status ON
                       strEmitIRStatus[i].Status = 2;

                       //�ð� �ʱ�ȭ
                       strEmitIRStatus[i].pretime = tick_10u_time;

                       //if( strEmitIRStatus[i].intindex >= 16 )

                       if( strEmitIRStatus[i].intindex >= 16 )
                       {
                            strEmitIRStatus[i].Status = 0;
                            return;
                       }

                       if( (strEmitIRStatus[i].sendeddata >> (15 - strEmitIRStatus[i].intindex) ) & 0x01 )
                       {
                           //���� data�� 1��
                           strEmitIRStatus[i].timegap = ONE_DELAY_TIME;
                       }
                       else
                       {
                           //���� data�� 0��
                           strEmitIRStatus[i].timegap = ZERO_DELAY_TIME;
                       }
                       
                       strEmitIRStatus[i].intindex++;
                   }
              }
              
          }
     }
}


struct {
       //���� IR ��� ������ �Ǵ��ϴ� Flag
       int CommStatus;
       int intindex;
       //int receiveddata;
       unsigned long pretime;
       unsigned long time[100];
       unsigned long receiveddata;
       unsigned long tdata;
       unsigned long receivedtick;
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
     int j;
     unsigned long timegap;
     if( strReceievedIRStatus[i].CommStatus == 0)
     {
         //���� ������� �ƴϾ���
         strReceievedIRStatus[i].CommStatus = 1;
         strReceievedIRStatus[i].pretime = tick_10u_time;
     }
     else if( strReceievedIRStatus[i].CommStatus == 1 )
     {
         timegap = tick_10u_time - strReceievedIRStatus[i].pretime;
         strReceievedIRStatus[i].pretime = tick_10u_time;
         strReceievedIRStatus[i].intindex = 0;
         strReceievedIRStatus[i].receiveddata = 0;
         
         if( timegap > 98  && timegap < 105 )
         {
              strReceievedIRStatus[i].CommStatus = 2;
         }
         else
         {
              strReceievedIRStatus[i].CommStatus = 1;
         }
     }
     else if( strReceievedIRStatus[i].CommStatus == 2 )
     {
         timegap = tick_10u_time - strReceievedIRStatus[i].pretime;
         strReceievedIRStatus[i].pretime = tick_10u_time;
         
         if( timegap > 58  && timegap < 65 )
         {

             strReceievedIRStatus[i].receiveddata |= 1;
         }
         else if( timegap > 28 && timegap < 35 )
         {
             //strReceievedIRStatus[i].receiveddata
         }
         else
         {
              strReceievedIRStatus[i].CommStatus = 1;
         }
         
         strReceievedIRStatus[i].intindex++;
         
         if( strReceievedIRStatus[i].intindex >= 16 )
         {
             strReceievedIRStatus[i].CommStatus = 0;
             strReceievedIRStatus[i].tdata = strReceievedIRStatus[i].receiveddata;
             strReceievedIRStatus[i].receivedtick = tick_1m_time;
             

             /*UARTIntegerPrint( i );
             UART2_Write(0x20);
             UARTLongHexPrint( strReceievedIRStatus[i].tdata );
             UART2_Write(0x0D);
             UART2_Write(0x0A);
             */
             
             //���⼭ �� ���� �Ǵ�
             if( (unsigned int)(strReceievedIRStatus[i].tdata & 0xff) == (unsigned int)BOARDID )
             {
               /*UART2_Write('a');
               UARTIntegerPrint( i );
               UART2_Write(0x0D);
               UART2_Write(0x0A);*/
               //UART2_Write('d');
               SensorStatus.status[i] = 1;
               SensorStatus.neighborid[i] = (strReceievedIRStatus[i].tdata >> 8) & 0xff;
             }
             
             return;
         }
         
         strReceievedIRStatus[i].receiveddata = strReceievedIRStatus[i].receiveddata << 1;
     }
}