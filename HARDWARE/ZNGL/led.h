#ifndef __LED_H
#define __LED_H	 
#include "sys.h"


#define key1 PCin(6)	// Pc6
#define LED0 PCout(15)	// Pc15



#define PWR_ctrl   PAout(1) //电池电路导通控制
#define Vbus_sta    PAin(3) //充电电路接入标志
#define Vout_sta    PAin(2) //开机按下检测



extern uint8_t Pwrstaflag;
extern uint8_t PWR_count;

void LED_Init(void);//初始化
void KEY_Init(void);
void Get_Powersta(void);


		 				    
#endif
