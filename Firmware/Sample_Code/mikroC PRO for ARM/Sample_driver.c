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
  TImage               multiple;
  TImage               divide;
  TImage               equal;
  TImage                 * const code Screen1_Images[15]=
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
         &multiple,            
         &divide,              
         &equal                
         };




static void InitializeObjects() {
  Screen1.Color                     = 0x8410;
  Screen1.Width                     = 240;
  Screen1.Height                    = 320;
  Screen1.ImagesCount               = 15;
  Screen1.Images                    = Screen1_Images;
  Screen1.ObjectsCount              = 15;


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

  multiple.OwnerScreen     = &Screen1;
  multiple.Order          = 12;
  multiple.Left           = 138;
  multiple.Top            = 136;
  multiple.Width          = 114;
  multiple.Height         = 113;
  multiple.Picture_Type   = 0;
  multiple.Picture_Ratio  = 1;
  multiple.Picture_Name   = mutiple_bmp;
  multiple.Visible        = 0;
  multiple.Active         = 1;
  multiple.OnUpPtr         = 0;
  multiple.OnDownPtr       = 0;
  multiple.OnClickPtr      = 0;
  multiple.OnPressPtr      = 0;

  divide.OwnerScreen     = &Screen1;
  divide.Order          = 13;
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
  equal.Order          = 14;
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

  InitializeObjects();
  display_width = Screen1.Width;
  display_height = Screen1.Height;
  DrawScreen(&Screen1);
  */
}