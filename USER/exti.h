#ifndef __EXTI_H
#define __EXTI_H	 
#include "stm32f10x.h"

extern uint8_t opes;
extern uint8_t key_flag;
void EXTI15_Init(void);	//�ⲿ�жϳ�ʼ��	
void EXTI8_Init(void);	
void EXTI_COUNT_Init(void);
void EXTI_WARK_Init(void);
void EXTI_WARK_DISABLE(void);
void EXTI_COUNT_DISABLE(void);
void EXTI_WARK1_Init(void);
#endif
