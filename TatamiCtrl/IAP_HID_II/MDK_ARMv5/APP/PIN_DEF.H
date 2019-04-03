#define LED_RED                BIT0  // P2.0 红灯亮起
#define LED_GRE                BIT0  // P2.0 绿灯亮起
#define RF_LPCTL               BIT3  // P2.3 射频卡休眠控制 ------RST   
#define RF_SS                  BIT7  // p2.7 射频卡从机选择(SS)---SDA
#define RF_SCLK                BIT6  // p2.6 射频卡数据时钟输出(SCLK)
#define RF_DATA_OUT            BIT5  // p2.5 射频卡数据输出(MOSI)
#define RF_DATA_IN             BIT1  // p2.1 射频模块输入(MISO) 


//------------------------------- RC522操作宏 ------------------------------//
//#define    RF_POWER_ON             P8OUT &=~RF_PCTL                      // 射频模块上电
//#define    RF_POWER_OFF            P8OUT |= RF_PCTL                      // 射频模块下电
//#define    RF_POWER_ON             _NOP()                                // 射频模块上电
//#define    RF_POWER_OFF            _NOP()                                // 射频模块下电
//#define    RED_LED_ON              P2OUT &=~LED_RED                      // 红灯亮起
//#define    RED_LED_OFF             P2OUT |= LED_RED                      // 红灯熄灭
//#define    GRE_LED_ON              P2OUT &=~LED_GRE                      // 绿灯亮起
//#define    GRE_LED_OFF             P2OUT |= LED_GRE                      // 绿灯熄灭

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



#define    RF_SLEEP                GPIO_WriteOutBits(RF_EN_PORT,RF_EN_PIN, RESET)                     // 射频模块唤醒
#define    RF_WAKEUP               GPIO_WriteOutBits(RF_EN_PORT,RF_EN_PIN, SET)                     // 射频模块休眠

#define    SCLK_HIGH               GPIO_WriteOutBits(RF_SCLK_PORT,RF_SCLK_PIN, RESET)                      // 数据时钟置高
#define    SCLK_LOW                GPIO_WriteOutBits(RF_SCLK_PORT,RF_SCLK_PIN, RESET)                      // 数据时钟置低
#define    DATA_OUT_HIGH           GPIO_WriteOutBits(RF_DATA_OUT_PORT,RF_DATA_OUT_PIN, RESET)                  // 数据置高
#define    DATA_OUT_LOW            GPIO_WriteOutBits(RF_DATA_OUT_PORT,RF_DATA_OUT_PIN, RESET)                  // 数据置低

#define    SCK522_1                GPIO_WriteOutBits(RF_SCLK_PORT,RF_SCLK_PIN, SET)                      // 数据时钟置高
#define    SCK522_0                GPIO_WriteOutBits(RF_SCLK_PORT,RF_SCLK_PIN, RESET)                      // 数据时钟置低
#define    SI522_1                 GPIO_WriteOutBits(RF_DATA_OUT_PORT,RF_DATA_OUT_PIN, SET)                 // 数据置高        
#define    SI522_0                 GPIO_WriteOutBits(RF_DATA_OUT_PORT,RF_DATA_OUT_PIN, RESET)                // 数据置低        
#define    SO522                   GPIO_ReadOutBit(RF_DATA_IN_PORT,RF_DATA_IN_PIN)              // 数据输入
#define    RST522_1                GPIO_WriteOutBits(RF_EN_PORT,RF_EN_PIN, SET)
#define    RST522_0                GPIO_WriteOutBits(RF_EN_PORT,RF_EN_PIN, RESET)


//------------------------------ 操作结果  ---------------------------------------//
#define    SUCCESS1                    0
#define    FAILURE 1                   1
#define    CRC_ERROR1                  2
