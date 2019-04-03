#ifndef __KEY_H
#define __KEY_H
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
//typedef unsigned char uint8_t;
//typedef signed char int8_t;
//typedef unsigned int uint16_t;

#define G_SET_BIT(a,b)                            (a |= (1 << b))
#define G_CLEAR_BIT(a,b)                          (a &= ~(1 << b))
#define G_IS_BIT_SET(a,b)                         (a & (1 << b))

#define KEY_TIMER_MS                            10//��ʱ���ж����� 2ms����һ���ж�
#define KEY_MAX_NUMBER                          12//��󰴼���
#define KEY_DELAY_MS                 			2//��������ʱ��
#define PRESS_LONG_TIME_S                 		(50*3)//����3s�㳤���¼�
#define PRESS_DOWN_STATUS						0//�������µ�״̬

#define NO_KEY                                  0x0000
#define KEY_DOWN                                0x1000
#define KEY_UP                                  0x2000
#define KEY_LIAN                                0x4000
#define KEY_LONG                                0x8000

typedef void (*gokitKeyFunction)(void);

 typedef enum _gpio_addr_t{
	 p0_=0x80,
	 p1_=0x90,
	 p2_=0xa0,
	 p3_=0xb0,
	 p4_=0xc0,
	 p5_=0xc8
	 
 }gpio_addr_t;
  typedef enum _gpio_t{
	 px_0=0x01,
	 px_1=0x02,
	 px_2=0x04,
	 px_3=0x08,
	 px_4=0x10,
	 px_5=0x20,
	 px_6=0x40,
	 px_7=0x80
	 
 }gpio_t;

typedef  struct _keyTypedef_t
{
    unsigned char    keyNum;//����������
    gpio_addr_t      keyPx;//
   	gpio_t           keyx;
    gokitKeyFunction shortPress; 
    gokitKeyFunction longPress; 
    void *shortArg;			//�������β�
    void *longArg;			//�������β���ʱ��ӣ�����ʵ���Ҳ���ô�пգ��Ͳ�ʵ���ˣ��ɲο�����̳����һƪ���ӡ���ʱ����
}keyTypedef_t;

typedef struct _keysTypedef_t
{
    unsigned char keyTotolNum;//���������ۼ�
    keyTypedef_t *singleKey; //�����ָ��
}keysTypedef_t; 



//extern keysTypedef_t keys;
void keyHandle(keysTypedef_t *keys);
void key_Init(void);//��main�����г�ʼ�������������
void TimeGetKey(void);
#endif /*_HAL_KEY_H*/





