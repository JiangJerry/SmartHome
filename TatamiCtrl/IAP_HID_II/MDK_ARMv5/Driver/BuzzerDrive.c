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

#define BUZZER_ON_TIME 	(15)
#define BUZZER_OFF_TIME (8)

typedef struct{
	 unsigned char Times;
	 int OnCnt;
	 int OffCnt;
}_BUZZER;

FlagStatus TaskBuzzerRdy;


_BUZZER Buzzer;
_BUZZER Output5V; 

void EnterSet(void)
{
	Buzzer.Times = 1;
	Buzzer.OnCnt = 15;
	Buzzer.OffCnt = 8;	
}
void ExitSet(void)
{
	Buzzer.Times = 2;
	Buzzer.OnCnt = 13;
	Buzzer.OffCnt = 8;	
}

void TaskBuzzer(void)
{
	if(TaskBuzzerRdy)
	{
		TaskBuzzerRdy = RESET;
		if(Buzzer.Times > 0)
		{
			if(Buzzer.OnCnt-- > 0)
			{
				HT32F_DVB_LEDOn(BUZZ);
			}
			else
			{
				if(Buzzer.OffCnt-- > 0)
				{
					HT32F_DVB_LEDOff(BUZZ);
				}
				else
				{
					if(Buzzer.Times > 0)
					{
						Buzzer.Times--;
						Buzzer.OnCnt = BUZZER_ON_TIME;
						Buzzer.OffCnt = BUZZER_OFF_TIME;
					}				
				}
			}		
		}
		else
		{		
			HT32F_DVB_LEDOff(BUZZ);
		}						
	}
}
