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
extern   TImage               divide;
extern   TImage               equal;
extern   TImage               multiple;
extern   TImage               alphaa;
extern   TImage               alphab;
extern   TImage               alphac;
extern   TImage               alphad;
extern   TImage               alphae;
extern   TImage               alphaf;
extern   TImage               alphag;
extern   TImage               alphah;
extern   TImage               alphai;
extern   TImage               alphaj;
extern   TImage               alphak;
extern   TImage               alphal;
extern   TImage               alpham;
extern   TImage               alphan;
extern   TImage               alphao;
extern   TImage               alphap;
extern   TImage               alphaq;
extern   TImage               alphar;
extern   TImage               alphas;
extern   TImage               alphat;
extern   TImage               alphau;
extern   TImage               alphav;
extern   TImage               alphaw;
extern   TImage               alphax;
extern   TImage               alphay;
extern   TImage               alphaz;
extern   TImage               pokeb1;
extern   TImage               pokeb2;
extern   TImage               pokeb3;
extern   TImage               pokef1;
extern   TImage               pokef2;
extern   TImage               pokef3;
extern   TImage               pokeg1;
extern   TImage               pokeg2;
extern   TImage               pokeg3;
extern   TImage                 * const code Screen1_Images[50];



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
extern char divide_Caption[];
extern char equal_Caption[];
extern char multiple_Caption[];
extern char alphaa_Caption[];
extern char alphab_Caption[];
extern char alphac_Caption[];
extern char alphad_Caption[];
extern char alphae_Caption[];
extern char alphaf_Caption[];
extern char alphag_Caption[];
extern char alphah_Caption[];
extern char alphai_Caption[];
extern char alphaj_Caption[];
extern char alphak_Caption[];
extern char alphal_Caption[];
extern char alpham_Caption[];
extern char alphan_Caption[];
extern char alphao_Caption[];
extern char alphap_Caption[];
extern char alphaq_Caption[];
extern char alphar_Caption[];
extern char alphas_Caption[];
extern char alphat_Caption[];
extern char alphau_Caption[];
extern char alphav_Caption[];
extern char alphaw_Caption[];
extern char alphax_Caption[];
extern char alphay_Caption[];
extern char alphaz_Caption[];
extern char pokeb1_Caption[];
extern char pokeb2_Caption[];
extern char pokeb3_Caption[];
extern char pokef1_Caption[];
extern char pokef2_Caption[];
extern char pokef3_Caption[];
extern char pokeg1_Caption[];
extern char pokeg2_Caption[];
extern char pokeg3_Caption[];
/////////////////////////////////

void DrawScreen(TScreen *aScreen);
void DrawImage(TImage *AImage);
void Check_TP();
void Start_TP();
