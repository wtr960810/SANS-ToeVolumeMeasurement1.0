#include "delay.h"
#include <string.h>
#include "stm32f10x.h"
#include "config.h"
#include "sys.h"
	
#define GRADE 0 //0:精度为1ul；1：精度为10ul 
u32 Weight;
u16 USART2_RX_STA=0;       //接收状态标记	 
u8  USART2_RX_BUF[256];     //接收缓冲,
u8 send_feedfoxerr[7]={0xaa,0xbb,0xee,0x01,0xcc,0xdd};
uint8_t iReceiveFlag = 0;
extern int timing;
/*******************************************************************************
* 函 数 名         : USART2_Init
* 函数功能		   : USART2初始化函数
* 输    入         : bound:波特率
* 输    出         : 无
*******************************************************************************/  

void USART2_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_AFIO, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //使能GPIOA时钟
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
	
	 //USART2_TX   PA.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9
   
    //USART2_RX	  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA3

  
	//USART2 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为9位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式    	
	USART_Init(USART2, &USART_InitStructure); //初始化串口
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
	
	
	USART_Cmd(USART2, ENABLE);  //使能串口 2
	
	USART_ClearFlag(USART2, USART_FLAG_TC);
}

	
/*******************************************************************************
* 函 数 名         : USART2_IRQHandler
* 函数功能		   : USART2中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/ 
void USART2_IRQHandler(void)                	//串口2中断服务程序  2d 0b 20 20 30 30 30 31 35 34 20 20 20 20 0d 0a
{
	u8 Res;
#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	  {
			
			Res = USART_ReceiveData(USART2);//(USART1->DR);	//读取接收到的数据
		if((USART2_RX_STA&0x8000)==0)//接收未完成
			{
			if(USART2_RX_STA&0x4000)//接收到了0x0d
				{
					if(Res!=0x0a)
					{	
					    USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
						  USART2_RX_STA++;
					
					}
					else
					{ 	
					   USART2_RX_STA|=0x8000;	//接收完成了
					   USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
					   USART2_RX_STA++;
					}
				}
			else //还没收到0X0D
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
#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
	OSIntExit();  											 
#endif
} 


