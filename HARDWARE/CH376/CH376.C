/*******************************************************************************

 * * * �ļ����ƣ�ch376.c

 * * * �ļ�˵����CH376оƬ SPI�������ӵ�Ӳ������� V1.0

 * * * �������ڣ�PowerAVR / 2009-12-19

 * * * �޸����ڣ� 


*******************************************************************************/
#include "stm32f10x.h"
#include "CH376INC.h"
#include "ch376.h"
#include "usart3.h"
#include "usart2.h"
/*****************************************************

 * Name:     mInitCH376Host

 * Function: ��ʼ��CH376

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
u8 mInitCH376Host( void )  
{
 u8 res;
 
 xWriteCH376Cmd( CMD11_CHECK_EXIST );  			/* ���Ե�Ƭ����CH376֮���ͨѶ�ӿ� */
 xWriteCH376Data( 0x65 );
 res = xReadCH376Data( );
 xEndCH376Cmd( );								// ����ͨ�Ų���
 if ( res != 0x9A ) 
 {
  u2_printf("!!!");
 	return( ERR_USB_UNKNOWN );  				/* ͨѶ�ӿڲ�����,����ԭ����:�ӿ������쳣,�����豸Ӱ��(Ƭѡ��Ψһ),���ڲ�����,һֱ�ڸ�λ,���񲻹��� */
 }
 xWriteCH376Cmd( CMD11_SET_USB_MODE );  		/* �豸USB����ģʽ */
 xWriteCH376Data( 0x06 );						// ģʽ����Ϊ0x06,��ʾ�л��������õ�USB������ʽ���Զ�����SOF��
 mDelayuS( 20 );
 res = xReadCH376Data( );						// ���ز���״̬
 xEndCH376Cmd( );							    // ����ģʽ���ý���

// xWriteCH376Cmd( CMD20_SET_SDO_INT );  			/* ����SPI��SDO���ŵ��жϷ�ʽ */
// xWriteCH376Data( 0x16 );
// xWriteCH376Data( 0x90 );  						/* SDO������SCSƬѡ��Чʱ�����ж�������� */
// xEndCH376Cmd( );							    // ��������SDO���ŷ�ʽ


 if ( res == CMD_RET_SUCCESS ) 
 	return( USB_INT_SUCCESS );
 else 
 {
	u2_printf("???");
 	return( ERR_USB_UNKNOWN );  				/* ����ģʽ���� */
 }	
}
/*****************************************************

 * Name:     CH376_PORT_INIT

 * Function: ��ʼ��CH376��SPI IO��

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
u8 mWaitInterrupt( void ) 
{								/* �ȴ�CH376�жϲ���ȡ״̬,�����˵ȴ��������,���ز���״̬ */
 while ( Query376Interrupt( ) == FALSE );  		/* һֱ���ж� */ 				
 xWriteCH376Cmd( CMD_GET_STATUS );  			/* ������������ж�,��ȡ�ж�״̬ */
 return( xReadCH376Data( ) );
}

/*****************************************************

 * Name:     xWriteCH376Cmd

 * Function: д���CH376ȥ

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
void	xWriteCH376Cmd( u8 mCmd )  /* ��CH376д���� */
{
	mDelay0_5uS( );
	UART3_SendByte(SER_SYNC_CODE1);
	UART3_SendByte(SER_SYNC_CODE2);
	UART3_SendByte( mCmd );  /* ���������� */


}
/*****************************************************

 * Name:     xWriteCH376Data

 * Function: д1�ֽ����ݵ�CH376

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
void	xWriteCH376Data( u8 mData )  /* ��CH376д���� */
{
	UART3_SendByte( mData );
//	mDelay0_5uS( );  /* ȷ����д���ڴ���0.6uS */
}

/*****************************************************

 * Name:     xReadCH376Data

 * Function: ��CH376��ȡ1�ֽ�����

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
u8	xReadCH376Data( void )  /* ��CH376������ */
{ u8 res;
//	mDelay0_5uS( );  /* ȷ����д���ڴ���0.6uS */
	res=UART3_ReadByte();
	return res;
}
/*****************************************************

 * Name:     Query376Interrupt

 * Function: ��ѯCH376�ж�(INT#�͵�ƽ)

 * Input: 	 no

 * Output:   no 

 * Author:   PowerAVR / 2009-12-19

 * Update:   	

*****************************************************/
u8	Query376Interrupt( void )
{
 return( GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)? FALSE : TRUE );  			/* ���δ����CH376���ж��������ѯ�����ж������SDO����״̬ */
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
void	mDelay0_5uS( void )  /* ������ʱ0.5uS,���ݵ�Ƭ����Ƶ���� */
{
 u8 i;
 i=20;
 while(i--);
}


