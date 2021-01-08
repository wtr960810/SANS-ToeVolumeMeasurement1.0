#ifndef __TB6600_H
#define __TB6600_H	 
#include "sys.h"

#define tq_off 					GPIO_SetBits(GPIOA,GPIO_Pin_4)    
#define tq_on 				  GPIO_ResetBits(GPIOA,GPIO_Pin_4) 
#define clk_up 					GPIO_SetBits(GPIOA,GPIO_Pin_5)    
#define clk_down 				GPIO_ResetBits(GPIOA,GPIO_Pin_5) 
#define motor_disable 	GPIO_SetBits(GPIOA,GPIO_Pin_6)    
#define motor_enable 		GPIO_ResetBits(GPIOA,GPIO_Pin_6)  
#define dir_cw 					GPIO_SetBits(GPIOA,GPIO_Pin_7)    
#define dir_ccw 				GPIO_ResetBits(GPIOA,GPIO_Pin_7)  

#define clk PAout(5)	// PA5


void TB6600_Init(void);
void MOTOR_ON(void);
void MOTOR_OFF(void);
		 				    
#endif

