/*********************************************************************************************************//**
 * @file    _HT32_USBBufCheck.h
 * @version $Rev:: 2061         $
 * @date    $Date:: 2017-11-07 #$
 * @brief   The header file of USB buffer check.
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
#ifndef __HT32_USB_BUF_CHECK_H
#define __HT32_USB_BUF_CHECK_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported functions --------------------------------------------------------------------------------------*/
bool _HT32_USBBufCheck(u8* buf, u32 len);
void _HT32_USBBufCheck_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif
