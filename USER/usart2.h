#ifndef _USART2_H
#define _USART2_H

#include "stm32f10x.h"

extern u8 USART2_RX_BUF[256];  //接收缓存，最大64字节
extern u8 send_feedfoxerr[7];



														 
void USART2_Init(u32 bound);
u8 UartRead(u8 *buf, u8 len) ;



#endif

