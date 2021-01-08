#ifndef __LED_H
#define __LED_H	 
#include "sys.h"


#define key1 PCin(6)	// Pc6
#define LED0 PCout(15)	// Pc15



#define PWR_ctrl   PAout(1) //��ص�·��ͨ����
#define Vbus_sta    PAin(3) //����·�����־
#define Vout_sta    PAin(2) //�������¼��



extern uint8_t Pwrstaflag;
extern uint8_t PWR_count;

void LED_Init(void);//��ʼ��
void KEY_Init(void);
void Get_Powersta(void);


		 				    
#endif
