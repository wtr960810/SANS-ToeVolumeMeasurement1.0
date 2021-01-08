#include "rs485.h"
#include "delay.h"
#include "crc16.h"
#include <string.h>
#include "stm32f10x.h"
#include "code.h"
#include "usart1.h"
#include "config.h"
#include "tb6600.h"
#include "sys.h"

u16 USART2_RX_STA=0;       //接收状态标记	 
u8  USART2_RX_BUF[256];     //接收缓冲,
u8 send_feedfoxerr[7]={0xaa,0xbb,0xee,0x01,0xcc,0xdd};

/*******************************************************************************
* 函 数 名         : RS485_Init
* 函数功能		   : USART2初始化函数
* 输    入         : bound:波特率
* 输    出         : 无
*******************************************************************************/  

void RS485_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;	//TX-485	//串口输出PA2
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;		  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);		/* 初始化串口输入IO */
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;	//RX-485	   //串口输入PA3
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	    //模拟输入
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;	//CS-485
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	   //推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//USART2 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART2, &USART_InitStructure); //初始化串口2
	
	USART_Cmd(USART2, ENABLE);  //使能串口 2
	
	USART_ClearFlag(USART2, USART_FLAG_TC);
		
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启接受中断

	//Usart2 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);				//默认为接收模式	
}

void RS485_SENDString(uint8_t *string,uint16_t size)
 {
	 uint8_t i;
	 GPIO_SetBits(GPIOB,GPIO_Pin_0);
	 delay_ms(3);
	 USART_GetFlagStatus(USART2,USART_FLAG_TC);
    for(i=0;i<size;i++)
	  {
	   USART_SendData(USART2, string[i]);
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
	  }
	 GPIO_ResetBits(GPIOB,GPIO_Pin_0);  
 }
							
		
/*******************************************************************************
* 函 数 名         : USART2_IRQHandler
* 函数功能		   : USART2中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/ 
void USART2_IRQHandler(void)
{
	u8 Res;	 	//定义数据缓存变量
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
			Res =USART_ReceiveData(USART2);//(USART1->DR);	//读取接收到的数据		
	   if((USART2_RX_STA&0x8000)==0)
			{
			  if(USART2_RX_STA&0x2000) 
			  {
				  if(USART2_RX_STA&0x1000)
					{				
					  	if(USART2_RX_STA&0x4000)
							{
							if(Res!=0xdd)USART2_RX_STA=0;
							  else 
									{ USART2_RX_STA|=0x8000;
									  USART2_RX_BUF[USART2_RX_STA&0XFF]=Res ;
					          USART2_RX_STA++;
									}
							}
						else
							{	
							  if(Res==0xcc)
									{
									 USART2_RX_STA|=0x4000;
									 USART2_RX_BUF[USART2_RX_STA&0XFF]=Res ;
					         USART2_RX_STA++;								
									}
							  else
								{
								USART2_RX_BUF[USART2_RX_STA&0XFF]=Res ;
								USART2_RX_STA++;	  
								}
					   }  
					}
	
				  else 
					{	  if( Res==0xbb)
						{ USART2_RX_STA|=0x1000;
							USART2_RX_BUF[USART2_RX_STA&0XFF]=Res ;
					    USART2_RX_STA++;
							
						}
					  	  else 	 USART2_RX_STA=0;					  					  
				    }
			   }
			  else
			  {
			   if(Res==0xaa)
         {USART2_RX_STA|=0x2000;
				  USART2_RX_BUF[USART2_RX_STA&0XFF]=Res ;
					USART2_RX_STA++;				
				 }
			   else USART2_RX_STA=0;
			  }
			} 
    if(USART2_RX_STA&0x8000)
			{
					if(USART2_RX_BUF[3]==0xfa)
				  {
							if(USART2_RX_BUF[4]==codeid||USART2_RX_BUF[4]==0xff)
						{
								
						}
					}
        USART2_RX_STA=0;					
			}
   } 
}
