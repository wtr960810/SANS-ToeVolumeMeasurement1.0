#ifndef __AD1232_H
#define __AD1232_H 			   
#include "sys.h"  

/************************
PA4=ADS1 PDWN
PA5=ADS1 SCLK
PA6=ADS1 RDY
************************/

#define ADS1_PDWN PAout(4)	
#define ADS1_SCLK PAout(5)	
//#define ADS1_RDY  PAin(6)	

#define ADS1_PDWN_H 			  GPIO_SetBits(GPIOA,GPIO_Pin_4)    
#define ADS1_PDWN_L				  GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define ADS1_SCLK_H					GPIO_SetBits(GPIOA,GPIO_Pin_5)    
#define ADS1_SCLK_L 				GPIO_ResetBits(GPIOA,GPIO_Pin_5) 

#define ADS1_RDY            GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6) 

#define codenum_max 30

#define NEGATIVE 0x800000

#define Zero_drift  126320


typedef struct _AD1232_MSG
{
  int Max;
  int	Min;
	
}ADS1232_MSG;

void ADS1232_Init(void);
int read_ADS1232(uint8_t calibit);
void adc_atvice(void);
int adc_convrt(void);

#endif
