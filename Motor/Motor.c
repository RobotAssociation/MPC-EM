# include "Include.h"






void PWM_Init(void)
{
	SIU.PCR[66].R = 0x0600;               // 设置PE[2]为eMIOS_0的18通道	电机正转	
	SIU.PCR[67].R = 0x0600;               // 设置PE[3]为eMIOS_0的19通道 电机翻转
	SIU.PCR[76].R = 0x0A00;               // 设置PE[12]为eMIOS_1的19通道 舵机	
	
    EMIOS_0.MCR.B.GPRE  = 1;        // 设置分频系数为2,分频为32MHz
    EMIOS_0.MCR.B.GPREN = 1;         // 使能eMIOS时钟
    EMIOS_0.MCR.B.GTBE  = 1;         // 使能全局时基
    EMIOS_0.MCR.B.FRZ   = 1;         // 在冻结模式下停止通道
  

   EMIOS_1.MCR.B.GPRE   =31;   //分频系数128.f=0.5MHZ=0.2us
   EMIOS_1.MCR.B.GPREN   = 0x1;   //全局预分频使能  
      
  //  EMIOS_1.MCR.B.GPRE  = 0;        // 设置分频系数为1,不分频为64MHz
  //  EMIOS_1.MCR.B.GPREN = 1;         // 使能eMIOS时钟
    EMIOS_1.MCR.B.GTBE  = 1;         // 使能全局时基
    EMIOS_1.MCR.B.FRZ   = 1;         // 在冻结模式下停止通道 
    		
 //设置18通道，周期100us，
    EMIOS_0.CH[18].CADR.R      = 0;      // 设置首边沿的匹配值
    EMIOS_0.CH[18].CBDR.R      = 1;      // 设置尾边沿的匹配值   
    EMIOS_0.CH[18].CCR.B.BSL   = 0x0;     // 使用通道23生成的Bus A
    EMIOS_0.CH[18].CCR.B.EDPOL = 1;       // 设置极性：A匹配时置1，B匹配时清0
    EMIOS_0.CH[18].CCR.B.MODE  = 0x60;    // 选择OPWMB模式
//设置19通道，周期100us，
    EMIOS_0.CH[19].CADR.R      = 0;      // 设置首边沿的匹配值
    EMIOS_0.CH[19].CBDR.R      = 1;      // 设置尾边沿的匹配值   
    EMIOS_0.CH[19].CCR.B.BSL   = 0x0;     // 使用Bus A
    EMIOS_0.CH[19].CCR.B.EDPOL = 1;       // 设置极性：A匹配时置1，B匹配时清0
    EMIOS_0.CH[19].CCR.B.MODE  = 0x60;    // 选择OPWMB模式 
 
  
    //设置23通道，作为18,19,20,21的时基Bus A
    EMIOS_0.CH[23].CADR.R      = 2133;    //计数周期为800=100us  
    EMIOS_0.CH[23].CCR.B.MODE  = 0x50;   //设置为缓冲模数计数器模式MCB
    EMIOS_0.CH[23].CCR.B.BSL   = 0x3;    //使用64MHz的内部计数器作为时钟源
    EMIOS_0.CH[23].CCR.B.UCPEN = 1;      //使能分频器
    EMIOS_0.CH[23].CCR.B.FREN  = 1;      //在冻结模式下停止计数 
    
    
    
    
    
 //设置EMIOS_1的19通道，周期20ms
    EMIOS_1.CH[19].CADR.R      = 0;      // 设置首边沿的匹配值
    EMIOS_1.CH[19].CBDR.R      = 1;      // 设置尾边沿的匹配值   
    EMIOS_1.CH[19].CCR.B.BSL   = 0x0;     // 使用通道23生成的Bus A
    EMIOS_1.CH[19].CCR.B.EDPOL = 1;       // 设置极性：A匹配时置1，B匹配时清0
    EMIOS_1.CH[19].CCR.B.MODE  = 0x60;    // 选择OPWMB模式
 //设置23通道，作为EMIOS_1的19的时基Bus A
    EMIOS_1.CH[23].CADR.R      = 10000;    //计数周期为10000=20ms  
    EMIOS_1.CH[23].CCR.B.MODE  = 0x50;   //设置为缓冲模数计数器模式MCB
    EMIOS_1.CH[23].CCR.B.BSL   = 0x3;    //使用64MHz的内部计数器作为时钟源

    EMIOS_1.CH[23].CCR.B.UCPEN = 1;      //使能分频器
    EMIOS_1.CH[23].CCR.B.FREN  = 1;      //在冻结模式下停止计数   
    
    
   // Angle =700;	//舵机初始化     //中间值800
  			
}


void car_direction(int angle)
 {
    Angle = MID_angle + angle;    // 只需要给出偏移角度
 }

void speed_control(int speed)
 {
       	Motor_R_Front = speed;  
 }







