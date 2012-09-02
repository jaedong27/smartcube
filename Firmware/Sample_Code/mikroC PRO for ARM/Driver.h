#ifndef __DRIVER
#define __DRIVER        1

extern unsigned int commcompleteflag;
extern unsigned int commstatusflag;

typedef struct {
       unsigned int avrid;
       unsigned int status[4];
       unsigned int neighborid[4];
} _tSensorStatus;

extern _tSensorStatus   SensorStatus;

extern unsigned long tick_10um_time = 0;

void Start_Driver(void);
void Check_Event(void);

#else

#endif