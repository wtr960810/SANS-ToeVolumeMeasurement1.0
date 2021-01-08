#include "stm32f10x.h"  //包含需要的头文件
#include "timer2.h"
#include "config.h"


//200hz  2500  72 
//20hz   2500  720 

void TIM2_Init()
{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//使能TIM4时钟
// if(type==16)
// {
//	TIM_TimeBaseInitStructure.TIM_Period=7500-1;   //自动装载值 
//	TIM_TimeBaseInitStructure.TIM_Prescaler=18-1; //分频系数
// }
//  if(type==4)
// {
//	TIM_TimeBaseInitStructure.TIM_Period=7500-1;   //自动装载值 
//	TIM_TimeBaseInitStructure.TIM_Prescaler=72-1; //分频系数
// }
//	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
//	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
//	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
//	
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //开启定时器中断
//	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//定时器中断通道
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	
//	
//	TIM_Cmd(TIM2,DISABLE); //使能定时器	
}
