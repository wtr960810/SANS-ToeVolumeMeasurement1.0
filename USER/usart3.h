#ifndef _USART3_H
#define _USART3_H

#include "stm32f10x.h"
#include "stdio.h"      //������Ҫ��ͷ�ļ�
#include "stdarg.h"		//������Ҫ��ͷ�ļ� 
#include "string.h"     //������Ҫ��ͷ�ļ�


                


														 
void USART3_Init(u32 bound);
void USART3_SENDString(u8 *string,u32 size);
void U3Send_date(uint8_t INS,uint8_t *buff,uint32_t size);
void UART3_SendByte(u16 Data);
void u3_printf(char* fmt,...) ;
//u8 UartRead(u8 *buf, u8 len) ;


#endif
