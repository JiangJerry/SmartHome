#include <string.h>
#include "BMP280Drive.h"
#include  <math.h>    //Keil library  
#include  <stdlib.h>  //Keil library  
#include  <stdio.h>   //Keil library

#include "USART0Drive.h"

#define   uchar unsigned char
#define   uint unsigned int	

#define	ADDRESS   0x5a	  //����������IIC�����еĴӵ�ַ                               

#define OSS 0	// Oversampling Setting (note: code is not set up to use other OSS values)

#define SDA_OUT()   GPIO_DirectionConfig(SDA_PORT, SDA_PIN, GPIO_DIR_OUT)
#define SDA_IN() GPIO_DirectionConfig(SDA_PORT, SDA_PIN, GPIO_DIR_IN);\
                    GPIO_InputConfig(SDA_PORT, SDA_PIN, ENABLE);

void delay_us(u8 i)    //��΢��ʱ  6usԼ>4.7us
{
    u8 j = 0;
    for(;i>0;i--)
    {
        for(j = 0;j < 250;j++)
        {
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
            
        }        
    }
}

//    GPIO_WriteOutBits(SCK_PORT, SCK_PIN, 1);;

//����IIC��ʼ�ź�
void IIC_Start(void)
{
	GPIO_WriteOutBits(SDA_PORT, SDA_PIN, SET);	  	  
	GPIO_WriteOutBits(SCK_PORT, SCK_PIN, SET);
	SDA_OUT();     //sda�����
	delay_us(4);
 	GPIO_WriteOutBits(SDA_PORT, SDA_PIN, RESET);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	GPIO_WriteOutBits(SCK_PORT, SCK_PIN, RESET);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	GPIO_WriteOutBits(SCK_PORT, SCK_PIN, RESET);
	GPIO_WriteOutBits(SDA_PORT, SDA_PIN, RESET);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	GPIO_WriteOutBits(SCK_PORT, SCK_PIN, SET); 
	GPIO_WriteOutBits(SDA_PORT, SDA_PIN, SET);//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	GPIO_WriteOutBits(SDA_PORT, SDA_PIN, SET);delay_us(1);	   
	GPIO_WriteOutBits(SCK_PORT, SCK_PIN, SET);delay_us(1);	 
	while(GPIO_ReadInBit(SDA_PORT, SDA_PIN) == SET)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	GPIO_WriteOutBits(SCK_PORT, SCK_PIN, RESET);//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	GPIO_WriteOutBits(SCK_PORT, SCK_PIN, RESET);
	SDA_OUT();
	GPIO_WriteOutBits(SDA_PORT, SDA_PIN, RESET);
	delay_us(2);
	GPIO_WriteOutBits(SCK_PORT, SCK_PIN, SET);
	delay_us(2);
	GPIO_WriteOutBits(SCK_PORT, SCK_PIN, RESET);
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	GPIO_WriteOutBits(SCK_PORT, SCK_PIN, RESET);
	SDA_OUT();
	GPIO_WriteOutBits(SDA_PORT, SDA_PIN, SET);
	delay_us(2);
	GPIO_WriteOutBits(SCK_PORT, SCK_PIN, SET);
	delay_us(2);
	GPIO_WriteOutBits(SCK_PORT, SCK_PIN, RESET);
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    GPIO_WriteOutBits(SCK_PORT, SCK_PIN, RESET);//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
		if((txd&0x80)>>7)
			GPIO_WriteOutBits(SDA_PORT, SDA_PIN, SET);
		else
			GPIO_WriteOutBits(SDA_PORT, SDA_PIN, RESET);
		txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		GPIO_WriteOutBits(SCK_PORT, SCK_PIN, SET);
		delay_us(2); 
		GPIO_WriteOutBits(SCK_PORT, SCK_PIN, RESET);	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        GPIO_WriteOutBits(SCK_PORT, SCK_PIN, RESET); 
        delay_us(2);
		GPIO_WriteOutBits(SCK_PORT, SCK_PIN, SET);
        delay_us(2);
        receive <<= 1;
        if(GPIO_ReadInBit(SDA_PORT, SDA_PIN))
        {
            receive++;   
        }
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}

//*********************************************************
//����BMP085�ڲ�����,��������
//*********************************************************
long Multiple_three_read(uchar ST_Address)
{   
	uchar msb, lsb,xlsb;
	long _data = 0;
	
	msb = BMP_ReadOneByte(ST_Address);
	lsb = BMP_ReadOneByte(ST_Address+1);
	xlsb = BMP_ReadOneByte(ST_Address+2);
	xlsb = BMP_ReadOneByte(ST_Address+2);
	xlsb = BMP_ReadOneByte(ST_Address+2);

 	_data = msb << 16;	
 	_data |= lsb << 8;	
 	_data |= xlsb;
 	_data = _data >> 4;
	return _data;
}

//дһ�����ݵ�BMP180
unsigned char Data[5];
void BMP_WriteOneByte(uint8_t WriteAddr,uint8_t DataToWrite)
{
	IIC_Start();	
	IIC_Send_Byte(0x5a);
	IIC_Wait_Ack();	
	IIC_Send_Byte(0xca);
	IIC_Wait_Ack();	
	IIC_Send_Byte(0xc2);
	IIC_Wait_Ack();
	IIC_Send_Byte(0xee);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x2c);
	IIC_Wait_Ack();
	IIC_Stop();
    
}

//��BMP180��һ���ֽ�����
uint8_t BMP_ReadOneByte(uint8_t ReadAddr)
{
	uint8_t data = 0;
	
	IIC_Start();
	
	IIC_Send_Byte(0XA5);
	IIC_Wait_Ack();

    Data[0] = IIC_Read_Byte(0);
    Data[1] = IIC_Read_Byte(0);
    Data[2] = IIC_Read_Byte(0);
    Data[3] = IIC_Read_Byte(0);
    Data[4] = IIC_Read_Byte(0);
	
//	data = IIC_Read_Byte(0);
	IIC_Stop();
	
	return data;
}

//��BMP180��һ��16λ������
short BMP_ReadTwoByte(uint8_t ReadAddr)
{
	short data;
	uint8_t msb,lsb;
	
	IIC_Start();
	
	IIC_Send_Byte(ADDRESS);
	IIC_Wait_Ack();
	
	IIC_Send_Byte(ReadAddr);
	IIC_Wait_Ack();
	
	IIC_Start();
	
	IIC_Send_Byte(0xEF);
	IIC_Wait_Ack();
	
	msb = IIC_Read_Byte(1);
	lsb = IIC_Read_Byte(0);
	
	IIC_Stop();
	
	data = msb + lsb*256;
	
	return data;
}
