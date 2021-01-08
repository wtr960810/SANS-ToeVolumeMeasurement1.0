#include "sys.h"
#include "delay.h"
#include "ADC_BAT.h"
#include "stm32f10x_adc.h"
#include "led.h"
uint8_t bat_val=50;  //防回数
uint8_t batty_flag;
uint8_t test_batty_flag;
uint16_t batty_count;
uint16_t batty_electr=0;
uint16_t test_bat=0;


/***********************
ADC初始化函数
*************************/
void  Adc_BAT_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

//PC01 作为模拟通道输入引脚  
	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	

	ADC_DeInit(ADC1);  //复位ADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}				  
//获得ADC值
//ch:通道值 0~3
u16 Get_Adc(uint8_t ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

/****************************************
输入：ADC采集通道，均值滤波基数TIMES
返回：12 BIT ADC采集数据
功能：采集特定ADC通道ADC值(0-4095) 并滤波
****************************************/
uint16_t Get_Adc_Average(uint8_t ch,uint8_t times)
{
	uint32_t temp_val=0;
	uint32_t bat_cap;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(1);
	}
	if(ch==ADC_Channel_10)
	{
		bat_cap=(temp_val/times);
		return bat_cap;
	}
	else if(ch==ADC_Channel_9)
		{
			bat_cap=(temp_val/times);
			return bat_cap;
		}
		return 0;
} 


float Get_Adc_Averagef(uint8_t ch,uint8_t times)
{
	uint32_t temp_val=0;
	float  bat_cap;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
		bat_cap=((temp_val/times)*0.8)*2/1000;
		return bat_cap;
} 
/****************************************
输入：空
返回：电池电量百分比
功能：采集电池电压，输出电池电量百分比数
****************************************/
uint16_t Get_bat_val(void)
{
	uint16_t bat_v;
	
		bat_v=((Get_Adc_Average(ADC_Channel_10,20)-2050)*100)/400;
		if(bat_v>120) bat_v=120;
//		if(test_batty_flag==0) {bat_val=bat_v; test_batty_flag++; return  bat_val;}
    if(Vbus_sta) 
       bat_val=bat_v;  
		else
			{
				if(bat_v<bat_val) bat_val=bat_v;  //非充电时只下降防止回数
			}
			
		 return  bat_val;
}

/****************************************
输入：空
返回：电池电量
功能：采集电池电压,根据电压计算电量显示
0： 空电 空格表示
1： 低电量
2： 中低电量
3： 中等电量
4： 充足电量
5： 满电量，充电完成
****************************************/
uint16_t Get_bat_v(void)
{
	int16_t val;
	val=Get_bat_val();
	test_bat=val;
	if(Vbus_sta) 
	{
		val-=50; //减去充电误差
		if(test_bat==120) 
			return 6;
	}
	if(val<=0)   val=0;   //防负数	
  if(val>=50)
			return 5;
			else if(val>=25)
				return 4;
				else if(val>=10)
					return 3;
					else if(val>0)
						return 2;
						else
							return 1;
}

