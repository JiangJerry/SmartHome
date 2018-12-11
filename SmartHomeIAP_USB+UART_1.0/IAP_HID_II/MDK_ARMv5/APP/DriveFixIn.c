#include "ht32.h"
#include "ht32_board.h"
#include "main.h"

extern __FUNC_STRUCT Func;

void FixInInit(void)
{

    HT32F_DVB_PBInit(BUTTON_KEY1, BUTTON_MODE_EXTI);    //RF����
    HT32F_DVB_PBInit(BUTTON_KEY2, BUTTON_MODE_GPIO);    //��ͨ��������
    HT32F_DVB_LEDInit(HT_LED1);
    HT32F_DVB_LEDInit(HT_LED2);
    
    HT32F_DVB_PBInit(LIMIT_SW1, BUTTON_MODE_GPIO);    //�г̿���1
    HT32F_DVB_PBInit(LIMIT_SW2, BUTTON_MODE_GPIO);    //�г̿���2
    HT32F_DVB_PBInit(LIMIT_SW3, BUTTON_MODE_GPIO);    //�г̿���3
    HT32F_DVB_PBInit(LIMIT_SW4, BUTTON_MODE_GPIO);    //�г̿���4

    HT32F_DVB_PBInit(CLOSE_SW1, BUTTON_MODE_GPIO);    //�ӽ�����1
    HT32F_DVB_PBInit(CLOSE_SW2, BUTTON_MODE_GPIO);    //�ӽ�����2
    HT32F_DVB_PBInit(CLOSE_SW3, BUTTON_MODE_GPIO);    //�ӽ�����3
    HT32F_DVB_PBInit(CLOSE_SW4, BUTTON_MODE_GPIO);    //�ӽ�����4   
    Func.KeyUnlockTime = 300;
}

u32 DriveGetCloseSW1(void)
{
    return HT32F_DVB_PBGetState(CLOSE_SW1);
}

u32 DriveGetCloseSW2(void)
{
    return HT32F_DVB_PBGetState(CLOSE_SW2);
}

u32 DriveGetCloseSW3(void)
{
    return HT32F_DVB_PBGetState(CLOSE_SW3);
}
u32 DriveGetCloseSW4(void)
{
    return HT32F_DVB_PBGetState(CLOSE_SW4);
}


u32 DriveGetLimitSW1(void)
{
    return HT32F_DVB_PBGetState(LIMIT_SW1);
}

u32 DriveGetLimitSW2(void)
{
    return HT32F_DVB_PBGetState(LIMIT_SW2);
}
u32 DriveGetLimitSW3(void)
{
    return HT32F_DVB_PBGetState(LIMIT_SW3);
}
u32 DriveGetLimitSW4(void)
{
    return HT32F_DVB_PBGetState(LIMIT_SW4);
}

