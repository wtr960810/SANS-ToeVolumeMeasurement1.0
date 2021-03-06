/*******************************************************************************

 * * * 文件名称：ch376.c

 * * * 文件说明：CH376芯片 SPI串行连接的硬件抽象层 V1.0

 * * * 创建日期：PowerAVR / 2009-12-19

 * * * 修改日期： 


*******************************************************************************/
#include "stm32f10x.h"
#include "CH376INC.h"
#include "ch376.h"
#include "usart3.h"
#include "usart2.h"
/*****************************************************

 * Name:     mInitCH376Host

 * Function: 初始化CH376

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
u8 mInitCH376Host( void )  
{
 u8 res;
 
 xWriteCH376Cmd( CMD11_CHECK_EXIST );  			/* 测试单片机与CH376之间的通讯接口 */
 xWriteCH376Data( 0x65 );
 res = xReadCH376Data( );
 xEndCH376Cmd( );								// 结束通信测试
 if ( res != 0x9A ) 
 {
  u2_printf("!!!");
 	return( ERR_USB_UNKNOWN );  				/* 通讯接口不正常,可能原因有:接口连接异常,其它设备影响(片选不唯一),串口波特率,一直在复位,晶振不工作 */
 }
 xWriteCH376Cmd( CMD11_SET_USB_MODE );  		/* 设备USB工作模式 */
 xWriteCH376Data( 0x06 );						// 模式代码为0x06,表示切换到已启用的USB主机方式，自动产生SOF包
 mDelayuS( 20 );
 res = xReadCH376Data( );						// 返回操作状态
 xEndCH376Cmd( );							    // 工作模式设置结束

// xWriteCH376Cmd( CMD20_SET_SDO_INT );  			/* 设置SPI的SDO引脚的中断方式 */
// xWriteCH376Data( 0x16 );
// xWriteCH376Data( 0x90 );  						/* SDO引脚在SCS片选无效时兼做中断请求输出 */
// xEndCH376Cmd( );							    // 结束设置SDO引脚方式


 if ( res == CMD_RET_SUCCESS ) 
 	return( USB_INT_SUCCESS );
 else 
 {
	u2_printf("???");
 	return( ERR_USB_UNKNOWN );  				/* 设置模式错误 */
 }	
}
/*****************************************************

 * Name:     CH376_PORT_INIT

 * Function: 初始化CH376的SPI IO！

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
u8 mWaitInterrupt( void ) 
{								/* 等待CH376中断并获取状态,主机端等待操作完成,返回操作状态 */
 while ( Query376Interrupt( ) == FALSE );  		/* 一直等中断 */ 				
 xWriteCH376Cmd( CMD_GET_STATUS );  			/* 产生操作完成中断,获取中断状态 */
 return( xReadCH376Data( ) );
}

/*****************************************************

 * Name:     xWriteCH376Cmd

 * Function: 写命令到CH376去

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
void	xWriteCH376Cmd( u8 mCmd )  /* 向CH376写命令 */
{
	mDelay0_5uS( );
	UART3_SendByte(SER_SYNC_CODE1);
	UART3_SendByte(SER_SYNC_CODE2);
	UART3_SendByte( mCmd );  /* 发出命令码 */


}
/*****************************************************

 * Name:     xWriteCH376Data

 * Function: 写1字节数据到CH376

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
void	xWriteCH376Data( u8 mData )  /* 向CH376写数据 */
{
	UART3_SendByte( mData );
//	mDelay0_5uS( );  /* 确保读写周期大于0.6uS */
}

/*****************************************************

 * Name:     xReadCH376Data

 * Function: 从CH376读取1字节数据

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
u8	xReadCH376Data( void )  /* 从CH376读数据 */
{ u8 res;
//	mDelay0_5uS( );  /* 确保读写周期大于0.6uS */
	res=UART3_ReadByte();
	return res;
}
/*****************************************************

 * Name:     Query376Interrupt

 * Function: 查询CH376中断(INT#低电平)

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
u8	Query376Interrupt( void )
{
 return( GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)? FALSE : TRUE );  			/* 如果未连接CH376的中断引脚则查询兼做中断输出的SDO引脚状态 */
}

/*****************************************************

 * Name:     mDelayuS

 * Function: delay

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
void mDelayuS(u8 us)
{
 while(us--);
}

/*****************************************************

 * Name:     mDelayuS

 * Function: delay

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/

void mDelaymS(u8 ms)
{
 unsigned int i;
 for(;ms>0;ms--)
     for(i=0;i<940;i++);
}

/*****************************************************

 * Name:     mDelayuS

 * Function: delay

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
void	mDelay0_5uS( void )  /* 至少延时0.5uS,根据单片机主频调整 */
{
 u8 i;
 i=20;
 while(i--);
}



