#include "ht32.h"
#include "ht32_board.h"
#include "main.h"
#include "BMP280Drive.h"



_WEIGHT_SENSOR WeightSensor;
    
FlagStatus TaskWeightRdy;

void WeightInit(void)
{
    WeightSensor.Sta = WEIGHT_QUIRY;
    WeightSensor.WeightAlarm = 0;
}


u8 SetZero[3]       = {0x3a,0x4c,0x80};     //�궨0
u8 SetWeight1[3]    = {0x3a,0x4c,0x43};     //�궨��һ����
u8 QueryWeight[3]   = {0xCA,0xc2,0xEE};     //��ѯ����

void WeightReset(void)
{
    WeightSensor.Sta = WEIGHT_QUIRY;
    SendCmd(&SetZero[0]);
}

void TaskWeight(void)
{
    if(TaskWeightRdy)
    {
        TaskWeightRdy = 0;
        if(WeightSensor.Sta == WEIGHT_RESET)
        {
            WeightSensor.Sta = WEIGHT_WAIT;
            SendCmd(&SetZero[0]);    
        }
        
        if(WeightSensor.Sta == WEIGHT_ZERO)
        {
            SendCmd(&SetWeight1[0]);    
            WeightSensor.Sta = WEIGHT_QUIRY;
            WeightSensor.InitSuccess = 0;         
        }
        
        if(WeightSensor.Sta == WEIGHT_QUIRY)
        {
            SendCmd(&QueryWeight[0]);            
        }
                
        if(WeightSensor.Sta == WEIGHT_FAIL) //�궨ʧ��
        {
            WeightSensor.Sta = WEIGHT_RESET;//���±궨
        }
    }
}