#include "sys.h"
#include "usart.h"
#include "delay.h"
//#include"getmotordata.h"
#include "key.h"	
#include "led.h"
#define GRADE 0 //0:����Ϊ1ul��1������Ϊ10ul 
//#define GRADE 0 //0:����Ϊ1ul��1������Ϊ10ul 
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)//ʹPrintf ӳ�䵽USART�˿����
{      
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); 
    USART_SendData(USART1,(uint8_t)ch);   
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if (EN_USART1_RX|EN_USART2_RX|EN_USART3_RX|EN_USART4_RX)   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART1_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 USART2_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 USART3_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 USART4_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 USART_RX_BUF[USART_REC_LEN];
u8 Com_Table[9]={0xdd,0xee,0x01,0x00,0x02,0xff,0xff,0xfd,0xfe};
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16  USART_RX_STA;
u16 USART1_RX_STA=0;       //����״̬���	  
u16 USART2_RX_STA=0;       //����״̬���
u16 USART3_RX_STA=0;       //����״̬���
u16 USART4_RX_STA=0;       //����״̬���
u8   COM=0;
u32 Weight;	
extern u8   StartFlage;
extern void DEBUG(u16 data);
//extern u8   StartFlage;
//��ʼ��IO ����1 
//bound:������
void uart_init(u32 bound){
    //GPIO�˿�����	 2
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA| RCC_APB2Periph_AFIO, ENABLE);	//ʹ��USART1��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//ʹ��USART1��GPIOAʱ��
	//USART_DeInit(USART3);  //��λ����3
 	USART_DeInit(USART2);  //��λ����2
	USART_DeInit(USART1);  //��λ����1
//	USART_DeInit(UART4);  //��λ����4

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10

	 //USART2_TX   PA.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9
   
    //USART2_RX	  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA3


	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure); //��ʼ������
    
	USART_InitStructure.USART_BaudRate = 9600;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ9λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ    	
	USART_Init(USART2, &USART_InitStructure); //��ʼ������

#if EN_USART1_RX	  //���ʹ���˽���  
   //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
   	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
#endif
	USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 
#if EN_USART2_RX	  //���ʹ���˽���  
   //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
   	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
#endif
	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���
	
#if EN_USART3_RX	  //���ʹ���˽���  
   //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
   	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
#endif
	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���
#if EN_USART4_RX	  //���ʹ���˽���  
   //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
   	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�����ж�
#endif
	USART_Cmd(UART4, ENABLE);                    //ʹ�ܴ��� 

}
// void USART4_SENDString(u8 *string,u16 size)
// {	u8 i;
//    for(i=0;i<size;i++)
//	{
//	   USART_SendData(UART4, string[i]);//�򴮿�2��������
//	  while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//	 delay_us(200);
//	
//	}
// 	 
// }
 void USART1_SENDString(u8 *string,u16 size)
 {	u8 i;
	 USART_GetFlagStatus(USART1,USART_FLAG_TC);
    for(i=0;i<size;i++)
	{
	   USART_SendData(USART1, string[i]);//???2????
	  while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//??????
	  delay_ms(1);
	
	}
 	 
 }
void USART2_SENDString(u8 *string,u16 size)
 {	u8 i;
	 USART_GetFlagStatus(USART2,USART_FLAG_TC);
    for(i=0;i<size;i++)
	{
	   USART_SendData(USART2, string[i]);//�򴮿�2��������
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
	 delay_ms(1);
	
	}
 	 
 }
// void USART3_SENDString(u8 *string,u16 size)
// {	u8 i;
//    for(i=0;i<size;i++)
//	{
//	   USART_SendData(USART3, string[i]);//�򴮿�2��������
//	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//	 delay_us(200);
//	
//	}
// 	 
// }
void USART1_IRQHandler(void)                	//����1�жϷ������
	{u8 Hand[8]={0xaa,0xbb,0x4d,0x4b,0x3d,0x02,0xcc,0xdd};
	 u8  GetData[8]={0xaa,0xbb,0x4d,0x4b,0x3d,0x52,0xcc,0xdd};
	u8 Res;
#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������		
	if((USART1_RX_STA&0x8000)==0)//?????
			{//	 LED2=!LED2;
			  if(USART1_RX_STA&0x2000) //???dd
			  {
				  if(USART1_RX_STA&0x1000)//???EE
					{				
					  	if(USART1_RX_STA&0x4000)//????0xfd
							{
							if(Res!=0xdd)USART1_RX_STA=0;//????,????
							  else {USART1_RX_STA|=0x8000;	}//????? }
							}
						else //????0X0D
							{	
							  if(Res==0xcc)USART1_RX_STA|=0x4000;
							  else
								{
								USART1_RX_BUF[USART1_RX_STA&0XFF]=Res ;
								USART1_RX_STA++;	  
								}
					         }  
					}
	
				  else //????EE
					{	  if( Res==0xbb)USART1_RX_STA|=0x1000;//???EE
					  	  else 	 USART1_RX_STA=0;					  					  
				    }
			   }
			  else
			  {
			   if(Res==0xaa){USART1_RX_STA|=0x2000;}
			   else USART1_RX_STA=0;
			  }

			} 
    if(USART1_RX_STA&0x8000)
			{if((USART1_RX_BUF[0]==0x4d)&&(USART1_RX_BUF[1]==0x4f))//�ж�����
				{ 
				  USART1_SENDString(Hand,8);//���������ź�							
				}
				if((USART1_RX_BUF[0]==0x47)&&(USART1_RX_BUF[1]==0x44))//�ж�ץȡ����
				{
				    if(StartFlage==0)
							{ delay_ms(5);
								COM=1;
							}
							else 
							{
							 COM=0;
				       USART1_SENDString(GetData,8);//�򴮿�2��������						
							}
				}
				USART1_RX_STA=0;
			}
     } 
#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
	OSIntExit();  											 
#endif
}
void USART2_IRQHandler(void)                	//����2�жϷ������  2d 0b 20 20 30 30 30 31 35 34 20 20 20 20 0d 0a
	{
	u8 Res;
#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	  {
			Res =USART_ReceiveData(USART2);//(USART1->DR);	//��ȡ���յ�������
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
				  if(GRADE==0)
				  Weight=(USART2_RX_BUF[3]-0X30)*100000+(USART2_RX_BUF[4]-0X30)*10000+(USART2_RX_BUF[5]-0X30)*1000+(USART2_RX_BUF[7]-0X30)*100+(USART2_RX_BUF[8]-0X30)*10+(USART2_RX_BUF[9]-0X30);
			      else
				  Weight=(USART2_RX_BUF[3]-0X30)*100000+(USART2_RX_BUF[4]-0X30)*10000+(USART2_RX_BUF[5]-0X30)*1000+(USART2_RX_BUF[7]-0X30)*100+(USART2_RX_BUF[8]-0X30)*10;
				 		//	DEBUG(Weight);
						// USART4_SENDString(USART4_RX_BUF,16); //delay_ms(200);
				  			
			} 		 
     }  
#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
	OSIntExit();  											 
#endif
} 
#endif	

