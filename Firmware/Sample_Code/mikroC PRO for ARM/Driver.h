#ifndef __DRIVER
#define __DRIVER        1

#include "ACCEL_driver.h"

#define Color24To565(value)   (((value&0xF80000)>>8) | ((value&0x00FC00)>>5) | (value&0x00001F))

extern unsigned int commcompleteflag;
extern unsigned int commstatusflag;

typedef struct {
       unsigned int avrid;
       unsigned int status[4];
       unsigned int neighborid[4];
} _tSensorStatus;

extern _tSensorStatus   SensorStatus;

void Start_Driver(void);
void Check_Event(void);

#else

#endif