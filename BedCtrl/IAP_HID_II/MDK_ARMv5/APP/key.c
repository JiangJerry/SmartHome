#include "ht32.h"
#include "ht32_board.h"
#include "ht32_board_config.h"
#include "ht32_usbd_core.h"
#include "ht32_usbd_class.h"
#include "ht32_usbd_descriptor.h"
#include "ap_handler.h"
#include "ap_config.h"

#include "ap_uart_handler.h"


#include "main.h"
#include "USART0Drive.h"
#include "key.h"

//�޸İ�����������󲻵ó���12�� 
#define GPIO_KEY_NUM 3                                  ///< ���尴����Ա����
keyTypedef_t singleKey[GPIO_KEY_NUM];                   ///< ���嵥��������Ա����ָ��
keysTypedef_t keys;                                     ///< �����ܵİ���ģ��ṹ��ָ��
gpio_addr_t gpio_addr;
gpio_t gpio;

/***********************���鲻Ҫ�޸�*************************************/

unsigned char                 keyCountTime;
static unsigned char          keyTotolNum = 0;

extern _ADC_FUNC  StopDelay,ADSw;

unsigned char _PX_Value(gpio_addr_t px)
{
	unsigned char value=0;
	switch(px)
	{
//		case p0_:value = HT32F_DVB_PBGetState(BUTTON_KEY2);break;
        case p1_:value = HT32F_DVB_PBGetState(BUTTON_KEY2);break;
//        case p2_:value = KEY_STOP(ADSw.Valu);break;
//        case p3_:value = HT32F_DVB_PBGetState(BUTTON_KEY2);break;
//		case p4_:value=P4;break;
//		case p5_:value=P5;break;
	}
	return value;
}
/**
* @brief Read the GPIO state
* @param [in] keys ��������ȫ�ֽṹ��ָ��
* @return unsigned int�͵�GPIO״ֵ̬
*/
unsigned int getKey(keysTypedef_t *keyS)
{
    unsigned char i = 0,px=0; 
    unsigned int readKey = 0;              //��Ҫ,��ʼ��
    unsigned char PX_Value=0;
    //GPIO Cyclic scan
    for(i = 0; i < keys.keyTotolNum; i++)//���ݰ�������ѭ��ɨ��
    {
    	
    	px |=keyS->singleKey[i].keyx;
    	PX_Value=_PX_Value(keyS->singleKey[i].keyPx);
        if(PRESS_DOWN_STATUS==(PX_Value & px ))
        {
            G_SET_BIT(readKey, keyS->singleKey[i].keyNum);//��һ���������£��ͽ�readKey���ĸ�λ��һ
			
        }
        px=0;
    }   
    return readKey;
}


/**
* @brief Read the KEY value
* @param [in] keys ��������ȫ�ֽṹ��ָ��
* @return unsigned int�͵İ���״ֵ̬
*/
unsigned int readKeyValue(keysTypedef_t *keyS)
{
    static unsigned char keyCheck = 0;
    static unsigned char keyState = 0;
    static unsigned int keyLongCheck = 0;
    static unsigned int keyPrev = 0;      //��һ�ΰ���

    unsigned int keyPress = 0;
    unsigned int keyReturn = 0;
    
    keyCountTime +=KEY_TIMER_MS;//ÿ����ʱ���жϽ���һ�� 2ms
    
    if(keyCountTime >= KEY_DELAY_MS)   //  ��������ʱ��
    {
        keyCountTime = 0;
        keyCheck = 1;
    }
    if(1 == keyCheck)//����һ��
    {
        keyCheck = 0;
        keyPress = getKey(keyS);
        switch (keyState)
        {
            case 0://����δ����
                if(keyPress != 0)
                {
                    keyPrev = keyPress;
                    keyState = 1;
                }
                break;
                
            case 1://�������£��ж��ǲ��Ƕ���
                if(keyPress == keyPrev)//���Ƕ���
                {
                    keyState = 2;
                    keyReturn= keyPrev | KEY_DOWN;//����δ�ɿ����ĸ��������¾ͽ��ĸ�λ��һ
                }
                else                //����̧��,�Ƕ���,����Ӧ����
                {
                    keyState = 0;
                }
                break;
                
            case 2:
                if(keyPress != keyPrev)//�������ɿ������ǳ�����
                {
                    keyState = 0;
                    keyLongCheck = 0;//
                    keyReturn = keyPrev | KEY_UP;//�������ɿ����ĸ��������¾ͽ��ĸ�λ��һ
                    return keyReturn;
                }
                if(keyPress == keyPrev)//�ж��ǲ��ǳ�����
                {
                    keyLongCheck++;
                    if(keyLongCheck >= PRESS_LONG_TIME_S)    //����3S��Ч
                    {
                        keyLongCheck = 0;
                        keyState = 3;
                        keyReturn= keyPress | KEY_LONG;//����δ�ɿ����ǳ�����
                        return keyReturn;
                    }
                }
                break;
            case 3:
                if(keyPress != keyPrev)//һ�ΰ���ɨ������ɣ��ȴ������ɿ����������ɿ���һֱ����case 3ִ��
                {
                    keyState = 0;
                }
                break;
        }
    }
    return  NO_KEY;
}


/**
* @brief �����ص�����

* �ڸú�������ɰ���״̬������ö�Ӧ�Ļص�����
* @param [in] keys ��������ȫ�ֽṹ��ָ��
* @return none
*/
void keyHandle(keysTypedef_t *keyS)
{
    unsigned char i = 0;
    unsigned int key_value = 0;

    key_value = readKeyValue(keyS);

    if(!key_value) return;
    
    //Check short press button
    if(key_value & KEY_UP)
    {
        //Valid key is detected
        for(i = 0; i < keyS->keyTotolNum; i++)//ѭ��ɨ�裬���ҳ����ĸ���������
        {
			//�ж�key_value��1��λ������һ��keyTypedef_t�ṹ��Ԫ��keyNum���
            if(G_IS_BIT_SET(key_value, keyS->singleKey[i].keyNum)) //
            {
                //key callback function of short press
                if(keyS->singleKey[i].shortPress) //�����ʼ���лص�����
                {
                    keyS->singleKey[i].shortPress(); //ִ�лص�����

                }
            }
        }
    }

    //Check short long button
    if(key_value & KEY_LONG)
    {
        //Valid key is detected
        for(i = 0; i < keyS->keyTotolNum; i++)
        {
            if(G_IS_BIT_SET(key_value, keyS->singleKey[i].keyNum))
            {
                //key callback function of long press
                if(keyS->singleKey[i].longPress) 
                {
                    keyS->singleKey[i].longPress(); 

                }
            }
        }
    }
} 


/**
* @brief ��������ʼ��

* �ڸú�������ɵ��������ĳ�ʼ����������Ҫ���STM32 GPIO�Ĵ����������ò���
* @param [in] keyPx GPIO_pins_define 
* @param [in] short_press �̰�״̬�Ļص�������ַ
* @param [in] long_press ����״̬�Ļص�������ַ
* @return �������ṹ��ָ��
*/
keyTypedef_t keyInitOne(gpio_addr_t keyPx,gpio_t keyx, gokitKeyFunction shortPress, gokitKeyFunction longPress)
{
    static char key_total = -1;

    keyTypedef_t singleKey;   
    //Platform-defined GPIO
    singleKey.keyPx = keyPx;
    singleKey.keyx = keyx;
    singleKey.keyNum = ++key_total;
    
    //Button trigger callback type
    singleKey.longPress = longPress;
    singleKey.shortPress = shortPress;
    
    keyTotolNum++;
    
    return singleKey;
}

/*********************���ϲ��ֲ�Ҫ�޸ģ�����Ϊ�û���Ӻ������������޸�************************************
@��Ϊ�����ص������������ж���ִ�еģ����鲻Ҫ�ڻص�������
 ִ�й���Ĵ��롣������������־λ������������ִ�а�������������
�öŰ������Ӱ���ʱ����ʱ���ɶ������³�����̰����ʴ�ʱ�Ƽ�ʹ�ö̰��¼����ɡ�
***************************************************************************/

void TimeGetKey(void)
{
    keyHandle((keysTypedef_t *)&keys);		
}
///**********
//@�����Ļص�������
//���а�������ʱ���ڶ�ʱ���ж���ִ�У�������ִ��ʱ�䲻Ӧ������ʱ�����ж�ʱ�䡣
//���߿�����һ����־λ����main.c while{}��ѭ����ɨ��ñ�־λ
//**********/
char flag,flag2,flag3,flag4,flag5;
void key1_Shrot(void)
{
	flag = !flag;
}
extern __FUNC_STRUCT Func;
extern _WEIGHT_SENSOR WeightSensor;
extern _ADC_FUNC  StopDelay,ADSw;

#define SET_RF_VALU     3200
void key1_Long(void)
{
    if((Func.Sta == RDY_STA))
    {
        if(StopDelay.Valu >= SET_RF_VALU)
        {
			EnterSet();
            Func.Sta = SET_RF;
        }
        else
        {
            WeightSensor.Sta = WEIGHT_RESET;
            Func.Sta = SET_WEIGHT;
        }
    }
    else
    {
		ExitSet();
        Func.Sta = RDY_STA;
    }
}

void key2_Shrot(void)
{
	flag3 = !flag3;
	
}
void key2_Long(void)
{

}

void key3_Long(void)
{
	flag4 = !flag4;
}

/*���������е��ô˺���*/
void key_Init(void)
{	
	singleKey[0]=keyInitOne(p1_,px_0,key1_Shrot,key1_Long);
	singleKey[1]=keyInitOne(p2_,px_2,key2_Shrot,key2_Long);
	singleKey[2]=keyInitOne(p2_,px_3,(void*)0,key3_Long);
	keys.singleKey=(keyTypedef_t*)&singleKey;
	if( keyTotolNum >12)
		keyTotolNum=12;
	keys.keyTotolNum = keyTotolNum;//��������
//	Timer0Init();
}

