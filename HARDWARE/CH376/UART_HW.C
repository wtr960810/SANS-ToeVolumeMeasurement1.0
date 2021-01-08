/********************************** (C) COPYRIGHT ******************************
* File Name          : UART_HW.c
* Author             : WCH
* Version            : 
* Date               : 2014/9/11
* Description        : ch376与stm32连接接口配置及寄存器读写
*******************************************************************************/

#include "globalhead.h"

/* 本例中的硬件连接方式如下(实际应用电路可以参照修改下述定义及子程序) */
/* 单片机的引脚    CH376芯片的引脚
      TXD                  RXD
      RXD                  TXD       
*/

#define	UART_INIT_BAUDRATE	9600	/* 默认通讯波特率9600bps,建议通过硬件引脚设定直接选择更高的CH376的默认通讯波特率 */
//#define	UART_WORK_BAUDRATE	57600	/* 正式通讯波特率57600bps */


#define CH376_PORT			GPIOC
#define CH376_TX_PIN		GPIO_Pin_10
#define CH376_RX_PIN		GPIO_Pin_11

#define CH376_UART			UART4

static void CH376_GPIO_Config(void);
static void CH376_UART_Config(void);

/**
  * Function Name  : CH376_PORT_INIT()
  * Description    : 调试串口初始化
  * Input          : None
  * Return         : None
**/

void CH376_PORT_INIT(void)
{	
	CH376_GPIO_Config();
	CH376_UART_Config();
}

/**
  * Function Name  : xEndCH376Cmd
  * Description    : 结束CH376命令,仅用于SPI接口方式
  * Input          : None
  * Return         : None
  */
//void xEndCH376Cmd(void)  /* 结束CH376命令,仅用于SPI接口方式 */
//{
//	;
//}

/**
  * Function Name  : xWriteCH376Cmd
  * Description    : 向CH376写命令
  * Input          : 命令码
  * Return         : None
  */
void	xWriteCH376Cmd( uint8_t mCmd )  /* 向CH376写命令 */
{
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(CH376_UART, USART_FLAG_TC) == RESET);
	USART_SendData(CH376_UART, SER_SYNC_CODE1);/* 启动操作的第1个串口同步码 */
	while (USART_GetFlagStatus(CH376_UART, USART_FLAG_TC) == RESET);
		
	USART_SendData(CH376_UART, SER_SYNC_CODE2);/* 启动操作的第2个串口同步码 */
	while (USART_GetFlagStatus(CH376_UART, USART_FLAG_TC) == RESET);
	
	USART_ReceiveData(CH376_UART);			/* 清除串口接收，必须做 */
	USART_SendData(CH376_UART, mCmd);/* 串口输出命令码 */
	while (USART_GetFlagStatus(CH376_UART, USART_FLAG_TC) == RESET);
}

/**
  * Function Name  : xWriteCH376Data
  * Description    : 向CH376写数据
  * Input          : 数据
  * Return         : None
  */
void	xWriteCH376Data( uint8_t mData )  /* 向CH376写数据 */
{
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(CH376_UART, USART_FLAG_TC) == RESET);
	USART_SendData(CH376_UART, mData);/* 串口输出 */
	while (USART_GetFlagStatus(CH376_UART, USART_FLAG_TC) == RESET);
}

/**
  * Function Name  : xReadCH376Data
  * Description    : 从CH376读数据
  * Input          : None
  * Return         : 数据
  */
uint8_t	xReadCH376Data( void )  /* 从CH376读数据 */
{
	uint32_t	i;
	
	for ( i = 0; i < 500000; i ++ ) {  /* 计数防止超时 */
		if ( USART_GetFlagStatus(CH376_UART, USART_FLAG_RXNE) ) 				/* 串口接收到 */
		{  			
			return((uint8_t)USART_ReceiveData(CH376_UART));  	/* 串口输入 */
		}
	}
	return( 0 );  /* 不应该发生的情况 */
}	

/**
  * Function Name  : Query376Interrupt()
  * Description    : 查询CH376中断(INT#低电平)
  * Input          : 寄存器地址addr
  * Return         : 寄存器值
  */
uint8_t	Query376Interrupt( void )
{
#ifdef	CH376_INT_WIRE	
	return( CH376_INT_WIRE ? FALSE : TRUE );  /* 如果连接了CH376的中断引脚则直接查询中断引脚 */
#else
	if (USART_GetFlagStatus(CH376_UART, USART_FLAG_RXNE)) {  /* 如果未连接CH376的中断引脚则查询串口中断状态码 */
		return( TRUE );
	}
	else return( FALSE );
#endif
}

uint8_t	mInitCH376Host( void )  /* 初始化CH376 */
{
	uint8_t	res;
	
	CH376_PORT_INIT( );  /* 接口硬件初始化 */
	xWriteCH376Cmd( CMD11_CHECK_EXIST );  /* 测试单片机与CH376之间的通讯接口 */
	xWriteCH376Data( 0x65 );
	res = xReadCH376Data( );
//	xEndCH376Cmd( );  // 异步串口方式不需要
	//u2_printf( "test:%02x \n",res);
	if ( res != 0x9A ) return( ERR_USB_UNKNOWN );  /* 通讯接口不正常,可能原因有:接口连接异常,其它设备影响(片选不唯一),串口波特率,一直在复位,晶振不工作 */
	
#ifdef	UART_WORK_BAUDRATE
	xWriteCH376Cmd( CMD21_SET_BAUDRATE );  /* 设置串口通讯波特率 */
#if		UART_WORK_BAUDRATE >= 6000000/256
	xWriteCH376Data( 0x03 );
	xWriteCH376Data( 256 - 6000000/UART_WORK_BAUDRATE );
#else
	xWriteCH376Data( 0x02 );
	xWriteCH376Data( 256 - 750000/UART_WORK_BAUDRATE );
#endif
	
	SET_WORK_BAUDRATE( );  /* 将单片机切换到正式通讯波特率 */
	res = xReadCH376Data( );
//	xEndCH376Cmd( ); 		// 异步串口方式不需要	
	if ( res != CMD_RET_SUCCESS ) return( ERR_USB_UNKNOWN );  /* 通讯波特率切换失败,建议通过硬件复位CH376后重试 */
#endif

	xWriteCH376Cmd( CMD11_SET_USB_MODE );  /* 设备USB工作模式 */
	xWriteCH376Data( 0x06 );
//	mDelayuS( 20 );  // 异步串口方式不需要
	res = xReadCH376Data( );
	//u2_printf( "mode:%02x \n",res);
//	xEndCH376Cmd( );  // 异步串口方式不需要
	
	if ( res == CMD_RET_SUCCESS ) return( USB_INT_SUCCESS );
	else return( ERR_USB_UNKNOWN );  /* 设置模式错误 */
}


////////  以下是内部函数  ///////////////////////////////////////////

static void CH376_GPIO_Config(void)
{
	GPIO_InitTypeDef ch376_gpio;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	ch376_gpio.GPIO_Pin = CH376_RX_PIN;
	ch376_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	ch376_gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(CH376_PORT, &ch376_gpio);

	ch376_gpio.GPIO_Pin = CH376_TX_PIN;
	ch376_gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(CH376_PORT, &ch376_gpio);
	
	ch376_gpio.GPIO_Pin = GPIO_Pin_1;
	ch376_gpio.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &ch376_gpio);
}

static void CH376_UART_Config(void)
{
	USART_InitTypeDef	ch376_uart4;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	
	ch376_uart4.USART_BaudRate = UART_INIT_BAUDRATE;
	ch376_uart4.USART_WordLength = USART_WordLength_8b;
	ch376_uart4.USART_StopBits = USART_StopBits_1;
	ch376_uart4.USART_Parity = USART_Parity_No;
	ch376_uart4.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	ch376_uart4.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(CH376_UART, &ch376_uart4);
	USART_Cmd(CH376_UART, ENABLE);
}


#ifdef	UART_WORK_BAUDRATE
void	SET_WORK_BAUDRATE( void )  /* 将单片机切换到正式通讯波特率 */
{
//	TL2 = RCAP2L = 0 - 18432000/32/UART_WORK_BAUDRATE; /* 18.432MHz晶振 */
	TL2 = RCAP2L = 0 - 24000000/32/UART_WORK_BAUDRATE; /* 24MHz晶振 */
	RI = 0;
}
#endif



