typedef enum {_taLeft, _taCenter, _taRight} TTextAlign;

typedef struct Screen TScreen;

typedef struct  Image {
  TScreen*  OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  const char    *Picture_Name;
  char          Visible;
  char          Active;
  char          Picture_Type;
  char          Picture_Ratio;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TImage;

struct Screen {
  unsigned int           Color;
  unsigned int           Width;
  unsigned int           Height;
  unsigned short         ObjectsCount;
  unsigned int           ImagesCount;
  TImage                 * const code *Images;
};

extern   TScreen                Screen1;
extern   TImage               ImageNum0;
extern   TImage               ImageNum1;
extern   TImage               ImageNum2;
extern   TImage               ImageNum3;
extern   TImage               ImageNum4;
extern   TImage               ImageNum5;
extern   TImage               ImageNum6;
extern   TImage               ImageNum7;
extern   TImage               ImageNum8;
extern   TImage               ImageNum9;
extern   TImage               plus;
extern   TImage               minus;
extern   TImage               multiple;
extern   TImage               divide;
extern   TImage               equal;
extern   TImage                 * const code Screen1_Images[15];



/////////////////////////
// Events Code Declarations
/////////////////////////

/////////////////////////////////
// Caption variables Declarations
extern char ImageNum0_Caption[];
extern char ImageNum1_Caption[];
extern char ImageNum2_Caption[];
extern char ImageNum3_Caption[];
extern char ImageNum4_Caption[];
extern char ImageNum5_Caption[];
extern char ImageNum6_Caption[];
extern char ImageNum7_Caption[];
extern char ImageNum8_Caption[];
extern char ImageNum9_Caption[];
extern char plus_Caption[];
extern char minus_Caption[];
extern char multiple_Caption[];
extern char divide_Caption[];
extern char equal_Caption[];
/////////////////////////////////

void DrawScreen(TScreen *aScreen);
void DrawImage(TImage *AImage);
void Check_TP();
void Start_TP();
