#include "ht32.h"
#include "ht32_board.h"
#include "main.h"

FlagStatus TaskADCRdy;

#define BUTTON_STOP 0
#define BUTTON_FWD  1
#define BUTTON_REV  2


#define DELAY_0P5S      1000

#define DELAY_1S        1750      

#define DELAY_1P5S      3200

_ADC_FUNC  StopDelay,ADSw;

_KEY_STRUCT StopKey,FwdKey,RevKey;

void ADCCallBack(void)
{
    KEY_STOP(ADSw.Valu);
}

extern __FUNC_STRUCT Func;


void TaskADC(void)
{
    int Valu;
    if(TaskADCRdy)
    {
        TaskADCRdy = 0;

        if(StopDelay.Valu >= DELAY_1P5S)
        {
            Func.DlyTime = 150;
        }
        else if(StopDelay.Valu >= DELAY_1S)
        {
            Func.DlyTime = 100;
        }
        else
        {
             Func.DlyTime = 50;          
        }              
    }    
}
