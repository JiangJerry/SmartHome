#include "ht32.h"
#include "ht32_board.h"
#include "main.h"
#include "BMP280Drive.h"

static unsigned int StaCnt[4];

u8 G_Input_Flag[4];
FlagStatus NewSta,OldSta[4];



void KeyIoInit(void)
{
    /* Configure AFIO mode of output pins                                                       */   
           
    AFIO_GPxConfig(GPIO_PA, GPIO_PIN_1, AFIO_MODE_DEFAULT);
    GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_1, GPIO_DIR_IN);
    /* Configure LED output pins                                                                */
        


OldSta[0] = 0;

}


//关闭灯带VCC电源
void LEDVCCClose(void)
{
    GPIO_WriteOutBits(LED_VCC_EN_PORT,LED_VCC_EN_PIN, RESET);
}
//打开灯带VCC电源
void LEDVCCOpen(void)
{
    GPIO_WriteOutBits(LED_VCC_EN_PORT,LED_VCC_EN_PIN, SET);	 
}


void WaitWakeUpKeyReset(void)
{
	while(GPIO_ReadInBit(HT_GPIOB,KEY_PIN) == SET);			//等待按键抬起
	OldSta[0] = 2;
}

//读取充电脚电平
FlagStatus GetCHRGSta(void)
{
    return GPIO_ReadInBit(HT_GPIOB,TP4056_CHRG_PIN);
}
//读取充饱脚电平
FlagStatus GetSTDBYSta(void)
{
    return GPIO_ReadInBit(HT_GPIOB,TP4056_STDBY_PIN);
}


//读取键值
extern _ADC_FUNC  StopDelay,ADSw;
extern __FUNC_STRUCT Func;
extern _WEIGHT_SENSOR WeightSensor;
extern u8 LEDAllOn = 0;
void GetKey(void)
{
    u8 i;
    for(i=0;i<4;i++)
    {
        if(i == 0)
            NewSta = 1;//HT32F_DVB_PBGetState(BUTTON_KEY2);
        if(i == 1)
		{
            NewSta = KEY_STOP(ADSw.Valu);
			if(NewSta == RESET)
			{
				LEDAllOn = 0x01;
			}
			else
			{
				LEDAllOn &= 0xfe;				
			}
		}
        if(i == 2)
		{
            NewSta = KEY_FWD(ADSw.Valu);
			if(NewSta == RESET)
			{
				LEDAllOn |= 0x02;
			}
			else
			{
				LEDAllOn &= 0xfd;				
			}
		}
        if(i == 3)
		{
            NewSta = KEY_REV(ADSw.Valu);           
			if(NewSta == RESET)
			{
				LEDAllOn |= 0x04;
			}
			else
			{
				LEDAllOn &= 0xfb;				
			}
		}
        if(OldSta[i] != NewSta)
            StaCnt[i] ++;
        else
            StaCnt[i] = 0;
        if(i <= 1)
        {
            if(StaCnt[i] > 10)
            {
                if(NewSta == RESET)
                {
                    G_Input_Flag[i] = 1;
                }
                else
                {
                    G_Input_Flag[i] = 2;
                }
                OldSta[i] = NewSta;
            }
        }
        else
        {
            if(NewSta == RESET)
            {
				if(Func.Sta == RDY_STA)
				{
					if(StaCnt[i] >= Func.KeyUnlockTime) //按键响应时间,只针对按下
					{
						if(Func.KeyUnlockTime == LONG_KEY)
						{
							Func.KeyUnlockTime = SHORT_KEY;
						}
						G_Input_Flag[i] = 1;
						OldSta[i] = NewSta;
					}
				}
				else
				{
					if(StaCnt[i] > 10)
					{
						G_Input_Flag[i] = 1;
						OldSta[i] = NewSta;
					}					
				}
            }
            else
            {
                
                if(StaCnt[i] > 10)
                {
                    G_Input_Flag[i] = 2;
                    OldSta[i] = NewSta;
                }
            }
        }
    }
}
