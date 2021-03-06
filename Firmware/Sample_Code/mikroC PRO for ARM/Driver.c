
#include "IR.h"
#include "Driver.h"
#include "Sample_resources.h"
// "#include " + Project + "_objects.h"
#include "Sample_objects.h"
#include "Comm.h"

_tSensorStatus   SensorStatus;


void USART0_interrupt() iv IVT_INT_UART0 {
  unsigned tdata;
  tdata = UART0_Read();
  receivePacket(tdata);
  UART_ICR_RXIC_bit = 1;                 //disable UART0 status clear
}

void USART2_interrupt() iv IVT_INT_UART2 {
  unsigned tdata;
  tdata = UART2_Read();
  receiveServerPacket(tdata);
  UART_ICR_RXIC_UART2_ICR_bit = 1;                 //disable UART0 status clear
}

// 0 :

void GPIOE_interrupt() iv IVT_INT_GPIOE {
  if(GPIO_PORTE_RIS & 0b10000000)
  {
       //UART2_Write('a');
       ReceivedIR(EAST);
  }
  else if(GPIO_PORTE_RIS & 0b01000000)
  {
       //UART2_Write('b');
       ReceivedIR(NORTH);
  }
  else if(GPIO_PORTE_RIS & 0b00100000)
  {
       //UART2_Write('c');
       ReceivedIR(WEST);
  }
  else if(GPIO_PORTE_RIS & 0b00010000)
  {
       //UART2_Write('d');
       ReceivedIR(SOUTH);
  }
  //UART2_Write('2');
  GPIO_PORTE_ICR = GPIO_PORTE_RIS;
}

long tick_mm_time = 0;
unsigned long tick_10u_time = 0;
void Timer0A_interrupt() iv IVT_INT_TIMER0A {
  TIMER_ICR_TATOCINT_bit = 1;              // Clear time-out timer A interrupt
  //GPIO_PORTJ_DATA = ~GPIO_PORTJ_DATA;      // Toggle PORTJ led's
  tick_10u_time++;
  SendIRInterruptProcess();
}

void Start_Driver(void) {
     char uart_rd;
     // -----  Accel Sensor

     // Initialize I2C communication
     //I2C0_Init_Advanced(100000, &_GPIO_MODULE_I2C0_B23);
     
     // Accel Sensor Init
     //ADXL345_Init();

     // Timer0 init

      /*GPIO_Digital_Output(&GPIO_PORTJ, _GPIO_PINMASK_ALL);  // Enable digital output on PORTJ
      GPIO_PORTJ_DATA = 0;
      */
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

     //UART2_Write_Text("Test Sample");

     EnableInterrupts();               // Enables the processor interrupt.

     //initReceivePacket();
}

void UARTStatusWall()
{
    if( SensorStatus.status[NORTH] )
    {
        UART2_WRITE(0x30);
    }
    else
    {
        UART2_WRITE(0x31);
    }
    
    if( SensorStatus.status[EAST] )
    {
        UART2_WRITE(0x30);
    }
    else
    {
        UART2_WRITE(0x31);
    }

    if( SensorStatus.status[SOUTH] )
    {
        UART2_WRITE(0x30);
    }
    else
    {
        UART2_WRITE(0x31);
    }

    if( SensorStatus.status[WEST] )
    {
        UART2_WRITE(0x30);
    }
    else
    {
        UART2_WRITE(0x31);
    }

    UART2_WRITE(0x0d);
    UART2_WRITE(0x0a);
}

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

    if( SensorStatus.status[NORTH] )
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

    if( SensorStatus.status[EAST] )
    {
        TFT_Set_Pen(CL_BLACK, 1);
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

    if( SensorStatus.status[SOUTH] )
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

    if( SensorStatus.status[WEST] )
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

int predisplaynumberindex = 0;
void Display_Number(char displaynumberindex)
{
            if(predisplaynumberindex == displaynumberindex) return;
            TFT_Set_Pen(CL_BLACK, 1);
            TFT_Set_Brush(1,CL_BLACK, 0,LEFT_TO_RIGHT,CL_BLACK,CL_BLACK);
            TFT_Rectangle(120 - 80, 160 - 90, 120 + 80, 160 + 90);
            switch(displaynumberindex)
              {
                           case 0:
                           
                           break;
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
                           case 13:
                             TFT_Ext_Image(120 - (multiple.Width >> 1), 160 - (multiple.Height >> 1), multiple_bmp, 1);
                           break;
                           case 14:
                             TFT_Ext_Image(120 - (divide.Width >> 1), 160 - (divide.Height >> 1), divide_bmp, 1);
                           break;
                           case 15:
                             TFT_Ext_Image(120 - (equal.Width >> 1), 160 - (equal.Height >> 1), equal_bmp, 1);
                           break;
                           case 16:
                             TFT_Ext_Image(120 - (alphaa.Width >> 1), 160 - (alphaa.Height >> 1), A_jpg, 1);
                           break;
                           case 17:
                             TFT_Ext_Image(120 - (alphab.Width >> 1), 160 - (alphab.Height >> 1), B_jpg, 1);
                           break;
                           case 18:
                             TFT_Ext_Image(120 - (alphac.Width >> 1), 160 - (alphac.Height >> 1), C_jpg, 1);
                           break;
                           case 19:
                             TFT_Ext_Image(120 - (alphad.Width >> 1), 160 - (alphad.Height >> 1), D_jpg, 1);
                           break;
                           case 20:
                             TFT_Ext_Image(120 - (alphae.Width >> 1), 160 - (alphae.Height >> 1), E_jpg, 1);
                           break;
                           case 21:
                             TFT_Ext_Image(120 - (alphaf.Width >> 1), 160 - (alphaf.Height >> 1), F_jpg, 1);
                           break;
                           case 22:
                             TFT_Ext_Image(120 - (alphag.Width >> 1), 160 - (alphag.Height >> 1), G_jpg, 1);
                           break;
                           case 23:
                             TFT_Ext_Image(120 - (alphah.Width >> 1), 160 - (alphah.Height >> 1), H_jpg, 1);
                           break;
                           case 24:
                             TFT_Ext_Image(120 - (alphai.Width >> 1), 160 - (alphai.Height >> 1), I_jpg, 1);
                           break;
                           case 25:
                             TFT_Ext_Image(120 - (alphaj.Width >> 1), 160 - (alphaj.Height >> 1), J_jpg, 1);
                           break;
                           case 26:
                             TFT_Ext_Image(120 - (alphak.Width >> 1), 160 - (alphak.Height >> 1), K_jpg, 1);
                           break;
                           case 27:
                             TFT_Ext_Image(120 - (alphal.Width >> 1), 160 - (alphal.Height >> 1), L_jpg, 1);
                           break;
                           case 28:
                             TFT_Ext_Image(120 - (alpham.Width >> 1), 160 - (alpham.Height >> 1), M_jpg, 1);
                           break;
                           case 29:
                             TFT_Ext_Image(120 - (alphan.Width >> 1), 160 - (alphan.Height >> 1), N_jpg, 1);
                           break;
                           case 30:
                             TFT_Ext_Image(120 - (alphao.Width >> 1), 160 - (alphao.Height >> 1), O_jpg, 1);
                           break;
                           case 31:
                             TFT_Ext_Image(120 - (alphap.Width >> 1), 160 - (alphap.Height >> 1), P_jpg, 1);
                           break;
                           case 32:
                             TFT_Ext_Image(120 - (alphaq.Width >> 1), 160 - (alphaq.Height >> 1), Q_jpg, 1);
                           break;
                           case 33:
                             TFT_Ext_Image(120 - (alphar.Width >> 1), 160 - (alphar.Height >> 1), R_jpg, 1);
                           break;
                           case 34:
                             TFT_Ext_Image(120 - (alphas.Width >> 1), 160 - (alphas.Height >> 1), S_jpg, 1);
                           break;
                           case 35:
                             TFT_Ext_Image(120 - (alphat.Width >> 1), 160 - (alphat.Height >> 1), T_jpg, 1);
                           break;
                           case 36:
                             TFT_Ext_Image(120 - (alphau.Width >> 1), 160 - (alphau.Height >> 1), U_jpg, 1);
                           break;
                           case 37:
                             TFT_Ext_Image(120 - (alphav.Width >> 1), 160 - (alphav.Height >> 1), V_jpg, 1);
                           break;
                           case 38:
                             TFT_Ext_Image(120 - (alphaw.Width >> 1), 160 - (alphaw.Height >> 1), W_jpg, 1);
                           break;
                           case 39:
                             TFT_Ext_Image(120 - (alphax.Width >> 1), 160 - (alphax.Height >> 1), X_jpg, 1);
                           break;
                           case 40:
                             TFT_Ext_Image(120 - (alphay.Width >> 1), 160 - (alphay.Height >> 1), Y_jpg, 1);
                           break;
                           case 41:
                             TFT_Ext_Image(120 - (alphaz.Width >> 1), 160 - (alphaz.Height >> 1), Z_jpg, 1);
                           break;
                           
                           case 42:
                             TFT_Ext_Image(120 - (pokeb1.Width >> 1), 160 - (pokeb1.Height >> 1), b1_jpg, 1);
                           break;
                           case 43:
                             TFT_Ext_Image(120 - (pokeb2.Width >> 1), 160 - (pokeb2.Height >> 1), b2_jpg, 1);
                           break;
                           case 44:
                             TFT_Ext_Image(120 - (pokeb3.Width >> 1), 160 - (pokeb3.Height >> 1), b3_jpg, 1);
                           break;
                           case 45:
                             TFT_Ext_Image(120 - (pokef1.Width >> 1), 160 - (pokef1.Height >> 1), f1_jpg, 1);
                           break;
                           case 46:
                             TFT_Ext_Image(120 - (pokef2.Width >> 1), 160 - (pokef2.Height >> 1), f2_jpg, 1);
                           break;
                           case 47:
                             TFT_Ext_Image(120 - (pokef3.Width >> 1), 160 - (pokef3.Height >> 1), f3_jpg, 1);
                           break;
                           case 48:
                             TFT_Ext_Image(120 - (pokeg1.Width >> 1), 160 - (pokeg1.Height >> 1), g1_jpg, 1);
                           break;
                           case 49:
                             TFT_Ext_Image(120 - (pokeg2.Width >> 1), 160 - (pokeg2.Height >> 1), g2_jpg, 1);
                           break;
                           case 50:
                             TFT_Ext_Image(120 - (pokeg3.Width >> 1), 160 - (pokeg3.Height >> 1), g3_jpg, 1);
                           break;
              }
              predisplaynumberindex = displaynumberindex;
}

int numberchangeanimationflag = 0;
int displaynumberindextimer = 0;
int sendtimerindex = 0;
int predisplaynumber = 0;
unsigned long preSendIRtick = 0;

unsigned long preSendWallRequesttick = 0;

int displaypictureflag = 0;
int displaypictureindex;
int getwallflag = 0;

int serverrequestwalldataflag = 0;
int serverrequestpictureflag = 0;

void Check_Event(void){
     // UART Event Check.
     int index;

     //GPIO_PORTC_DATA = 0xf;
     //TFT_Fill_Screen(CL_BLUE);
     if(commcompleteflag)
     {
        // Comm A Packet Received
        commcompleteflag = 0;
     }
     
     if(commstatusflag)
     {
        //Status A Packet Received
        commstatusflag = 0;
     }
     
     if( serverrequestwalldataflag )
     {
         sendtoServerWalldata();
         serverrequestwalldataflag = 0;
     }
     
     if( serverrequestpictureflag )
     {
         //UART2_Write_Text("J");
         if ( serverrequestpictureboardid == 1){
             Display_Number( serverrequestpictureindex );
         }
         else
         {
             RequestSetData(serverrequestpictureboardid,  serverrequestpictureindex);
         }
         serverrequestpictureflag = 0;
     }
     
     if( displaypictureflag )
     {
         displaypictureflag = 0;
         Display_Number(displaypictureindex);
     }
     
     if( getwallflag )
     {
         getwallflag = 0;
         sendStatusData();
     }

     if( tick_1m_time >= (preSendIRtick + 100) )
     {
       //UART2_Write_Text("test");
       preSendIRtick = tick_1m_time;
       for(index = 0 ; index < 4 ; index++ )
       {
        if( strReceievedIRStatus[index].receivedtick + 300 < tick_1m_time )
        {
       //     UART2_Write('d');
            //time out
            SendIR(index, BOARDID, 0);
            SensorStatus.status[index] = 0;
        }
        else
        {
            SendIR(index, BOARDID, (strReceievedIRStatus[index].tdata >> 8) & 0xff );
        }
       }
       //RequestWallData();
       StatusWall();
     }
     
     if( tick_1m_time >= (preSendWallRequesttick + 300) && (BOARDID == 1) )
     {
       //UART2_Write_Text("test");
       preSendWallRequesttick = tick_1m_time;
       RequestWallData();
     }
}