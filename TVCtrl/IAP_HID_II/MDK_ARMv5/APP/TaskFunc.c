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

//CLOSE1 �����յ�λ
//CLOSE2 ǰ���յ�λ
//CLOSE3 ǰ��������λ
//CLOSE4 ����������λ
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
        case RDY_STA:   //����״̬
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
                    if(DriveGetCloseSW2() == 1)	//�ڵ�λ,Xû���յ�
                    {
                        Func.Sta = RUN_FWD_STA;
                        DriveRY1ON();	//ǰ��ת
                        DriveRY2OFF();
                        DriveRY3OFF(); 
                        DriveRY4OFF();
                        Func.StartDly = 0;
                        Func.DlyAct = 0;                        
                    }
					else		//�ڸ�λ����Ҫ��������ͨTV��Դ
					{
						if(DriveGetCloseSW4() == 1)	//�ڵ�λ,Yû���յ�
						{						
							Func.Sta = RUN_FWD_STA;
							DriveRY1OFF();
							DriveRY2ON();//����ת
							DriveRY3OFF(); 
							DriveRY4OFF();
							Func.StartDly = 0;
							Func.DlyAct = 0;  
						}							
					}
                    OpCmd = NONE_CMD;                
                    break;
                case REV_CMD:
                    if(DriveGetCloseSW3() == 1)	//�ڵ�λ,Xû���յ�
                    {
                        Func.Sta = RUN_FWD_STA;
                        DriveRY1OFF();
                        DriveRY2OFF();
                        DriveRY3OFF(); 
                        DriveRY4ON();//�½�ת
                        Func.StartDly = 0;
                        Func.DlyAct = 0;                        
                    }
					else		//�ڸ�λ����Ҫ��������ͨTV��Դ
					{
						if(DriveGetCloseSW1() == 1)	//�ڵ�λ,Xû���յ�
						{						
							Func.Sta = RUN_FWD_STA;
							DriveRY1OFF();
							DriveRY2OFF();
							DriveRY3ON(); //����ת
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
            if(WeightSensor.WeightAlarm)        //����
            {
                HT32F_DVB_LEDOn(HT_LED1);
            }
            else
            {
                HT32F_DVB_LEDOff(HT_LED1);
            }            
            break;
        case LOCK_STA:      //����״̬
            
            break;
        case RUN_FWD_STA:                       //��ת����״̬           
            if(OpCmd != NONE_CMD)				//ֻҪ�����������
            {
                DriveRY1OFF();
                DriveRY2OFF();
                DriveRY3OFF(); 
                DriveRY4OFF();
                OpCmd = STOP_CMD;
                Func.Sta = RDY_STA;                				
            }
//            if(Func.StartDly == 0)              //�Ƿ��⵽�г̿��ؿ�ʼ��ʱ
//            {
//                if(DriveGetCloseSW1() == 0)     //���г̿���λ��
//                {
//                    Func.StartDly = 1;
//                    Func.DlyCnt = 0;
//                }
//            }
			if(DriveGetCloseSW2() == 0)	//�ڵ�λ,Xû���յ�
			{
				DriveRY1OFF();	//ǰ��ֹͣ
				if(DriveGetCloseSW4() == 1)	//�ڵ�λ,Yû���յ�
				{						
					DriveRY2ON();//����ת
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
            if(Func.DlyAct == 1)                //��ʱ����
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
        case RUN_REV_STA:                       //��ת����״̬
            if(OpCmd != NONE_CMD)				//ֻҪ�����������
            {
                DriveRY1OFF();
                DriveRY2OFF();
                DriveRY3OFF(); 
                DriveRY4OFF();
                OpCmd = STOP_CMD;
                Func.Sta = RDY_STA;                				
            }   
			if(DriveGetCloseSW3() == 0)	//�ڵ�λ,Xû���յ�
			{
				DriveRY4OFF();	//�½�ֹͣ
				if(DriveGetCloseSW1() == 1)	//�ڵ�λ,Yû���յ�
				{						
					DriveRY3ON();//����ת
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
		
//            if(Func.StartDly == 0)            	//�Ƿ��⵽�г̿��ؿ�ʼ��ʱ
//            {
//                if(DriveGetCloseSW2() == 0)     //���г̿���λ��
//                {
//                    Func.StartDly = 1;
//                    Func.DlyCnt = 0;
//                }
//            } 
//            if(Func.DlyAct == 1)           		//��ʱ����
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
            
        case SET_RF:        //����RF����
            if(ReadyReFlag == SET)
            {
                ReadyReFlag = RESET;
                SaveData((RFRecord[1]<<8)+RFRecord[0]);
                Func.Sta = RDY_STA;
            }
            break;
        case SET_WEIGHT:   //���ñ��
            if(WeightSensor.InitSuccess == 1)
            {
                Func.Sta = RDY_STA;
            }
            break;
        default:
            break;
    }
}
