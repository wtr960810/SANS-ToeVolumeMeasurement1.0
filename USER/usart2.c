#include "delay.h"
#include <string.h>
#include "stm32f10x.h"
#include "config.h"
#include "sys.h"
	
#define GRADE 0 //0:����Ϊ1ul��1������Ϊ10ul 
u32 Weight;
u16 USART2_RX_STA=0;       //����״̬���	 
u8  USART2_RX_BUF[256];     //���ջ���,
u8 send_feedfoxerr[7]={0xaa,0xbb,0xee,0x01,0xcc,0xdd};
uint8_t iReceiveFlag = 0;
extern int timing;
/*******************************************************************************
* �� �� ��         : USART2_Init
* ��������		   : USART2��ʼ������
* ��    ��         : bound:������
* ��    ��         : ��
*******************************************************************************/  

void USART2_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_AFIO, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
	
	 //USART2_TX   PA.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9
   
    //USART2_RX	  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA3

  
	//USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ9λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ    	
	USART_Init(USART2, &USART_InitStructure); //��ʼ������
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
	
	
	USART_Cmd(USART2, ENABLE);  //ʹ�ܴ��� 2
	
	USART_ClearFlag(USART2, USART_FLAG_TC);
}

	
/*******************************************************************************
* �� �� ��         : USART2_IRQHandler
* ��������		   : USART2�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/ 
void USART2_IRQHandler(void)                	//����2�жϷ������  2d 0b 20 20 30 30 30 31 35 34 20 20 20 20 0d 0a
{
	u8 Res;
#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	  {
			
			Res = USART_ReceiveData(USART2);//(USART1->DR);	//��ȡ���յ�������
		if((USART2_RX_STA&0x8000)==0)//����δ���
			{
			if(USART2_RX_STA&0x4000)//���յ���0x0d
				{
					if(Res!=0x0a)
					{	
					    USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
						  USART2_RX_STA++;
					
					}
					else
					{ 	
					   USART2_RX_STA|=0x8000;	//���������
					   USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
					   USART2_RX_STA++;
					}
				}
			else //��û�յ�0X0D
				{	
					if((Res==0x2d)||(Res==0x2b))
					{   USART2_RX_STA|=0x4000; 	//LED2=!LED2;
					    USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
						USART2_RX_STA++;
					}
				   else
					{
				    	USART2_RX_STA=0;	  
					}		 
				}
			}
			if((USART2_RX_STA&0xff)>16)USART2_RX_STA=0;
			if(USART2_RX_STA&0x8000)
			{
				  USART2_RX_STA=0;
				  if(USART2_RX_BUF[3]==0x20)
				  { 
				    USART2_RX_BUF[3]=0X30;
				   if(USART2_RX_BUF[4]==0x20)USART2_RX_BUF[4]=0X30;
				  }
					
					//iReceiveFlag = !iReceiveFlag;
					timing = 0;
				  if(GRADE==0)
				  {Weight=(USART2_RX_BUF[3]-0X30)*100000+(USART2_RX_BUF[4]-0X30)*10000+(USART2_RX_BUF[5]-0X30)*1000+(USART2_RX_BUF[7]-0X30)*100+(USART2_RX_BUF[8]-0X30)*10+(USART2_RX_BUF[9]-0X30);}
			    else
				  {Weight=(USART2_RX_BUF[3]-0X30)*100000+(USART2_RX_BUF[4]-0X30)*10000+(USART2_RX_BUF[5]-0X30)*1000+(USART2_RX_BUF[7]-0X30)*100+(USART2_RX_BUF[8]-0X30)*10;} 			
						
			}
      		
   }  
#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
	OSIntExit();  											 
#endif
} 


