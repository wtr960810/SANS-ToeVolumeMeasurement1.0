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

/* 附加的USB操作状态定义 */
#define		ERR_USB_UNKNOWN		0xFA	/* 未知错误,不应该发生的情况,需检查硬件或者程序错误 */

#define 	CH376_INT_WIRE		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)
#include "UART_HW.h"

extern unsigned char buf[64];
#define		GlobalBuf	buf		/* 长文件名子程序需要提供全局缓冲区,长度不小于64字节 */

#define		EN_LONG_NAME		1	/* 支持长文件名 */
#include "FILE_SYS.H"
