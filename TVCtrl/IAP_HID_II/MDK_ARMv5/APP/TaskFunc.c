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
extern u8 LEDAllOn;

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

u8 OpCmd,LedFlash = 0;

//CLOSE1 后退终点位
//CLOSE2 前进终点位
//CLOSE3 前进落点最低位
//CLOSE4 上升落点最高位
void TaskFunc(void)
{  
	if((LEDAllOn > 0)||(LedFlash == 1))
	{
		Led1Duty.Sta = ALL_LIGHT;
	}
	else
	{
		Led1Duty.Sta = TINY_LIGHT;
	}
	
    switch(Func.Sta)
    {
        case RDY_STA:   //就绪状态
            switch(OpCmd)
            {
                case STOP_CMD:
                    Func.Sta = RDY_STA;
                    DriveRY1OFF();
                    DriveRY2OFF();
                    DriveRY3OFF();
                    DriveRY4OFF();
                    OpCmd = NONE_CMD;
                    break;
                case FWD_CMD:
                    if(DriveGetCloseSW2() == 1)	//在低位,X没有终点
                    {
                        Func.Sta = RUN_FWD_STA;
                        DriveRY1ON();	//前进转
                        DriveRY2OFF();
                        DriveRY3OFF(); 
                        DriveRY4OFF();
                        Func.StartDly = 0;
                        Func.DlyAct = 0;                        
                    }
					else		//在高位，需要上升，接通TV电源
					{
						if(DriveGetCloseSW4() == 1)	//在低位,Y没有终点
						{						
							Func.Sta = RUN_FWD_STA;
							DriveRY1OFF();
							DriveRY2ON();//上升转
							DriveRY3OFF(); 
							DriveRY4OFF();
							Func.StartDly = 0;
							Func.DlyAct = 0;  
						}							
					}
                    OpCmd = NONE_CMD;                
                    break;
                case REV_CMD:
                    if(DriveGetCloseSW3() == 1)	//在低位,X没有终点
                    {
                        Func.Sta = RUN_FWD_STA;
                        DriveRY1OFF();
                        DriveRY2OFF();
                        DriveRY3OFF(); 
                        DriveRY4ON();//下降转
                        Func.StartDly = 0;
                        Func.DlyAct = 0;                        
                    }
					else		//在高位，需要上升，接通TV电源
					{
						if(DriveGetCloseSW1() == 1)	//在低位,X没有终点
						{						
							Func.Sta = RUN_FWD_STA;
							DriveRY1OFF();
							DriveRY2OFF();
							DriveRY3ON(); //回退转
							DriveRY4OFF();
							Func.StartDly = 0;
							Func.DlyAct = 0;  
						}							
					}
                    OpCmd = NONE_CMD;                
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
        case RUN_FWD_STA:                       //正转运行状态           
            if(OpCmd != NONE_CMD)				//只要有任意键按下
            {
                DriveRY1OFF();
                DriveRY2OFF();
                DriveRY3OFF(); 
                DriveRY4OFF();
                OpCmd = STOP_CMD;
                Func.Sta = RDY_STA;                				
            }
//            if(Func.StartDly == 0)              //是否检测到行程开关开始延时
//            {
//                if(DriveGetCloseSW1() == 0)     //到行程开关位置
//                {
//                    Func.StartDly = 1;
//                    Func.DlyCnt = 0;
//                }
//            }
			if(DriveGetCloseSW2() == 0)	//在低位,X没有终点
			{
				DriveRY1OFF();	//前进停止
				if(DriveGetCloseSW4() == 1)	//在低位,Y没有终点
				{						
					DriveRY2ON();//上升转
					DriveRY4OFF();
				}	
				else
				{
					LedFlash = 1;
					Func.DlyAct = 0;
					DriveRY1OFF();
					DriveRY2OFF();
					DriveRY3OFF(); 
					DriveRY4OFF();
					OpCmd = STOP_CMD;
					Func.Sta = RDY_STA;                					
				}
			}
            if(Func.DlyAct == 1)                //延时结束
            {
				LedFlash = 1;
				Func.DlyAct = 0;
                DriveRY1OFF();
                DriveRY2OFF();
                DriveRY3OFF(); 
                DriveRY4OFF();
                OpCmd = STOP_CMD;
                Func.Sta = RDY_STA;                
            }
            break;
        case RUN_REV_STA:                       //反转运行状态
            if(OpCmd != NONE_CMD)				//只要有任意键按下
            {
                DriveRY1OFF();
                DriveRY2OFF();
                DriveRY3OFF(); 
                DriveRY4OFF();
                OpCmd = STOP_CMD;
                Func.Sta = RDY_STA;                				
            }   
			if(DriveGetCloseSW3() == 0)	//在低位,X没有终点
			{
				DriveRY4OFF();	//下降停止
				if(DriveGetCloseSW1() == 1)	//在低位,Y没有终点
				{						
					DriveRY3ON();//后退转
				}	
				else
				{
					LedFlash = 1;
					Func.DlyAct = 0;
					DriveRY1OFF();
					DriveRY2OFF();
					DriveRY3OFF(); 
					DriveRY4OFF();
					OpCmd = STOP_CMD;
					Func.Sta = RDY_STA;                					
				}
			}           
		
//            if(Func.StartDly == 0)            	//是否检测到行程开关开始延时
//            {
//                if(DriveGetCloseSW2() == 0)     //到行程开关位置
//                {
//                    Func.StartDly = 1;
//                    Func.DlyCnt = 0;
//                }
//            } 
//            if(Func.DlyAct == 1)           		//延时结束
//            {
//				LedFlash = 1;
//                Func.DlyAct = 0;
//                DriveRY1OFF();
//                DriveRY2OFF();
//                DriveRY3OFF(); 
//                DriveRY4OFF();
//                OpCmd = STOP_CMD;
//                Func.Sta = RDY_STA;                
//            }                    
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
