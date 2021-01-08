#include "delay.h"
#include <string.h>
#include "stm32f10x.h"
#include "config.h"
#include "sys.h"
#include "exdata_process.h"
#include "usart3.h"


/*******************************************************************************
* 函 数 名         : USART3_Init
* 函数功能		   : USART3初始化函数
* 输    入         : bound:波特率
* 输    出         : 无
*******************************************************************************/  

void USART3_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART3时钟
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;	//TX	//串口输出PB10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;		  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB,&GPIO_InitStructure);		/* 初始化串口输入IO */
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;	//RX	   //串口输入PB11
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	    //模拟输入
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	//USART3 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART3, &USART_InitStructure); //初始化串口2
	
	USART_Cmd(USART3, ENABLE);  //使能串口 2
	
	USART_ClearFlag(USART3, USART_FLAG_TC);
		
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启接受中断

	//USART3 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
	
}
			



 void USART3_SENDString(u8 *string,u32 size)
 {	
	 u32 i;
	 USART_GetFlagStatus(USART3,USART_FLAG_TC);
    for(i=0;i<size;i++)
	  {
	   USART_SendData(USART3, string[i]);
	   while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	  }
 }
 
 void U3Send_date(uint8_t INS,uint8_t *buff,uint32_t size)  // INS 指令类型  buff  负载/数据   size  负载长度
 { 
		memcpy(&senddate[0],BEN,sizeof(BEN));												//拷贝通讯头部
		senddate[sizeof(BEN)]=mac_id;                               //加入机器地址
		senddate[sizeof(BEN)+1]=INS;													      //加入指令类型
		memcpy(&senddate[sizeof(BEN)+2],buff,size);						      //加入负载/数据
		memcpy(&senddate[sizeof(BEN)+2+size],OVER,sizeof(OVER));    //拷贝通讯尾部
		USART3_SENDString(senddate,sizeof(BEN)+sizeof(OVER)+2+size);//发送通讯数据
 }
 



 /*-------------------------------------------------*/
/*函数名：串口3 printf函数                         */
/*参  数：char* fmt,...  格式化输出字符串和参数    */
/*返回值：无                                       */
/*-------------------------------------------------*/
#define USART3_TXBUFF_SIZE   256    //定义串口1 发送缓冲区大小 256字节
__align(8) char Usart3_TxBuff[USART3_TXBUFF_SIZE];  

void u3_printf(char* fmt,...) 
{  
	unsigned int i,length;
	
	va_list ap;
	va_start(ap,fmt);
	vsprintf(Usart3_TxBuff,fmt,ap);
	va_end(ap);	
	
	length=strlen((const char*)Usart3_TxBuff);		
	while((USART3->SR&0X40)==0);
	for(i = 0;i < length;i ++)
	{			
		USART1->DR = Usart3_TxBuff[i];
		while((USART3->SR&0X40)==0);	
	}	
}

void UART3_SendByte(u16 Data)
{ 
   EXTI->IMR = 0x00000000;
   while (!(USART3->SR & USART_FLAG_TXE)); 
   USART1->DR = (Data & (uint16_t)0x01FF);         
   EXTI->IMR = 0xfffff;   
}
 

