#ifndef __DRIVEFIXOUT_H
#define __DRIVEFIXOUT_H

void FixOutInit(void);

#define DriveRY1ON()    HT32F_DVB_LEDOn(RY1)
#define DriveRY2ON()    HT32F_DVB_LEDOn(RY2)
#define DriveRY3ON()    HT32F_DVB_LEDOn(RY3)
#define DriveRY4ON()    HT32F_DVB_LEDOn(RY4)
#define DriveRY5ON()    HT32F_DVB_LEDOn(RY5)

#define DriveRY1OFF()    HT32F_DVB_LEDOff(RY1)
#define DriveRY2OFF()    HT32F_DVB_LEDOff(RY2)
#define DriveRY3OFF()    HT32F_DVB_LEDOff(RY3)
#define DriveRY4OFF()    HT32F_DVB_LEDOff(RY4)
#define DriveRY5OFF()    HT32F_DVB_LEDOff(RY5)

#endif