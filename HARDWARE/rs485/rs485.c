#include "rs485.h"
#include "delay.h"
#include "crc16.h"
#include <string.h>
#include "stm32f10x.h"
#include "code.h"
#include "usart1.h"
#include "config.h"
#include "tb6600.h"
#include "sys.h"

u16 USART2_RX_STA=0;       //����״̬���	 
u8  USART2_RX_BUF[256];     //���ջ���,
u8 send_feedfoxerr[7]={0xaa,0xbb,0xee,0x01,0xcc,0xdd};

/*******************************************************************************
* �� �� ��         : RS485_Init
* ��������		   : USART2��ʼ������
* ��    ��         : bound:������
* ��    ��         : ��
*******************************************************************************/  

void RS485_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
	
	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;	//TX-485	//�������PA2
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;		  //�����������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);		/* ��ʼ����������IO */
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;	//RX-485	   //��������PA3
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	    //ģ������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;	//CS-485
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	   //�������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART2, &USART_InitStructure); //��ʼ������2
	
	USART_Cmd(USART2, ENABLE);  //ʹ�ܴ��� 2
	
	USART_ClearFlag(USART2, USART_FLAG_TC);
		
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//���������ж�

	//Usart2 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);				//Ĭ��Ϊ����ģʽ	
}

void RS485_SENDString(uint8_t *string,uint16_t size)
 {
	 uint8_t i;
	 GPIO_SetBits(GPIOB,GPIO_Pin_0);
	 delay_ms(3);
	 USART_GetFlagStatus(USART2,USART_FLAG_TC);
    for(i=0;i<size;i++)
	  {
	   USART_SendData(USART2, string[i]);
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
	  }
	 GPIO_ResetBits(GPIOB,GPIO_Pin_0);  
 }
							
		
/*******************************************************************************
* �� �� ��         : USART2_IRQHandler
* ��������		   : USART2�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/ 
void USART2_IRQHandler(void)
{
	u8 Res;	 	//�������ݻ������
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
			Res =USART_ReceiveData(USART2);//(USART1->DR);	//��ȡ���յ�������		
	   if((USART2_RX_STA&0x8000)==0)
			{
			  if(USART2_RX_STA&0x2000) 
			  {
				  if(USART2_RX_STA&0x1000)
					{				
					  	if(USART2_RX_STA&0x4000)
							{
							if(Res!=0xdd)USART2_RX_STA=0;
							  else 
									{ USART2_RX_STA|=0x8000;
									  USART2_RX_BUF[USART2_RX_STA&0XFF]=Res ;
					          USART2_RX_STA++;
									}
							}
						else
							{	
							  if(Res==0xcc)
									{
									 USART2_RX_STA|=0x4000;
									 USART2_RX_BUF[USART2_RX_STA&0XFF]=Res ;
					         USART2_RX_STA++;								
									}
							  else
								{
								USART2_RX_BUF[USART2_RX_STA&0XFF]=Res ;
								USART2_RX_STA++;	  
								}
					   }  
					}
	
				  else 
					{	  if( Res==0xbb)
						{ USART2_RX_STA|=0x1000;
							USART2_RX_BUF[USART2_RX_STA&0XFF]=Res ;
					    USART2_RX_STA++;
							
						}
					  	  else 	 USART2_RX_STA=0;					  					  
				    }
			   }
			  else
			  {
			   if(Res==0xaa)
         {USART2_RX_STA|=0x2000;
				  USART2_RX_BUF[USART2_RX_STA&0XFF]=Res ;
					USART2_RX_STA++;				
				 }
			   else USART2_RX_STA=0;
			  }
			} 
    if(USART2_RX_STA&0x8000)
			{
					if(USART2_RX_BUF[3]==0xfa)
				  {
							if(USART2_RX_BUF[4]==codeid||USART2_RX_BUF[4]==0xff)
						{
								
						}
					}
        USART2_RX_STA=0;					
			}
   } 
}
