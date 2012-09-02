
#include "Driver.h"
#include "ACCEL_driver.h"
#include "Sample_resources.h"
// "#include " + Project + "_objects.h"
#include "Sample_objects.h"

#define COMM_IDLE 0
#define COMM_DATA 1

//   1111 1000 0000 0000


unsigned int commstatus = COMM_IDLE;
unsigned int predata = 0xff;
unsigned int commdata[255];
unsigned int commdataindex = 0;

//DLE Format Complete
unsigned int commcompleteflag = 0;

_tSensorStatus   SensorStatus;

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

//minor Packet => case by case
unsigned int commstatusflag = 0;



#define TOP                 0
#define RIGHT               1
#define BOTTOM              2
#define LEFT                3

void processPacket(int major, int minor, int length, unsigned int* tdata )
{
     if(minor == 0x060)
     {
      //memcpy(
      //SensorStatus.avrid = tdata[0];
      SensorStatus.status[0] = tdata[0];
      SensorStatus.neighborid[0] = tdata[1];
      SensorStatus.status[1] = tdata[2];
      SensorStatus.neighborid[1] = tdata[3];
      SensorStatus.status[2] = tdata[4];
      SensorStatus.neighborid[2] = tdata[5];
      SensorStatus.status[3] = tdata[6];
      SensorStatus.neighborid[3] = tdata[7];
      commstatusflag = 1;
     }
}

void UART_WRITE_HEX(unsigned int temp)
{
     UART_WRITE(((temp & 0xf0)>>4) + 0x30);
     UART_WRITE((temp & 0x0f) + 0x30);
}

void sendDLEData(char* tdata, int length)
{
     int index;
     UART0_Write((char)0x01);
     UART0_Write((char)0x02);

     for( index = 0 ; index < length ; index++ )
     {
          if(tdata[index] == 0x01)
          {
              UART0_Write((char)0x01);
              UART0_Write((char)0x01);
          }
          else
          {
              UART0_Write(tdata[index]);
          }
     }
     UART0_Write(0x01);
     UART0_Write(0x03);
}

void SendPacketData()
{
     char tdata[100];
     tdata[0] = CommStructData.boardID;
     tdata[1] = SensorStatus.status[TOP];
     tdata[2] = SensorStatus.status[BOTTOM];
     tdata[3] = SensorStatus.status[LEFT];
     tdata[4] = SensorStatus.status[RIGHT];
     tdata[5] = CommStructData.lm_status;
     tdata[6] = CommStructData.lm_value;

     //int lm_gyro;
     //tdata[7] = (CommStructData.lm_gyro >> 24) & 0xff;
     //tdata[8] = (CommStructData.lm_gyro >> 16) & 0xff;
     //tdata[9] = (CommStructData.lm_gyro >> 8) & 0xff;
     //tdata[10] = CommStructData.lm_gyro & 0xff;
     tdata[7] = CommStructData.lm_gyro_x;
     tdata[8] = CommStructData.lm_gyro_y;
     tdata[9] = CommStructData.lm_gyro_z;
     tdata[10] = 0;


     //Red Green Blue
     tdata[11] = CommStructData.RGB[0];
     tdata[12] = CommStructData.RGB[1];
     tdata[13] = CommStructData.RGB[2];
     
     //UART0_Write_Text("Test");
     
     sendDLEData(tdata, 14);
}

void analyzePacket()
{
     if( commdataindex != 14 ) return;

     //UARTIntegerPrint(commdataindex);
     
     if( commdata[0] > 0xB0 && commdata[0] < 0xC0 )
     {
       CommStructData.BoardID = commdata[0];
       SensorStatus.status[TOP] = commdata[1];
       SensorStatus.status[BOTTOM] = commdata[2];
       SensorStatus.status[LEFT] = commdata[3];
       SensorStatus.status[RIGHT] = commdata[4];
       CommStructData.lm_status = commdata[5];
       CommStructData.lm_value = commdata[6];
       commstatusflag = 1;
     }
}

/*
void analyzePacket()
{
     int index=0;
     int length;
     int major, minor;
     int checksum = 0;
     if(commdata[0] != 0x55) return; //wrong packet
     
     major = commdata[1];
     minor = commdata[2];
     length = (commdata[3]<<8) + commdata[4];

     for(index = 0 ; index < length ; index++)
     {
               checksum += commdata[5+index];
     }
     checksum &= 0xff;

     if( checksum != commdata[5+length] ) return; // check sum fail

     if( commdata[6+length] != 0xaa) return; // End Packet Fail

     // Succes Packet

     processPacket(major, minor, length, commdata + 5);

     commstatusflag = 1;
}
*/
void completePacket()
{
     // Comm data buffer -> Data Buffer
     commcompleteflag = 1;
     analyzePacket();
}

#define MAX_CMD_SIZE    80
unsigned char rxSerialCmdBuf[MAX_CMD_SIZE];
unsigned char rxSerialCmdIndex = 0;
unsigned char rxSerialCmdflag = 0;
unsigned char ReceFlag=0;
unsigned char StxFlag=0;
unsigned char DleFlag=0;


void DLE_RecvData(char tdata)
{
    if(tdata==0x01) { //DLE TOGGLE
                if(DleFlag == 0) {
                        DleFlag  = 1;
                        ReceFlag = 1;
                }
                else
                {
                        DleFlag = 0;
                }
        }

    if((ReceFlag == 1) && (DleFlag == 0) && (StxFlag == 1))
    {
        rxSerialCmdBuf[rxSerialCmdIndex++%MAX_CMD_SIZE] = tdata;
        commdata[commdataindex] = tdata;
        commdataindex++;

    } //DATA RESTORE
    else if ((tdata==0x02) && (DleFlag == 1)) { //RECEIVE START
      DleFlag = 0;
      StxFlag = 1;
      rxSerialCmdIndex = 0;
      commdataindex = 0;
    }
    else if((DleFlag==1) && (tdata==0x03)) { //RECEIVE END
      rxSerialCmdflag = 1;
      ReceFlag = 0;
      StxFlag = 0;
      DleFlag = 0;

      //rxSerialCmdIndex = 0;
    }

    if(rxSerialCmdflag)
    {

        rxSerialCmdflag  = 0;
        rxSerialCmdIndex = 0;

        completePacket();

    }
}

void receivePacket(unsigned int tdata)
{
     //UART_Write(
     switch(commstatus)
     {
           case COMM_IDLE:
                if(predata == 0x01 && tdata == 0x02)
                {
                           //Start Packet
                           commstatus = COMM_DATA;
                           commdataindex = 0;
                }
           break;
           case COMM_DATA:
                if(tdata == 0x01)
                {
                         if(predata == 0x01)
                         {
                             //push data
                             commdata[commdataindex] = 0x01;
                             commdataindex++;
                             tdata = 0xff;
                         }
                         else
                         {
                             //check next packet
                         }
                }
                else
                {
                         if(predata == 0x01 && tdata == 0x03)
                         {
                                    //End of Packet
                                    //TFT_Fill_Screen(CL_YELLOW);
                                    completePacket();
                                    commstatus = COMM_IDLE;
                                    initReceivePacket();
                         }
                         else
                         {
                             //push data
                             commdata[commdataindex] = tdata;
                             commdataindex++;
                         }
                }
           break;
     }
     predata = tdata;
}

void USART0_interrupt() iv IVT_INT_UART0 {
  unsigned tdata;
  tdata = UART0_Read();
  //UART2_Write(tdata);     //Echo
  //UART0_Write(tdata);     //Echo
  commcompleteflag = 1;
  //receivePacket(tdata);
  //DLE_RecvData(tdata);
  UART_ICR_RXIC_bit = 1;                 //disable UART0 status clear
}

void USART2_interrupt() iv IVT_INT_UART2 {
  unsigned tdata;
  tdata = UART2_Read();
  //UART0_Write(tdata);     //Echo
  //UART2_Write(tdata);
  //commcompleteflag = 1;
  //receivePacket(tdata);
  //DLE_RecvData(tdata);
  UART_ICR_RXIC_UART2_ICR_bit = 1;                 //disable UART0 status clear
}

void GPIOE_interrupt() iv IVT_INT_GPIOE {
  if(GPIO_PORTE_RIS & 0b10000000)
  {
       UART2_Write('a');
  }
  else if(GPIO_PORTE_RIS & 0b01000000)
  {
       UART2_Write('b');
  }
  else if(GPIO_PORTE_RIS & 0b00100000)
  {
       UART2_Write('c');
  }
  else if(GPIO_PORTE_RIS & 0b00010000)
  {
       UART2_Write('d');
  }
  //UART2_Write('2');
  GPIO_PORTE_ICR = GPIO_PORTE_RIS;
}

long tick_mm_time = 0;
unsigned long tick_10um_time = 0;
void Timer0A_interrupt() iv IVT_INT_TIMER0A {
  TIMER_ICR_TATOCINT_bit = 1;              // Clear time-out timer A interrupt
  //GPIO_PORTJ_DATA = ~GPIO_PORTJ_DATA;      // Toggle PORTJ led's
  tick_10um_time++;
}

void Start_Driver(void) {
     char uart_rd;
     // -----  Accel Sensor

     // Initialize I2C communication
     I2C0_Init_Advanced(100000, &_GPIO_MODULE_I2C0_B23);
     
     // Accel Sensor Init
     ADXL345_Init();

     // Timer0 init

      GPIO_Digital_Output(&GPIO_PORTJ, _GPIO_PINMASK_ALL);  // Enable digital output on PORTJ
      GPIO_PORTJ_DATA = 0;

      SYSCTL_RCGC1_TIMER0_bit = 1;        // Enable clock gating for timer module 0

      //EnableInterrupts();                 // Enables the processor interrupt.

      TIMER_CTL_TAEN_bit = 0;             // Disable timer
      TIMER0_CFG = 0;                     // Set 32-bit timer configuration
      TIMER0_TAMR |= 2;                   // Set periodic mode
      TIMER0_TAILR = Get_Fosc_kHz()/100; // Set interval load
      NVIC_IntEnable(IVT_INT_TIMER0A);    // Enable timer interrupt
      TIMER_IMR_TATOIM_bit = 1;           // Enable time-out timer A interrupt
      TIMER_CTL_TAEN_bit = 1;             // Enable timer A

     // --------------------
     
     // -----  UARD0

     UART0_Init(115200);                 // Initialize UART0 module at 9600 bps
     UART_IM_RXIM_bit = 1;             // Enable UART0 interrupt flag on
     UART_LCRH_FEN_bit = 0;
     NVIC_IntEnable(IVT_INT_UART0);    // Enable UART0 interrupt


     UART2_Init(115200);
     UART_IM_RXIM_UART2_IM_bit = 1;             // Enable UART2 interrupt flag on
     UART_LCRH_FEN_UART2_LCRH_bit = 0;
     NVIC_IntEnable(IVT_INT_UART2);    // Enable UART2 interrupt

     UART2_Write("Test Sample");

     EnableInterrupts();               // Enables the processor interrupt.

     //initReceivePacket();
}
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

void UARTStatusWall()
{
    //TImage *local_image;
    //local_image = CurrentScreen->Images[3];
    //TFT_Fill_Screen(CL_WHITE);
    //TFT_Ext_Image(AImage->Left, AImage->Top, AImage->Picture_Name, AImage->Picture_Ratio);
    //TFT_Ext_Image( 120 - ((local_image->width)>>1), 160-((local_image->height)>>1), local_image->Picture_Name, local_image->Picture_Ratio );

    //if(
    if( SensorStatus.status[TOP] )
    {
        UART_WRITE(0x30);
    }
    else
    {
        UART_WRITE(0x31);
    }
    
    if( SensorStatus.status[RIGHT] )
    {
        UART_WRITE(0x30);
    }
    else
    {
        UART_WRITE(0x31);
    }

    if( SensorStatus.status[BOTTOM] )
    {
        UART_WRITE(0x30);
    }
    else
    {
        UART_WRITE(0x31);
    }

    if( SensorStatus.status[LEFT] )
    {
        UART_WRITE(0x30);
    }
    else
    {
        UART_WRITE(0x31);
    }

    UART_WRITE(0x0d);
    UART_WRITE(0x0a);
}

#define COLOR_BLACK   TFT_RGBToColor16bit(0x47,0x45,0x44)
#define COLOR_YELLOW  TFT_RGBToColor16bit(0xFF,0xE0,0x5C)
#define COLOR_ORANGE  TFT_RGBToColor16bit(0xFF,0xA5,0x56)

#define WALLSIZE     20
void StatusWall()
{
    //TFT_Fill_Screen(CL_WHITE);
    int thenumberoftouchedarea = 0;
    /*SensorStatus.status[TOP] = 1;
    SensorStatus.status[RIGHT] = 1;
    SensorStatus.status[LEFT] = 1;
    SensorStatus.status[BOTTOM] = 1;
    */

    TFT_Set_Pen(CL_YELLOW, 1);
    TFT_Set_Brush(1,CL_YELLOW, 0,LEFT_TO_RIGHT,CL_YELLOW,CL_YELLOW);
    
    TFT_Rectangle(0,0,WALLSIZE,WALLSIZE);
    TFT_Rectangle(240-WALLSIZE,0,240,WALLSIZE);
    TFT_Rectangle(0,320-WALLSIZE,WALLSIZE,320);
    TFT_Rectangle(240-WALLSIZE,320-WALLSIZE,240,320);

    if( SensorStatus.status[TOP] )
    {
        TFT_Set_Pen(CL_BLACK, 1);
        TFT_Set_Brush(1,CL_BLACK, 0,LEFT_TO_RIGHT,CL_BLACK,CL_BLACK);
        TFT_Rectangle(WALLSIZE,0,240-WALLSIZE,WALLSIZE);
    }
    else
    {
        TFT_Set_Pen(CL_YELLOW, 1);
        TFT_Set_Brush(1,CL_YELLOW, 0,LEFT_TO_RIGHT,CL_YELLOW,CL_YELLOW);
        TFT_Rectangle(WALLSIZE,0,240-WALLSIZE,WALLSIZE);
        thenumberoftouchedarea++;
    }

    if( SensorStatus.status[RIGHT] )
    {
        TFT_Set_Pen(COLOR_BLACK, 1);
        TFT_Set_Brush(1,CL_BLACK, 0,LEFT_TO_RIGHT,CL_BLACK,CL_BLACK);
        TFT_Rectangle(240-WALLSIZE, WALLSIZE, 240 ,320-WALLSIZE);
    }
    else
    {
        TFT_Set_Pen(CL_YELLOW, 1);
        TFT_Set_Brush(1,CL_YELLOW, 0,LEFT_TO_RIGHT,CL_YELLOW,CL_YELLOW);
        TFT_Rectangle(240-WALLSIZE, WALLSIZE, 240 ,320-WALLSIZE);
        thenumberoftouchedarea++;
    }

    if( SensorStatus.status[BOTTOM] )
    {
        TFT_Set_Pen(CL_BLACK, 1);
        TFT_Set_Brush(1,CL_BLACK, 0,LEFT_TO_RIGHT,CL_BLACK,CL_BLACK);
        TFT_Rectangle(WALLSIZE, 320-WALLSIZE, 240-WALLSIZE, 320);
    }
    else
    {
        TFT_Set_Pen(CL_YELLOW, 1);
        TFT_Set_Brush(1,CL_YELLOW, 0,LEFT_TO_RIGHT,CL_YELLOW,CL_YELLOW);
        TFT_Rectangle(WALLSIZE, 320-WALLSIZE, 240-WALLSIZE, 320);
        thenumberoftouchedarea++;
    }

    if( SensorStatus.status[LEFT] )
    {
        TFT_Set_Pen(CL_BLACK, 1);
        TFT_Set_Brush(1,CL_BLACK, 0,LEFT_TO_RIGHT,CL_BLACK,CL_BLACK);
        TFT_Rectangle(0,WALLSIZE,WALLSIZE,320-WALLSIZE);
    }
    else
    {
        TFT_Set_Pen(CL_YELLOW, 1);
        TFT_Set_Brush(1,CL_YELLOW, 0,LEFT_TO_RIGHT,CL_YELLOW,CL_YELLOW);
        TFT_Rectangle(0,WALLSIZE,WALLSIZE,320-WALLSIZE);
        thenumberoftouchedarea++;
    }
    
    // Center BackGround Initialize
    //TFT_Set_Brush(1,CL_WHITE, 0,LEFT_TO_RIGHT,CL_WHITE,CL_WHITE);
    //TFT_Rectangle(50, 50,240 - 50, 320 - 50);
    /*
    switch (thenumberoftouchedarea)
    {
          case 0:
              break;
          case 1:
              TFT_Ext_Image(50, 50, number1_jpg, 1);
              break;
          case 2:
              //TFT_Ext_Image(50, 50, number2_jpg, 1);
              break;
          case 3:
              //TFT_Ext_Image(50, 50, number3_jpg, 1);
              break;
          default:
              break;
    } */
}

//int displaynumberindex = 0;

void Display_Number(char displaynumberindex)
{
if(displaynumberindex == 13) return;
            TFT_Set_Pen(CL_BLACK, 1);
            TFT_Set_Brush(1,CL_BLACK, 0,LEFT_TO_RIGHT,CL_BLACK,CL_BLACK);
            TFT_Rectangle(120 - 60, 160 - 80, 120 + 60, 160 + 80);
            switch(displaynumberindex)
              {
                           case 1:
                             TFT_Ext_Image(120 - (ImageNum1.Width >> 1), 160 - (ImageNum1.Height >> 1), number1_bmp, 1);
                           break;
                           case 2:
                             TFT_Ext_Image(120 - (ImageNum2.Width >> 1), 160 - (ImageNum2.Height >> 1), number2_bmp, 1);
                           break;
                           case 3:
                             TFT_Ext_Image(120 - (ImageNum3.Width >> 1), 160 - (ImageNum3.Height >> 1), number3_bmp, 1);
                           break;
                           case 4:
                             TFT_Ext_Image(120 - (ImageNum4.Width >> 1), 160 - (ImageNum4.Height >> 1), number4_bmp, 1);
                           break;
                           case 5:
                             TFT_Ext_Image(120 - (ImageNum5.Width >> 1), 160 - (ImageNum5.Height >> 1), number5_bmp, 1);
                           break;
                           case 6:
                             TFT_Ext_Image(120 - (ImageNum6.Width >> 1), 160 - (ImageNum6.Height >> 1), number6_bmp, 1);
                           break;
                           case 7:
                             TFT_Ext_Image(120 - (ImageNum7.Width >> 1), 160 - (ImageNum7.Height >> 1), number7_bmp, 1);
                           break;
                           case 8:
                             TFT_Ext_Image(120 - (ImageNum8.Width >> 1), 160 - (ImageNum8.Height >> 1), number8_bmp, 1);
                           break;
                           case 9:
                             TFT_Ext_Image(120 - (ImageNum9.Width >> 1), 160 - (ImageNum9.Height >> 1), number9_bmp, 1);
                           break;
                           case 10:
                             TFT_Ext_Image(120 - (ImageNum0.Width >> 1), 160 - (ImageNum0.Height >> 1), number0_bmp, 1);
                           break;
                           case 11:
                             TFT_Ext_Image(120 - (plus.Width >> 1), 160 - (plus.Height >> 1), plus_bmp, 1);
                           break;
                           case 12:
                             TFT_Ext_Image(120 - (minus.Width >> 1), 160 - (minus.Height >> 1), minus_bmp, 1);
                           break;
                           case 14:
                             TFT_Ext_Image(120 - (multiple.Width >> 1), 160 - (multiple.Height >> 1), multiple_bmp, 1);
                           break;
                           case 15:
                             TFT_Ext_Image(120 - (divide.Width >> 1), 160 - (divide.Height >> 1), divide_bmp, 1);
                           break;
                           case 16:
                             TFT_Ext_Image(120 - (equal.Width >> 1), 160 - (equal.Height >> 1), equal_bmp, 1);
                           break;
                           
              }

}


unsigned int accelflag = 0;
void Check_Accel(void)
{
     long x , y , z, total;
     double force_size;
     x = (long)(Accel_ReadX());
     y = (long)(Accel_ReadY());
     z = (long)(Accel_ReadZ());
     CommStructData.lm_gyro_x = (short)(x>>2);
     CommStructData.lm_gyro_y = (short)(y>>2);
     CommStructData.lm_gyro_z = (short)(z>>2);
     /*
     UARTShortPrint(CommStructData.lm_gyro_x);
     UART0_Write(',');
     UARTShortPrint(CommStructData.lm_gyro_y);
     UART0_Write(',');
     UARTShortPrint(CommStructData.lm_gyro_z);
     UART0_Write(0x0D);
     UART0_Write(0x0A);
     */
     total = x*x + y*y + z*z;

     force_size = sqrt((double)total);
     
     if(force_size > 520.)
     {
           accelflag = 1;
           //UART_Write_Text("AccelDetect\r\n");
     }
/*
     UART0_Write_Text("X:");
     UARTIntegerPrint(x);
     UART0_Write_Text("Y:");
     UARTIntegerPrint(y);
     UART0_Write_Text("Z:");
     UARTIntegerPrint(z);
     UART0_Write_Text("Total:");
     UARTDoublePrint(force_size); */
}
int numberchangeanimationflag = 0;
int displaynumberindextimer = 0;
int sendtimerindex = 0;
int predisplaynumber = 0;
void Check_Event(void){
     // UART Event Check.
     int index;
     
     // Accel Sensor Check
     Check_Accel();
     //GPIO_PORTC_DATA = 0xf;
     //TFT_Fill_Screen(CL_BLUE);
     if(commcompleteflag)
     {
        // Comm A Packet Received
        commcompleteflag = 0;
        UART0_Write_Text("2");
        UART0_Write(0x0d);
     }
     
     if(commstatusflag)
     {
        //Status A Packet Received
        //UARTStatusWall();
        StatusWall();
        if(predisplaynumber != CommStructData.lm_value)
        {
            Display_Number(CommStructData.lm_value);
            predisplaynumber = CommStructData.lm_value;
        }
        if(CommStructData.lm_status == 2)
        {
            SendPacketData();
        }
        commstatusflag = 0;
     }
     // Accel Sensor Event Check


     if( accelflag )
     {
        //UART_Write_Text("AccelFlagOn\r\n");
        //numberchangeanimationflag = 1;
        accelflag = 0;
     }
     
     /*
     if( tick_mm_time > 33 )
     {
          tick_mm_time = 0;
          sendtimerindex++;
          if(sendtimerindex>10)
          {
               //Send Data every 330ms
               SendPacketData();
               sendtimerindex = 0;
          }
     }
     */
}