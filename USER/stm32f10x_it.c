/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "config.h"
#include "delay.h"
#include "AD1232.h"
#include "hw_config.h"
#include "cmd_queue.h"
#include "ADC_BAT.h"
#include "exdata_process.h"
#include "led.h"

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)     		             	
		{   			                               
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);    //清除TIM1溢出中断标志 
		}	
}

extern uint8  timerout;
extern uint8  timeroutflag;
uint16_t  timerout_led0;

void TIM3_IRQHandler(void)       //10ms
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		{   
			timerout++;
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
		}	
}
void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
		{  	  
			TIM_ClearITPendingBit(TIM1, TIM_IT_Update); 
		}	
}

void EXTI0_IRQHandler(void)
{		
	if(EXTI_GetITStatus(EXTI_Line0)==SET)	//是0线的中断
	{  

	}
	EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位	
} 

void EXTI1_IRQHandler(void)
{		
	if(EXTI_GetITStatus(EXTI_Line1)==SET)	//是1线的中断
	{  
    
	}
	EXTI_ClearITPendingBit(EXTI_Line1);  //清除EXTI1线路挂起位	
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		  uint8_t data = USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
	    queue_push(data);
    } 
}


void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
