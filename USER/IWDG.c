#include "iwdg.h"



void LSI_RCC_Configuration(void)
{
RCC_LSICmd(ENABLE);//��LSI
while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY)==RESET);//�ȴ�ֱ��LSI�ȶ�
}

void IWDG_Configuration(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);// ��ʹ�ܣ���Ϊiwdg�ļĴ�����д����,������д��0x5555�����ܲ����Ĵ���
	IWDG_SetPrescaler(IWDG_Prescaler_256);// �������Ź�ʹ���ڲ���������LSI����LSI����256��Ƶ
	IWDG_SetReload(2500);// �趨�������Ź��������ļ���ֵ(0x000~0xFFF;0~4095)����λʱ��Ϊ16s
	IWDG_ReloadCounter();// ���ض������Ź�����������Ĵ���д��0xAAAA�����߸��¼���ֵ
	IWDG_Enable();// �������Ź�����Ĵ���д��0xCCCC����
}

void IWDG_Init(void)
{
	LSI_RCC_Configuration();
	IWDG_Configuration();
}
