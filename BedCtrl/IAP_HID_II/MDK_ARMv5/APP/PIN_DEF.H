#define LED_RED                BIT0  // P2.0 �������
#define LED_GRE                BIT0  // P2.0 �̵�����
#define RF_LPCTL               BIT3  // P2.3 ��Ƶ�����߿��� ------RST   
#define RF_SS                  BIT7  // p2.7 ��Ƶ���ӻ�ѡ��(SS)---SDA
#define RF_SCLK                BIT6  // p2.6 ��Ƶ������ʱ�����(SCLK)
#define RF_DATA_OUT            BIT5  // p2.5 ��Ƶ���������(MOSI)
#define RF_DATA_IN             BIT1  // p2.1 ��Ƶģ������(MISO) 


//------------------------------- RC522������ ------------------------------//
//#define    RF_POWER_ON             P8OUT &=~RF_PCTL                      // ��Ƶģ���ϵ�
//#define    RF_POWER_OFF            P8OUT |= RF_PCTL                      // ��Ƶģ���µ�
//#define    RF_POWER_ON             _NOP()                                // ��Ƶģ���ϵ�
//#define    RF_POWER_OFF            _NOP()                                // ��Ƶģ���µ�
//#define    RED_LED_ON              P2OUT &=~LED_RED                      // �������
//#define    RED_LED_OFF             P2OUT |= LED_RED                      // ���Ϩ��
//#define    GRE_LED_ON              P2OUT &=~LED_GRE                      // �̵�����
//#define    GRE_LED_OFF             P2OUT |= LED_GRE                      // �̵�Ϩ��

//#define RF_EN_PORT          (HT_GPIOA)
//#define RF_EN_PIN           (GPIO_PIN_1)

//#define RF_SCLK_PORT        (HT_GPIOA)
//#define RF_SCLK_PIN         (GPIO_PIN_15)

//#define RF_DATA_OUT_PORT     (HT_GPIOA)
//#define RF_DATA_OUT_PIN      (GPIO_PIN_12)

//#define RF_DATA_IN_PORT     (HT_GPIOA)
//#define RF_DATA_IN_PIN      (GPIO_PIN_13)

//#define RF_SLAVE_PORT       (HT_GPIOA)
//#define RF_SLAVE_PIN        (GPIO_PIN_0)



#define    RF_SLEEP                GPIO_WriteOutBits(RF_EN_PORT,RF_EN_PIN, RESET)                     // ��Ƶģ�黽��
#define    RF_WAKEUP               GPIO_WriteOutBits(RF_EN_PORT,RF_EN_PIN, SET)                     // ��Ƶģ������

#define    SCLK_HIGH               GPIO_WriteOutBits(RF_SCLK_PORT,RF_SCLK_PIN, RESET)                      // ����ʱ���ø�
#define    SCLK_LOW                GPIO_WriteOutBits(RF_SCLK_PORT,RF_SCLK_PIN, RESET)                      // ����ʱ���õ�
#define    DATA_OUT_HIGH           GPIO_WriteOutBits(RF_DATA_OUT_PORT,RF_DATA_OUT_PIN, RESET)                  // �����ø�
#define    DATA_OUT_LOW            GPIO_WriteOutBits(RF_DATA_OUT_PORT,RF_DATA_OUT_PIN, RESET)                  // �����õ�

#define    SCK522_1                GPIO_WriteOutBits(RF_SCLK_PORT,RF_SCLK_PIN, SET)                      // ����ʱ���ø�
#define    SCK522_0                GPIO_WriteOutBits(RF_SCLK_PORT,RF_SCLK_PIN, RESET)                      // ����ʱ���õ�
#define    SI522_1                 GPIO_WriteOutBits(RF_DATA_OUT_PORT,RF_DATA_OUT_PIN, SET)                 // �����ø�        
#define    SI522_0                 GPIO_WriteOutBits(RF_DATA_OUT_PORT,RF_DATA_OUT_PIN, RESET)                // �����õ�        
#define    SO522                   GPIO_ReadOutBit(RF_DATA_IN_PORT,RF_DATA_IN_PIN)              // ��������
#define    RST522_1                GPIO_WriteOutBits(RF_EN_PORT,RF_EN_PIN, SET)
#define    RST522_0                GPIO_WriteOutBits(RF_EN_PORT,RF_EN_PIN, RESET)


//------------------------------ �������  ---------------------------------------//
#define    SUCCESS1                    0
#define    FAILURE 1                   1
#define    CRC_ERROR1                  2
