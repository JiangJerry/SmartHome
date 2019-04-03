#include "ht32.h"
#include "ht32_board.h"
#include "main.h"


FlagStatus TaskRFRdy,ReadyReFlag;
extern _RF_STRUCT RFCtrl;
FLASH_State SaveSta;
u8 RFRecord[3];
extern __FUNC_STRUCT Func;
extern u8 SaveID[2];

extern u8 OpCmd;
void KeyBuzzer(char Buzz_1)	;

void TaskRF(void)
{
    if(TaskRFRdy)
    {
        TaskRFRdy = 0;
        if(RFCtrl.Flag == 1)
        {
            RFCtrl.Flag = 0;          
			
            if((RFCtrl.Valu[0] == SaveID[0])&&(RFCtrl.Valu[1] == SaveID[1]))
            {
                switch(RFCtrl.Valu[2])
                {
                    case RF_FWD_CODE: 
                        OpCmd = FWD_CMD;                         
                        break;
                    case RF_REV_CODE: 
                        OpCmd = REV_CMD;
                        break;
                    case RF_STOP_CODE:
                    default:          
                        OpCmd = STOP_CMD;                        
                        break;
                }
            }
            if(Func.Sta == SET_RF)
            {
				ExitSet();
                ReadyReFlag = SET;
                RFRecord[0] = RFCtrl.Valu[0];
                RFRecord[1] = RFCtrl.Valu[1];
                RFRecord[2] = RFCtrl.Valu[2];
            }
        }        
    }    
}
