#ifndef __ADC_H_
#define __ADC_H_
#include "MPC5604B_0M27V_0102.h" /* Use proper include file */

void ADC_Init(void);

uint16_t ADC_Value_ch0(void);
uint16_t Get_Adc_Average_ch0(uint8_t times);

uint16_t ADC_Value_ch1(void);
uint16_t Get_Adc_Average_ch1(uint8_t times);

uint16_t ADC_Value_ch2(void);
uint16_t Get_Adc_Average_ch2(uint8_t times);

uint16_t ADC_Value_ch3(void);
uint16_t Get_Adc_Average_ch3(uint8_t times);

uint16_t ADC_Value_ch4(void);
uint16_t Get_Adc_Average_ch4(uint8_t times);

uint16_t ADC_Value_ch5(void);
uint16_t Get_Adc_Average_ch5(uint8_t times);

uint16_t ADC_Value_ch6(void);
uint16_t Get_Adc_Average_ch6(uint8_t times);

uint16_t ADC_Value_ch7(void);
uint16_t Get_Adc_Average_ch7(uint8_t times);

 

#endif

