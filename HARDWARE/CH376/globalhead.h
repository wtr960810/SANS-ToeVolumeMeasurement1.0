/********************************** (C) COPYRIGHT ******************************
* File Name          : globalhead.h
* Author             : WCH
* Version            : 
* Date               : 2014/9/11
* Description        : All head files
*******************************************************************************/
#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>

#include "CH376INC.H"

/* ���ӵ�USB����״̬���� */
#define		ERR_USB_UNKNOWN		0xFA	/* δ֪����,��Ӧ�÷��������,����Ӳ�����߳������ */

#define 	CH376_INT_WIRE		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)
#include "UART_HW.h"

extern unsigned char buf[64];
#define		GlobalBuf	buf		/* ���ļ����ӳ�����Ҫ�ṩȫ�ֻ�����,���Ȳ�С��64�ֽ� */

#define		EN_LONG_NAME		1	/* ֧�ֳ��ļ��� */
#include "FILE_SYS.H"
