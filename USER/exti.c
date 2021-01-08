#include "stm32f10x.h"
#include "exti.h"
#include "delay.h"
#include "config.h"
#include "usart1.h"
#include "rs485.h"
#include "tb6600.h"
uint8_t opes;


void EXTI_COUNT_Init(void)
{												  
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_SetBits(GPIOC, GPIO_Pin_1);
	
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);

 	   	 
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�����ж��������飺��2�� �������ȼ���0 1 2 3 �����ȼ���0 1 2 3
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//�����ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���   
}

void EXTI_COUNT_DISABLE(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,DISABLE);
   	 
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�����ж��������飺��2�� �������ȼ���0 1 2 3 �����ȼ���0 1 2 3
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//�����ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���   
}

void EXTI_WARK_Init(void)
{												  
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_0);
	
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

 	   	 
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�����ж��������飺��2�� �������ȼ���0 1 2 3 �����ȼ���0 1 2 3
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//�����ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���   
}


void EXTI_WARK1_Init(void)
{												  
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_1);
	
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);

 	   	 
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�����ж��������飺��2�� �������ȼ���0 1 2 3 �����ȼ���0 1 2 3
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//�����ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���   
}

void EXTI_WARK_DISABLE(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,DISABLE);
   	 
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�����ж��������飺��2�� �������ȼ���0 1 2 3 �����ȼ���0 1 2 3
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//�����ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���   
}

void EXTI15_Init(void)
{												  
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure; 

	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits(GPIOB, GPIO_Pin_15);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource15);//PB15���ж���15
 	   	 
	EXTI_InitStructure.EXTI_Line = EXTI_Line15;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//�����ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���   
}

void EXTI8_Init(void)
{												  
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure; 

	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_8);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);//PB15���ж���15
 	   	 
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//�����ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���   
}


//void EXTI15_10_IRQHandler(void)
//{		 		
//	if(EXTI_GetITStatus(EXTI_Line15)==SET)	//��15�ߵ��ж�
//	{   
//	  countt++;
//		ConfigMsg.TIME1_COUNT+=5;
//		u1_printf("�������£�  %d\r\n",countt);
//		MOTOR_ON();
//	}
//	EXTI_ClearITPendingBit(EXTI_Line15);  //���EXTI15��·����λ						  
//} 

//void EXTI9_5_IRQHandler(void)
//{		 		
//	if(EXTI_GetITStatus(EXTI_Line8)==SET)	//��8�ߵ��ж�
//	{   
//	  MOTOR_OFF();
//		countt=0;
//		ConfigMsg.TIME1_COUNT=5;
//	}
//	EXTI_ClearITPendingBit(EXTI_Line8);  //���EXTI8��·����λ						  
//} 




