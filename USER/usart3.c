#include "delay.h"
#include <string.h>
#include "stm32f10x.h"
#include "config.h"
#include "sys.h"
#include "exdata_process.h"
#include "usart3.h"


/*******************************************************************************
* �� �� ��         : USART3_Init
* ��������		   : USART3��ʼ������
* ��    ��         : bound:������
* ��    ��         : ��
*******************************************************************************/  

void USART3_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART3ʱ��
	
	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;	//TX	//�������PB10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;		  //�����������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB,&GPIO_InitStructure);		/* ��ʼ����������IO */
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;	//RX	   //��������PB11
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	    //ģ������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	//USART3 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART3, &USART_InitStructure); //��ʼ������2
	
	USART_Cmd(USART3, ENABLE);  //ʹ�ܴ��� 2
	
	USART_ClearFlag(USART3, USART_FLAG_TC);
		
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//���������ж�

	//USART3 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	
}
			



 void USART3_SENDString(u8 *string,u32 size)
 {	
	 u32 i;
	 USART_GetFlagStatus(USART3,USART_FLAG_TC);
    for(i=0;i<size;i++)
	  {
	   USART_SendData(USART3, string[i]);
	   while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	  }
 }
 
 void U3Send_date(uint8_t INS,uint8_t *buff,uint32_t size)  // INS ָ������  buff  ����/����   size  ���س���
 { 
		memcpy(&senddate[0],BEN,sizeof(BEN));												//����ͨѶͷ��
		senddate[sizeof(BEN)]=mac_id;                               //���������ַ
		senddate[sizeof(BEN)+1]=INS;													      //����ָ������
		memcpy(&senddate[sizeof(BEN)+2],buff,size);						      //���븺��/����
		memcpy(&senddate[sizeof(BEN)+2+size],OVER,sizeof(OVER));    //����ͨѶβ��
		USART3_SENDString(senddate,sizeof(BEN)+sizeof(OVER)+2+size);//����ͨѶ����
 }
 



 /*-------------------------------------------------*/
/*������������3 printf����                         */
/*��  ����char* fmt,...  ��ʽ������ַ����Ͳ���    */
/*����ֵ����                                       */
/*-------------------------------------------------*/
#define USART3_TXBUFF_SIZE   256    //���崮��1 ���ͻ�������С 256�ֽ�
__align(8) char Usart3_TxBuff[USART3_TXBUFF_SIZE];  

void u3_printf(char* fmt,...) 
{  
	unsigned int i,length;
	
	va_list ap;
	va_start(ap,fmt);
	vsprintf(Usart3_TxBuff,fmt,ap);
	va_end(ap);	
	
	length=strlen((const char*)Usart3_TxBuff);		
	while((USART3->SR&0X40)==0);
	for(i = 0;i < length;i ++)
	{			
		USART1->DR = Usart3_TxBuff[i];
		while((USART3->SR&0X40)==0);	
	}	
}

void UART3_SendByte(u16 Data)
{ 
   EXTI->IMR = 0x00000000;
   while (!(USART3->SR & USART_FLAG_TXE)); 
   USART1->DR = (Data & (uint16_t)0x01FF);         
   EXTI->IMR = 0xfffff;   
}
 

