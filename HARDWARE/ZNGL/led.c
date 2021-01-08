#include "led.h"
#include "exdata_process.h"
#include "hmi_driver.h"

#define OPENTIME     200                        //��������ʱ��2S
#define CLOSETIME    200                        //�ػ�����ʱ��2S
uint8_t Pwrstaflag=0;
uint8_t PWR_count=0;
extern uint8_t Firstop;
uint8_t test_debug[5]={0};

void LED_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA,PD,PC�˿�ʱ��
		
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	    		 //LED1-->PD.3 �˿�����, �������
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	 GPIO_SetBits(GPIOC,GPIO_Pin_14); 						 //PD.3 ����� 
	
}


