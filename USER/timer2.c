#include "stm32f10x.h"  //������Ҫ��ͷ�ļ�
#include "timer2.h"
#include "config.h"


//200hz  2500  72 
//20hz   2500  720 

void TIM2_Init()
{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//ʹ��TIM4ʱ��
// if(type==16)
// {
//	TIM_TimeBaseInitStructure.TIM_Period=7500-1;   //�Զ�װ��ֵ 
//	TIM_TimeBaseInitStructure.TIM_Prescaler=18-1; //��Ƶϵ��
// }
//  if(type==4)
// {
//	TIM_TimeBaseInitStructure.TIM_Period=7500-1;   //�Զ�װ��ֵ 
//	TIM_TimeBaseInitStructure.TIM_Prescaler=72-1; //��Ƶϵ��
// }
//	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
//	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
//	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
//	
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //������ʱ���ж�
//	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//��ʱ���ж�ͨ��
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	
//	
//	TIM_Cmd(TIM2,DISABLE); //ʹ�ܶ�ʱ��	
}
