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

//修改按键个数，最大不得超过12个 
#define GPIO_KEY_NUM 3                                  ///< 定义按键成员总数
keyTypedef_t singleKey[GPIO_KEY_NUM];                   ///< 定义单个按键成员数组指针
keysTypedef_t keys;                                     ///< 定义总的按键模块结构体指针
gpio_addr_t gpio_addr;
gpio_t gpio;

/***********************建议不要修改*************************************/

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
* @param [in] keys 按键功能全局结构体指针
* @return unsigned int型的GPIO状态值
*/
unsigned int getKey(keysTypedef_t *keyS)
{
    unsigned char i = 0,px=0; 
    unsigned int readKey = 0;              //必要,初始化
    unsigned char PX_Value=0;
    //GPIO Cyclic scan
    for(i = 0; i < keys.keyTotolNum; i++)//根据按键数，循环扫描
    {
    	
    	px |=keyS->singleKey[i].keyx;
    	PX_Value=_PX_Value(keyS->singleKey[i].keyPx);
        if(PRESS_DOWN_STATUS==(PX_Value & px ))
        {
            G_SET_BIT(readKey, keyS->singleKey[i].keyNum);//哪一个按键按下，就将readKey的哪个位置一
			
        }
        px=0;
    }   
    return readKey;
}


/**
* @brief Read the KEY value
* @param [in] keys 按键功能全局结构体指针
* @return unsigned int型的按键状态值
*/
unsigned int readKeyValue(keysTypedef_t *keyS)
{
    static unsigned char keyCheck = 0;
    static unsigned char keyState = 0;
    static unsigned int keyLongCheck = 0;
    static unsigned int keyPrev = 0;      //上一次按键

    unsigned int keyPress = 0;
    unsigned int keyReturn = 0;
    
    keyCountTime +=KEY_TIMER_MS;//每个定时器中断进入一次 2ms
    
    if(keyCountTime >= KEY_DELAY_MS)   //  按键消抖时长
    {
        keyCountTime = 0;
        keyCheck = 1;
    }
    if(1 == keyCheck)//进入一次
    {
        keyCheck = 0;
        keyPress = getKey(keyS);
        switch (keyState)
        {
            case 0://按键未按下
                if(keyPress != 0)
                {
                    keyPrev = keyPress;
                    keyState = 1;
                }
                break;
                
            case 1://按键按下，判断是不是抖动
                if(keyPress == keyPrev)//不是抖动
                {
                    keyState = 2;
                    keyReturn= keyPrev | KEY_DOWN;//按键未松开，哪个按键按下就将哪个位置一
                }
                else                //按键抬起,是抖动,不响应按键
                {
                    keyState = 0;
                }
                break;
                
            case 2:
                if(keyPress != keyPrev)//按键已松开，不是长按键
                {
                    keyState = 0;
                    keyLongCheck = 0;//
                    keyReturn = keyPrev | KEY_UP;//按键已松开，哪个按键按下就将哪个位置一
                    return keyReturn;
                }
                if(keyPress == keyPrev)//判断是不是长按键
                {
                    keyLongCheck++;
                    if(keyLongCheck >= PRESS_LONG_TIME_S)    //长按3S有效
                    {
                        keyLongCheck = 0;
                        keyState = 3;
                        keyReturn= keyPress | KEY_LONG;//按键未松开，是长按键
                        return keyReturn;
                    }
                }
                break;
            case 3:
                if(keyPress != keyPrev)//一次按键扫描已完成，等待按键松开，按键不松开就一直调到case 3执行
                {
                    keyState = 0;
                }
                break;
        }
    }
    return  NO_KEY;
}


/**
* @brief 按键回调函数

* 在该函数内完成按键状态监测后调用对应的回调函数
* @param [in] keys 按键功能全局结构体指针
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
        for(i = 0; i < keyS->keyTotolNum; i++)//循环扫描，查找出是哪个按键按下
        {
			//判断key_value置1的位数与哪一个keyTypedef_t结构体元素keyNum相等
            if(G_IS_BIT_SET(key_value, keyS->singleKey[i].keyNum)) //
            {
                //key callback function of short press
                if(keyS->singleKey[i].shortPress) //如果初始化有回调函数
                {
                    keyS->singleKey[i].shortPress(); //执行回调函数

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
* @brief 单按键初始化

* 在该函数内完成单个按键的初始化，这里需要结合STM32 GPIO寄存器配置设置参数
* @param [in] keyPx GPIO_pins_define 
* @param [in] short_press 短按状态的回调函数地址
* @param [in] long_press 长按状态的回调函数地址
* @return 单按键结构体指针
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

/*********************以上部分不要修改，以下为用户添加函数，可自行修改************************************
@因为按键回调函数都是在中断中执行的，建议不要在回调函数中
 执行过多的代码。可设立按键标志位，在主函数中执行按键操作函数。
用杜邦线连接按键时，有时会松动，导致长按变短按，故此时推荐使用短按事件即可。
***************************************************************************/

void TimeGetKey(void)
{
    keyHandle((keysTypedef_t *)&keys);		
}
///**********
//@按键的回调函数。
//当有按键按下时会在定时器中断中执行，函数的执行时间不应超过定时器的中断时间。
//或者可声明一个标志位，在main.c while{}大循环中扫描该标志位
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

/*在主函数中调用此函数*/
void key_Init(void)
{	
	singleKey[0]=keyInitOne(p1_,px_0,key1_Shrot,key1_Long);
	singleKey[1]=keyInitOne(p2_,px_2,key2_Shrot,key2_Long);
	singleKey[2]=keyInitOne(p2_,px_3,(void*)0,key3_Long);
	keys.singleKey=(keyTypedef_t*)&singleKey;
	if( keyTotolNum >12)
		keyTotolNum=12;
	keys.keyTotolNum = keyTotolNum;//按键数量
//	Timer0Init();
}

