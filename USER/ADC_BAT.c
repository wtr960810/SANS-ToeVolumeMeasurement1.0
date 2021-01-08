#include "sys.h"
#include "delay.h"
#include "ADC_BAT.h"
#include "stm32f10x_adc.h"
#include "led.h"
uint8_t bat_val=50;  //������
uint8_t batty_flag;
uint8_t test_batty_flag;
uint16_t batty_count;
uint16_t batty_electr=0;
uint16_t test_bat=0;


/***********************
ADC��ʼ������
*************************/
void  Adc_BAT_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

//PC01 ��Ϊģ��ͨ����������  
	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	

	ADC_DeInit(ADC1);  //��λADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}				  
//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(uint8_t ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

/****************************************
���룺ADC�ɼ�ͨ������ֵ�˲�����TIMES
���أ�12 BIT ADC�ɼ�����
���ܣ��ɼ��ض�ADCͨ��ADCֵ(0-4095) ���˲�
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
���룺��
���أ���ص����ٷֱ�
���ܣ��ɼ���ص�ѹ�������ص����ٷֱ���
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
				if(bat_v<bat_val) bat_val=bat_v;  //�ǳ��ʱֻ�½���ֹ����
			}
			
		 return  bat_val;
}

/****************************************
���룺��
���أ���ص���
���ܣ��ɼ���ص�ѹ,���ݵ�ѹ���������ʾ
0�� �յ� �ո��ʾ
1�� �͵���
2�� �е͵���
3�� �еȵ���
4�� �������
5�� ��������������
****************************************/
uint16_t Get_bat_v(void)
{
	int16_t val;
	val=Get_bat_val();
	test_bat=val;
	if(Vbus_sta) 
	{
		val-=50; //��ȥ������
		if(test_bat==120) 
			return 6;
	}
	if(val<=0)   val=0;   //������	
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

