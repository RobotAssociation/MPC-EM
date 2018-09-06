# include "Include.h"

void SWT_DisableWatchDog(void)
{
  SWT.SR.R = 0x0000C520;                // 向SR中写入C520和D928清除CR中的SLK位
  SWT.SR.R = 0x0000D928;                
  SWT.CR.R = 0x8000010A;                // 清除看门狗使能位 (WEN)，禁止软件看门狗工作。
}


void SYSTEM_Init(void)
{
//模式配置: 使能DRUN, RUN0, SAFE, RESET模式
  ME.MER.R = 0x0000001D;   

//初始化锁相环，
//外部晶振为8MHz，设置PLL0为64MHz  // 0x05400100: 0000 0101 0100 0000 0000 0001 0000 0000
//设置IDF=2,ODF=4,NDIV=64;
//锁相环输出时钟phi=(clkin*NDIV)/(IDF*ODF)=(8*64)/(2*4)=64MHz
  CGM.FMPLL_CR.R = 0x05400100;

//RUN0配置: 主电压调节器打开，Data Flash处于正常模式。Code Flash处于正常模式。
//使能锁相环，锁相环输出时钟作为系统时钟。
  ME.RUN[0].R   = 0x001F0074;           
  
//外设运行配置0: 外设在所有模式下都工作
  ME.RUNPC[0].R = 0x000000FE;    
  
  
  
  ME.RUNPC[1].R = 0x00000010;            
// SIUL: 选择 ME.RUNPC[0] 的配置  
   
  ME.PCTL[32].R = 0x01;        // for ADC  
 	
// SIUL: 选择 ME.RUNPC[1] 的配置  
  ME.PCTL[68].R = 0x01;                 
// PIT: 选择 ME.RUNPC[1] 的配置    
  ME.PCTL[92].R = 0x01;        //for PIT1 
  // I2C: 选择 ME.RUNPC[0] 的配置  
  ME.PCTL[44].R = 0x01;    
             

  

// 设置进入RUN0模式
  ME.MCTL.R = 0x40005AF0;               //写入模式和密钥
  ME.MCTL.R = 0x4000A50F;               //写入模式和反密钥

//等待模式转换完成
  while(ME.GS.B.S_MTRANS) {};           
//验证进入了RUN0模式
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
/*                       延时函数                           */
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
