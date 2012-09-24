#include "Comm.h"
#include "Driver.h"
#include "IR.h"
#include "UARTprint.h"
//   1111 1000 0000 0000

unsigned int commstatus = COMM_IDLE;
unsigned int predata = 0xff;
unsigned int commdata[255];
unsigned int commdataindex = 0;

//DLE Format Complete
unsigned int commcompleteflag = 0;

unsigned int servercommstatus = COMM_IDLE;
unsigned int serverpredata = 0xff;
unsigned int servercommdata[255];
unsigned int servercommdataindex = 0;

//DLE Format Complete
unsigned int serverrequestpictureboardid = 0;
unsigned int serverrequestpictureindex = 0;


/*
void sendPacket(unsigned short major, unsigned short minor, unsigned int length, unsigned short* tdata)
{
     unsigned short tempdata[255];
     unsigned int index;
     unsigned int checksum = 0;
     tempdata[0] = 0x55;
     tempdata[1] = major;
     tempdata[2] = minor;
     tempdata[3] = (length >> 8) & 0xff;
     tempdata[4] = (length & 0xff);
     for(index = 0; index < length ; index++)
     {
               tempdata[5 + index] = tdata[index];
               //make check sum
               checksum += tdata[index];
     }

     tempdata[5 + length] = (unsigned short)(checksum & 0xff);
     tempdata[6 + length] = 0x0a;

     //DLE Format Start
     UART0_Write(0x01);
     UART0_Write(0x02);

     for(index = 0 ; index < length + 7; index++)
     {
               UART0_Write(tempdata[index]);
               if(tempdata[index] == 0x01)
               {
                     UART0_Write(0x01);
               }
     }

     //DLE Format End
     UART0_Write(0x01);
     UART0_Write(0x03);
}
*/


struct {
       char BoardID;
       char walldata[4];

       char lm_status;
       char lm_value;
       //unsigned long lm_gyro;
       short lm_gyro_x;
       short lm_gyro_y;
       short lm_gyro_z;
       unsigned char RGB[3];
} CommStructData;

struct {
       char BoardID;
       char walldata[4];
} AllBoardStatus[4];

/*
void SendCommData(char *tdata, length)
{
     int i;
     for(i = 0 ; i < length ; i++)
     {
           //UART0_Write((char)*(tdata+i));
     }
}
*/

void initReceivePacket(void)
{
     predata = 0xff;
     commdataindex = 0;
     commstatus = COMM_IDLE;
}

void initServerReceivePacket(void)
{
     serverpredata = 0xff;
     servercommdataindex = 0;
     servercommstatus = COMM_IDLE;
}

void sendtoServerDLEData(char* tdata, int length)
{
     int index;
     UART2_Write((char)0xFF);
     UART2_Write((char)0xFE);

     for( index = 0 ; index < length ; index++ )
     {
          if(tdata[index] == 0xFF)
          {
              UART2_Write((char)0xFF);
              UART2_Write((char)0xFF);
          }
          else
          {
              UART2_Write(tdata[index]);
          }
     }
     UART2_Write(0xFF);
     UART2_Write(0xFD);
}

void sendtoServerWalldata()
{
     char tdata[100];
     int i, j = 0;
     AllBoardStatus[BOARDID - 1].BoardID = BOARDID;
     if(SensorStatus.status[NORTH])
     {
         AllBoardStatus[BOARDID - 1].walldata[0] = SensorStatus.neighborid[NORTH];
     }
     else
     {
         AllBoardStatus[BOARDID - 1].walldata[0] = 0;
     }

     if(SensorStatus.status[EAST])
     {
         AllBoardStatus[BOARDID - 1].walldata[1] = SensorStatus.neighborid[EAST];
     }
     else
     {
         AllBoardStatus[BOARDID - 1].walldata[1] = 0;
     }

     if(SensorStatus.status[SOUTH])
     {
         AllBoardStatus[BOARDID - 1].walldata[2] = SensorStatus.neighborid[SOUTH];
     }
     else
     {
         AllBoardStatus[BOARDID - 1].walldata[2] = 0;
     }

     if(SensorStatus.status[WEST])
     {
         AllBoardStatus[BOARDID - 1].walldata[3] = SensorStatus.neighborid[WEST];
     }
     else
     {
         AllBoardStatus[BOARDID - 1].walldata[3] = 0;
     }
     
     for(i = 0 ; i < 4 ; i++)
     {
           tdata[j++] = AllBoardStatus[i].BoardID;
           tdata[j++] = AllBoardStatus[i].walldata[0];
           tdata[j++] = AllBoardStatus[i].walldata[1];
           tdata[j++] = AllBoardStatus[i].walldata[2];
           tdata[j++] = AllBoardStatus[i].walldata[3];
     }
     sendtoServerDLEData(tdata, j);
}


//minor Packet => case by case
unsigned int commstatusflag = 0;

void sendDLEData(char* tdata, int length)
{
     int index;
     UART0_Write((char)0xFF);
     UART0_Write((char)0xFE);

     for( index = 0 ; index < length ; index++ )
     {
          if(tdata[index] == 0xFF)
          {
              UART0_Write((char)0xFF);
              UART0_Write((char)0xFF);
          }
          else
          {
              UART0_Write(tdata[index]);
          }
     }
     UART0_Write(0xFF);
     UART0_Write(0xFD);
     UART0_Write(0x0D);
}

void RequestWallData(void)
{
     char tdata[10];
     tdata[0] = 0;
     sendDLEData(tdata , 1);
}

void RequestSetData(unsigned int BoardID, unsigned int pictureindex)
{
     char tdata[100];

     tdata[0] = 1;
     tdata[1] = BoardID;
     tdata[2] = pictureindex;
     sendDLEData(tdata , 3);
}

void sendStatusData(void)
{
     char tdata[100];
     tdata[0] = 10;
     tdata[1] = BOARDID;
     if( SensorStatus.status[NORTH] )
     {
         tdata[2] = SensorStatus.neighborid[NORTH];
     }
     else
     {
         tdata[2] = 0;
     }
     if( SensorStatus.status[EAST] )
     {
         tdata[3] = SensorStatus.neighborid[EAST];
     }
     else
     {
         tdata[3] = 0;
     }
     if( SensorStatus.status[SOUTH] )
     {
         tdata[4] = SensorStatus.neighborid[SOUTH];
     }
     else
     {
         tdata[4] = 0;
     }
     if( SensorStatus.status[WEST] )
     {
         tdata[5] = SensorStatus.neighborid[WEST];
     }
     else
     {
         tdata[5] = 0;
     }

     sendDLEData(tdata, 6);
}

void completePacket()
{
     // Comm data buffer -> Data Buffer
      switch(commdata[0])
     {
         case 0:
              //GET IR WALL DATA
              getwallflag = 1;
         break;
         case 1:
              //SET DISPLAY DATA
              if( commdata[1] != BOARDID ) return;
              displaypictureflag = 1;
              displaypictureindex = commdata[2];
              break;
         case 10:
              AllBoardStatus[commdata[1] - 1].BoardID = commdata[1];
              AllBoardStatus[commdata[1] - 1].Walldata[0] = commdata[2];
              AllBoardStatus[commdata[1] - 1].Walldata[1] = commdata[3];
              AllBoardStatus[commdata[1] - 1].Walldata[2] = commdata[4];
              AllBoardStatus[commdata[1] - 1].Walldata[3] = commdata[5];
         break;
     }
     commstatusflag = 1;
}

void completeServerPacket()
{
     switch(servercommdata[0])
     {
         case 0:
              //GET IR WALL DATA
              serverrequestwalldataflag = 1;
         break;
         case 1:
              //UART2_Write_Text("A");
              //SET DISPLAY DATA
              serverrequestpictureflag = 1;
              serverrequestpictureboardid = servercommdata[1];
              serverrequestpictureindex = servercommdata[2];
              break;
     }

}

void receivePacket(unsigned int tdata)
{
     //UART_Write(
     switch(commstatus)
     {
           case COMM_IDLE:
                if(predata == 0xFF && tdata == 0xFE)
                {
                           //Start Packet
                           commstatus = COMM_DATA;
                           commdataindex = 0;
                           //UART2_Write("a");
                }
           break;
           case COMM_DATA:
                if(tdata == 0xFF)
                {
                         if(predata == 0xFF)
                         {
                             //push data
                             commdata[commdataindex] = 0xFF;
                             commdataindex++;
                             tdata = 0x0;
                         }
                         else
                         {
                             //check next packet
                         }
                }
                else
                {
                         if(predata == 0xFF && tdata == 0xFD)
                         {
                                    //End of Packet
                                    //TFT_Fill_Screen(CL_YELLOW);
                                    completePacket();
                                    commstatus = COMM_IDLE;
                                    initReceivePacket();
                           //UART2_Write("c");
                         }
                         else
                         {
                             //push data
                             commdata[commdataindex] = tdata;
                             commdataindex++;
                           //UART2_Write("b");
                         }
                }
           break;
     }
     predata = tdata;
}

void receiveServerPacket(unsigned int tdata)
{
     switch(servercommstatus)
     {
           case COMM_IDLE:
                if(serverpredata == 0xFF && tdata == 0xFE)
                {
                           //Start Packet
                           servercommstatus = COMM_DATA;
                           servercommdataindex = 0;
                           //UART2_Write_Text("a");
                }
           break;
           case COMM_DATA:
                if(tdata == 0xFF)
                {
                         if(serverpredata == 0xFF)
                         {
                             //push data
                             servercommdata[commdataindex] = 0xFF;
                             servercommdataindex++;
                             tdata = 0x0;
                         }
                         else
                         {
                             //check next packet
                         }
                }
                else
                {
                         if(serverpredata == 0xFF && tdata == 0xFD)
                         {
                                    //End of Packet
                                    //TFT_Fill_Screen(CL_YELLOW);
                                    completeServerPacket();
                                    servercommstatus = COMM_IDLE;
                                    initServerReceivePacket();
                                    //UART2_Write_Text("c");
                         }
                         else
                         {
                             //push data
                             servercommdata[servercommdataindex] = tdata;
                             servercommdataindex++;
                             //UART2_Write_Text("b");
                         }
                }
           break;
     }
     serverpredata = tdata;
}