/*********************************************************************************************************//**
 * @file    IAP/IAP_HID_II/Src_AP/ht32f5xxxx_01_it.c
 * @version $Rev:: 2524         $
 * @date    $Date:: 2018-01-29 #$
 * @brief   This file provides all interrupt service routine.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"
#include "ht32_usbd_core.h"
#include "main.h"

/* Private variables ---------------------------------------------------------------------------------------*/
static u32 LedFlag = 0;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief   This function handles SysTick Handler.
 * @retval  None,1ms中断一次
 ************************************************************************************************************/
extern u16 DlySet,DlyTime;
extern FlagStatus TaskWeightRdy,TaskRFRdy,TaskLEDRdy,TaskKeyRdy,TaskADCRdy;
void LedCallBack(void);
extern u8 LedFlash;
u8 SFlag = 0;
u16 CntForLockTime = 0;
extern __FUNC_STRUCT Func;

#define COUNT_1S    1000  
#define COUNT_2S	2000
#define COUNT_100MS 100
#define LOCK_TIME   180 //3分钟 
void SysTick_Handler(void)
{    
    static u16 CntFor1s = 0,CntFor1ms = 0,CntForFlick = 0,CntFor100ms = 0,CntForFlash = 0;
	static u8 CntLEDScan = 0;
	static u8 DutyScnt = 0;
	static u8 Temp = 0;
    LedCallBack();   
    AP_TimebaseHandler();
    CntFor1ms++;
	if(LedFlash == 1)
	{
		CntForFlash++;
		if(CntForFlash >= COUNT_1S)
		{
			CntForFlash = 0;
			LedFlash = 0;
		}
	}
    if(CntFor1ms >= COUNT_1S)           //1秒计时
    {
        CntFor1ms = 0;		
        if(CntForLockTime++ >= LOCK_TIME)     //大于锁住时间
        {
            CntForLockTime = 0;
            Func.KeyUnlockTime = LONG_KEY;
        }
		if(Func.MaxShutDnDCT > 0)
			Func.MaxShutDnDCT--;
    }
    if(Func.Sta == SET_RF)
    {
        if(CntForFlick++ >= 100)
        {
            CntForFlick = 0;
            HT32F_DVB_LEDToggle(HT_LED1);
        }
    }
    else
    {
        if(Func.Sta == SET_WEIGHT)
        {
            if(CntForFlick++ >= 500)
            {
                CntForFlick = 0;
                HT32F_DVB_LEDToggle(HT_LED1);
            }
        }
        if(CntForFlick++ >= 1000)
        {
            CntForFlick = 0;
        }
    }
    if(CntFor100ms++ >= COUNT_100MS)
    {
        CntFor100ms = 0;
        TaskWeightRdy = SET;    //计重任务就绪           
    }
	CntLEDScan++;
	if(CntLEDScan >= 10)	    //10ms任务
	{
		SFlag = 1;
		CntLEDScan = 0;
		DutyScnt++;
        TaskRFRdy = SET;
		TaskLEDRdy = SET;       //LED扫描任务就绪
        TaskADCRdy = SET;       //ADC任务就绪
        TaskKeyRdy = SET;       //按键扫描任务就绪
        if(Func.StartDly == 1)
        {
            Func.DlyCnt++;
            if(Func.DlyCnt >= Func.DlyTime)
            {
                Func.StartDly  = 0;
                Func.DlyCnt = 0;
                Func.DlyAct = 1;
            }
        }
	}
}

/*********************************************************************************************************//**
 * @brief   This function handles KEY1 button interrupt.
 * @retval  None
 ************************************************************************************************************/
static u8 Flag = 0;
extern u8 TSCnt;

#define STA_START   1
#define STA_DATA    2

_RF_STRUCT RFCtrl;

void KEY1_Button_Process(void)
{
    static u8 SameCnt = 0,Temp = 100;
    if (EXTI_GetEdgeStatus(KEY1_BUTTON_EXTI_CHANNEL, EXTI_EDGE_NEGATIVE))
    {
        EXTI_ClearEdgeFlag(KEY1_BUTTON_EXTI_CHANNEL);
        switch(RFCtrl.Sta)
        {
            case STA_START:    //检测引导
//                if((TSCnt >= 100)&&(TSCnt <= 130))
                if(TSCnt > 50)
                {
                    RFCtrl.Sta = STA_DATA;                    
                    RFCtrl.Cnt = 0;
                }
                break;
            case STA_DATA:      //收数据
                if((TSCnt <= 5)&&(TSCnt >= 3))      //底电平时间370/100= 3.7
                {
                    RFCtrl.Data[(RFCtrl.Cnt>>3)] &= ~(1<<(RFCtrl.Cnt&0x07));
                    RFCtrl.Cnt++;                   
                }
                else
                {
                    if((TSCnt <= 14)&&(TSCnt >= 10))   //1120/100 = 11.2 高电平时间
                    {                       
                        RFCtrl.Data[(RFCtrl.Cnt>>3)] |= (1<<(RFCtrl.Cnt&0x07));
                        RFCtrl.Cnt++;                       
                    }
                    else
                    {
                        RFCtrl.Sta = STA_START;
                    }
                }
                if(RFCtrl.Cnt >= 24)
                {
                    if((RFCtrl.DataBak[2] != RFCtrl.Data[2])||(RFCtrl.DataBak[1] != RFCtrl.Data[1])||(RFCtrl.DataBak[0] != RFCtrl.Data[0]))
                    {
                        RFCtrl.DataBak[2] = RFCtrl.Data[2];
                        RFCtrl.DataBak[1] = RFCtrl.Data[1];
                        RFCtrl.DataBak[0] = RFCtrl.Data[0]; 
                        if(RFCtrl.Data[2] == RF_STOP_CODE)
                        {
                            Temp = 2;
                        }
                        else
                        {
                            Temp = 20;
                        }
                        SameCnt = 0;
                    }
                    else
                    {
                        SameCnt++;
                    }                   
                    if(SameCnt >= Temp)                      //二帧一样,1帧50ms
                    {
                        RFCtrl.Valu[2] = RFCtrl.Data[2];
                        RFCtrl.Valu[1] = RFCtrl.Data[1];
                        RFCtrl.Valu[0] = RFCtrl.Data[0];
                        if(RFCtrl.ForbidTime == 0)
                        {
                            RFCtrl.Flag = 1;
                        }
                    }
                }
                break;
            default:
                RFCtrl.Sta = STA_START;
                break;
        }      

    }
    else if(EXTI_GetEdgeStatus(KEY1_BUTTON_EXTI_CHANNEL, EXTI_EDGE_POSITIVE))
    {
        EXTI_ClearEdgeFlag(KEY1_BUTTON_EXTI_CHANNEL);
        TSCnt = 0;
    }
}


/*********************************************************************************************************//**
 * @brief   This function handles EXTI interrupt.
 * @retval  None
 ************************************************************************************************************/
void EXTI0_1_IRQHandler(void)
{
  #if defined(USE_HT32F52253_SK)
  KEY1_Button_Process();
  #endif

  #if defined(USE_HT32F52341_SK)
  KEY1_Button_Process();
  #endif

  #if defined(USE_HT32F52352_SK)
  KEY1_Button_Process();
  #endif
}

/*********************************************************************************************************//**
 * @brief   This function handles USB interrupt.
 * @retval  None
 ************************************************************************************************************/
void USB_IRQHandler(void)
{
    __ALIGN4 extern USBDCore_TypeDef gUSBCore;
    USBDCore_IRQHandler(&gUSBCore);
}
u8 WakeUpType = 0;
void EVWUP_IRQHandler(void)
{
    static u8 Flag = 0;
    u32 wRtcCounterTmp = 0;    
    if(PWRCU_GetFlagStatus()&PWRCU_FLAG_WUP)
    {
        WakeUpType = 1;
    }   
    else if (RTC_GetFlagStatus() & RTC_FLAG_CM)
    {
        WakeUpType = 2;    
    }    
}

#define LOW_BAT 2171    //3.5V


/*********************************************************************************************************//**
 * @brief   This function handles ADC interrupt.
 * @retval  None
 ************************************************************************************************************/
extern _ADC_FUNC  StopDelay,ADSw;

extern _KEY_STRUCT StopKey,FwdKey,RevKey;

void ADC_IRQHandler(void)
{
  if (ADC_GetIntStatus(HT_ADC, ADC_INT_CYCLE_EOC) == SET)
  {
    ADC_ClearIntPendingBit(HT_ADC, ADC_FLAG_CYCLE_EOC);
    StopDelay.Valu  = ((HT_ADC->DR[0]&0x0FFF));
    ADSw.Valu       = ((HT_ADC->DR[1]&0x0FFF));
  }    
}
/*********************************************************************************************************//**
 * @brief   This function handles RTC interrupt.
 * @retval  None
 * @details In RTC interrupt service routine:
 *  - Reset RTC init time when Time is 23:59:59.
 *    - Set RTC Compare register as 86400.
 *    - Reset PWRCU_BAKREG_1 to 0.
 *  - Toggle LED1 each 1s.
 *  - Set gwTimeDisplay to 1 to enable time update.
 *
 ************************************************************************************************************/
void RTC_IRQHandler(void)
{
    extern vu32 gwTimeDisplay;
    static u8 Flag = 0;
    u8 bFlags;

    bFlags = RTC_GetFlagStatus();
//  if((bFlags & 0x2) != 0x0) /* Match flag */
//  {
//    /* Reset RTC init time when Time is 23:59:59 */
//    RTC_SetCompare(86400);
//    TimeReg = 0;
//  }
    if(Flag == 0)
    {
        Flag = 1;
        GPIO_WriteOutBits(LED_GREEN_PORT, LED_GREEN_PIN, RESET);	   
    }
    else
    {
        Flag = 0;
        GPIO_WriteOutBits(LED_GREEN_PORT, LED_GREEN_PIN, SET);	   
    }

  /* Toggle LED1 each 1s */
//  HT32F_DVB_LEDToggle(HT_LED1);
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH0_1_IRQHandler(void)
{

}
