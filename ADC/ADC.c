/********************************************************************
*
*ADC数据转换获取模块
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
/*                     初始化ADC转换                        */
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
 
  ADC.NCMR[1].R = 0x000000FD;     /* Select ANS0:8 inputs for conversion *///选择ANS 0-7作为输入转换，ADC的NCMR寄存器1配置
   								  /* 最后两位ADC.NCMR[1].R=0x000000FD ,设置ANS0:7选择*/
 
  ADC.CTR[1].R = 0x00008606;      /* Conversion times for 32MHz ADClock *///设置转换频率
  ADC.MCR.B.NSTART=1;             /* Trigger normal conversions for ADC0 */ //触发标准转换 	
}
/************************************************************/
/*                     获取通道0的值       ANS0 PB[8]       */
/************************************************************/
uint16_t ADC_Value_ch0(void)
{


	while(ADC.CDR[32].B.VALID != 1) {}         //等待ADC0转换结果有效
    return  ((uint16_t)ADC.CDR[32].B.CDATA);    //读取ADC0的转换结果
	
}       

/************************************************************/
/*                     获取通道0的平均值    ANS0   PB[8]    */
/************************************************************/
uint16_t Get_Adc_Average_ch0(uint8_t times)//每个通道平均取times次值，通道的值已经通过ADC_Value_ch1()函数取回，该函数是对ADC_Value_ch1()函数连续取5次。
{
	uint32_t temp_val=0;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		temp_val += ADC_Value_ch0();//对times次采样的值进行累加	
	}
	delayBanking(5);//延时近似5个微秒多一点
	return temp_val/times;//返回通道采样的平均值
} 

/************************************************************/
/*                     获取通道1的值      ANS1  PB[9]       */
/************************************************************/
uint16_t ADC_Value_ch1(void)
{
	while(ADC.CDR[33].B.VALID != 1) {}         //等待ADC0转换结果有效
	return  ((uint16_t)ADC.CDR[33].B.CDATA);    //读取ADC0的转换结果
}
/************************************************************/
/*                     获取通道1的平均值      ANS1   PB[9]  */
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
/*                     获取通道2的值    ANS2    PB[10]      */
/************************************************************/
uint16_t ADC_Value_ch2(void)
{
 
	while(ADC.CDR[34].B.VALID != 1) {}         //等待ADC0转换结果有效
 
    return  ((uint16_t)ADC.CDR[34].B.CDATA);    //读取ADC0的转换结果
	
}     

/************************************************************/
/*                     获取通道2的平均值     ANS2   PB[10]  */
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
/*                     获取通道3的值     ANS3    PB[11]     */
/************************************************************/
uint16_t ADC_Value_ch3(void)
{
 
	while(ADC.CDR[35].B.VALID != 1) {}         //等待ADC0转换结果有效
 
    return  ((uint16_t)ADC.CDR[35].B.CDATA);    //读取ADC0的转换结果
	
}     

/************************************************************/
/*                     获取通道3的平均值   ANS3  PB[11]     */
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
/*                     获取通道4的值      ANS4    PD[12]    */
/************************************************************/
uint16_t ADC_Value_ch4(void)
{
 
	while(ADC.CDR[36].B.VALID != 1) {}         //等待ADC0转换结果有效
 
    return  ((uint16_t)ADC.CDR[36].B.CDATA);    //读取ADC0的转换结果
	
}     

/************************************************************/
/*                     获取通道4的平均值      ANS4    PD[12]*/
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
/*                     获取通道5的值         ANS5  PD[13]   */
/************************************************************/
uint16_t ADC_Value_ch5(void)
{
 
	while(ADC.CDR[37].B.VALID != 1) {}         //等待ADC0转换结果有效
 
    return  ((uint16_t)ADC.CDR[37].B.CDATA);    //读取ADC0的转换结果
	
}     

/************************************************************/
/*                     获取通道5的平均值       ANS5  PD[13] */
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
/*                     获取通道6的值            ANS6  PD[14]*/
/************************************************************/
uint16_t ADC_Value_ch6(void)
{
 
	while(ADC.CDR[38].B.VALID != 1) {}         //等待ADC0转换结果有效
 
    return  ((uint16_t)ADC.CDR[38].B.CDATA);    //读取ADC0的转换结果
	
}     

/************************************************************/
/*                     获取通道6的平均值        ANS6  PD[14]*/
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
/*                     获取通道7的值     ANS7  PD[15]       */
/************************************************************/
uint16_t ADC_Value_ch7(void)
{
 
	while(ADC.CDR[39].B.VALID != 1) {}         //等待ADC0转换结果有效
 
    return  ((uint16_t)ADC.CDR[39].B.CDATA);    //读取ADC0的转换结果
	
}     

/************************************************************/
/*                     获取通道7的平均值      ANS7  PD[15]  */
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

 
 

