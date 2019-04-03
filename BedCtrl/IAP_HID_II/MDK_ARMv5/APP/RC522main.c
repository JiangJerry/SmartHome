                                                                        //
//===========================================================================//
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
#include "PIN_DEF.H"
#include "RC522.H"
#include "ctype.h" 

#define uchar unsigned char
    
//******************************************************************/
//��    �ܣ���RC522�Ĵ���
//����˵����Address[IN]:�Ĵ�����ַ
//��    �أ�������ֵ
//******************************************************************/
unsigned char ReadRawRC(unsigned char Address)
{
  unsigned char i, ucAddr             ;
  unsigned char ucResult=0            ;
//  NSS522_0                            ;
  SCK522_0                            ;
  ucAddr = ((Address<<1)&0x7E)|0x80   ;
  for(i=8;i>0;i--)
  {
    if((ucAddr&0x80)==0x80)
      SI522_1                         ;
    else
      SI522_0                         ;
    SCK522_1                          ;
    ucAddr <<= 1                      ;
    SCK522_0                          ;
  }
  for(i=8;i>0;i--)
  {
    SCK522_1                          ;
    ucResult <<=1                     ;
    ucResult |= SO522                 ;
    SCK522_0                          ;
  }
  SCK522_0                            ;
//  NSS522_1                            ;
  return ucResult                     ;
}

//******************************************************************/
//��    �ܣ�дRC522�Ĵ���
//����˵����Address[IN]:�Ĵ�����ַ
//          value[IN]:д���ֵ
//******************************************************************/
/*
void WriteRawRC(unsigned char Address, unsigned char value)
{  
    unsigned char i, ucAddr      ;

    NSS522_0                     ;
    SCK522_0                     ;
    ucAddr = ((Address<<1)&0x7E) ;
    for(i=8;i>0;i--)
    {
        if ((ucAddr&0x80)==0x80)
        {   SI522_1;   }
        else
        {   SI522_0;   }
        SCK522_1;
        ucAddr <<= 1;
        SCK522_0;
    }
    for(i=8;i>0;i--)
    {
        if ((value&0x80)==0x80)
        {   SI522_1;   }
        else
        {   SI522_0;   }
        SCK522_1;
        value <<= 1;
        SCK522_0;
    }
    SCK522_0;
    NSS522_1;
}
*/

void WriteRawRC(unsigned char Address, unsigned char value)
{  
    unsigned char  ucAddr        ;

//    NSS522_0                     ;
    SCK522_0                     ;
    ucAddr = ((Address<<1)&0x7E) ;
    {
      if(ucAddr&0x80)
        SI522_1                  ;
      else
        SI522_0                  ; 
      SCK522_1                   ;
      ucAddr <<= 1               ;
      SCK522_0                   ;
      
      if(ucAddr&0x80)
        SI522_1                  ;
      else
        SI522_0                  ; 
      SCK522_1                   ;
      ucAddr <<= 1               ;
      SCK522_0                   ;
      
      if(ucAddr&0x80)
        SI522_1                  ;
      else
        SI522_0                  ; 
      SCK522_1                   ;
      ucAddr <<= 1               ;
      SCK522_0                   ;
      
      if(ucAddr&0x80)
        SI522_1                  ;
      else
        SI522_0                  ; 
      SCK522_1                   ;
      ucAddr <<= 1               ;
      SCK522_0                   ;
      
      if(ucAddr&0x80)
        SI522_1                  ;
      else
        SI522_0                  ; 
      SCK522_1                   ;
      ucAddr <<= 1               ;
      SCK522_0                   ;
      
      if(ucAddr&0x80)
        SI522_1                  ;
      else
        SI522_0                  ; 
      SCK522_1                   ;
      ucAddr <<= 1               ;
      SCK522_0                   ;
      
      if(ucAddr&0x80)
        SI522_1                  ;
      else
        SI522_0                  ; 
      SCK522_1                   ;
      ucAddr <<= 1               ;
      SCK522_0                   ;
      
      if(ucAddr&0x80)
        SI522_1                  ;
      else
        SI522_0                  ; 
      SCK522_1                   ;
      ucAddr <<= 1               ;
      SCK522_0                   ;                  
    }
    {
      if(value&0x80)
        SI522_1                  ;
      else
        SI522_0                  ;
      SCK522_1                   ;
      value <<= 1                ;
      SCK522_0                   ;
      
      if(value&0x80)
        SI522_1                  ;
      else
        SI522_0                  ;
      SCK522_1                   ;
      value <<= 1                ;
      SCK522_0                   ;
      
      if(value&0x80)
        SI522_1                  ;
      else
        SI522_0                  ;
      SCK522_1                   ;
      value <<= 1                ;
      SCK522_0                   ;
      
      if(value&0x80)
        SI522_1                  ;
      else
        SI522_0                  ;
      SCK522_1                   ;
      value <<= 1                ;
      SCK522_0                   ;
      
      if(value&0x80)
        SI522_1                  ;
      else
        SI522_0                  ;
      SCK522_1                   ;
      value <<= 1                ;
      SCK522_0                   ;
      
      if(value&0x80)
        SI522_1                  ;
      else
        SI522_0                  ;
      SCK522_1                   ;
      value <<= 1                ;
      SCK522_0                   ;
      
      if(value&0x80)
        SI522_1                  ;
      else
        SI522_0                  ;
      SCK522_1                   ;
      value <<= 1                ;
      SCK522_0                   ;
      
      if(value&0x80)
        SI522_1                  ;
      else
        SI522_0                  ;
      SCK522_1                   ;
      value <<= 1                ;
      SCK522_0                   ;      
    }
    SCK522_0;
//    NSS522_1;
}

//******************************************************************/
//��    �ܣ���RC522�Ĵ���λ
//����˵����reg[IN]:�Ĵ�����ַ
//          mask[IN]:��λֵ
//******************************************************************/
void SetBitMask(unsigned char reg,unsigned char mask)  
{
  char tmp = 0x0            ;
  tmp = ReadRawRC(reg)| mask;
  WriteRawRC(reg,tmp | mask);  // set bit mask
}

//******************************************************************/
//��    �ܣ���RC522�Ĵ���λ
//����˵����reg[IN]:�Ĵ�����ַ
//          mask[IN]:��λֵ
//******************************************************************/
void ClearBitMask(unsigned char reg,unsigned char mask)  
{
  char tmp = 0x0              ;
  tmp = ReadRawRC(reg)&(~mask);
  WriteRawRC(reg, tmp)        ;  // clear bit mask
} 

//******************************************************************/
//��    �ܣ���λRC522
//��    ��: �ɹ�����MI_OK
//******************************************************************/
char PcdReset()
{
//  RF_POWER_ON                          ;
  RST522_1                             ;
  Delay(1)                             ;
  RST522_0                             ;
  Delay(1)                             ;
  RST522_1                             ;
  Delay(1)                             ;
  WriteRawRC(CommandReg,PCD_RESETPHASE);
  Delay(1)                             ;
  WriteRawRC(ModeReg,0x3D)             ;
  WriteRawRC(TReloadRegL,30)           ;
  WriteRawRC(TReloadRegH,0)            ;
  WriteRawRC(TModeReg,0x8D)            ;
  WriteRawRC(TPrescalerReg,0x3E)       ;   
//  WriteRawRC(TxASKReg,0x40)            ; // FOR DEBUG AND TEST
  return MI_OK                         ; 
}

//******************************************************************/
//�������߷���  
//ÿ��������ر����շ���֮��Ӧ������1ms�ļ��
//******************************************************************/
void PcdAntennaOn()
{
  unsigned char i;
  WriteRawRC(TxASKReg,0x40)       ;
  Delay(10)                       ;
  i = ReadRawRC(TxControlReg)     ;
  if(!(i&0x03))
    SetBitMask(TxControlReg, 0x03);
  i=ReadRawRC(TxASKReg)       ;
}

//******************************************************************/
//�������߷���  
//ÿ��������ر����շ���֮��Ӧ������1ms�ļ��
//******************************************************************/
void PcdAntennaTestOn()
{
//*
  RST522_1                         ;
  Delay(15)                        ; // 2010.10.09 ???? FOR DEBUG
//  Delay(5)                        ; // 2010.10.09 ???? FOR DEBUG
  
  WriteRawRC(TxControlReg,0x02)    ;
//*/
/*
  Delay(1)                         ; 
  SetBitMask(TxControlReg, 0x03);// FOR DEBUG 
*/
}


//******************************************************************/
//�ر����߷���
//******************************************************************/
void PcdAntennaOff()
{
  ClearBitMask(TxControlReg, 0x03);
}

//******************************************************************/
//��    �ܣ�ͨ��RC522��ISO14443��ͨѶ
//����˵����Command[IN]:RC522������
//          pInData[IN]:ͨ��RC522���͵���Ƭ������
//          InLenByte[IN]:�������ݵ��ֽڳ���
//          pOutData[OUT]:���յ��Ŀ�Ƭ��������
//          *pOutLenBit[OUT]:�������ݵ�λ����
//******************************************************************/
char PcdComMF522(unsigned char Command  ,unsigned char *pInData , 
                 unsigned char InLenByte,unsigned char *pOutData, 
                 unsigned int  *pOutLenBit                       )
{
  char status = MI_ERR                          ;
  unsigned char irqEn   = 0x00                  ;
  unsigned char waitFor = 0x00                  ;
  unsigned char lastBits                        ;
  unsigned char n                               ;
  unsigned int  i                               ;
  switch (Command)
  {
    case PCD_AUTHENT:
      irqEn   = 0x12                            ;
      waitFor = 0x10                            ;
      break                                     ;
    case PCD_TRANSCEIVE:
      irqEn   = 0x77                            ;
      waitFor = 0x30                            ;
      break                                     ;
    default:
      break                                     ;
  }
  WriteRawRC(ComIEnReg,irqEn|0x80)              ; //
  ClearBitMask(ComIrqReg,0x80)                  ;
  WriteRawRC(CommandReg,PCD_IDLE)               ;
  SetBitMask(FIFOLevelReg,0x80)                 ; // ���FIFO 
  for(i=0; i<InLenByte; i++)
    WriteRawRC(FIFODataReg,pInData[i])          ; // ����д��FIFO 
  WriteRawRC(CommandReg, Command)               ; // ����д������Ĵ���
  if(Command == PCD_TRANSCEIVE)
    SetBitMask(BitFramingReg,0x80)              ; // ��ʼ����     
  i = 6000                                      ; //����ʱ��Ƶ�ʵ���������M1�����ȴ�ʱ��25ms
  do 
  {
    n = ReadRawRC(ComIrqReg)                    ;
    i--                                         ;
  }
  while((i!=0)&&!(n&0x01)&&!(n&waitFor))        ;
  ClearBitMask(BitFramingReg,0x80)              ;
  if(i!=0)
  {
    if(!(ReadRawRC(ErrorReg)&0x1B))
    {
      status = MI_OK                            ;
      if (n&irqEn&0x01)
        status = MI_NOTAGERR                    ;
      if(Command==PCD_TRANSCEIVE)
      {
        n = ReadRawRC(FIFOLevelReg)             ;
        lastBits = ReadRawRC(ControlReg)&0x07   ;
        if(lastBits)
          *pOutLenBit = (n-1)*8 + lastBits      ;
        else
          *pOutLenBit = n*8                     ;
        if(n==0)
          n = 1                                 ;
        if(n>MAXRLEN)
          n = MAXRLEN                           ;
        for (i=0; i<n; i++)
          pOutData[i] = ReadRawRC(FIFODataReg)  ; 
      }
    }
    else
      status = MI_ERR                           ;        
  }
  SetBitMask(ControlReg,0x80)                   ;// stop timer now
  WriteRawRC(CommandReg,PCD_IDLE)               ; 
  return status;
}

//******************************************************************/
//��    �ܣ�Ѱ��                                                    /
//����˵��: req_code[IN]:Ѱ����ʽ                                   /
//                0x52 = Ѱ��Ӧ�������з���14443A��׼�Ŀ�           /
//                0x26 = Ѱδ��������״̬�Ŀ�                       /
//          pTagType[OUT]����Ƭ���ʹ���                             /
//                0x4400 = Mifare_UltraLight                        /
//                0x0400 = Mifare_One(S50)                          /
//                0x0200 = Mifare_One(S70)                          /
//                0x0800 = Mifare_Pro(X)                            /
//                0x4403 = Mifare_DESFire                           /
//��    ��: �ɹ�����MI_OK                                           /
//******************************************************************/
char PcdRequest(unsigned char req_code,unsigned char *pTagType)
{
  char status                                        ;  
  unsigned int  unLen                                ;
  unsigned char ucComMF522Buf[MAXRLEN]               ; 

  ClearBitMask(Status2Reg,0x08)                      ;
  WriteRawRC(BitFramingReg,0x07)                     ;
  SetBitMask(TxControlReg,0x03)                      ;
 
  ucComMF522Buf[0] = req_code                        ;

  status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,
                       1,ucComMF522Buf,&unLen       );
  if ((status == MI_OK) && (unLen == 0x10))
  {    
    *pTagType     = ucComMF522Buf[0]                 ;
    *(pTagType+1) = ucComMF522Buf[1]                 ;
  }
  else
    status = MI_ERR                                  ;
  return status                                      ;
}

//******************************************************************/
//��    �ܣ�����ײ                                                  /
//����˵��: pSnr[OUT]:��Ƭ���кţ�4�ֽ�                             /
//��    ��: �ɹ�����MI_OK                                           /
//******************************************************************/
char PcdAnticoll(unsigned char *pSnr)
{
    char status;
    unsigned char i,snr_check=0;
    unsigned int  unLen;
    unsigned char ucComMF522Buf[MAXRLEN]; 
    
    ClearBitMask(Status2Reg,0x08);
    WriteRawRC(BitFramingReg,0x00);
    ClearBitMask(CollReg,0x80);
 
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x20;

    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,2,ucComMF522Buf,&unLen);

    if (status == MI_OK)
    {
    	 for (i=0; i<4; i++)
         {   
             *(pSnr+i)  = ucComMF522Buf[i];
             snr_check ^= ucComMF522Buf[i];
         }
         if (snr_check != ucComMF522Buf[i])
         {   status = MI_ERR;    }
    }
    
    SetBitMask(CollReg,0x80);
    return status;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ�ѡ����Ƭ
//����˵��: pSnr[IN]:��Ƭ���кţ�4�ֽ�
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////
char PcdSelect(unsigned char *pSnr)
{
    char status;
    unsigned char i;
    unsigned int  unLen;
    unsigned char ucComMF522Buf[MAXRLEN]; 
    
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x70;
    ucComMF522Buf[6] = 0;
    for (i=0; i<4; i++)
    {
    	ucComMF522Buf[i+2] = *(pSnr+i);
    	ucComMF522Buf[6]  ^= *(pSnr+i);
    }
    CalulateCRC(ucComMF522Buf,7,&ucComMF522Buf[7]);
  
    ClearBitMask(Status2Reg,0x08);

    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,9,ucComMF522Buf,&unLen);
    
    if ((status == MI_OK) && (unLen == 0x18))
    {   status = MI_OK;  }
    else
    {   status = MI_ERR;    }

    return status;
}

//******************************************************************/
//��    �ܣ���֤��Ƭ����
//����˵��: auth_mode[IN]: ������֤ģʽ
//                 0x60 = ��֤A��Կ
//                 0x61 = ��֤B��Կ 
//          addr[IN]�����ַ
//          pKey[IN]������
//          pSnr[IN]����Ƭ���кţ�4�ֽ�
//��    ��: �ɹ�����MI_OK
//******************************************************************/
char PcdAuthState(unsigned char auth_mode,unsigned char addr,
                  unsigned char *pKey,unsigned char *pSnr    )
{
    char status;
    unsigned int  unLen;
    unsigned char i,ucComMF522Buf[MAXRLEN]; 

    ucComMF522Buf[0] = auth_mode;
    ucComMF522Buf[1] = addr;
    for (i=0; i<6; i++)
    {    ucComMF522Buf[i+2] = *(pKey+i);   }
    for (i=0; i<6; i++)
    {    ucComMF522Buf[i+8] = *(pSnr+i);   }
    
    status = PcdComMF522(PCD_AUTHENT,ucComMF522Buf,12,ucComMF522Buf,&unLen);
    if ((status != MI_OK) || (!(ReadRawRC(Status2Reg) & 0x08)))
    {   status = MI_ERR;   }
    
    return status;
}

//******************************************************************/
//��    �ܣ���ȡM1��һ������
//����˵��: addr[IN]�����ַ
//          pData[OUT]�����������ݣ�16�ֽ�
//��    ��: �ɹ�����MI_OK
//******************************************************************/
char PcdRead(unsigned char addr,unsigned char *pData)
{
    char status                                          ;
    unsigned int  unLen                                  ;
    unsigned char i,ucComMF522Buf[MAXRLEN]               ; 

    ucComMF522Buf[0] = PICC_READ                         ;
    ucComMF522Buf[1] = addr                              ;
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2])       ;   
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,
                         ucComMF522Buf,&unLen           );
    if ((status == MI_OK) && (unLen == 0x90))
    {
        for (i=0; i<16; i++)
            *(pData+i) = ucComMF522Buf[i];   
    }
    else
      status = MI_ERR;       
    return status;
}

//******************************************************************/
//��    �ܣ���ȡM1��һ������
//����˵��: addr[IN]�����ַ
//          pData[OUT]�����������ݣ�16�ֽ�
//��    ��: �ɹ�����MI_OK
//******************************************************************/
char Read_Block(unsigned char Block,unsigned char *Buf)
{
  char result                                             ;
  result = PcdAuthState(0x60,Block,Password_Buffer,UID)   ;
  if(result!=MI_OK)
    return result                                         ;
  result = PcdRead(Block,Buf)                             ;
//  return result; // 2011.01.03
  
  if(result!=MI_OK)     return   result                   ;
  if(Block!=0x00&&des_on)
  {
//    Des_Decrypt((char *)Buf    ,KK,(char *)Buf    )       ;
//    Des_Decrypt((char *)&Buf[8],KK,(char *)&Buf[8])       ;  
  }
  return SUCCESS                                          ; 
}

//******************************************************************/
//��    �ܣ�д���ݵ�M1��һ��
//����˵��: addr[IN]�����ַ
//          pData[IN]��д������ݣ�16�ֽ�
//��    ��: �ɹ�����MI_OK
//******************************************************************/
char PcdWrite(unsigned char addr,unsigned char *pData)
{
  char status                                             ;
  unsigned int  unLen                                     ;
  unsigned char i,ucComMF522Buf[MAXRLEN]                  ; 
    
  ucComMF522Buf[0] = PICC_WRITE                           ;
  ucComMF522Buf[1] = addr                                 ;
  CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2])          ;
  status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,
                       ucComMF522Buf,&unLen          )    ;
  if(  ( status != MI_OK)||(unLen != 4)
     ||((ucComMF522Buf[0]&0x0F)!= 0x0A))
    status = MI_ERR                                       ;           
  if (status == MI_OK)
  {
    for (i=0; i<16; i++)
      ucComMF522Buf[i] = *(pData+i)                       ;  
    CalulateCRC(ucComMF522Buf,16,&ucComMF522Buf[16])      ;
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,
                         18,ucComMF522Buf,&unLen     )    ;
    if(  (status != MI_OK)||(unLen != 4 )
       ||((ucComMF522Buf[0]&0x0F)!= 0x0A))
      status = MI_ERR                                     ;   
  }    
  return status                                           ;
}
//******************************************************************/
//��    �ܣ�д���ݵ�M1��һ��
//����˵��: addr[IN]�����ַ
//          pData[IN]��д������ݣ�16�ֽ�
//��    ��: �ɹ�����MI_OK
//******************************************************************/

char Write_Block(unsigned char Block)
{
  char result                                             ;
  if(des_on)
  {
//    Des_Encrypt((char *)RF_Buffer    ,KK,
//                (char *)RF_Buffer        )                ;// for debug
//    Des_Encrypt((char *)&RF_Buffer[8],KK,
//                (char *)&RF_Buffer[8]    )                ;// for debug  
  }
  result = PcdAuthState(0x60,Block,Password_Buffer,UID)   ;
  if(result!=MI_OK)
    return result                                         ;  
  result = PcdWrite(Block,RF_Buffer)                      ;
  return result                                           ;  
}

//******************************************************************/
//��    �ܣ��ۿ�ͳ�ֵ
//����˵��: dd_mode[IN]��������
//               0xC0 = �ۿ�
//               0xC1 = ��ֵ
//          addr[IN]��Ǯ����ַ
//          pValue[IN]��4�ֽ���(��)ֵ����λ��ǰ
//��    ��: �ɹ�����MI_OK
//******************************************************************/
char PcdValue(unsigned char dd_mode,unsigned char addr,unsigned char *pValue)
{
    char status;
    unsigned int  unLen;
    unsigned char i,ucComMF522Buf[MAXRLEN]; 
    
    ucComMF522Buf[0] = dd_mode;
    ucComMF522Buf[1] = addr;
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

    if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {   status = MI_ERR;   }
        
    if (status == MI_OK)
    {
        for (i=0; i<16; i++)
        {    ucComMF522Buf[i] = *(pValue+i);   }
        CalulateCRC(ucComMF522Buf,4,&ucComMF522Buf[4]);
        unLen = 0;
        status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,6,ucComMF522Buf,&unLen);
        if (status != MI_ERR)
        {    status = MI_OK;    }
    }
    
    if (status == MI_OK)
    {
        ucComMF522Buf[0] = PICC_TRANSFER;
        ucComMF522Buf[1] = addr;
        CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]); 
   
        status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

        if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
        {   status = MI_ERR;   }
    }
    return status;
}

//******************************************************************/
//��    �ܣ�����Ǯ��
//����˵��: sourceaddr[IN]��Դ��ַ
//          goaladdr[IN]��Ŀ���ַ
//��    ��: �ɹ�����MI_OK
//******************************************************************/
char PcdBakValue(unsigned char sourceaddr, unsigned char goaladdr)
{
    char status;
    unsigned int  unLen;
    unsigned char ucComMF522Buf[MAXRLEN]; 

    ucComMF522Buf[0] = PICC_RESTORE;
    ucComMF522Buf[1] = sourceaddr;
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

    if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {   status = MI_ERR;   }
    
    if (status == MI_OK)
    {
        ucComMF522Buf[0] = 0;
        ucComMF522Buf[1] = 0;
        ucComMF522Buf[2] = 0;
        ucComMF522Buf[3] = 0;
        CalulateCRC(ucComMF522Buf,4,&ucComMF522Buf[4]);
 
        status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,6,ucComMF522Buf,&unLen);
        if (status != MI_ERR)
        {    status = MI_OK;    }
    }
    
    if (status != MI_OK)
    {    return MI_ERR;   }
    
    ucComMF522Buf[0] = PICC_TRANSFER;
    ucComMF522Buf[1] = goaladdr;

    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

    if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {   status = MI_ERR;   }

    return status;
}


//******************************************************************/
//��    �ܣ����Ƭ��������״̬
//��    ��: �ɹ�����MI_OK
//******************************************************************/
char PcdHalt(void)
{
    char status;
    unsigned int  unLen;
    unsigned char ucComMF522Buf[MAXRLEN]; 

    ucComMF522Buf[0] = PICC_HALT;
    ucComMF522Buf[1] = 0;
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);
    return status;
//    return MI_OK;
}

//******************************************************************/
//��    �ܣ����Ƭ��������״̬
//��    ��: �ɹ�����MI_OK
//******************************************************************/
char MIF_Halt(void)
{
    char status;
    unsigned int  unLen;
    unsigned char ucComMF522Buf[MAXRLEN]; 

    ucComMF522Buf[0] = PICC_HALT;
    ucComMF522Buf[1] = 0;
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);
    return status ;  
//    return MI_OK;
}



//******************************************************************/
//��MF522����CRC16����
//******************************************************************/
void CalulateCRC(unsigned char *pIndata,unsigned char len,unsigned char *pOutData)
{
    unsigned char i,n;
    ClearBitMask(DivIrqReg,0x04);
    WriteRawRC(CommandReg,PCD_IDLE);
    SetBitMask(FIFOLevelReg,0x80);
    for (i=0; i<len; i++)
    {   WriteRawRC(FIFODataReg, *(pIndata+i));   }
    WriteRawRC(CommandReg, PCD_CALCCRC);
    i = 0xFF;
    do 
    {
        n = ReadRawRC(DivIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x04));
    pOutData[0] = ReadRawRC(CRCResultRegL);
    pOutData[1] = ReadRawRC(CRCResultRegM);
}



void DisplayConfigMenu(void);
void tochar(uchar id);


unsigned char UID[5],Temp[4]                                       ;
unsigned char RF_Buffer[18]                                        ;
unsigned char Password_Buffer[6]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}   ; // Mifare One ȱʡ����

char          MBRX[30]                                             ;
char          MBKeyTP[30]                                          ;
char          Event                                                ;
static unsigned char DISP_MODE,i                                            ; // �༭�ؼ���ʾģʽ
unsigned char des_on       = 0                                     ; // DES���ܱ�־
void Key_TP_Task(void)                                             ;

//***************************************************************************//


void Delay1(unsigned int time)
{
  unsigned int i,k                             ;
  for(i=0;i<255;i++)
    for(k=0;k<time;k++);
}
extern void PutString0(uchar *ptr);

void Auto_Reader(void)
{
//  while(1)
//  {
    if(PcdRequest(0x52,Temp)==MI_OK)
    {
      if(Temp[0]==0x04&&Temp[1]==0x00)  
          PutString("MFOne-S50");
        else if(Temp[0]==0x02&&Temp[1]==0x00)
          PutString("MFOne-S70");
        else if(Temp[0]==0x44&&Temp[1]==0x00)
          PutString("MF-UltraLight");
        else if(Temp[0]==0x08&&Temp[1]==0x00)
          PutString("MF-Pro");
        else if(Temp[0]==0x44&&Temp[1]==0x03)
          PutString("MF Desire");
        else
          PutString("Unknown");
      if(PcdAnticoll(UID)==MI_OK)
      { 
        PutString0("Card Id is:");
        tochar(UID[0]);
        tochar(UID[1]);
        tochar(UID[2]);
        tochar(UID[3]);
    while (!USART_GetFlagStatus(HTCFG_USART, USART_FLAG_TXC));
    USART_SendData(HTCFG_USART, '\n');
                        
//        RED_LED_ON                                            ;
//        Delay1(200)                                           ;
//        RED_LED_OFF                                           ;
//        Delay1(200)                                           ;
      }
    }
//  else GRE_LED_OFF                                            ;
//  } 
}

void Find_Card(void)
{
    if(PcdRequest(0x52,Temp)==MI_OK)
    {
      if(Temp[0]==0x04&&Temp[1]==0x00)  
          PutString("MFOne-S50");
        else if(Temp[0]==0x02&&Temp[1]==0x00)
          PutString("MFOne-S70");
        else if(Temp[0]==0x44&&Temp[1]==0x00)
          PutString("MF-UltraLight");
        else if(Temp[0]==0x08&&Temp[1]==0x00)
          PutString("MF-Pro");
        else if(Temp[0]==0x44&&Temp[1]==0x03)
          PutString("MF Desire");
        else
          PutString("Unknown");
        PutString("SUCCESS!");
    }
    else PutString("Faile!");                                             
}

void Init_Port(void)
{
//  P4DIR   =   RF_LPCTL + RF_SS   + RF_SCLK  + RF_DATA_OUT                     ;
//  P2DIR |= BIT0+RF_LPCTL + RF_SS   + RF_SCLK  + RF_DATA_OUT;
//  P1DIR   =   RF_LPCTL + RF_SS   + RF_SCLK  + RF_DATA_OUT                     ;
}
/*******************************************
�������ƣ�HandleConfigMenu
��    �ܣ�����PC�����ú���
��    ����inputvalue--���յ�������PC�����ַ�
����ֵ  ����
********************************************/
void HandleConfigMenu(uchar inputvalue)
{
    switch(toupper(inputvalue)) 
    {
    case 'A':
              Auto_Reader();
              break;
    case 'F':
              Find_Card();
              break;
    default:
//              DisplayConfigMenu();  
    }
}


void CardFunc( void )
{
  PcdReset();//��λRC522
  PcdAntennaOn();//�������߷��� 
  DisplayConfigMenu();
  while(1)
  {
//        Send1Char('>');
//        Send1Char('\n');
      //AP_Uart_Handler();
//        i=Get1Char();
        //HandleConfigMenu(i);
      Auto_Reader();
              WDT_Restart();                    // Reload Counter as WDTV Value        

  }
}