#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"


#define CH1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)//��ȡ����0
#define CH2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)//��ȡ����1

void KEY_Init(void);//IO��ʼ��			    
#endif
