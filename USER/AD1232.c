#include "sys.h"
#include "AD1232.h"
#include "delay.h"
#include "usart1.h"
#include "hmi_user_uart.h"
#include "cmd_queue.h"
#include "exdata_process.h"
#include "hw_config.h"


#define  Gain_Select  128 
 int MAX,MIN,SUM;
 int adc_v,adc_v1,Middle1;
//static double adc_val;
 int adcode[codenum_max]={0};

ADS1232_MSG  ADS1232Msg;

/*******************
ADS1232初始化函数
********************/


void ADS1232_Init(void)
{
	uint8_t  i=0;
	
	GPIO_InitTypeDef  GPIO_InitStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA
	
	ADS1_PDWN_L;
	ADS1_SCLK_L;
	delay_ms(100);
	ADS1_PDWN_H;
	
	while(ADS1_RDY){;}                    //等待RDY拉高
		
	for(i=0;i<26;i++)                    //offset calibration
		{	
			ADS1_SCLK_H;
			delay_us(2);
			ADS1_SCLK_L;
			delay_us(2);
		}
		
		ADS1232Msg.Max=-8000000;
		ADS1232Msg.Min=8000000;
}



int read_ADS1232(uint8_t calibit)
{
	uint8_t i;
	
	  loop:
	  adc_v=0;
		while(ADS1_RDY){;}                      //等待RDY拉高
		 for(i=0;i<24;i++)                      //读取数据
    {
			ADS1_SCLK_H;
			delay_us(2);
      adc_v = (adc_v<< 1)|(ADS1_RDY);			
			ADS1_SCLK_L;
			delay_us(2);			
    }	
    		
		ADS1_SCLK_H;
		delay_us(2);
		ADS1_SCLK_L;
		delay_us(2);                            //数据校验
		
		adc_v&=0x00ffffff;
		if(adc_v==0xffffffff)
		goto loop;
		if(adc_v&NEGATIVE)                      //判断负值
   {  
		  adc_v|=0xff000000;
		  return adc_v;
   }
			
		return adc_v;

}
/****************************
输入：空
输出：滤波后采集数
功能：均值平滑滤波，输出为原始数据带符号的32位整数
*****************************/

int num_now;
extern uint8_t offset_flag;
extern int X_offset_calibration;
extern int B_offset_calibration;
extern float K_offset_calibration;
int adc_convrt(void)
{
	uint8_t i=0;
	int REG_Value;
	float vel;
  
			REG_Value = read_ADS1232(0);
			num_now=REG_Value;
			SUM=SUM-adcode[codenum_max-1];
			MIN=REG_Value;MAX=REG_Value;
			for(i=codenum_max-1;i>0;i--)//数据存储移位
			{
				Middle1=adcode[i-1];
				if(Middle1>MAX)MAX=Middle1;
				if(Middle1<MIN)MIN=Middle1;
				adcode[i]=Middle1;
			}
			adcode[0]=REG_Value;
			SUM=SUM + REG_Value;
			adc_v1=(SUM-MAX-MIN)/(codenum_max-2);

			//针对传感器的算法
			if(offset_flag==1)
      return adc_v1;
//			if (Gain_Select==128)
//			vel=(adc_v1/10+12770)/5611.25;
//			else if(Gain_Select==64)
//				vel=(adc_v1/10+12770/2)/(5611.25/2);
			//增益不同情况
			//算法待更新
			/**************************
			y=kx+b  
			
			x=(y-b)/k
			
			空置时X=0  读数为b值 
			
			X=I值时 k=(y-b)/I
			得 公式 ----待续。。。
			***************************/
      else 
			vel=((adc_v1-B_offset_calibration)*1.0)/K_offset_calibration;
			adc_v1=vel;              //取克单位	

			return adc_v1;
}

