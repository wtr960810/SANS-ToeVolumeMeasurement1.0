#ifndef _USAR_TFT_
#define _USAR_TFT_
#include "sys.h"


#define errno         0   //״̬NO
#define errok         1   //״̬OK
#define errsta1        2  //״̬1
#define errsta2        3  //״̬2
#define errsta3        4  //״̬3


#define Press_max    5000															   				//��ѹ���5g
#define TIME_100MS   10               												  //100����(10����λ)
#define coel_max     151777                                     //�������ֵ
#define h_code_max   100																  				//�洢���������ֵ
#define h_buff_max   32*1024                                    //�ɼ����ֵ
#define date_addr    1*1024*1024													   		//��ʵ���ݴ洢�׵�ַλ
#define date_max     4*32*1024                                  //�������������

void Usart_tft(void);

void Signle_scan(void);//�źż��
extern uint8_t keys_flag;
extern uint8_t  EX_num_flag;  																																		 //ʵ���¼����־λ
extern uint8_t  EX_num; 

#endif
