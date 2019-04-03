#include "ht32.h"
#include "ht32_board.h"
#include "main.h"


void FixOutInit(void)
{
    HT32F_DVB_LEDInit(HT_LED1);
    HT32F_DVB_LEDInit(HT_LED2);
    HT32F_DVB_LEDInit(HT_LED3);
    HT32F_DVB_LEDInit(HT_LED4);
    HT32F_DVB_LEDInit(BUZZ);
    HT32F_DVB_LEDInit(RY1);
    HT32F_DVB_LEDInit(RY2);
    HT32F_DVB_LEDInit(RY3);
    HT32F_DVB_LEDInit(RY4);
    HT32F_DVB_LEDInit(RY5);   
}

