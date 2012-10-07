#include "Sample_objects.h"
#include "Sample_resources.h"
#include "built_in.h"

// Extern memory interface
// MMC/SD Connections
sbit Mmc_Chip_Select_Direction at GPIO_PORTD_DIR.B1;
sbit Mmc_Chip_Select           at GPIO_PORTD_DATA.B1;
// end of MMC/SD
// TFT Get Data globals
unsigned long currentSector = -1, res_file_size;
// end of TFT Get Data
// End of extern memory interface


// TFT module connections
char TFT_DataPort at GPIO_PORTJ_DATA;
sbit TFT_RST at GPIO_PORTH_DATA.B5;
sbit TFT_BLED at GPIO_PORTD_DATA.B3;
sbit TFT_RS at GPIO_PORTG_DATA.B7;
sbit TFT_CS at GPIO_PORTH_DATA.B6;
sbit TFT_RD at GPIO_PORTA_DATA.B6;
sbit TFT_WR at GPIO_PORTA_DATA.B7;
char TFT_DataPort_Direction at GPIO_PORTJ_DIR;
sbit TFT_RST_Direction at GPIO_PORTH_DIR.B5;
sbit TFT_BLED_Direction at GPIO_PORTD_DIR.B3;
sbit TFT_RS_Direction at GPIO_PORTG_DIR.B7;
sbit TFT_CS_Direction at GPIO_PORTH_DIR.B6;
sbit TFT_RD_Direction at GPIO_PORTA_DIR.B6;
sbit TFT_WR_Direction at GPIO_PORTA_DIR.B7;
// End TFT module connections

// Touch Panel module connections
sbit DRIVEX_LEFT at GPIO_PORTB_DATA.B4;
sbit DRIVEX_RIGHT at GPIO_PORTE_DATA.B0;
sbit DRIVEY_UP at GPIO_PORTE_DATA.B1;
sbit DRIVEY_DOWN at GPIO_PORTB_DATA.B5;
sbit DRIVEX_LEFT_DIRECTION at GPIO_PORTB_DIR.B4;
sbit DRIVEX_RIGHT_DIRECTION at GPIO_PORTE_DIR.B0;
sbit DRIVEY_UP_DIRECTION at GPIO_PORTE_DIR.B1;
sbit DRIVEY_DOWN_DIRECTION at GPIO_PORTB_DIR.B5;
// End Touch Panel module connections

// Global variables
unsigned int Xcoord, Ycoord;
const ADC_THRESHOLD = 750;
char PenDown;
void *PressedObject;
int PressedObjectType;
unsigned int caption_length, caption_height;
unsigned int display_width, display_height;

int _object_count;
unsigned short object_pressed;
TImage *local_image;
TImage *exec_image;
int image_order;


void Init_ADC() {
  ADC_Set_Input_Channel(_ADC_CHANNEL_10 | _ADC_CHANNEL_11);
  ADC0_Init_Advanced(_ADC_EXTERNAL_REF);
}

char* TFT_Get_Data(unsigned long offset, unsigned long count, unsigned long *num) {
unsigned long start_sector;
unsigned int pos;

  start_sector = Mmc_Get_File_Write_Sector() + offset/512;
  pos = (unsigned long)offset%512;

  if(start_sector == currentSector+1) {
    Mmc_Multi_Read_Sector(f16_sector.fSect);
    currentSector = start_sector;
  } else if (start_sector != currentSector) {
    if(currentSector != -1)
      Mmc_Multi_Read_Stop();
    Mmc_Multi_Read_Start(start_sector);
    Mmc_Multi_Read_Sector(f16_sector.fSect);
    currentSector = start_sector;
  }

  if(count>512-pos)
    *num = 512-pos;
  else
    *num = count;

  return f16_sector.fSect+pos;
}
static void InitializeTouchPanel() {
  Init_ADC();
  TFT_Init(240, 320);
  TFT_Set_Ext_Buffer(TFT_Get_Data);

  TP_TFT_Init(240, 320, 11, 10);                                  // Initialize touch panel
  TP_TFT_Set_ADC_Threshold(ADC_THRESHOLD);                              // Set touch panel ADC threshold

  PenDown = 0;
  PressedObject = 0;
  PressedObjectType = -1;
}

void Calibrate() {
  TFT_Set_Pen(CL_WHITE, 3);
  TFT_Set_Font(TFT_defaultFont, CL_WHITE, FO_HORIZONTAL);
  TFT_Write_Text("Touch selected corners for calibration", 1, 150);
  TFT_Line(0, 319, 5, 319);
  TFT_Line(0, 319, 0, 314);
  TFT_Line(0, 319, 10, 309);
  TFT_Write_Text("first here", 20, 290);

  TP_TFT_Calibrate_Min();                      // Calibration of bottom left corner
  Delay_ms(500);

  TFT_Set_Pen(CL_BLACK, 3);
  TFT_Set_Font(TFT_defaultFont, CL_BLACK, FO_HORIZONTAL);
  TFT_Line(0, 319, 5, 319);
  TFT_Line(0, 319, 0, 314);
  TFT_Line(0, 319, 10, 309);
  TFT_Write_Text("first here", 20, 290);

  TFT_Set_Pen(CL_WHITE, 3);
  TFT_Set_Font(TFT_defaultFont, CL_WHITE, FO_HORIZONTAL);
  TFT_Write_Text("now here ", 180, 15);
  TFT_Line(239, 0, 234, 0);
  TFT_Line(239, 0, 239, 5);
  TFT_Line(239, 0, 229, 10);

  TP_TFT_Calibrate_Max();                      // Calibration of bottom left corner
  Delay_ms(500);
}


/////////////////////////
  TScreen*  CurrentScreen;

  TScreen                Screen1;
  TImage               ImageNum0;
  TImage               ImageNum1;
  TImage               ImageNum2;
  TImage               ImageNum3;
  TImage               ImageNum4;
  TImage               ImageNum5;
  TImage               ImageNum6;
  TImage               ImageNum7;
  TImage               ImageNum8;
  TImage               ImageNum9;
  TImage               plus;
  TImage               minus;
  TImage               divide;
  TImage               equal;
  TImage               multiple;
  TImage               alphaa;
  TImage               alphab;
  TImage               alphac;
  TImage               alphad;
  TImage               alphae;
  TImage               alphaf;
  TImage               alphag;
  TImage               alphah;
  TImage               alphai;
  TImage               alphaj;
  TImage               alphak;
  TImage               alphal;
  TImage               alpham;
  TImage               alphan;
  TImage               alphao;
  TImage               alphap;
  TImage               alphaq;
  TImage               alphar;
  TImage               alphas;
  TImage               alphat;
  TImage               alphau;
  TImage               alphav;
  TImage               alphaw;
  TImage               alphax;
  TImage               alphay;
  TImage               alphaz;
  TImage               pokeb1;
  TImage               pokeb2;
  TImage               pokeb3;
  TImage               pokef1;
  TImage               pokef2;
  TImage               pokef3;
  TImage               pokeg1;
  TImage               pokeg2;
  TImage               pokeg3;
  TImage                 * const code Screen1_Images[50]=
         {
         &ImageNum0,           
         &ImageNum1,           
         &ImageNum2,           
         &ImageNum3,           
         &ImageNum4,           
         &ImageNum5,           
         &ImageNum6,           
         &ImageNum7,           
         &ImageNum8,           
         &ImageNum9,           
         &plus,                
         &minus,               
         &divide,              
         &equal,               
         &multiple,            
         &alphaa,              
         &alphab,              
         &alphac,              
         &alphad,              
         &alphae,              
         &alphaf,              
         &alphag,              
         &alphah,              
         &alphai,              
         &alphaj,              
         &alphak,              
         &alphal,              
         &alpham,              
         &alphan,              
         &alphao,              
         &alphap,              
         &alphaq,              
         &alphar,              
         &alphas,              
         &alphat,              
         &alphau,              
         &alphav,              
         &alphaw,              
         &alphax,              
         &alphay,              
         &alphaz,              
         &pokeb1,              
         &pokeb2,              
         &pokeb3,              
         &pokef1,              
         &pokef2,              
         &pokef3,              
         &pokeg1,              
         &pokeg2,              
         &pokeg3               
         };




static void InitializeObjects() {
  Screen1.Color                     = 0x8410;
  Screen1.Width                     = 240;
  Screen1.Height                    = 320;
  Screen1.ImagesCount               = 50;
  Screen1.Images                    = Screen1_Images;
  Screen1.ObjectsCount              = 50;


  ImageNum0.OwnerScreen     = &Screen1;
  ImageNum0.Order          = 0;
  ImageNum0.Left           = 11;
  ImageNum0.Top            = 15;
  ImageNum0.Width          = 110;
  ImageNum0.Height         = 157;
  ImageNum0.Picture_Type   = 0;
  ImageNum0.Picture_Ratio  = 1;
  ImageNum0.Picture_Name   = number0_bmp;
  ImageNum0.Visible        = 0;
  ImageNum0.Active         = 1;
  ImageNum0.OnUpPtr         = 0;
  ImageNum0.OnDownPtr       = 0;
  ImageNum0.OnClickPtr      = 0;
  ImageNum0.OnPressPtr      = 0;

  ImageNum1.OwnerScreen     = &Screen1;
  ImageNum1.Order          = 1;
  ImageNum1.Left           = 22;
  ImageNum1.Top            = 26;
  ImageNum1.Width          = 61;
  ImageNum1.Height         = 161;
  ImageNum1.Picture_Type   = 0;
  ImageNum1.Picture_Ratio  = 1;
  ImageNum1.Picture_Name   = number1_bmp;
  ImageNum1.Visible        = 0;
  ImageNum1.Active         = 1;
  ImageNum1.OnUpPtr         = 0;
  ImageNum1.OnDownPtr       = 0;
  ImageNum1.OnClickPtr      = 0;
  ImageNum1.OnPressPtr      = 0;

  ImageNum2.OwnerScreen     = &Screen1;
  ImageNum2.Order          = 2;
  ImageNum2.Left           = 34;
  ImageNum2.Top            = 36;
  ImageNum2.Width          = 110;
  ImageNum2.Height         = 154;
  ImageNum2.Picture_Type   = 0;
  ImageNum2.Picture_Ratio  = 1;
  ImageNum2.Picture_Name   = number2_bmp;
  ImageNum2.Visible        = 0;
  ImageNum2.Active         = 1;
  ImageNum2.OnUpPtr         = 0;
  ImageNum2.OnDownPtr       = 0;
  ImageNum2.OnClickPtr      = 0;
  ImageNum2.OnPressPtr      = 0;

  ImageNum3.OwnerScreen     = &Screen1;
  ImageNum3.Order          = 3;
  ImageNum3.Left           = 44;
  ImageNum3.Top            = 46;
  ImageNum3.Width          = 86;
  ImageNum3.Height         = 154;
  ImageNum3.Picture_Type   = 0;
  ImageNum3.Picture_Ratio  = 1;
  ImageNum3.Picture_Name   = number3_bmp;
  ImageNum3.Visible        = 0;
  ImageNum3.Active         = 1;
  ImageNum3.OnUpPtr         = 0;
  ImageNum3.OnDownPtr       = 0;
  ImageNum3.OnClickPtr      = 0;
  ImageNum3.OnPressPtr      = 0;

  ImageNum4.OwnerScreen     = &Screen1;
  ImageNum4.Order          = 4;
  ImageNum4.Left           = 54;
  ImageNum4.Top            = 56;
  ImageNum4.Width          = 113;
  ImageNum4.Height         = 151;
  ImageNum4.Picture_Type   = 0;
  ImageNum4.Picture_Ratio  = 1;
  ImageNum4.Picture_Name   = number4_bmp;
  ImageNum4.Visible        = 0;
  ImageNum4.Active         = 1;
  ImageNum4.OnUpPtr         = 0;
  ImageNum4.OnDownPtr       = 0;
  ImageNum4.OnClickPtr      = 0;
  ImageNum4.OnPressPtr      = 0;

  ImageNum5.OwnerScreen     = &Screen1;
  ImageNum5.Order          = 5;
  ImageNum5.Left           = 64;
  ImageNum5.Top            = 66;
  ImageNum5.Width          = 95;
  ImageNum5.Height         = 154;
  ImageNum5.Picture_Type   = 0;
  ImageNum5.Picture_Ratio  = 1;
  ImageNum5.Picture_Name   = number5_bmp;
  ImageNum5.Visible        = 0;
  ImageNum5.Active         = 1;
  ImageNum5.OnUpPtr         = 0;
  ImageNum5.OnDownPtr       = 0;
  ImageNum5.OnClickPtr      = 0;
  ImageNum5.OnPressPtr      = 0;

  ImageNum6.OwnerScreen     = &Screen1;
  ImageNum6.Order          = 6;
  ImageNum6.Left           = 78;
  ImageNum6.Top            = 76;
  ImageNum6.Width          = 118;
  ImageNum6.Height         = 158;
  ImageNum6.Picture_Type   = 0;
  ImageNum6.Picture_Ratio  = 1;
  ImageNum6.Picture_Name   = number6_bmp;
  ImageNum6.Visible        = 0;
  ImageNum6.Active         = 1;
  ImageNum6.OnUpPtr         = 0;
  ImageNum6.OnDownPtr       = 0;
  ImageNum6.OnClickPtr      = 0;
  ImageNum6.OnPressPtr      = 0;

  ImageNum7.OwnerScreen     = &Screen1;
  ImageNum7.Order          = 7;
  ImageNum7.Left           = 88;
  ImageNum7.Top            = 86;
  ImageNum7.Width          = 105;
  ImageNum7.Height         = 151;
  ImageNum7.Picture_Type   = 0;
  ImageNum7.Picture_Ratio  = 1;
  ImageNum7.Picture_Name   = number7_bmp;
  ImageNum7.Visible        = 0;
  ImageNum7.Active         = 1;
  ImageNum7.OnUpPtr         = 0;
  ImageNum7.OnDownPtr       = 0;
  ImageNum7.OnClickPtr      = 0;
  ImageNum7.OnPressPtr      = 0;

  ImageNum8.OwnerScreen     = &Screen1;
  ImageNum8.Order          = 8;
  ImageNum8.Left           = 98;
  ImageNum8.Top            = 96;
  ImageNum8.Width          = 110;
  ImageNum8.Height         = 157;
  ImageNum8.Picture_Type   = 0;
  ImageNum8.Picture_Ratio  = 1;
  ImageNum8.Picture_Name   = number8_bmp;
  ImageNum8.Visible        = 0;
  ImageNum8.Active         = 1;
  ImageNum8.OnUpPtr         = 0;
  ImageNum8.OnDownPtr       = 0;
  ImageNum8.OnClickPtr      = 0;
  ImageNum8.OnPressPtr      = 0;

  ImageNum9.OwnerScreen     = &Screen1;
  ImageNum9.Order          = 9;
  ImageNum9.Left           = 108;
  ImageNum9.Top            = 106;
  ImageNum9.Width          = 118;
  ImageNum9.Height         = 158;
  ImageNum9.Picture_Type   = 0;
  ImageNum9.Picture_Ratio  = 1;
  ImageNum9.Picture_Name   = number9_bmp;
  ImageNum9.Visible        = 0;
  ImageNum9.Active         = 1;
  ImageNum9.OnUpPtr         = 0;
  ImageNum9.OnDownPtr       = 0;
  ImageNum9.OnClickPtr      = 0;
  ImageNum9.OnPressPtr      = 0;

  plus.OwnerScreen     = &Screen1;
  plus.Order          = 10;
  plus.Left           = 118;
  plus.Top            = 116;
  plus.Width          = 115;
  plus.Height         = 119;
  plus.Picture_Type   = 0;
  plus.Picture_Ratio  = 1;
  plus.Picture_Name   = plus_bmp;
  plus.Visible        = 0;
  plus.Active         = 1;
  plus.OnUpPtr         = 0;
  plus.OnDownPtr       = 0;
  plus.OnClickPtr      = 0;
  plus.OnPressPtr      = 0;

  minus.OwnerScreen     = &Screen1;
  minus.Order          = 11;
  minus.Left           = 128;
  minus.Top            = 126;
  minus.Width          = 109;
  minus.Height         = 35;
  minus.Picture_Type   = 0;
  minus.Picture_Ratio  = 1;
  minus.Picture_Name   = minus_bmp;
  minus.Visible        = 0;
  minus.Active         = 1;
  minus.OnUpPtr         = 0;
  minus.OnDownPtr       = 0;
  minus.OnClickPtr      = 0;
  minus.OnPressPtr      = 0;

  divide.OwnerScreen     = &Screen1;
  divide.Order          = 12;
  divide.Left           = 148;
  divide.Top            = 146;
  divide.Width          = 115;
  divide.Height         = 131;
  divide.Picture_Type   = 0;
  divide.Picture_Ratio  = 1;
  divide.Picture_Name   = divide_bmp;
  divide.Visible        = 0;
  divide.Active         = 1;
  divide.OnUpPtr         = 0;
  divide.OnDownPtr       = 0;
  divide.OnClickPtr      = 0;
  divide.OnPressPtr      = 0;

  equal.OwnerScreen     = &Screen1;
  equal.Order          = 13;
  equal.Left           = 158;
  equal.Top            = 156;
  equal.Width          = 115;
  equal.Height         = 73;
  equal.Picture_Type   = 0;
  equal.Picture_Ratio  = 1;
  equal.Picture_Name   = equal_bmp;
  equal.Visible        = 0;
  equal.Active         = 1;
  equal.OnUpPtr         = 0;
  equal.OnDownPtr       = 0;
  equal.OnClickPtr      = 0;
  equal.OnPressPtr      = 0;

  multiple.OwnerScreen     = &Screen1;
  multiple.Order          = 14;
  multiple.Left           = 115;
  multiple.Top            = 194;
  multiple.Width          = 114;
  multiple.Height         = 113;
  multiple.Picture_Type   = 0;
  multiple.Picture_Ratio  = 1;
  multiple.Picture_Name   = multiple_bmp;
  multiple.Visible        = 1;
  multiple.Active         = 1;
  multiple.OnUpPtr         = 0;
  multiple.OnDownPtr       = 0;
  multiple.OnClickPtr      = 0;
  multiple.OnPressPtr      = 0;

  alphaa.OwnerScreen     = &Screen1;
  alphaa.Order          = 15;
  alphaa.Left           = 2;
  alphaa.Top            = 1;
  alphaa.Width          = 127;
  alphaa.Height         = 141;
  alphaa.Picture_Type        = 1;
  alphaa.Picture_Ratio  = 1;
  alphaa.Picture_Name   = A_jpg;
  alphaa.Visible        = 1;
  alphaa.Active         = 1;
  alphaa.OnUpPtr         = 0;
  alphaa.OnDownPtr       = 0;
  alphaa.OnClickPtr      = 0;
  alphaa.OnPressPtr      = 0;

  alphab.OwnerScreen     = &Screen1;
  alphab.Order          = 16;
  alphab.Left           = 9;
  alphab.Top            = 8;
  alphab.Width          = 115;
  alphab.Height         = 137;
  alphab.Picture_Type        = 1;
  alphab.Picture_Ratio  = 1;
  alphab.Picture_Name   = B_jpg;
  alphab.Visible        = 1;
  alphab.Active         = 1;
  alphab.OnUpPtr         = 0;
  alphab.OnDownPtr       = 0;
  alphab.OnClickPtr      = 0;
  alphab.OnPressPtr      = 0;

  alphac.OwnerScreen     = &Screen1;
  alphac.Order          = 17;
  alphac.Left           = 22;
  alphac.Top            = 18;
  alphac.Width          = 123;
  alphac.Height         = 141;
  alphac.Picture_Type        = 1;
  alphac.Picture_Ratio  = 1;
  alphac.Picture_Name   = C_jpg;
  alphac.Visible        = 1;
  alphac.Active         = 1;
  alphac.OnUpPtr         = 0;
  alphac.OnDownPtr       = 0;
  alphac.OnClickPtr      = 0;
  alphac.OnPressPtr      = 0;

  alphad.OwnerScreen     = &Screen1;
  alphad.Order          = 18;
  alphad.Left           = 30;
  alphad.Top            = 28;
  alphad.Width          = 118;
  alphad.Height         = 137;
  alphad.Picture_Type        = 1;
  alphad.Picture_Ratio  = 1;
  alphad.Picture_Name   = D_jpg;
  alphad.Visible        = 1;
  alphad.Active         = 1;
  alphad.OnUpPtr         = 0;
  alphad.OnDownPtr       = 0;
  alphad.OnClickPtr      = 0;
  alphad.OnPressPtr      = 0;

  alphae.OwnerScreen     = &Screen1;
  alphae.Order          = 19;
  alphae.Left           = 42;
  alphae.Top            = 44;
  alphae.Width          = 107;
  alphae.Height         = 137;
  alphae.Picture_Type        = 1;
  alphae.Picture_Ratio  = 1;
  alphae.Picture_Name   = E_jpg;
  alphae.Visible        = 1;
  alphae.Active         = 1;
  alphae.OnUpPtr         = 0;
  alphae.OnDownPtr       = 0;
  alphae.OnClickPtr      = 0;
  alphae.OnPressPtr      = 0;

  alphaf.OwnerScreen     = &Screen1;
  alphaf.Order          = 20;
  alphaf.Left           = 52;
  alphaf.Top            = 54;
  alphaf.Width          = 97;
  alphaf.Height         = 139;
  alphaf.Picture_Type        = 1;
  alphaf.Picture_Ratio  = 1;
  alphaf.Picture_Name   = F_jpg;
  alphaf.Visible        = 1;
  alphaf.Active         = 1;
  alphaf.OnUpPtr         = 0;
  alphaf.OnDownPtr       = 0;
  alphaf.OnClickPtr      = 0;
  alphaf.OnPressPtr      = 0;

  alphag.OwnerScreen     = &Screen1;
  alphag.Order          = 21;
  alphag.Left           = 64;
  alphag.Top            = 70;
  alphag.Width          = 130;
  alphag.Height         = 141;
  alphag.Picture_Type        = 1;
  alphag.Picture_Ratio  = 1;
  alphag.Picture_Name   = G_jpg;
  alphag.Visible        = 1;
  alphag.Active         = 1;
  alphag.OnUpPtr         = 0;
  alphag.OnDownPtr       = 0;
  alphag.OnClickPtr      = 0;
  alphag.OnPressPtr      = 0;

  alphah.OwnerScreen     = &Screen1;
  alphah.Order          = 22;
  alphah.Left           = 76;
  alphah.Top            = 82;
  alphah.Width          = 117;
  alphah.Height         = 141;
  alphah.Picture_Type        = 1;
  alphah.Picture_Ratio  = 1;
  alphah.Picture_Name   = H_jpg;
  alphah.Visible        = 1;
  alphah.Active         = 1;
  alphah.OnUpPtr         = 0;
  alphah.OnDownPtr       = 0;
  alphah.OnClickPtr      = 0;
  alphah.OnPressPtr      = 0;

  alphai.OwnerScreen     = &Screen1;
  alphai.Order          = 23;
  alphai.Left           = 88;
  alphai.Top            = 92;
  alphai.Width          = 34;
  alphai.Height         = 141;
  alphai.Picture_Type        = 1;
  alphai.Picture_Ratio  = 1;
  alphai.Picture_Name   = I_jpg;
  alphai.Visible        = 1;
  alphai.Active         = 1;
  alphai.OnUpPtr         = 0;
  alphai.OnDownPtr       = 0;
  alphai.OnClickPtr      = 0;
  alphai.OnPressPtr      = 0;

  alphaj.OwnerScreen     = &Screen1;
  alphaj.Order          = 24;
  alphaj.Left           = 104;
  alphaj.Top            = 108;
  alphaj.Width          = 93;
  alphaj.Height         = 141;
  alphaj.Picture_Type        = 1;
  alphaj.Picture_Ratio  = 1;
  alphaj.Picture_Name   = J_jpg;
  alphaj.Visible        = 1;
  alphaj.Active         = 1;
  alphaj.OnUpPtr         = 0;
  alphaj.OnDownPtr       = 0;
  alphaj.OnClickPtr      = 0;
  alphaj.OnPressPtr      = 0;

  alphak.OwnerScreen     = &Screen1;
  alphak.Order          = 25;
  alphak.Left           = 116;
  alphak.Top            = 116;
  alphak.Width          = 118;
  alphak.Height         = 141;
  alphak.Picture_Type        = 1;
  alphak.Picture_Ratio  = 1;
  alphak.Picture_Name   = K_jpg;
  alphak.Visible        = 1;
  alphak.Active         = 1;
  alphak.OnUpPtr         = 0;
  alphak.OnDownPtr       = 0;
  alphak.OnClickPtr      = 0;
  alphak.OnPressPtr      = 0;

  alphal.OwnerScreen     = &Screen1;
  alphal.Order          = 26;
  alphal.Left           = 128;
  alphal.Top            = 137;
  alphal.Width          = 99;
  alphal.Height         = 139;
  alphal.Picture_Type        = 1;
  alphal.Picture_Ratio  = 1;
  alphal.Picture_Name   = L_jpg;
  alphal.Visible        = 1;
  alphal.Active         = 1;
  alphal.OnUpPtr         = 0;
  alphal.OnDownPtr       = 0;
  alphal.OnClickPtr      = 0;
  alphal.OnPressPtr      = 0;

  alpham.OwnerScreen     = &Screen1;
  alpham.Order          = 27;
  alpham.Left           = 140;
  alpham.Top            = 144;
  alpham.Width          = 132;
  alpham.Height         = 139;
  alpham.Picture_Type        = 1;
  alpham.Picture_Ratio  = 1;
  alpham.Picture_Name   = M_jpg;
  alpham.Visible        = 1;
  alpham.Active         = 1;
  alpham.OnUpPtr         = 0;
  alpham.OnDownPtr       = 0;
  alpham.OnClickPtr      = 0;
  alpham.OnPressPtr      = 0;

  alphan.OwnerScreen     = &Screen1;
  alphan.Order          = 28;
  alphan.Left           = 148;
  alphan.Top            = 152;
  alphan.Width          = 115;
  alphan.Height         = 141;
  alphan.Picture_Type        = 1;
  alphan.Picture_Ratio  = 1;
  alphan.Picture_Name   = N_jpg;
  alphan.Visible        = 1;
  alphan.Active         = 1;
  alphan.OnUpPtr         = 0;
  alphan.OnDownPtr       = 0;
  alphan.OnClickPtr      = 0;
  alphan.OnPressPtr      = 0;

  alphao.OwnerScreen     = &Screen1;
  alphao.Order          = 29;
  alphao.Left           = 10;
  alphao.Top            = 12;
  alphao.Width          = 134;
  alphao.Height         = 141;
  alphao.Picture_Type        = 1;
  alphao.Picture_Ratio  = 1;
  alphao.Picture_Name   = O_jpg;
  alphao.Visible        = 1;
  alphao.Active         = 1;
  alphao.OnUpPtr         = 0;
  alphao.OnDownPtr       = 0;
  alphao.OnClickPtr      = 0;
  alphao.OnPressPtr      = 0;

  alphap.OwnerScreen     = &Screen1;
  alphap.Order          = 30;
  alphap.Left           = 20;
  alphap.Top            = 18;
  alphap.Width          = 106;
  alphap.Height         = 139;
  alphap.Picture_Type        = 1;
  alphap.Picture_Ratio  = 1;
  alphap.Picture_Name   = P_jpg;
  alphap.Visible        = 1;
  alphap.Active         = 1;
  alphap.OnUpPtr         = 0;
  alphap.OnDownPtr       = 0;
  alphap.OnClickPtr      = 0;
  alphap.OnPressPtr      = 0;

  alphaq.OwnerScreen     = &Screen1;
  alphaq.Order          = 31;
  alphaq.Left           = 27;
  alphaq.Top            = 22;
  alphaq.Width          = 141;
  alphaq.Height         = 150;
  alphaq.Picture_Type        = 1;
  alphaq.Picture_Ratio  = 1;
  alphaq.Picture_Name   = Q_jpg;
  alphaq.Visible        = 1;
  alphaq.Active         = 1;
  alphaq.OnUpPtr         = 0;
  alphaq.OnDownPtr       = 0;
  alphaq.OnClickPtr      = 0;
  alphaq.OnPressPtr      = 0;

  alphar.OwnerScreen     = &Screen1;
  alphar.Order          = 32;
  alphar.Left           = 38;
  alphar.Top            = 32;
  alphar.Width          = 115;
  alphar.Height         = 139;
  alphar.Picture_Type        = 1;
  alphar.Picture_Ratio  = 1;
  alphar.Picture_Name   = R_jpg;
  alphar.Visible        = 1;
  alphar.Active         = 1;
  alphar.OnUpPtr         = 0;
  alphar.OnDownPtr       = 0;
  alphar.OnClickPtr      = 0;
  alphar.OnPressPtr      = 0;

  alphas.OwnerScreen     = &Screen1;
  alphas.Order          = 33;
  alphas.Left           = 56;
  alphas.Top            = 48;
  alphas.Width          = 110;
  alphas.Height         = 141;
  alphas.Picture_Type        = 1;
  alphas.Picture_Ratio  = 1;
  alphas.Picture_Name   = S_jpg;
  alphas.Visible        = 1;
  alphas.Active         = 1;
  alphas.OnUpPtr         = 0;
  alphas.OnDownPtr       = 0;
  alphas.OnClickPtr      = 0;
  alphas.OnPressPtr      = 0;

  alphat.OwnerScreen     = &Screen1;
  alphat.Order          = 34;
  alphat.Left           = 68;
  alphat.Top            = 60;
  alphat.Width          = 117;
  alphat.Height         = 139;
  alphat.Picture_Type        = 1;
  alphat.Picture_Ratio  = 1;
  alphat.Picture_Name   = T_jpg;
  alphat.Visible        = 1;
  alphat.Active         = 1;
  alphat.OnUpPtr         = 0;
  alphat.OnDownPtr       = 0;
  alphat.OnClickPtr      = 0;
  alphat.OnPressPtr      = 0;

  alphau.OwnerScreen     = &Screen1;
  alphau.Order          = 35;
  alphau.Left           = 78;
  alphau.Top            = 70;
  alphau.Width          = 116;
  alphau.Height         = 141;
  alphau.Picture_Type        = 1;
  alphau.Picture_Ratio  = 1;
  alphau.Picture_Name   = U_jpg;
  alphau.Visible        = 1;
  alphau.Active         = 1;
  alphau.OnUpPtr         = 0;
  alphau.OnDownPtr       = 0;
  alphau.OnClickPtr      = 0;
  alphau.OnPressPtr      = 0;

  alphav.OwnerScreen     = &Screen1;
  alphav.Order          = 36;
  alphav.Left           = 94;
  alphav.Top            = 92;
  alphav.Width          = 120;
  alphav.Height         = 141;
  alphav.Picture_Type        = 1;
  alphav.Picture_Ratio  = 1;
  alphav.Picture_Name   = V_jpg;
  alphav.Visible        = 1;
  alphav.Active         = 1;
  alphav.OnUpPtr         = 0;
  alphav.OnDownPtr       = 0;
  alphav.OnClickPtr      = 0;
  alphav.OnPressPtr      = 0;

  alphaw.OwnerScreen     = &Screen1;
  alphaw.Order          = 37;
  alphaw.Left           = 106;
  alphaw.Top            = 104;
  alphaw.Width          = 170;
  alphaw.Height         = 141;
  alphaw.Picture_Type        = 1;
  alphaw.Picture_Ratio  = 1;
  alphaw.Picture_Name   = W_jpg;
  alphaw.Visible        = 1;
  alphaw.Active         = 1;
  alphaw.OnUpPtr         = 0;
  alphaw.OnDownPtr       = 0;
  alphaw.OnClickPtr      = 0;
  alphaw.OnPressPtr      = 0;

  alphax.OwnerScreen     = &Screen1;
  alphax.Order          = 38;
  alphax.Left           = 122;
  alphax.Top            = 120;
  alphax.Width          = 110;
  alphax.Height         = 141;
  alphax.Picture_Type        = 1;
  alphax.Picture_Ratio  = 1;
  alphax.Picture_Name   = X_jpg;
  alphax.Visible        = 1;
  alphax.Active         = 1;
  alphax.OnUpPtr         = 0;
  alphax.OnDownPtr       = 0;
  alphax.OnClickPtr      = 0;
  alphax.OnPressPtr      = 0;

  alphay.OwnerScreen     = &Screen1;
  alphay.Order          = 39;
  alphay.Left           = 136;
  alphay.Top            = 134;
  alphay.Width          = 112;
  alphay.Height         = 141;
  alphay.Picture_Type        = 1;
  alphay.Picture_Ratio  = 1;
  alphay.Picture_Name   = Y_jpg;
  alphay.Visible        = 1;
  alphay.Active         = 1;
  alphay.OnUpPtr         = 0;
  alphay.OnDownPtr       = 0;
  alphay.OnClickPtr      = 0;
  alphay.OnPressPtr      = 0;

  alphaz.OwnerScreen     = &Screen1;
  alphaz.Order          = 40;
  alphaz.Left           = 150;
  alphaz.Top            = 152;
  alphaz.Width          = 121;
  alphaz.Height         = 137;
  alphaz.Picture_Type        = 1;
  alphaz.Picture_Ratio  = 1;
  alphaz.Picture_Name   = Z_jpg;
  alphaz.Visible        = 1;
  alphaz.Active         = 1;
  alphaz.OnUpPtr         = 0;
  alphaz.OnDownPtr       = 0;
  alphaz.OnClickPtr      = 0;
  alphaz.OnPressPtr      = 0;

  pokeb1.OwnerScreen     = &Screen1;
  pokeb1.Order          = 41;
  pokeb1.Left           = 10;
  pokeb1.Top            = 10;
  pokeb1.Width          = 166;
  pokeb1.Height         = 171;
  pokeb1.Picture_Type        = 1;
  pokeb1.Picture_Ratio  = 1;
  pokeb1.Picture_Name   = b1_jpg;
  pokeb1.Visible        = 1;
  pokeb1.Active         = 1;
  pokeb1.OnUpPtr         = 0;
  pokeb1.OnDownPtr       = 0;
  pokeb1.OnClickPtr      = 0;
  pokeb1.OnPressPtr      = 0;

  pokeb2.OwnerScreen     = &Screen1;
  pokeb2.Order          = 42;
  pokeb2.Left           = 34;
  pokeb2.Top            = 32;
  pokeb2.Width          = 164;
  pokeb2.Height         = 170;
  pokeb2.Picture_Type        = 1;
  pokeb2.Picture_Ratio  = 1;
  pokeb2.Picture_Name   = b2_jpg;
  pokeb2.Visible        = 1;
  pokeb2.Active         = 1;
  pokeb2.OnUpPtr         = 0;
  pokeb2.OnDownPtr       = 0;
  pokeb2.OnClickPtr      = 0;
  pokeb2.OnPressPtr      = 0;

  pokeb3.OwnerScreen     = &Screen1;
  pokeb3.Order          = 43;
  pokeb3.Left           = 54;
  pokeb3.Top            = 46;
  pokeb3.Width          = 165;
  pokeb3.Height         = 171;
  pokeb3.Picture_Type        = 1;
  pokeb3.Picture_Ratio  = 1;
  pokeb3.Picture_Name   = b3_jpg;
  pokeb3.Visible        = 1;
  pokeb3.Active         = 1;
  pokeb3.OnUpPtr         = 0;
  pokeb3.OnDownPtr       = 0;
  pokeb3.OnClickPtr      = 0;
  pokeb3.OnPressPtr      = 0;

  pokef1.OwnerScreen     = &Screen1;
  pokef1.Order          = 44;
  pokef1.Left           = 14;
  pokef1.Top            = 16;
  pokef1.Width          = 165;
  pokef1.Height         = 170;
  pokef1.Picture_Type        = 1;
  pokef1.Picture_Ratio  = 1;
  pokef1.Picture_Name   = f1_jpg;
  pokef1.Visible        = 1;
  pokef1.Active         = 1;
  pokef1.OnUpPtr         = 0;
  pokef1.OnDownPtr       = 0;
  pokef1.OnClickPtr      = 0;
  pokef1.OnPressPtr      = 0;

  pokef2.OwnerScreen     = &Screen1;
  pokef2.Order          = 45;
  pokef2.Left           = 36;
  pokef2.Top            = 30;
  pokef2.Width          = 165;
  pokef2.Height         = 170;
  pokef2.Picture_Type        = 1;
  pokef2.Picture_Ratio  = 1;
  pokef2.Picture_Name   = f2_jpg;
  pokef2.Visible        = 1;
  pokef2.Active         = 1;
  pokef2.OnUpPtr         = 0;
  pokef2.OnDownPtr       = 0;
  pokef2.OnClickPtr      = 0;
  pokef2.OnPressPtr      = 0;

  pokef3.OwnerScreen     = &Screen1;
  pokef3.Order          = 46;
  pokef3.Left           = 52;
  pokef3.Top            = 48;
  pokef3.Width          = 163;
  pokef3.Height         = 169;
  pokef3.Picture_Type        = 1;
  pokef3.Picture_Ratio  = 1;
  pokef3.Picture_Name   = f3_jpg;
  pokef3.Visible        = 1;
  pokef3.Active         = 1;
  pokef3.OnUpPtr         = 0;
  pokef3.OnDownPtr       = 0;
  pokef3.OnClickPtr      = 0;
  pokef3.OnPressPtr      = 0;

  pokeg1.OwnerScreen     = &Screen1;
  pokeg1.Order          = 47;
  pokeg1.Left           = 42;
  pokeg1.Top            = 26;
  pokeg1.Width          = 164;
  pokeg1.Height         = 169;
  pokeg1.Picture_Type        = 1;
  pokeg1.Picture_Ratio  = 1;
  pokeg1.Picture_Name   = g1_jpg;
  pokeg1.Visible        = 1;
  pokeg1.Active         = 1;
  pokeg1.OnUpPtr         = 0;
  pokeg1.OnDownPtr       = 0;
  pokeg1.OnClickPtr      = 0;
  pokeg1.OnPressPtr      = 0;

  pokeg2.OwnerScreen     = &Screen1;
  pokeg2.Order          = 48;
  pokeg2.Left           = 66;
  pokeg2.Top            = 44;
  pokeg2.Width          = 166;
  pokeg2.Height         = 171;
  pokeg2.Picture_Type        = 1;
  pokeg2.Picture_Ratio  = 1;
  pokeg2.Picture_Name   = g2_jpg;
  pokeg2.Visible        = 1;
  pokeg2.Active         = 1;
  pokeg2.OnUpPtr         = 0;
  pokeg2.OnDownPtr       = 0;
  pokeg2.OnClickPtr      = 0;
  pokeg2.OnPressPtr      = 0;

  pokeg3.OwnerScreen     = &Screen1;
  pokeg3.Order          = 49;
  pokeg3.Left           = 76;
  pokeg3.Top            = 54;
  pokeg3.Width          = 163;
  pokeg3.Height         = 171;
  pokeg3.Picture_Type        = 1;
  pokeg3.Picture_Ratio  = 1;
  pokeg3.Picture_Name   = g3_jpg;
  pokeg3.Visible        = 1;
  pokeg3.Active         = 1;
  pokeg3.OnUpPtr         = 0;
  pokeg3.OnDownPtr       = 0;
  pokeg3.OnClickPtr      = 0;
  pokeg3.OnPressPtr      = 0;
}

static char IsInsideObject (unsigned int X, unsigned int Y, unsigned int Left, unsigned int Top, unsigned int Width, unsigned int Height) { // static
  if ( (Left<= X) && (Left+ Width - 1 >= X) &&
       (Top <= Y)  && (Top + Height - 1 >= Y) )
    return 1;
  else
    return 0;
}


#define GetImage(index)               CurrentScreen->Images[index]

 void DeleteTrailingSpaces(char* str){
   char i;
   i = 0;
   while(1) {
   if(str[0] == ' ') {
      for(i = 0; i < strlen(str); i++) {
       str[i] = str[i+1];
      }
   }
   else
     break;
  }
 }

void DrawImage(TImage *AImage) {
  if (AImage->Visible) {
    TFT_Ext_Image(AImage->Left, AImage->Top, AImage->Picture_Name, AImage->Picture_Ratio);
  }
}

void DrawScreen(TScreen *aScreen) {
 int order;
  unsigned short image_idx;
  TImage *local_image;
  char save_bled, save_bled_direction;

  object_pressed = 0;
  order = 0;
  image_idx = 0;
  CurrentScreen = aScreen;

  if ((display_width != CurrentScreen->Width) || (display_height != CurrentScreen->Height)) {
    save_bled = TFT_BLED;
    save_bled_direction = TFT_BLED_Direction;
    TFT_BLED_Direction = 1;
    TFT_BLED           = 0;
    TFT_Init(CurrentScreen->Width, CurrentScreen->Height);
    TFT_Set_Ext_Buffer(TFT_Get_Data);
    TP_TFT_Init(CurrentScreen->Width, CurrentScreen->Height, 11, 10);                                  // Initialize touch panel
    TP_TFT_Set_ADC_Threshold(ADC_THRESHOLD);                              // Set touch panel ADC threshold
    TFT_Fill_Screen(CurrentScreen->Color);
    display_width = CurrentScreen->Width;
    display_height = CurrentScreen->Height;
    TFT_BLED           = save_bled;
    TFT_BLED_Direction = save_bled_direction;
  }
  else
    TFT_Fill_Screen(CurrentScreen->Color);


  while (order < CurrentScreen->ObjectsCount) {
    if (image_idx  < CurrentScreen->ImagesCount) {
      local_image = GetImage(image_idx);
      if (order == local_image->Order) {
        image_idx++;
        order++;
        DrawImage(local_image);
      }
    }

  }
}

void Get_Object(unsigned int X, unsigned int Y) {
  image_order         = -1;
  //  Images
  for ( _object_count = 0 ; _object_count < CurrentScreen->ImagesCount ; _object_count++ ) {
    local_image = GetImage(_object_count);
    if (local_image->Active == 1) {
      if (IsInsideObject(X, Y, local_image->Left, local_image->Top,
                         local_image->Width, local_image->Height) == 1) {
        image_order = local_image->Order;
        exec_image = local_image;
      }
    }
  }

  _object_count = -1;
  if (image_order >  _object_count )
    _object_count = image_order;
}


static void Process_TP_Press(unsigned int X, unsigned int Y) {
  exec_image          = 0;

  Get_Object(X, Y);


  if (_object_count != -1) {
    if (_object_count == image_order) {
      if (exec_image->Active == 1) {
        if (exec_image->OnPressPtr != 0) {
          exec_image->OnPressPtr();
          return;
        }
      }
    }

  }
}

static void Process_TP_Up(unsigned int X, unsigned int Y) {

  exec_image          = 0;

  Get_Object(X, Y);


  if (_object_count != -1) {
  // Images
    if (_object_count == image_order) {
      if (exec_image->Active == 1) {
        if (exec_image->OnUpPtr != 0)
          exec_image->OnUpPtr();
        if (PressedObject == (void *)exec_image)
          if (exec_image->OnClickPtr != 0)
            exec_image->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }

  }
  PressedObject = 0;
  PressedObjectType = -1;
}

static void Process_TP_Down(unsigned int X, unsigned int Y) {

  object_pressed      = 0;
  exec_image          = 0;

  Get_Object(X, Y);

  if (_object_count != -1) {
    if (_object_count == image_order) {
      if (exec_image->Active == 1) {
        PressedObject = (void *)exec_image;
        PressedObjectType = 3;
        if (exec_image->OnDownPtr != 0) {
          exec_image->OnDownPtr();
          return;
        }
      }
    }

  }
}

void Check_TP() {
  if (TP_TFT_Press_Detect()) {
    // After a PRESS is detected read X-Y and convert it to Display dimensions space
    if (TP_TFT_Get_Coordinates(&Xcoord, &Ycoord) == 0) {
      Process_TP_Press(Xcoord, Ycoord);
      if (PenDown == 0) {
        PenDown = 1;
        Process_TP_Down(Xcoord, Ycoord);
      }
    }
  }
  else if (PenDown == 1) {
    PenDown = 0;
    Process_TP_Up(Xcoord, Ycoord);
  }
}


void Init_MCU(){
  //  GPIO_Config(&GPIO_PORTE_DATA_BITS, 0b11110000, _GPIO_DIR_OUTPUT, _GPIO_CFG_DIGITAL_ENABLE | _GPIO_CFG_DRIVE_8mA, 0);
  // R Sensor
  // This is analog to :
  GPIO_Config(&GPIO_PORTE_DATA_BITS, 0b11110000, _GPIO_DIR_INPUT, _GPIO_CFG_DIGITAL_ENABLE, _GPIO_PINCODE_NONE);

  //rising edge :
  GPIO_PORTE_IEV = 0b11110000;
  GPIO_PORTE_IBE = 0b00000000;

  NVIC_IntEnable(IVT_INT_GPIOE);    // Enable GPIO interrupt

  // interrupt on
  GPIO_PORTE_IM = 0b11110000;

  // Emition Sensor
  GPIO_Config(&GPIO_PORTH_DATA_BITS, 0b00001111, _GPIO_DIR_OUTPUT, _GPIO_CFG_DIGITAL_ENABLE | _GPIO_CFG_DRIVE_8mA, 0);
  GPIO_Config(&GPIO_PORTD_DATA_BITS, 0b00001000, _GPIO_DIR_OUTPUT, _GPIO_CFG_DIGITAL_ENABLE | _GPIO_CFG_DRIVE_8mA, 0);
  GPIO_PORTD_DEN   = 0b01101000;     //digital enable
  GPIO_PORTD_AFSEL = 0b01100000;     // PD5 PD6 Peripheral Signal
  //GPIO_PORTD_DR8R  = 0b00000000;     // 8mA Drive( I think it's not necessary )
  GPIO_PORTD_PCTL  = 0x09900000;     // Spec P.1264 Table

  TFT_BLED = 1;
  TP_TFT_Rotate_180(0);
}


void Init_Ext_Mem() {
  // Initialize SPI
  SPI0_Init_Advanced(20000000, _SPI_MASTER, _SPI_8_BIT, &_GPIO_MODULE_SPI0_A245);
  Delay_ms(10);

  // Initialize MMC
  if (!Mmc_Fat_Init()) {

    // Open resource file for read
    Mmc_Fat_Assign("Sample_r.RES", 0);
    Mmc_Fat_Reset(&res_file_size);
  }
}

void Start_TP() {
  Init_MCU();

  Init_Ext_Mem();

  InitializeTouchPanel();
  /*
  Delay_ms(1000);
  TFT_Fill_Screen(0);
  Calibrate();
  TFT_Fill_Screen(0);
  */
  InitializeObjects();
  display_width = Screen1.Width;
  display_height = Screen1.Height;
  //DrawScreen(&Screen1);
}