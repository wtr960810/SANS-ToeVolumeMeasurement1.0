#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"


#define CH1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)//读取按键0
#define CH2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)//读取按键1

void KEY_Init(void);//IO初始化			    
#endif
