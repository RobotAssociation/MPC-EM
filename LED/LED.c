# include "Include.h"


void LED_Init(void)
{
//寄存器设置，参考MPC560XPRM寄存器参考手册.pdf第280页寄存器说明即可
//PCR:pad configuration register
//在100脚的封装中，是PCR[0..78]
//PCR[0:15]=port A;     PA0......PA15
//PCR[16:31]=port B;    PB0......PB15
//PCR[32:47]=port C     PC0......PC15
//PCR[48:63]=port D     PD0......PD15
//PCR[64:76]=port E     PE0......PE12
//PCR[77:78]=port H     PH9，PH10
//PB[4:7]和PC[0:11] 是ADC入口，在作为ADC时，要单独配置
  SIU.PCR[7].R = 0x0220;               // 设置PA[7]为开漏输出 
  SIU.PCR[9].R = 0x0220;               // 设置PA[9]为开漏输出
  SIU.PCR[10].R = 0x0220;               // 设置PA[10]为开漏输出
  SIU.PCR[11].R = 0x0220;               // 设置PA[11]为开漏输出
  
  SIU.PCR[5].R = 0x0220;//蜂鸣器
  
  SIU.PCR[12].R = 0x0220;               // 设置PA[12]为开漏输出
  SIU.PCR[13].R = 0x0220;               // 设置PA[13]为开漏输出
  SIU.PCR[14].R = 0x0220;               // 设置PA[14]为开漏输出
  SIU.PCR[15].R = 0x0220;               // 设置PA[15]为开漏输出 
   
  SIU.PCR[0].R = 0x0103;	            // 设置PA[0]为开漏输入,下拉选择，上拉使能  
  SIU.PCR[16].R = 0x0103;				// 设置PB[0]为开漏输入  
  SIU.PCR[17].R = 0x0103; 				// 设置PB[1]为开漏输入  
  SIU.PCR[42].R = 0x0103;				// 设置PC[10]为开漏输入
  
  SIU.PCR[74].R = 0x0100; 				//设置PE[10]为开漏输入
  
    		
  LED0 = 1;
  LED1 = 1;		
  LED2 = 1;	
  LED3 = 1;	
  
  

  Ming=1;
}