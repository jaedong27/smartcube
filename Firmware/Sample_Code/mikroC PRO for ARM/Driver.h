#ifndef __DRIVER
#define __DRIVER        1


#define BOARDID             0x1

extern unsigned int commcompleteflag;
extern unsigned int servercommcompleteflag;
extern unsigned int commstatusflag;

extern int serverrequestwalldataflag;
extern int serverrequestpictureflag;


extern int displaypictureflag;
extern int displaypictureindex;
extern int getwallflag;

typedef struct {
       unsigned int avrid;
       unsigned int status[4];
       unsigned int neighborid[4];
} _tSensorStatus;

extern _tSensorStatus   SensorStatus;

extern unsigned long tick_10u_time = 0;
#define tick_1m_time (unsigned long)(tick_10u_time / 100)

void Start_Driver(void);
void Check_Event(void);

#else

#endif