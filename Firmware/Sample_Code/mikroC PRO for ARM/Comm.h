#ifndef __COMM
#define __COMM        1

#define COMM_IDLE 0
#define COMM_DATA 1

extern unsigned int commstatusflag = 0;

extern unsigned int serverrequestpictureboardid = 0;
extern unsigned int serverrequestpictureindex = 0;

extern void sendtoServerWalldata();
extern void RequestWallData(void);
extern void RequestSetData(unsigned int BoardID, unsigned int pictureindex);

extern void sendStatusData(void);
extern void receivePacket(unsigned int tdata);
extern void receiveServerPacket(unsigned int tdata);
#endif