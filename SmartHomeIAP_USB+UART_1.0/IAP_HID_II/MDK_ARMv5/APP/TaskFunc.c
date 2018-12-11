#include "ht32.h"
#include "ht32_board.h"
#include "main.h"

typedef struct
{
    u8 Sta;
    u8 OnTime;
}
_LED_DUTY;

_LED_DUTY Led1Duty;

#define TINY_LIGHT  1
#define ALL_LIGHT   2
#define OFF_LIGTH   3


__FUNC_STRUCT Func;

extern _KEY_STRUCT StopKey,FwdKey,RevKey;
extern __FUNC_STRUCT Func;
extern _WEIGHT_SENSOR WeightSensor;
extern FlagStatus ReadyReFlag;
extern u8 RFRecord[3];

void LedCallBack(void)
{
    switch(Led1Duty.Sta)
    {
        case TINY_LIGHT:
            if(Led1Duty.OnTime++ < 1)
            {
                HT32F_DVB_LEDOn(HT_LED2);
                HT32F_DVB_LEDOn(HT_LED3);
                HT32F_DVB_LEDOn(HT_LED4);
            }
            else
            {
                if(Led1Duty.OnTime >= 8)
                    Led1Duty.OnTime = 0;
                HT32F_DVB_LEDOff(HT_LED2);
                HT32F_DVB_LEDOff(HT_LED3);
                HT32F_DVB_LEDOff(HT_LED4);
            }
            break;
        case ALL_LIGHT:
            HT32F_DVB_LEDOn(HT_LED2);
            HT32F_DVB_LEDOn(HT_LED3);
            HT32F_DVB_LEDOn(HT_LED4);
            break;
        default:
            HT32F_DVB_LEDOff(HT_LED2);
            HT32F_DVB_LEDOff(HT_LED3);
            HT32F_DVB_LEDOff(HT_LED4);
            break;
    }
}

u8 OpCmd;

void TaskFunc(void)
{  
    switch(Func.Sta)
    {
        case RDY_STA:   //就绪状态
            Led1Duty.Sta = TINY_LIGHT;

            switch(OpCmd)
            {
                case STOP_CMD:
                    Func.Sta = RDY_STA;
                    DriveRY1OFF();
                    DriveRY2OFF();
                    DriveRY3OFF();
                    DriveRY4OFF();
                    OpCmd = 0;
                    break;
                case FWD_CMD:
                    if(DriveGetLimitSW4() == 1) 
                    {
                        Func.Sta = RUN_FWD_STA;
                        DriveRY1ON();
                        DriveRY2ON();
                        DriveRY3OFF(); 
                        DriveRY4OFF();
                        Led1Duty.Sta = ALL_LIGHT;  
                        Func.StartDly = 0;
                        Func.DlyAct = 0;                        
                    }
                    OpCmd = 0;                
                    break;
                case REV_CMD:
                    if(DriveGetLimitSW3() == 1) 
                    {
                        Func.Sta = RUN_REV_STA;
                        DriveRY1OFF();
                        DriveRY2OFF();
                        DriveRY3OFF();
                        DriveRY4ON();
                        Led1Duty.Sta = ALL_LIGHT; 
                        Func.StartDly = 0;                        
                        Func.DlyAct = 0;                        
                    }
                    OpCmd = 0;                
                    break;
                default:
                    break;
            }            
            if(WeightSensor.WeightAlarm)        //报警
            {
                HT32F_DVB_LEDOn(HT_LED1);
            }
            else
            {
                HT32F_DVB_LEDOff(HT_LED1);
            }            
            break;
        case LOCK_STA:      //锁定状态
            
            break;
        case RUN_FWD_STA:                        //正转运行状态           
            if(OpCmd == STOP_CMD)
            {
                Func.Sta = RDY_STA;
            }
            if(Func.StartDly == 0)              //是否检测到行程开关开始延时
            {
                if(DriveGetLimitSW4() == 0)     //到行程开关位置
                {
                    Func.StartDly = 1;
                    Func.DlyCnt = 0;
                }
            } 
            if(Func.DlyAct == 1)                //延时结束
            {
                Func.DlyAct = 0;
                DriveRY1OFF();
                DriveRY2OFF();
                DriveRY3OFF(); 
                DriveRY4OFF();
                OpCmd = STOP_CMD;
                Func.Sta = RDY_STA;                
            }
            if(WeightSensor.WeightAlarm)        //报警
            {
                HT32F_DVB_LEDOn(HT_LED1);
                OpCmd = STOP_CMD;
                Func.Sta = RDY_STA;  
            }
            else
            {
                HT32F_DVB_LEDOff(HT_LED1);
            }            
            break;
        case RUN_REV_STA:                       //反转运行状态
            if(OpCmd == STOP_CMD)
            {
                Func.Sta = RDY_STA;
            }   
            //到位后打开离开器电磁铁,接近开关
            if(DriveGetCloseSW1() == 0)
            {
                //DriveRY4OFF(); //开锁电磁铁要关吗？
                DriveRY2ON();
                DriveRY3ON(); 
            }
            
             if(Func.StartDly == 0)              //是否检测到行程开关开始延时
            {
                if(DriveGetLimitSW3() == 0)     //到行程开关位置
                {
                    Func.StartDly = 1;
                    Func.DlyCnt = 0;
                }
            } 
            if(Func.DlyAct == 1)            //延时结束
            {
                Func.DlyAct = 0;
                DriveRY1OFF();
                DriveRY2OFF();
                DriveRY3OFF(); 
                DriveRY4OFF();
                OpCmd = STOP_CMD;
                Func.Sta = RDY_STA;                
            }           
            if(WeightSensor.WeightAlarm)        //报警
            {
                HT32F_DVB_LEDOn(HT_LED1);
                OpCmd = STOP_CMD;
                Func.Sta = RDY_STA;  
            }
            else
            {
                HT32F_DVB_LEDOff(HT_LED1);
            }            
            break;
            
        case SET_RF:        //设置RF接收
            if(ReadyReFlag == SET)
            {
                ReadyReFlag = RESET;
                SaveData((RFRecord[1]<<8)+RFRecord[0]);
                Func.Sta = RDY_STA;
            }
            break;
        case SET_WEIGHT:   //设置标称
            if(WeightSensor.InitSuccess == 1)
            {
                Func.Sta = RDY_STA;
            }
            break;
        default:
            break;
    }
}
