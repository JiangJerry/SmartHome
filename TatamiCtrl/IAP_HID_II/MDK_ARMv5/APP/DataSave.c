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



u32 SaveData(u32 Data)
{
    u32 Addr,Err;
    FLASH_State FLASHState;
    /* Erase Flash pages before program data                                                                  */
    for (Addr = StartAddress; Addr < EndAddress; Addr += FLASH_PAGE_SIZE)
    {
        FLASHState = FLASH_ErasePage(Addr);
        if (FLASHState != FLASH_COMPLETE)
        {
          Err++;
        }
    }
    /* Program Word data                                                                                      */
    for (Addr = StartAddress; Addr < EndAddress; Addr += 4)
    {
        FLASHState = FLASH_ProgramWordData(Addr, Data);
        if (FLASHState != FLASH_COMPLETE)
        {
          Err++;
        }
    }
    /* Check Flash data                                                                                       */
    for (Addr = StartAddress; Addr < EndAddress; Addr += 4)
    {
        if (rw(Addr) != TEST_DATA)
        {
            Err++;
        }
    }
    return Err;
}

u32 ReadData(void)
{
    return rw(StartAddress);
}