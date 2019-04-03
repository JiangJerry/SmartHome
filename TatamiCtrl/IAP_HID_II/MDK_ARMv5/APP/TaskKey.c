#include "ht32.h"
#include "ht32_board.h"
#include "main.h"
#include "BMP280Drive.h"

FlagStatus TaskLEDRdy,TaskKeyRdy;

u16 DlySet = 60,DlyTime;

extern u8 G_Input_Flag[];

extern u8 SFlag;
extern u8 PressDn,PressDnFlag,LowBatFlag;
u8 PressDnBak = 0,BATSta = 0;


extern u8 WakeUpType;

_BAT_STATUS BatSta;
void Delay(u8 i)
{
    for(;i>0;i--);
}

extern __FUNC_STRUCT Func;
extern _WEIGHT_SENSOR WeightSensor;
extern u8 OpCmd;
extern u16 CntForLockTime;
#define STOP_INDEX  1
#define FWD_INDEX  2
#define REV_INDEX  3

void TaskKey(void)
{	   
    if(TaskKeyRdy)
    {
        TaskKeyRdy = RESET;
        GetKey(); 
        ADCStart();        
        TimeGetKey();
        if(G_Input_Flag[STOP_INDEX] == 1)
        {
            G_Input_Flag[STOP_INDEX] = 0;
            CntForLockTime = 0;             //清锁定时间
            OpCmd = STOP_CMD;
        }
        if(G_Input_Flag[FWD_INDEX] == 1)
        {
            G_Input_Flag[FWD_INDEX] = 0;
            CntForLockTime = 0;
            OpCmd = FWD_CMD;         
        }
        if(G_Input_Flag[REV_INDEX] == 1)
        {
            G_Input_Flag[REV_INDEX] = 0;
            CntForLockTime = 0;
            OpCmd = REV_CMD;
        }      
    }        
}
