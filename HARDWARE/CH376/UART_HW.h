/********************************** (C) COPYRIGHT ******************************
* File Name          : port.h
* Author             : WCH
* Version            : 
* Date               : 2014/9/1
* Description        :ch438与stm32连接接口配置头文件
*******************************************************************************/

#ifndef _UART_HW
#define _UART_HW

void CH376_PORT_INIT(void);												   	/* CH376接口配置 */
void xWriteCH376Cmd( unsigned char mCmd );					  /* 写CH376命令码 */
void xWriteCH376Data( unsigned char mData );					/* 写CH376数据 */
//void xEndCH376Cmd( void );
unsigned char xReadCH376Data( void );									/* 读CH376数据 */

unsigned char Query376Interrupt( void );
unsigned char mInitCH376Host( void );

#endif
