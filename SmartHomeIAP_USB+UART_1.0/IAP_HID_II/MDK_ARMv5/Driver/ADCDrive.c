#include "ht32.h"
#include "ht32_board.h"
#include "main.h"

#define HTCFG_START_GPIO                 (GPIO_PC)
#define HTCFG_START_PIN                  (AFIO_PIN_5)
#define HTCFG_START_ADC_CH               (ADC_CH_9)

#define HTCFG_DELAY_GPIO                 (GPIO_PC)
#define HTCFG_DELAY_PIN                  (AFIO_PIN_4)
#define HTCFG_DELAY_ADC_CH               (ADC_CH_8)



void ADCInit(void)
{
    /* ADCLK frequency is set to CK_AHB/64                                                                    */
    CKCU_SetADCPrescaler(CKCU_ADCPRE_DIV16);
    /* Config AFIO mode as ADC function                                                                       */
    AFIO_GPxConfig(HTCFG_START_GPIO, HTCFG_START_PIN, AFIO_FUN_ADC);
    AFIO_GPxConfig(HTCFG_DELAY_GPIO, HTCFG_DELAY_PIN, AFIO_FUN_ADC);
    /* Continuous Mode, Length 1, SubLength 1                                                                 */
    ADC_RegularGroupConfig(HT_ADC, ONE_SHOT_MODE, 2, 1);
    /* ADC Channel n, Rank 0, Sampling clock is (1.5 + 0) ADCLK
     Conversion time = (sampling clock + 12.5) / ADCLK = 12.4 uS */
    ADC_RegularChannelConfig(HT_ADC, HTCFG_START_ADC_CH, 0);
    ADC_RegularChannelConfig(HT_ADC, HTCFG_DELAY_ADC_CH, 1);
    /* Use Software Trigger as ADC trigger source                                                             */
    ADC_RegularTrigConfig(HT_ADC, ADC_TRIG_SOFTWARE);
    /* Enable ADC single end of conversion interrupt,
     The ADC ISR will store the ADC result into global variable gPotentiometerLevel. */
  ADC_IntConfig(HT_ADC, ADC_INT_SINGLE_EOC | ADC_INT_CYCLE_EOC, ENABLE);
    ADC_Cmd(HT_ADC, ENABLE);   
    /* Software trigger to start continuous mode                                                              */
    ADC_SoftwareStartConvCmd(HT_ADC, ENABLE);
    NVIC_EnableIRQ(ADC_IRQn); 
}

void ADCStart(void)
{
    ADC_SoftwareStartConvCmd(HT_ADC, ENABLE);
}


void ADCDisable(void)
{
    ADC_Cmd(HT_ADC, DISABLE);   
}



void ADCEnable(void)
{
    ADC_Cmd(HT_ADC, ENABLE);   
}
