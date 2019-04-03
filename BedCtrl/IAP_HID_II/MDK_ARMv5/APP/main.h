#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "WeightSensor.h"
#include "DriveFixIn.h"
#include "DriveFixOut.h"
#include "DataSave.h"
#include "key.h"
/* Exported types ------------------------------------------------------------------------------------------*/
typedef struct
{
  u8 uRed;
  u8 uGreen;
  u8 uBlue;
} LED_RGB_Data_TypeDef;

typedef struct 
{
	u8	RecSta;
	u8	DataSize;
	u8	DataCnt;
	u8	DataChk;
	u8	TxSta;
    u8 	TxBusy;
    u8        Tx_Buf[20]; 
    u8        Rx_Buf[20]; 
    u8        Rx_Buf_Invalid[20];
    u8        Receive_Bytes;
    u8        Receive_Sign;
    u8        MS_1_Receive;
    u8        Receive_Bytes_Temp;
    u8        Receive_Enable;
}Communicate; 	  	

typedef enum
{
    NOSTATUS = 0,
    CHARG,
    STDBY,
    LOWBAT,
}_BAT_STATUS;

extern _BAT_STATUS BatSta;
extern Communicate APPFrame;

/* Exported constants --------------------------------------------------------------------------------------*/
#define      OUTPUT_TABLE1      1
#define      OUTPUT_TABLE2      2
#define      RESET_TABLE        3
#define      OFF_CONST          4

#define CODE_0      15
#define CODE_1      45

#define GPTMx       HT_GPTM0

/* Exported macro ------------------------------------------------------------------------------------------*/
#define LED_NUM 72

#define LED_MODE1   0
#define LED_MODE2   1
#define LED_MODE3   2
#define LED_MODE4   3
#define LED_MODE5   4
#define LED_MODE6   5

#define LED_ALTER   15

#define CONFIG_IN_NUM 1


typedef struct
{
    u8 Flag;
    u8 Sta;
    u8 Cnt;
    u8 Data[3];
    u8 DataBak[3];
    u8 Valu[3]; 
    u8 ForbidTime;
}_RF_STRUCT;

typedef struct
{
    u8 Sta;
    u8 StartDly;
    u8 DlyAct;
    u16 DlyTime;
    u16 DlyCnt;
    u16 KeyUnlockTime;
	u16 MaxShutDnDCT;
}__FUNC_STRUCT;

#define RDY_STA     0   //就绪状态
#define LOCK_STA    1   //锁定状态
#define RUN_FWD_STA     2   //运行正转状态
#define RUN_REV_STA     3   //运行反转状态

#define SET_RF     4   //设置状态
#define SET_WEIGHT    5   //设置状态

#define NONE_CMD	0
#define STOP_CMD    1
#define FWD_CMD     2
#define REV_CMD     3

#define RF_FWD_CODE     0xFC                               
#define RF_REV_CODE     0xcf
#define RF_STOP_CODE    0xf3

#define LONG_KEY	300
#define SHORT_KEY	100


typedef struct
{
    u8 Cnt;
    u32 Valu;
    u8 Sta;
    u8 LastSta;
}_ADC_FUNC;


typedef struct
{
    u8 Cnt;
    u8 Sta;
}_KEY_STRUCT;

//#define KEY_UP      1
//#define KEY_DOWN    2

#define START_ADDR          0x20

#define VERSION1  0

#define SDA_PORT       (HT_GPIOB)
#define SCK_PORT       (HT_GPIOB)

#if VERSION1 > 0

#define SDA_PIN       (GPIO_PIN_4)
#define SCK_PIN       (GPIO_PIN_5)

#else

#define SDA_PIN       (GPIO_PIN_8)
#define SCK_PIN       (GPIO_PIN_7)

#endif



#define EN_PIN          (GPIO_PIN_8)

#define KEY_PORT       (HT_GPIOB)
#define KEY_PIN        (GPIO_PIN_12)

#define DC_PORT       (HT_GPIOC)
#define DC_PIN        (GPIO_PIN_4)

#define LED_CTR         (GPIO_PIN_5)
#define WAKE_UP         (GPIO_PIN_0)
#define WAKE_UP_PORT   (HT_GPIOA)

//#define BLEWAKEUP_PORT      HT_GPIOA
//#define BLEWAKEUP_PIN       GPIO_PIN_0

#define TP4056_CHRG_PORT    HT_GPIOB
#define TP4056_CHRG_PIN     GPIO_PIN_4

#define TP4056_STDBY_PORT   HT_GPIOB
#define TP4056_STDBY_PIN    GPIO_PIN_5


#define LED_RED_PORT        (HT_GPIOA)
#define LED_RED_PIN         GPIO_PIN_6
#define LED_GREEN_PORT      (HT_GPIOC)
#define LED_GREEN_PIN       GPIO_PIN_1
#define LED_BLUE_PORT       (HT_GPIOC)
#define LED_BLUE_PIN        GPIO_PIN_2

#define LED_VCC_EN_PORT     (HT_GPIOA)
#define LED_VCC_EN_PIN      (GPIO_PIN_8)

//#define RF_EN_PORT          (HT_GPIOA)
//#define RF_EN_PIN           (GPIO_PIN_1)

//#define RF_SCLK_PORT        (HT_GPIOC)
//#define RF_SCLK_PIN         (GPIO_PIN_8)

//#define RF_DATA_OUT_PORT     (HT_GPIOC)
//#define RF_DATA_OUT_PIN      (GPIO_PIN_2)

//#define RF_DATA_IN_PORT     (HT_GPIOC)
//#define RF_DATA_IN_PIN      (GPIO_PIN_9)

//#define RF_SLAVE_PORT       (HT_GPIOA)
//#define RF_SLAVE_PIN        (GPIO_PIN_0)


/* Exported functions --------------------------------------------------------------------------------------*/
void NVIC_Configuration(void);
void CKCU_Configuration(void);
void GPIO_Configuration(void);
void GPTM_Configuration(void);
void GPTM_PDMA_Configuration(void);
void LEDDisp(void);
void KeyIoInit(void);
void USART1Init(void);
void Tab0Encode(u8 bRED,u8 bGREEN,u8 bBLUE);
void NextLEDRGBEncode(u8 bRED,u8 bGREEN,u8 bBLUE);
void ColorDataRdy3(u8 Ratio);
void ColorDataRdy2(u8 Ratio);
void ColorDataRdy1(u8 Ratio,u8 type);
void ColorDataRdy4(u8 Ratio);
void ColorDataRdy5(u8 Ratio);
void ColorDataRdy6(u8 Ratio);
void ModifyColorTable1(void);
void ModifyColorTable2(void);
void ModifyColorTable3(void);
void ModifyColorTable4(void);    
void ModifyColorTable5(void);
void ModifyColorTable6(void);    
void GetKey(void);
void Init_BMP280(void);  //初始化气压温度传感器
void LEDInit(void);
void AckDataToBleModle(void);
void LEDModeDatePre(u8 DutyData);
void ColorRadioDnBak(void);
void PressBrightAdj(u8 PressData);
void GetInitPressure(void);
void GetPressure(void);
void ModityDnUpTable(void);
void WaitWakeUpKeyReset(void);
void AP_TimebaseHandler(void);
void ADCInit(void);
void ADCStart(void);
void ADCStop(void);
void ADCEnable(void);
void ADCDisable(void);
void SendCmd(u8 *CmdPtr);

void LEDVCCClose(void);
void LEDVCCOpen(void);


FlagStatus GetCHRGSta(void);
FlagStatus GetSTDBYSta(void);

void EnterSet(void);
void ExitSet(void);


void BatLedOrg(void);
void BatLedGreen(void);
void BatLedRed(void);

void BatLedOff(void);
#ifdef __cplusplus
}
#endif

#endif
