/********************************** (C) COPYRIGHT ******************************
* File Name          : UART_HW.c
* Author             : WCH
* Version            : 
* Date               : 2014/9/11
* Description        : ch376��stm32���ӽӿ����ü��Ĵ�����д
*******************************************************************************/

#include "globalhead.h"

/* �����е�Ӳ�����ӷ�ʽ����(ʵ��Ӧ�õ�·���Բ����޸��������弰�ӳ���) */
/* ��Ƭ��������    CH376оƬ������
      TXD                  RXD
      RXD                  TXD       
*/

#define	UART_INIT_BAUDRATE	9600	/* Ĭ��ͨѶ������9600bps,����ͨ��Ӳ�������趨ֱ��ѡ����ߵ�CH376��Ĭ��ͨѶ������ */
//#define	UART_WORK_BAUDRATE	57600	/* ��ʽͨѶ������57600bps */


#define CH376_PORT			GPIOC
#define CH376_TX_PIN		GPIO_Pin_10
#define CH376_RX_PIN		GPIO_Pin_11

#define CH376_UART			UART4

static void CH376_GPIO_Config(void);
static void CH376_UART_Config(void);

/**
  * Function Name  : CH376_PORT_INIT()
  * Description    : ���Դ��ڳ�ʼ��
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
  * Description    : ����CH376����,������SPI�ӿڷ�ʽ
  * Input          : None
  * Return         : None
  */
//void xEndCH376Cmd(void)  /* ����CH376����,������SPI�ӿڷ�ʽ */
//{
//	;
//}

/**
  * Function Name  : xWriteCH376Cmd
  * Description    : ��CH376д����
  * Input          : ������
  * Return         : None
  */
void	xWriteCH376Cmd( uint8_t mCmd )  /* ��CH376д���� */
{
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(CH376_UART, USART_FLAG_TC) == RESET);
	USART_SendData(CH376_UART, SER_SYNC_CODE1);/* ���������ĵ�1������ͬ���� */
	while (USART_GetFlagStatus(CH376_UART, USART_FLAG_TC) == RESET);
		
	USART_SendData(CH376_UART, SER_SYNC_CODE2);/* ���������ĵ�2������ͬ���� */
	while (USART_GetFlagStatus(CH376_UART, USART_FLAG_TC) == RESET);
	
	USART_ReceiveData(CH376_UART);			/* ������ڽ��գ������� */
	USART_SendData(CH376_UART, mCmd);/* ������������� */
	while (USART_GetFlagStatus(CH376_UART, USART_FLAG_TC) == RESET);
}

/**
  * Function Name  : xWriteCH376Data
  * Description    : ��CH376д����
  * Input          : ����
  * Return         : None
  */
void	xWriteCH376Data( uint8_t mData )  /* ��CH376д���� */
{
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(CH376_UART, USART_FLAG_TC) == RESET);
	USART_SendData(CH376_UART, mData);/* ������� */
	while (USART_GetFlagStatus(CH376_UART, USART_FLAG_TC) == RESET);
}

/**
  * Function Name  : xReadCH376Data
  * Description    : ��CH376������
  * Input          : None
  * Return         : ����
  */
uint8_t	xReadCH376Data( void )  /* ��CH376������ */
{
	uint32_t	i;
	
	for ( i = 0; i < 500000; i ++ ) {  /* ������ֹ��ʱ */
		if ( USART_GetFlagStatus(CH376_UART, USART_FLAG_RXNE) ) 				/* ���ڽ��յ� */
		{  			
			return((uint8_t)USART_ReceiveData(CH376_UART));  	/* �������� */
		}
	}
	return( 0 );  /* ��Ӧ�÷�������� */
}	

/**
  * Function Name  : Query376Interrupt()
  * Description    : ��ѯCH376�ж�(INT#�͵�ƽ)
  * Input          : �Ĵ�����ַaddr
  * Return         : �Ĵ���ֵ
  */
uint8_t	Query376Interrupt( void )
{
#ifdef	CH376_INT_WIRE	
	return( CH376_INT_WIRE ? FALSE : TRUE );  /* ���������CH376���ж�������ֱ�Ӳ�ѯ�ж����� */
#else
	if (USART_GetFlagStatus(CH376_UART, USART_FLAG_RXNE)) {  /* ���δ����CH376���ж��������ѯ�����ж�״̬�� */
		return( TRUE );
	}
	else return( FALSE );
#endif
}

uint8_t	mInitCH376Host( void )  /* ��ʼ��CH376 */
{
	uint8_t	res;
	
	CH376_PORT_INIT( );  /* �ӿ�Ӳ����ʼ�� */
	xWriteCH376Cmd( CMD11_CHECK_EXIST );  /* ���Ե�Ƭ����CH376֮���ͨѶ�ӿ� */
	xWriteCH376Data( 0x65 );
	res = xReadCH376Data( );
//	xEndCH376Cmd( );  // �첽���ڷ�ʽ����Ҫ
	//u2_printf( "test:%02x \n",res);
	if ( res != 0x9A ) return( ERR_USB_UNKNOWN );  /* ͨѶ�ӿڲ�����,����ԭ����:�ӿ������쳣,�����豸Ӱ��(Ƭѡ��Ψһ),���ڲ�����,һֱ�ڸ�λ,���񲻹��� */
	
#ifdef	UART_WORK_BAUDRATE
	xWriteCH376Cmd( CMD21_SET_BAUDRATE );  /* ���ô���ͨѶ������ */
#if		UART_WORK_BAUDRATE >= 6000000/256
	xWriteCH376Data( 0x03 );
	xWriteCH376Data( 256 - 6000000/UART_WORK_BAUDRATE );
#else
	xWriteCH376Data( 0x02 );
	xWriteCH376Data( 256 - 750000/UART_WORK_BAUDRATE );
#endif
	
	SET_WORK_BAUDRATE( );  /* ����Ƭ���л�����ʽͨѶ������ */
	res = xReadCH376Data( );
//	xEndCH376Cmd( ); 		// �첽���ڷ�ʽ����Ҫ	
	if ( res != CMD_RET_SUCCESS ) return( ERR_USB_UNKNOWN );  /* ͨѶ�������л�ʧ��,����ͨ��Ӳ����λCH376������ */
#endif

	xWriteCH376Cmd( CMD11_SET_USB_MODE );  /* �豸USB����ģʽ */
	xWriteCH376Data( 0x06 );
//	mDelayuS( 20 );  // �첽���ڷ�ʽ����Ҫ
	res = xReadCH376Data( );
	//u2_printf( "mode:%02x \n",res);
//	xEndCH376Cmd( );  // �첽���ڷ�ʽ����Ҫ
	
	if ( res == CMD_RET_SUCCESS ) return( USB_INT_SUCCESS );
	else return( ERR_USB_UNKNOWN );  /* ����ģʽ���� */
}


////////  �������ڲ�����  ///////////////////////////////////////////

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
void	SET_WORK_BAUDRATE( void )  /* ����Ƭ���л�����ʽͨѶ������ */
{
//	TL2 = RCAP2L = 0 - 18432000/32/UART_WORK_BAUDRATE; /* 18.432MHz���� */
	TL2 = RCAP2L = 0 - 24000000/32/UART_WORK_BAUDRATE; /* 24MHz���� */
	RI = 0;
}
#endif


