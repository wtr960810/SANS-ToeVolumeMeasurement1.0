#include "delay.h"
#include "sys.h"
#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "timer1.h"
#include "timer2.h"
#include "timer3.h"
#include "timer4.h"
#include "IWDG.h"
#include "config.h"
#include "AD1232.h"
#include "ADC_BAT.h"
#include "hmi_user_uart.h"
#include "cmd_queue.h"
#include "hw_config.h"
#include "24cxx.h"
#include "w25qxx.h"
#include "spi.h"
#include "led.h"
#include "dht11.h"
#include "exdata_process.h"
#include "ch376inc.h"
#include "FILE_SYS.h"
#include "UART_HW.h"



CONFIG_MSG  ConfigMsg;

 void TIM_Init(void);
 void Hardware_Init(void);
 void Read_Config(void);
 extern uint16_t EX_SUM; 
 extern uint8_t DataOverflowFlag;
 int32_t now_vel=0;                    
 extern uint8_t test_type; 																											 
 extern uint8_t iLanguageType;                           
 extern uint16_t current_screen_id;  
 extern u8 BeepStatus; 
 uint8_t senddate[h_buff_max/2]={0};                            
 uint8_t senddate_size;                                 
 uint8_t BEN[2] ={0xaa,0xbb};                           
 uint8_t OVER[2]={0xcc,0xdd};
 unsigned char buf[64]; 
 
 int main(void)
 {		
  	delay_init();	          
    Hardware_Init();	 
	  TIM_Init();
		Read_Config();
		while(1)
		{
			LCD_HANDLE();
		}	 
 }

 
 void TIM_Init(void)
 {
	 TIM3_Init();
 }
 
 void Hardware_Init(void)
 {
	 USART2_Init(9600);  
	 Interrupts_Config();	 
	 UartInit(115200);	 		
   queue_reset();     		
   delay_ms(300);                    
	 KEY_Init();            
	 LED_Init();            
	 AT24CXX_Init();        
	 W25QXX_Init();		
   DHT11_Init();	 
	 CH376_PORT_INIT();
 }
 
 void Read_Config(void)    
 {
	 u8 num[2] = {0};
	 uint8_t load[32]={0};
	 uint8_t back[1] ={0};
	 uint8_t sound[1] = {0};
	 AT24CXX_Read(0,load,32);
	 AT24CXX_Read(0,num,2);
	 BeepStatus = load[31];
   EX_SUM  =	num[0] << 8;
	 EX_SUM +=  num[1];
	 if(EX_SUM > Ex_Time_Max) EX_SUM=Ex_Time_Max;
	 DataOverflowFlag = load[1];
	 sprintf((char*)back,"%c",(255-(load[7]*2+55)));
	 SetBackLight(back[0]);
	 iLanguageType=load[8];
	 SetLanguage(iLanguageType,0);                 
   sprintf((char*)sound,"%c",(load[10]));
 }
 
 


