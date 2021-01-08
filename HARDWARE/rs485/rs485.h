#ifndef _rs485_H
#define _rs485_H

#include "stm32f10x.h"

extern u8 USART2_RX_BUF[256];  //接收缓存，最大64字节
extern u8 send_feedfoxerr[7];




//模式控制
#define RS485_TX_EN		GPIO_ResetBits(GPIOB,GPIO_Pin_0)	//485模式控制
														 
void RS485_Init(u32 bound);
void TIM4_485_Init(void);
void UartRxMonitor(u8 ms); //串口接收监控
void UartDriver(void); //串口驱动函数void UartRead(u8 *buf, u8 len); //串口接收数据
void RS485_SENDString(uint8_t *string,uint16_t size);
u8 rs485_UartWrite(u8 *buf2 ,u8 len2);  //串口发送数
u8 UartRead(u8 *buf, u8 len) ;



#endif

