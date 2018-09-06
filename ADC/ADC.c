/********************************************************************
*
*ADC����ת����ȡģ��
********************************************************************/

# include "Include.h"

void delayBanking(uint16_t time)
{
	while(time--)
	{
	   asm
   	   {
	      nop;
       }
   	}
}

/************************************************************/
/*                     ��ʼ��ADCת��                        */
/************************************************************/
void ADC_Init(void)
{
  //SIU.PCR[24].R = 0x2000;         /* MPC56xxB: Initialize PB[8] as ANS0  */
  //SIU.PCR[25].R = 0x2000;         /* MPC56xxB: Initialize PB[9] as ANS1 */
  SIU.PCR[26].R = 0x2000;         /* MPC56xxB: Initialize PB[10] as ANS2 */	
  SIU.PCR[27].R = 0x2000;         /* MPC56xxB: Initialize PB[11] as ANS3 */
  SIU.PCR[60].R = 0x2000;         /* MPC56xxB: Initialize PD[12] as ANS4 */	
  SIU.PCR[61].R = 0x2000;         /* MPC56xxB: Initialize PD[13] as ANS5 */
  SIU.PCR[62].R = 0x2000;         /* MPC56xxB: Initialize PD[14] as ANS6 */	
  SIU.PCR[63].R = 0x2000;         /* MPC56xxB: Initialize PD[15] as ANS7 */
  
  ADC.MCR.R = 0x20000000;         /* Initialize ADC0 for scan mode */
 
  ADC.NCMR[1].R = 0x000000FD;     /* Select ANS0:8 inputs for conversion *///ѡ��ANS 0-7��Ϊ����ת����ADC��NCMR�Ĵ���1����
   								  /* �����λADC.NCMR[1].R=0x000000FD ,����ANS0:7ѡ��*/
 
  ADC.CTR[1].R = 0x00008606;      /* Conversion times for 32MHz ADClock *///����ת��Ƶ��
  ADC.MCR.B.NSTART=1;             /* Trigger normal conversions for ADC0 */ //������׼ת�� 	
}
/************************************************************/
/*                     ��ȡͨ��0��ֵ       ANS0 PB[8]       */
/************************************************************/
uint16_t ADC_Value_ch0(void)
{


	while(ADC.CDR[32].B.VALID != 1) {}         //�ȴ�ADC0ת�������Ч
    return  ((uint16_t)ADC.CDR[32].B.CDATA);    //��ȡADC0��ת�����
	
}       

/************************************************************/
/*                     ��ȡͨ��0��ƽ��ֵ    ANS0   PB[8]    */
/************************************************************/
uint16_t Get_Adc_Average_ch0(uint8_t times)//ÿ��ͨ��ƽ��ȡtimes��ֵ��ͨ����ֵ�Ѿ�ͨ��ADC_Value_ch1()����ȡ�أ��ú����Ƕ�ADC_Value_ch1()��������ȡ5�Ρ�
{
	uint32_t temp_val=0;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		temp_val += ADC_Value_ch0();//��times�β�����ֵ�����ۼ�	
	}
	delayBanking(5);//��ʱ����5��΢���һ��
	return temp_val/times;//����ͨ��������ƽ��ֵ
} 

/************************************************************/
/*                     ��ȡͨ��1��ֵ      ANS1  PB[9]       */
/************************************************************/
uint16_t ADC_Value_ch1(void)
{
	while(ADC.CDR[33].B.VALID != 1) {}         //�ȴ�ADC0ת�������Ч
	return  ((uint16_t)ADC.CDR[33].B.CDATA);    //��ȡADC0��ת�����
}
/************************************************************/
/*                     ��ȡͨ��1��ƽ��ֵ      ANS1   PB[9]  */
/************************************************************/
uint16_t Get_Adc_Average_ch1(uint8_t times)
{
	uint32_t temp_val=0;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		temp_val += ADC_Value_ch1();	
	}
	delayBanking(5);
	return temp_val/times;
} 


/************************************************************/
/*                     ��ȡͨ��2��ֵ    ANS2    PB[10]      */
/************************************************************/
uint16_t ADC_Value_ch2(void)
{
 
	while(ADC.CDR[34].B.VALID != 1) {}         //�ȴ�ADC0ת�������Ч
 
    return  ((uint16_t)ADC.CDR[34].B.CDATA);    //��ȡADC0��ת�����
	
}     

/************************************************************/
/*                     ��ȡͨ��2��ƽ��ֵ     ANS2   PB[10]  */
/************************************************************/
uint16_t Get_Adc_Average_ch2(uint8_t times)
{
	uint32_t temp_val=0;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		temp_val += ADC_Value_ch2();	
	}
	delayBanking(5);
	return temp_val/times;
} 
/************************************************************/
/*                     ��ȡͨ��3��ֵ     ANS3    PB[11]     */
/************************************************************/
uint16_t ADC_Value_ch3(void)
{
 
	while(ADC.CDR[35].B.VALID != 1) {}         //�ȴ�ADC0ת�������Ч
 
    return  ((uint16_t)ADC.CDR[35].B.CDATA);    //��ȡADC0��ת�����
	
}     

/************************************************************/
/*                     ��ȡͨ��3��ƽ��ֵ   ANS3  PB[11]     */
/************************************************************/
uint16_t Get_Adc_Average_ch3(uint8_t times)
{
	uint32_t temp_val=0;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		temp_val += ADC_Value_ch3();	
	}
	delayBanking(5);
	return temp_val/times;
}

/************************************************************/
/*                     ��ȡͨ��4��ֵ      ANS4    PD[12]    */
/************************************************************/
uint16_t ADC_Value_ch4(void)
{
 
	while(ADC.CDR[36].B.VALID != 1) {}         //�ȴ�ADC0ת�������Ч
 
    return  ((uint16_t)ADC.CDR[36].B.CDATA);    //��ȡADC0��ת�����
	
}     

/************************************************************/
/*                     ��ȡͨ��4��ƽ��ֵ      ANS4    PD[12]*/
/************************************************************/
uint16_t Get_Adc_Average_ch4(uint8_t times)
{
	uint32_t temp_val=0;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		temp_val += ADC_Value_ch4();	
	}
	delayBanking(5);
	return temp_val/times;
}

/************************************************************/
/*                     ��ȡͨ��5��ֵ         ANS5  PD[13]   */
/************************************************************/
uint16_t ADC_Value_ch5(void)
{
 
	while(ADC.CDR[37].B.VALID != 1) {}         //�ȴ�ADC0ת�������Ч
 
    return  ((uint16_t)ADC.CDR[37].B.CDATA);    //��ȡADC0��ת�����
	
}     

/************************************************************/
/*                     ��ȡͨ��5��ƽ��ֵ       ANS5  PD[13] */
/************************************************************/
uint16_t Get_Adc_Average_ch5(uint8_t times)
{
	uint32_t temp_val=0;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		temp_val += ADC_Value_ch5();	
	}
	delayBanking(5);
	return temp_val/times;
}


/************************************************************/
/*                     ��ȡͨ��6��ֵ            ANS6  PD[14]*/
/************************************************************/
uint16_t ADC_Value_ch6(void)
{
 
	while(ADC.CDR[38].B.VALID != 1) {}         //�ȴ�ADC0ת�������Ч
 
    return  ((uint16_t)ADC.CDR[38].B.CDATA);    //��ȡADC0��ת�����
	
}     

/************************************************************/
/*                     ��ȡͨ��6��ƽ��ֵ        ANS6  PD[14]*/
/************************************************************/
uint16_t Get_Adc_Average_ch6(uint8_t times)
{
	uint32_t temp_val=0;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		temp_val += ADC_Value_ch6();	
	}
	delayBanking(5);
	return temp_val/times;
}



/************************************************************/
/*                     ��ȡͨ��7��ֵ     ANS7  PD[15]       */
/************************************************************/
uint16_t ADC_Value_ch7(void)
{
 
	while(ADC.CDR[39].B.VALID != 1) {}         //�ȴ�ADC0ת�������Ч
 
    return  ((uint16_t)ADC.CDR[39].B.CDATA);    //��ȡADC0��ת�����
	
}     

/************************************************************/
/*                     ��ȡͨ��7��ƽ��ֵ      ANS7  PD[15]  */
/************************************************************/
uint16_t Get_Adc_Average_ch7(uint8_t times)
{
	uint32_t temp_val=0;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		temp_val += ADC_Value_ch7();	
	}
	delayBanking(5);
	return temp_val/times;
}

 
 

