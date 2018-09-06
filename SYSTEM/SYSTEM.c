# include "Include.h"

void SWT_DisableWatchDog(void)
{
  SWT.SR.R = 0x0000C520;                // ��SR��д��C520��D928���CR�е�SLKλ
  SWT.SR.R = 0x0000D928;                
  SWT.CR.R = 0x8000010A;                // ������Ź�ʹ��λ (WEN)����ֹ������Ź�������
}


void SYSTEM_Init(void)
{
//ģʽ����: ʹ��DRUN, RUN0, SAFE, RESETģʽ
  ME.MER.R = 0x0000001D;   

//��ʼ�����໷��
//�ⲿ����Ϊ8MHz������PLL0Ϊ64MHz  // 0x05400100: 0000 0101 0100 0000 0000 0001 0000 0000
//����IDF=2,ODF=4,NDIV=64;
//���໷���ʱ��phi=(clkin*NDIV)/(IDF*ODF)=(8*64)/(2*4)=64MHz
  CGM.FMPLL_CR.R = 0x05400100;

//RUN0����: ����ѹ�������򿪣�Data Flash��������ģʽ��Code Flash��������ģʽ��
//ʹ�����໷�����໷���ʱ����Ϊϵͳʱ�ӡ�
  ME.RUN[0].R   = 0x001F0074;           
  
//������������0: ����������ģʽ�¶�����
  ME.RUNPC[0].R = 0x000000FE;    
  
  
  
  ME.RUNPC[1].R = 0x00000010;            
// SIUL: ѡ�� ME.RUNPC[0] ������  
   
  ME.PCTL[32].R = 0x01;        // for ADC  
 	
// SIUL: ѡ�� ME.RUNPC[1] ������  
  ME.PCTL[68].R = 0x01;                 
// PIT: ѡ�� ME.RUNPC[1] ������    
  ME.PCTL[92].R = 0x01;        //for PIT1 
  // I2C: ѡ�� ME.RUNPC[0] ������  
  ME.PCTL[44].R = 0x01;    
             

  

// ���ý���RUN0ģʽ
  ME.MCTL.R = 0x40005AF0;               //д��ģʽ����Կ
  ME.MCTL.R = 0x4000A50F;               //д��ģʽ�ͷ���Կ

//�ȴ�ģʽת�����
  while(ME.GS.B.S_MTRANS) {};           
//��֤������RUN0ģʽ
  while(ME.GS.B.S_CURRENTMODE != 4) {}  
}

void System_init()
{
	  SWT_DisableWatchDog(); 
	  SYSTEM_Init(); 
	  LED_Init();  
	  PWM_Init();
	   EX_Interrupt();
	  initIrqVectors();
	  initINTC();  
	  enableIrq();
	   initPIT();
	  ADC_Init();
	  Encoder_Init();
	  LINFlex0_init();
	  init_I2C();
	  	
}

/************************************************************/
/*                       ��ʱ����                           */
/************************************************************/
void delay_ms(int ms)
{   
   int ii,jj;
   if (ms<1) ms=1;
   for(ii=0;ii<ms;ii++)
     for(jj=0;jj<20000;jj++){}        
}

 void delay_us(int us)
 {
      int a;  
   for(a=0;a<us;a++)
   {
   	 asm{nop;} asm{nop;} asm{nop;} asm{nop;} asm{nop;}
   	 asm{nop;} asm{nop;} asm{nop;} asm{nop;} asm{nop;}
	 asm{nop;} asm{nop;} asm{nop;} asm{nop;} asm{nop;}
   	 asm{nop;} asm{nop;} asm{nop;} asm{nop;} asm{nop;}
   	 asm{nop;} asm{nop;} asm{nop;} asm{nop;} asm{nop;}
   	 asm{nop;} asm{nop;} asm{nop;} asm{nop;} asm{nop;} 
   	 asm{nop;} asm{nop;} asm{nop;} asm{nop;} asm{nop;}
   	 asm{nop;} asm{nop;} asm{nop;} asm{nop;} asm{nop;}
	 asm{nop;} asm{nop;} asm{nop;} asm{nop;} asm{nop;}
   	 asm{nop;} asm{nop;} asm{nop;} asm{nop;} asm{nop;}
   	 asm{nop;} asm{nop;} asm{nop;} asm{nop;} asm{nop;}
   	 
   } 
 }
