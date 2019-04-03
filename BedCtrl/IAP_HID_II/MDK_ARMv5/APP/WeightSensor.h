#ifndef __WEIGHT
#define __WEIGHT

#define WEIGHT_RESET    0
#define WEIGHT_ZERO     1
#define WEIGHT_3KG      2
#define WEIGHT_QUIRY    3
#define WEIGHT_FAIL     4
#define WEIGHT_WAIT     0XFF

#define u8 unsigned char

typedef struct
{
    u8 Sta;
    u8 WeightAlarm;
    u8 InitSuccess; //标定成功标示位
}_WEIGHT_SENSOR;


#define KEY_STOP(a) ((a < 50))?0:1

#define KEY_FWD(a) ((a > 1800) && (a < 2500))? 0 : 1

#define KEY_REV(a) ((a > 2800)&&(a < 3100))? 0 : 1


void WeightInit(void);
void WeightReset(void);
void TaskWeight(void);
#endif
