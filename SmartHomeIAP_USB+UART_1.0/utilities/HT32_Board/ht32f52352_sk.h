/*********************************************************************************************************//**
 * @file    ht32f52352_sk.h
 * @version $Rev:: 2830         $
 * @date    $Date:: 2018-06-04 #$
 * @brief   The header file of HT32F52352 Starter kit.
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

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F52352_SK_H
#define __HT32F52352_SK_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "common/i2c_eeprom.h"
#include "common/spi_flash.h"
#include "common/ebi_lcd.h"

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup HT32_Board
  * @{
  */

/** @addtogroup HT32F52352_SK
  * @{
  */


/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup HT32F52352_SK_Exported_Constants HT32F52352 Starter kit exported constants
  * @{
  */
extern HT_GPIO_TypeDef* const GPIO_PORT[GPIO_PORT_NUM];

/** @addtogroup HT32F52352_SK_LED
  * @{
  */
#define LEDn                        (9)

#define LED1_GPIO_ID                (GPIO_PA)
#define LED1_GPIO_PIN               (GPIO_PIN_0)
#define LED1_AFIO_MODE              (AFIO_FUN_GPIO)


#define LED2_GPIO_ID                (GPIO_PA)
#define LED2_GPIO_PIN               (GPIO_PIN_10)
#define LED2_AFIO_MODE              (AFIO_FUN_GPIO)


#define LED3_GPIO_ID                (GPIO_PA)
#define LED3_GPIO_PIN               (GPIO_PIN_11)
#define LED3_AFIO_MODE              (AFIO_FUN_GPIO)

#define LED4_GPIO_ID                (GPIO_PA)
#define LED4_GPIO_PIN               (GPIO_PIN_14)
#define LED4_AFIO_MODE              (AFIO_FUN_GPIO)


#define RY1_GPIO_ID                (GPIO_PC)
#define RY1_GPIO_PIN               (GPIO_PIN_2)
#define RY1_AFIO_MODE              (AFIO_FUN_GPIO)

#define RY2_GPIO_ID                (GPIO_PC)
#define RY2_GPIO_PIN               (GPIO_PIN_1)
#define RY2_AFIO_MODE              (AFIO_FUN_GPIO)

#define RY3_GPIO_ID                (GPIO_PB)
#define RY3_GPIO_PIN               (GPIO_PIN_5)
#define RY3_AFIO_MODE              (AFIO_FUN_GPIO)

#define RY4_GPIO_ID                (GPIO_PB)
#define RY4_GPIO_PIN               (GPIO_PIN_4)
#define RY4_AFIO_MODE              (AFIO_FUN_GPIO)

#define RY5_GPIO_ID                (GPIO_PB)
#define RY5_GPIO_PIN               (GPIO_PIN_3)
#define RY5_AFIO_MODE              (AFIO_FUN_GPIO)

typedef enum
{
    HT_LED1 = 0,
    HT_LED2 = 1,
    HT_LED3 = 2,
    RY1     = 3,
    RY2     = 4,
    RY3     = 5,
    RY4     = 6,
    RY5     = 7,
    HT_LED4 = 8,
} LED_TypeDef;
/**
  * @}
  */

/** @addtogroup HT32F52352_SK_BUTTON
  * @{
  */
#define BUTTONn                     (11)

#define WAKEUP_BUTTON_GPIO_ID       (GPIO_PB)
#define WAKEUP_BUTTON_GPIO_PIN      (GPIO_PIN_12)
#define WAKEUP_BUTTON_AFIO_MODE     (AFIO_FUN_GPIO)
#define WAKEUP_BUTTON_EXTI_CHANNEL  (12)

#define KEY1_BUTTON_GPIO_ID         (GPIO_PA)
#define KEY1_BUTTON_GPIO_PIN        (GPIO_PIN_1)
#define KEY1_BUTTON_AFIO_MODE       (AFIO_FUN_GPIO)
#define KEY1_BUTTON_EXTI_CHANNEL    (1)

#define KEY2_BUTTON_GPIO_ID         (GPIO_PB)
#define KEY2_BUTTON_GPIO_PIN        (GPIO_PIN_12)
#define KEY2_BUTTON_AFIO_MODE       (AFIO_FUN_GPIO)
#define KEY2_BUTTON_EXTI_CHANNEL    (12)

#define LIMIT_SW1_GPIO_ID         (GPIO_PB)
#define LIMIT_SW1_GPIO_PIN        (GPIO_PIN_2)
#define LIMIT_SW1_AFIO_MODE       (AFIO_FUN_GPIO)
#define LIMIT_SW1_EXTI_CHANNEL    (2)

#define LIMIT_SW2_GPIO_ID         (GPIO_PB)
#define LIMIT_SW2_GPIO_PIN        (GPIO_PIN_1)
#define LIMIT_SW2_AFIO_MODE       (AFIO_FUN_GPIO)
#define LIMIT_SW2_EXTI_CHANNEL    (1)

#define LIMIT_SW3_GPIO_ID         (GPIO_PB)
#define LIMIT_SW3_GPIO_PIN        (GPIO_PIN_0)
#define LIMIT_SW3_AFIO_MODE       (AFIO_FUN_GPIO)
#define LIMIT_SW3_EXTI_CHANNEL    (0)

#define LIMIT_SW4_GPIO_ID         (GPIO_PA)
#define LIMIT_SW4_GPIO_PIN        (GPIO_PIN_15)
#define LIMIT_SW4_AFIO_MODE       (AFIO_FUN_GPIO)
#define LIMIT_SW4_EXTI_CHANNEL    (15)


#define CLOSE_SW1_GPIO_ID         (GPIO_PB)
#define CLOSE_SW1_GPIO_PIN        (GPIO_PIN_8)
#define CLOSE_SW1_AFIO_MODE       (AFIO_FUN_GPIO)
#define CLOSE_SW1_EXTI_CHANNEL    (8)

#define CLOSE_SW2_GPIO_ID         (GPIO_PB)
#define CLOSE_SW2_GPIO_PIN        (GPIO_PIN_6)
#define CLOSE_SW2_AFIO_MODE       (AFIO_FUN_GPIO)
#define CLOSE_SW2_EXTI_CHANNEL    (6)

#define CLOSE_SW3_GPIO_ID         (GPIO_PB)
#define CLOSE_SW3_GPIO_PIN        (GPIO_PIN_7)
#define CLOSE_SW3_AFIO_MODE       (AFIO_FUN_GPIO)
#define CLOSE_SW3_EXTI_CHANNEL    (7)

#define CLOSE_SW4_GPIO_ID         (GPIO_PC)
#define CLOSE_SW4_GPIO_PIN        (GPIO_PIN_3)
#define CLOSE_SW4_AFIO_MODE       (AFIO_FUN_GPIO)
#define CLOSE_SW4_EXTI_CHANNEL    (3)

typedef enum
{
    BUTTON_WAKEUP = 0,
    BUTTON_KEY1   = 1,
    BUTTON_KEY2   = 2,
    LIMIT_SW1     = 3,
    LIMIT_SW2     = 4,
    LIMIT_SW3     = 5,
    LIMIT_SW4     = 6,    
    CLOSE_SW1     = 7,
    CLOSE_SW2     = 8,
    CLOSE_SW3     = 9,
    CLOSE_SW4     = 10    
} BUTTON_TypeDef;

typedef enum
{
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} BUTTON_MODE_TypeDef;
/**
  * @}
  */

/** @addtogroup HT32F52352_SK_BUZZER
  * @{
  */
#define BUZZER_GPIO_ID              (GPIO_PA)
#define BUZZER_AFIO_PIN             (AFIO_PIN_10)
#define BUZZER_AFIO_MODE            (AFIO_FUN_MCTM_GPTM)
#define BUZZER_GPIO_CLK(CK)         (CK.Bit.PA)

#define BUZZER_TM_CLK(CK)           (CK.Bit.MCTM0)
#define BUZZER_TM                   (HT_MCTM0)
#define BUZZER_TM_CHANNEL           (TM_CH_1)
#define BUZZER_IRQn                 (MCTM0_IRQn)
/**
  * @}
  */

/** @addtogroup HT32F52352_SK_COM
  * @{
  */
#define COM_NUM                     (1)

#define COM1_CLK(CK)                (CK.Bit.USART1)
#define COM1_PORT                   (HT_USART1)
#define COM1_IRQn                   (USART1_IRQn)
#define COM1_IRQHandler             (USART1_IRQHandler)

#define COM1_TX_GPIO_ID             (GPIO_PA)
#define COM1_TX_AFIO_PIN            (AFIO_PIN_4)
#define COM1_TX_AFIO_MODE           (AFIO_FUN_USART_UART)

#define COM1_RX_GPIO_ID             (GPIO_PA)
#define COM1_RX_AFIO_PIN            (AFIO_PIN_5)
#define COM1_RX_AFIO_MODE           (AFIO_FUN_USART_UART)

typedef enum
{
  COM1 = 0,
  COM2 = 1
} COM_TypeDef;
/**
  * @}
  */

/** @addtogroup HT32F52352_SK_SPI_FLASH
  * @{
  */
#define FLASH_SPI_CLK(CK)           (CK.Bit.SPI1)
#define FLASH_SPI                   (HT_SPI1)

#define FLASH_SPI_SCK_GPIO_ID       (GPIO_PC)
#define FLASH_SPI_SCK_AFIO_PIN      (AFIO_PIN_5)
#define FLASH_SPI_SCK_AFIO_MODE     (AFIO_FUN_SPI)

#define FLASH_SPI_MOSI_GPIO_ID      (GPIO_PC)
#define FLASH_SPI_MOSI_AFIO_PIN     (AFIO_PIN_8)
#define FLASH_SPI_MOSI_AFIO_MODE    (AFIO_FUN_SPI)

#define FLASH_SPI_MISO_GPIO_ID      (GPIO_PC)
#define FLASH_SPI_MISO_AFIO_PIN     (AFIO_PIN_9)
#define FLASH_SPI_MISO_AFIO_MODE    (AFIO_FUN_SPI)

#define FLASH_SPI_SEL_GPIO_ID       (GPIO_PD)
#define FLASH_SPI_SEL_GPIO_PIN      (GPIO_PIN_0)
#define FLASH_SPI_SEL_AFIO_MODE     (AFIO_FUN_GPIO)
#define FLASH_SPI_SEL_CLK(CK)       (CK.Bit.PD)
/**
  * @}
  */

/** @addtogroup HT32F52352_SK_EBI_LCD
  * @{
  */
#define LCD_EBI                     (HT_EBI)

#define LCD_EBI_CS_GPIO_ID          (GPIO_PC)
#define LCD_EBI_CS_AFIO_PIN         (AFIO_PIN_2)
#define LCD_EBI_CS_AFIO_MODE        (AFIO_FUN_EBI)

#define LCD_EBI_OE_GPIO_ID          (GPIO_PC)
#define LCD_EBI_OE_AFIO_PIN         (AFIO_PIN_1)
#define LCD_EBI_OE_AFIO_MODE        (AFIO_FUN_EBI)

#define LCD_EBI_WE_GPIO_ID          (GPIO_PC)
#define LCD_EBI_WE_AFIO_PIN         (AFIO_PIN_3)
#define LCD_EBI_WE_AFIO_MODE        (AFIO_FUN_EBI)

#define LCD_EBI_RS_GPIO_ID          (GPIO_PA)
#define LCD_EBI_RS_AFIO_PIN         (AFIO_PIN_11)
#define LCD_EBI_RS_AFIO_MODE        (AFIO_FUN_EBI)

#define LCD_EBI_RS1_GPIO_ID         (GPIO_PB)
#define LCD_EBI_RS1_AFIO_PIN        (AFIO_PIN_15)
#define LCD_EBI_RS1_AFIO_MODE       (AFIO_FUN_EBI)
#define LCD_EBI_RS1_ADDR_PIN        (16)

#define LCD_EBI_AD0_GPIO_ID         (GPIO_PA)
#define LCD_EBI_AD0_AFIO_PIN        (AFIO_PIN_14)
#define LCD_EBI_AD0_AFIO_MODE       (AFIO_FUN_EBI)

#define LCD_EBI_AD1_GPIO_ID         (GPIO_PA)
#define LCD_EBI_AD1_AFIO_PIN        (AFIO_PIN_15)
#define LCD_EBI_AD1_AFIO_MODE       (AFIO_FUN_EBI)

#define LCD_EBI_AD2_GPIO_ID         (GPIO_PB)
#define LCD_EBI_AD2_AFIO_PIN        (AFIO_PIN_0)
#define LCD_EBI_AD2_AFIO_MODE       (AFIO_FUN_EBI)

#define LCD_EBI_AD3_GPIO_ID         (GPIO_PB)
#define LCD_EBI_AD3_AFIO_PIN        (AFIO_PIN_1)
#define LCD_EBI_AD3_AFIO_MODE       (AFIO_FUN_EBI)

#define LCD_EBI_AD4_GPIO_ID         (GPIO_PB)
#define LCD_EBI_AD4_AFIO_PIN        (AFIO_PIN_2)
#define LCD_EBI_AD4_AFIO_MODE       (AFIO_FUN_EBI)

#define LCD_EBI_AD5_GPIO_ID         (GPIO_PB)
#define LCD_EBI_AD5_AFIO_PIN        (AFIO_PIN_3)
#define LCD_EBI_AD5_AFIO_MODE       (AFIO_FUN_EBI)

#define LCD_EBI_AD6_GPIO_ID         (GPIO_PB)
#define LCD_EBI_AD6_AFIO_PIN        (AFIO_PIN_4)
#define LCD_EBI_AD6_AFIO_MODE       (AFIO_FUN_EBI)

#define LCD_EBI_AD7_GPIO_ID         (GPIO_PB)
#define LCD_EBI_AD7_AFIO_PIN        (AFIO_PIN_5)
#define LCD_EBI_AD7_AFIO_MODE       (AFIO_FUN_EBI)

#define LCD_EBI_AD8_GPIO_ID         (GPIO_PC)
#define LCD_EBI_AD8_AFIO_PIN        (AFIO_PIN_14)
#define LCD_EBI_AD8_AFIO_MODE       (AFIO_FUN_EBI)

#define LCD_EBI_AD9_GPIO_ID         (GPIO_PC)
#define LCD_EBI_AD9_AFIO_PIN        (AFIO_PIN_15)
#define LCD_EBI_AD9_AFIO_MODE       (AFIO_FUN_EBI)

#define LCD_EBI_AD10_GPIO_ID        (GPIO_PD)
#define LCD_EBI_AD10_AFIO_PIN       (AFIO_PIN_1)
#define LCD_EBI_AD10_AFIO_MODE      (AFIO_FUN_EBI)

#define LCD_EBI_AD11_GPIO_ID        (GPIO_PD)
#define LCD_EBI_AD11_AFIO_PIN       (AFIO_PIN_2)
#define LCD_EBI_AD11_AFIO_MODE      (AFIO_FUN_EBI)

#define LCD_EBI_AD12_GPIO_ID        (GPIO_PD)
#define LCD_EBI_AD12_AFIO_PIN       (AFIO_PIN_3)
#define LCD_EBI_AD12_AFIO_MODE      (AFIO_FUN_EBI)

#define LCD_EBI_AD13_GPIO_ID        (GPIO_PC)
#define LCD_EBI_AD13_AFIO_PIN       (AFIO_PIN_10)
#define LCD_EBI_AD13_AFIO_MODE      (AFIO_FUN_EBI)

#define LCD_EBI_AD14_GPIO_ID        (GPIO_PC)
#define LCD_EBI_AD14_AFIO_PIN       (AFIO_PIN_11)
#define LCD_EBI_AD14_AFIO_MODE      (AFIO_FUN_EBI)

#define LCD_EBI_AD15_GPIO_ID        (GPIO_PC)
#define LCD_EBI_AD15_AFIO_PIN       (AFIO_PIN_12)
#define LCD_EBI_AD15_AFIO_MODE      (AFIO_FUN_EBI)

#define LCD_EBI_BL_ENABLE           (1)
#define LCD_EBI_BL_GPIO_ID          (GPIO_PB)
#define LCD_EBI_BL_GPIO_PIN         (GPIO_PIN_6)
#define LCD_EBI_BL_AFIO_MODE        (AFIO_FUN_GPIO)
#define LCD_EBI_BL_CLK(CK)          (CK.Bit.PB)

#define LCD_EBI_RST_GPIO_ID         (GPIO_PB)
#define LCD_EBI_RST_GPIO_PIN        (GPIO_PIN_7)
#define LCD_EBI_RST_AFIO_MODE       (AFIO_FUN_GPIO)
#define LCD_EBI_RST_CLK(CK)         (CK.Bit.PB)
/**
  * @}
  */

/** @addtogroup HT32F52352_SK_SPI_LCD
  * @{
  */
#define LCD_SPI_CLK(CK)             (CK.Bit.SPI1)
#define LCD_SPI                     (HT_SPI1)

#define LCD_SPI_SCK_GPIO_ID         (GPIO_PC)
#define LCD_SPI_SCK_AFIO_PIN        (AFIO_PIN_5)
#define LCD_SPI_SCK_AFIO_MODE       (AFIO_FUN_SPI)

#define LCD_SPI_MOSI_GPIO_ID        (GPIO_PC)
#define LCD_SPI_MOSI_AFIO_PIN       (AFIO_PIN_8)
#define LCD_SPI_MOSI_AFIO_MODE      (AFIO_FUN_SPI)

#define LCD_SPI_MISO_GPIO_ID        (GPIO_PC)
#define LCD_SPI_MISO_AFIO_PIN       (AFIO_PIN_9)
#define LCD_SPI_MISO_AFIO_MODE      (AFIO_FUN_SPI)

#define LCD_SPI_SEL_GPIO_ID         (GPIO_PC)
#define LCD_SPI_SEL_AFIO_PIN        (AFIO_PIN_2)
#define LCD_SPI_SEL_AFIO_MODE       (AFIO_FUN_GPIO)
#define LCD_SPI_SEL_CLK(CK)         (CK.Bit.PC)

#define LCD_SPI_BL_ENABLE           (1)
#define LCD_SPI_BL_GPIO_ID          (GPIO_PB)
#define LCD_SPI_BL_GPIO_PIN         (GPIO_PIN_6)
#define LCD_SPI_BL_AFIO_MODE        (AFIO_FUN_GPIO)
#define LCD_SPI_BL_CLK(CK)          (CK.Bit.PB)

#define LCD_SPI_RST_GPIO_ID         (GPIO_PB)
#define LCD_SPI_RST_GPIO_PIN        (GPIO_PIN_7)
#define LCD_SPI_RST_AFIO_MODE       (AFIO_FUN_GPIO)
#define LCD_SPI_RST_CLK(CK)         (CK.Bit.PB)
/**
  * @}
  */

/** @addtogroup HT32F52352_SK_I2C_EEPROM
  * @{
  */
#define EEPROM_I2C_CLK(CK)          (CK.Bit.I2C1)
#define EEPROM_I2C                  (HT_I2C1)

#define EEPROM_I2C_SCL_GPIO_ID      (GPIO_PA)
#define EEPROM_I2C_SCL_AFIO_PIN     (AFIO_PIN_0)
#define EEPROM_I2C_SCL_AFIO_MODE    (AFIO_FUN_I2C)

#define EEPROM_I2C_SDA_GPIO_ID      (GPIO_PA)
#define EEPROM_I2C_SDA_AFIO_PIN     (AFIO_PIN_1)
#define EEPROM_I2C_SDA_AFIO_MODE    (AFIO_FUN_I2C)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup HT32F52352_SK_Exported_Functions HT32F52352 Starter kit exported functions
  * @{
  */
#define HT32F_DVB_USBConnect()      USBD_DPpullupCmd(ENABLE)
#define HT32F_DVB_USBDisConnect()   USBD_DPpullupCmd(DISABLE)
#define HT32F_DVB_GPxConfig         AFIO_GPxConfig

#define HT32F_DVB_BuzzerInit(hFreq, bDuty)    HT32F_DVB_BuzzerFun(hFreq, bDuty, 0);
#define HT32F_DVB_BuzzerConfig(hFreq, bDuty)  HT32F_DVB_BuzzerFun(hFreq, bDuty, 1);


void HT32F_DVB_LEDInit(LED_TypeDef HT_LEDn);
void HT32F_DVB_LEDOn(LED_TypeDef HT_LEDn);
void HT32F_DVB_LEDOff(LED_TypeDef HT_LEDn);
void HT32F_DVB_LEDToggle(LED_TypeDef HT_LEDn);

void HT32F_DVB_PBInit(BUTTON_TypeDef BUTTON_x, BUTTON_MODE_TypeDef BUTTON_MODE_x);
u32 HT32F_DVB_PBGetState(BUTTON_TypeDef BUTTON_x);

void HT32F_DVB_COMInit(COM_TypeDef COMn, USART_InitTypeDef* USART_InitStructure);

void HT32F_DVB_BuzzerFun(u16 hFreq, u8 bDuty, u32 mode);
void HT32F_DVB_BuzzerOutputCmd(ControlStatus Control);
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
