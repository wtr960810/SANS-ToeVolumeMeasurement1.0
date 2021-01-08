#include "iwdg.h"



void LSI_RCC_Configuration(void)
{
RCC_LSICmd(ENABLE);//打开LSI
while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY)==RESET);//等待直到LSI稳定
}

void IWDG_Configuration(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);// 打开使能，因为iwdg的寄存器有写保护,必须先写入0x5555，才能操作寄存器
	IWDG_SetPrescaler(IWDG_Prescaler_256);// 独立看门狗使用内部低速振荡器LSI，对LSI进行256分频
	IWDG_SetReload(2500);// 设定独立看门狗计数器的计数值(0x000~0xFFF;0~4095)，复位时间为16s
	IWDG_ReloadCounter();// 重载独立看门狗计数器，向寄存器写入0xAAAA，或者更新计数值
	IWDG_Enable();// 开启看门狗，向寄存器写入0xCCCC即可
}

void IWDG_Init(void)
{
	LSI_RCC_Configuration();
	IWDG_Configuration();
}
