/*
 * File      : msd.h
 * SPI mode SD Card Driver
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-04-17     Bernard      first version.
 */

#ifndef _BMP280_H
#define _BMP280_H
					   
#include "ht32.h"
#include "ht32_board.h"
#include "main.h"
							   
typedef unsigned char  BYTE;
typedef unsigned short WORD;
   	


#define SUCCESS  0
#define ERROR    -1



typedef struct __BMP180
{
	short AC1;
	short AC2;
	short AC3;
	unsigned short AC4;
	unsigned short AC5;
	unsigned short AC6;
	short B1;
	short B2;
	short MB;
	short MC;
	short MD;
	long UT;
	long UP;
	long X1;
	long X2;
	long X3;
	long B3;
	unsigned long B4;
	long B5;
	long B6;
	long B7;
	long p;
	long Temp;
	float altitude;
}_bmp180;

extern _bmp180 bmp180;

void BMP_Init(void);
uint8_t BMP_ReadOneByte(uint8_t ReadAddr);
void BMP_WriteOneByte(uint8_t WriteAddr,uint8_t DataToWrite);
short BMP_ReadTwoByte(uint8_t ReadAddr);
void BMP_ReadCalibrationData(void);
long BMP_Read_UT(void);
long BMP_Read_UP(void);
void BMP_UncompemstatedToTrue(void);
//#define	FRAME_SIZE			20
//------------------------------------
void BMP280_Start(void);
void BMP280_Stop(void);


void BMP280_SendByte(BYTE bat);
BYTE BMP280_RecvByte(void);
void BMP280_ReadPage(void);
void BMP280_WritePage(void);
void BMP280_SendACK(void);
//bit BMP280_RecvACK();
int	bmp280_init(void);
void Init_BMP280(void);
void GetPressure(void);
long bmp280Convert(void);
#endif // MSD_H_INCLUDED

