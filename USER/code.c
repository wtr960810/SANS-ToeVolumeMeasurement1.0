#include "code.h"
#include "usart1.h"

uint8_t codeid;

void CODE_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;	    		 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //…œ¿≠ ‰»Î
	 GPIO_Init(GPIOB, &GPIO_InitStructure);	   
}

void READ_CODE(void)
{
  codeid= GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)|(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)<<1)
	|(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)<<2)|(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)<<3);
	u1_printf("code num is %d \r\n",codeid);
}

