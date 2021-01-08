/********************************** (C) COPYRIGHT ******************************
* File Name          : port.h
* Author             : WCH
* Version            : 
* Date               : 2014/9/1
* Description        :ch438��stm32���ӽӿ�����ͷ�ļ�
*******************************************************************************/

#ifndef _UART_HW
#define _UART_HW

void CH376_PORT_INIT(void);												   	/* CH376�ӿ����� */
void xWriteCH376Cmd( unsigned char mCmd );					  /* дCH376������ */
void xWriteCH376Data( unsigned char mData );					/* дCH376���� */
//void xEndCH376Cmd( void );
unsigned char xReadCH376Data( void );									/* ��CH376���� */

unsigned char Query376Interrupt( void );
unsigned char mInitCH376Host( void );

#endif
