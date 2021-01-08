#ifndef __ADC_BAT_H
#define __ADC_BAT_H	
#include "sys.h"






void Adc_BAT_Init(void);
uint16_t Get_Adc_Average(uint8_t ch,uint8_t times);
float Get_Adc_Averagef(uint8_t ch,uint8_t times);
uint16_t Get_bat_val(void);
uint16_t Get_bat_v(void);

extern uint8_t batty_flag;
extern uint16_t batty_count;
extern uint16_t batty_electr;
extern uint16_t test_bat;
#endif

