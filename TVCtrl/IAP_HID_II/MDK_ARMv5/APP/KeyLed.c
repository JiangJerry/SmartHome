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
    
//    AFIO_GPxConfig(GPIO_PC, LED_RED_PIN, AFIO_MODE_DEFAULT);                //LEDָʾ�ƽ�λ����
//    AFIO_GPxConfig(GPIO_PC, LED_GREEN_PIN, AFIO_MODE_DEFAULT);    
//    AFIO_GPxConfig(GPIO_PC, LED_BLUE_PIN, AFIO_MODE_DEFAULT);
//    GPIO_DirectionConfig(LED_RED_PORT, LED_RED_PIN, GPIO_DIR_OUT);
//    GPIO_DirectionConfig(LED_GREEN_PORT, LED_GREEN_PIN, GPIO_DIR_OUT);
//    GPIO_DirectionConfig(LED_BLUE_PORT, LED_BLUE_PIN, GPIO_DIR_OUT);
 
//    AFIO_GPxConfig(GPIO_PC, RF_DATA_OUT_PIN, AFIO_MODE_DEFAULT);                //LEDָʾ�ƽ�λ����
//    AFIO_GPxConfig(GPIO_PA, RF_EN_PIN, AFIO_MODE_DEFAULT);    
//    AFIO_GPxConfig(GPIO_PC, RF_SCLK_PIN, AFIO_MODE_DEFAULT);
//    GPIO_DirectionConfig(RF_DATA_OUT_PORT, RF_DATA_OUT_PIN, GPIO_DIR_OUT);
//    GPIO_DirectionConfig(RF_EN_PORT, RF_EN_PIN, GPIO_DIR_OUT);
//    GPIO_DirectionConfig(RF_SCLK_PORT, RF_SCLK_PIN, GPIO_DIR_OUT);
    

    GPIO_WriteOutBits(LED_RED_PORT, LED_RED_PIN, SET);	   
    GPIO_WriteOutBits(LED_GREEN_PORT, LED_GREEN_PIN, SET);	   
    GPIO_WriteOutBits(LED_BLUE_PORT, LED_BLUE_PIN, SET);	   
    
    GPIO_DirectionConfig(LED_VCC_EN_PORT, LED_VCC_EN_PIN, GPIO_DIR_OUT);        //LED�Ƶ�Դ����
    GPIO_WriteOutBits(LED_VCC_EN_PORT,LED_VCC_EN_PIN, RESET);	   

    /* Configure GPIO direction of output pins                                                                */
    AFIO_GPxConfig(GPIO_PB, SCK_PIN, AFIO_MODE_DEFAULT);
    AFIO_GPxConfig(GPIO_PB, SDA_PIN, AFIO_MODE_DEFAULT);
    GPIO_DirectionConfig(SCK_PORT, SCK_PIN, GPIO_DIR_OUT);
    GPIO_DirectionConfig(SDA_PORT, SDA_PIN, GPIO_DIR_OUT);
    
    AFIO_GPxConfig(GPIO_PA, EN_PIN, AFIO_MODE_DEFAULT);                         //ʹ��LED���ʵƿ���
    GPIO_DirectionConfig(SDA_PORT, EN_PIN, GPIO_DIR_OUT);
    
    
    AFIO_GPxConfig(GPIO_PB, KEY_PIN, AFIO_MODE_1);                              //��������
    GPIO_DirectionConfig(KEY_PORT, KEY_PIN, GPIO_DIR_IN);                       
    GPIO_InputConfig(KEY_PORT, KEY_PIN, ENABLE);

//    AFIO_GPxConfig(GPIO_PC, RF_DATA_IN_PIN, AFIO_MODE_1);                              //��������
//    GPIO_DirectionConfig(RF_DATA_IN_PORT, RF_DATA_IN_PIN, GPIO_DIR_IN);                       
//    GPIO_InputConfig(RF_DATA_IN_PORT, RF_DATA_IN_PIN, ENABLE);

    AFIO_GPxConfig(GPIO_PB, TP4056_CHRG_PIN, AFIO_MODE_DEFAULT);
    GPIO_DirectionConfig(TP4056_CHRG_PORT, TP4056_CHRG_PIN, GPIO_DIR_IN);       //���ڳ����״̬
    GPIO_InputConfig(TP4056_CHRG_PORT, TP4056_CHRG_PIN, ENABLE);
    GPIO_PullResistorConfig(TP4056_CHRG_PORT, TP4056_CHRG_PIN, GPIO_PR_UP);

    AFIO_GPxConfig(GPIO_PB, TP4056_STDBY_PIN, AFIO_MODE_DEFAULT);
    GPIO_DirectionConfig(TP4056_STDBY_PORT, TP4056_STDBY_PIN, GPIO_DIR_IN);     //������״̬
    GPIO_InputConfig(TP4056_STDBY_PORT, TP4056_STDBY_PIN, ENABLE);
    GPIO_PullResistorConfig(TP4056_STDBY_PORT, TP4056_STDBY_PIN, GPIO_PR_UP);


    AFIO_GPxConfig(GPIO_PC, DC_PIN, AFIO_MODE_DEFAULT);
    GPIO_DirectionConfig(DC_PORT, DC_PIN, GPIO_DIR_IN);                         //DC����
    GPIO_InputConfig(DC_PORT, DC_PIN, ENABLE);
    GPIO_PullResistorConfig(DC_PORT, DC_PIN, GPIO_PR_UP);

OldSta[0] = 0;

}


//�رյƴ�VCC��Դ
void LEDVCCClose(void)
{
    GPIO_WriteOutBits(LED_VCC_EN_PORT,LED_VCC_EN_PIN, RESET);
}
//�򿪵ƴ�VCC��Դ
void LEDVCCOpen(void)
{
    GPIO_WriteOutBits(LED_VCC_EN_PORT,LED_VCC_EN_PIN, SET);	 
}


void WaitWakeUpKeyReset(void)
{
	while(GPIO_ReadInBit(HT_GPIOB,KEY_PIN) == SET);			//�ȴ�����̧��
	OldSta[0] = 2;
}

//��ȡ���ŵ�ƽ
FlagStatus GetCHRGSta(void)
{
    return GPIO_ReadInBit(HT_GPIOB,TP4056_CHRG_PIN);
}
//��ȡ�䱥�ŵ�ƽ
FlagStatus GetSTDBYSta(void)
{
    return GPIO_ReadInBit(HT_GPIOB,TP4056_STDBY_PIN);
}
//��ʾ�ȵ�
void BatLedOrg(void)
{
    GPIO_WriteOutBits(LED_RED_PORT, LED_RED_PIN, RESET);	   
}
//��ʾ�̵�
void BatLedGreen(void)
{
    GPIO_WriteOutBits(LED_RED_PORT, LED_RED_PIN, SET);	   
    GPIO_WriteOutBits(LED_GREEN_PORT, LED_GREEN_PIN, RESET);	   
    GPIO_WriteOutBits(LED_BLUE_PORT, LED_BLUE_PIN, SET);	       
}
//��ʾ���
void BatLedRed(void)
{
    GPIO_WriteOutBits(LED_RED_PORT, LED_RED_PIN, SET);	   
}
//���
void BatLedOff(void)
{
    GPIO_WriteOutBits(LED_RED_PORT, LED_RED_PIN, RESET);	   
}

FlagStatus GetDCInFlag(void)
{
    return GPIO_ReadInBit(HT_GPIOC,DC_PIN);
}

//��ȡ��ֵ
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
					if(StaCnt[i] >= Func.KeyUnlockTime) //������Ӧʱ��,ֻ��԰���
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
