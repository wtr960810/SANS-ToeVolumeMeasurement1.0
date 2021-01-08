#ifndef _rs485_H
#define _rs485_H

#include "stm32f10x.h"

extern u8 USART2_RX_BUF[256];  //���ջ��棬���64�ֽ�
extern u8 send_feedfoxerr[7];




//ģʽ����
#define RS485_TX_EN		GPIO_ResetBits(GPIOB,GPIO_Pin_0)	//485ģʽ����
														 
void RS485_Init(u32 bound);
void TIM4_485_Init(void);
void UartRxMonitor(u8 ms); //���ڽ��ռ��
void UartDriver(void); //������������void UartRead(u8 *buf, u8 len); //���ڽ�������
void RS485_SENDString(uint8_t *string,uint16_t size);
u8 rs485_UartWrite(u8 *buf2 ,u8 len2);  //���ڷ�����
u8 UartRead(u8 *buf, u8 len) ;



#endif

