///////////////////////////////									//
//		   //			//							      		//
//	 	  //			//							//////////////////////	
//		  //			//							        //	//
//	\\	  //	     //		//							      //	//
//	 \\	  //	    //		//						            //		//
//		  //			//							  //		//			
//		  //			//							/////////////////////////		
//		  //			//									//
//////////////////////////////									//		
		 //												//
 		 //												//
		 //								       //////////////////////////////////////				
	////////////////											//
		 //												//
		 //												//
//////////////////////////////									//	
//         \\         \\          \\ 									//



# include "Include.h"

extern IVOR4Handler();
extern uint32_t __IVPR_VALUE; /* Interrupt Vector Prefix vaue from link file*/
extern const vuint32_t IntcIsrVectorTable[];

    uint32_t Pit1Ctr = 0;   /* Counter for PIT 1 interrupts */
      uint16_t angle_Ctr = 0;                      /* Counter for software interrupt 4 */
      uint16_t bb = 0,cc=0,jishi=0;
      uint16_t jishi_1=0;
      uint16_t Pit1Ctr_1=0;
      uint16_t Pit1Ctr_2=0;
      uint16_t Pit1Ctr_3=0;
      uint16_t Fangxiang=0;
      uint16_t Sudu=0;
     
 void Tingche(void); 
/************************************************************/
/*                       初始化中断向量                     */
/************************************************************/
asm void initIrqVectors(void) {
  lis	   r3, __IVPR_VALUE@h   /* IVPR value is passed from link file */
  ori      r3, r3, __IVPR_VALUE@l 
  mtivpr   r3									 
}


/************************************************************/
/*                         配置中断                         */
/************************************************************/
void initINTC(void) 
{	
  INTC.MCR.B.HVEN = 0;       //配置为软件中断
  INTC.MCR.B.VTES = 0;       //配置向量表大小为4字节
  INTC.IACKR.R = (uint32_t) &IntcIsrVectorTable[0];    //设置中断向量表基地址
}
/************************************************************/
/*                      初始化PIT模块                       */
/************************************************************/
void initPIT(void) 
{
                            
  PIT.PITMCR.R = 0x00000000;       //使能PIT模块，并且在debug模式下继续运行
  PIT.CH[1].LDVAL.R = 320000;    //设置计数值为320000，系统时钟为64MHz，则计数时间为5ms
  PIT.CH[1].TCTRL.R = 0x000000003; //使能PIT1计数，并使能中断 
  INTC.PSR[60].R = 0x01;           //设置PIT1的中断优先级为1
}

void EX_Interrupt(void)
{
	
    
    /*INTC.MCR.B.HVEN = 1;               //硬件向量模式  向量地址4个字节
   SIU.IRER.B.EIRE8    = 0;           //EIRQ[8]禁止
     SIU.IFEER.B.IFEE8 = 1;             //中断上升沿使能寄存器--1口（PC14）下降沿有效，场中断    
   SIU.PCR[46].R = 0X0103;            //配置PC[14]引脚为EIRQ8功能--IRQ1组 
    INTC.PSR[42].R = 0x04;  
   SIU.IRER.B.EIRE8    = 1;           //使能中断 
   */
   
   INTC.MCR.B.HVEN = 1;               //硬件向量模式  向量地址1个字节
    SIU.IRER.B.EIRE10    = 0;           //EIRQ[10]禁止
    
   // SIU.IREER.B.IREE10 = 1;             //中断上升沿使能寄存器--0口（PA14）上升沿有效,行中断
    SIU.IFEER.B.IFEE10 = 1;             //中断下降沿
    SIU.PCR[74].R = 0X0103;            //配置PC[14]引脚为EIRQ8功能--IRQ1组 H	
    INTC.PSR[42].R = 0x04;               //外部中断42优先级为4
    SIU.IRER.B.EIRE10    = 1;           //使能中断    
                     	
}
/************************************************************/
/*               			       初始化软件中断        	              */
/************************************************************/
/*void initSwIrq4(void) 
{
  INTC.PSR[4].R = 2;		//软件中断4优先级为2
}
*/
/************************************************************/
/*                        使能中断                          */
/************************************************************/
void enableIrq(void) 
{
  INTC.CPR.B.PRI = 0;          //设置当前的优先级
  asm(" wrteei 1");	    	   //使能外部中断
}

/************************************************************/
/*                     PIT1中断函数                         */
/************************************************************/
void PIT1inter(void) 
{
  static float A_Value=0;
  PIT.CH[1].TFLG.B.TIF = 1;   //清除中断标志位  
  Pit1Ctr++;                 //PIT中断次数计数加1

  Pit1Ctr_2++;
  jishi++;
  			
  			//		白 		黑
   			//K1		270		350
   			//K2		230		320
  
  						
   		     	Encoder_count();
   
   		     	if(K1==1&&K2!=1)//标记，逐渐稳定 圆的	kp=200+FeedBack/2.8;kd =(float)FeedBack*8;
   		     	{
   		     	
   		     		 kp=200+FeedBack/2.3;  
			      	 kd = (float)FeedBack*3.8;//4.7//kd= (float)FeedBack*30;
			      	 kp_1=250+FeedBack/2.8;
				 kd_1 =(float)FeedBack*8;//kd= (float)FeedBack*30; 
				
   		     		if(flag_B_B==1)
		 			{
		 			
		 				Pit1Ctr_1++;
		 		
		 			
		 			
			 			if(Pit1Ctr_1<35)//35 此处应该大于 _##_ 哪里的值
			 			{		
			 				/*
				 			if(K3!=1)
				 			Angle = 2700;//直接给值右转
				 			else if(K3==1)
				 			*/
				 			
				 			Angle = 3900;
				 			
				 			
			 			}
			 		
			 		
			 	//		Motor_R_Back=1000;//倒转减速 
			 			if(Pit1Ctr_1==20)//20  _##_
			 			{
			 				
			 				flag_B=1;//跳入圆执行代码
			 		//		Pit1Ctr=0;//开启方向函数
			 				Ming=1;
			 			
			 			}
			 			
			 			if(Pit1Ctr_1==60)
			 			Pit1Ctr=0;
		 			
			 			if(Pit1Ctr_1==150)//圆的标志条件关闭时间
			 			{
			 				
			 				flag_B_B=0;
			 				Pit1Ctr_1=0;//关闭条件
			 				Motor_R_Back=0;
			 				Motor_R_Front=50;
			 				Pit1Ctr_2=0;//开启速度
			 		
			 			}
		 			
		 			
		 			}
			 		if(Pit1Ctr_2==2)//速度控制函数
			 		{
			 				
			 				Pit1Ctr_2=0;
			 				
			 				if(flag_B==1)
			 				{
			 					speed_control(230);
			 				}
			 				
			 				speed_control(355);
			 				}
			 			
			 		}
   		     
   		     
 		     ///////////////////////////////////////////
        	else if(K2==1&&K1!=1)//标记，逐渐稳定 圆的	kp=200+FeedBack/2.8;kd =(float)FeedBack*8;
   		     	{
   		     	
   		     		 kp=300+FeedBack/3;  
			      	 kd = (float)FeedBack*2.5;//kd= (float)FeedBack*30;
			     	 kp_1=160+FeedBack/2.8;
				 kd_1 =(float)FeedBack*6;//kd= (float)FeedBack*30; 
	
   		     		if(flag_B_B==1)
		 			{
		 				 
		 				Pit1Ctr_1++;
		 		
			 		//	Ming=0;//凤鸣响起
				 		if(Pit1Ctr_1<25)//35 此处应该大于 _##_ 哪里的值
				 		{
				 		/*
				 			if(K3!=1)
				 			Angle = 2700;//直接给值右转
				 			else if(K3==1)
				 		*/
				 			Angle = 3900;
				 		}
			 		
			 	//		Motor_R_Back=1000;//倒转减速 
			 			if(Pit1Ctr_1==20)//20  _##_
			 			{
			 				
			 				flag_B=1;//跳入圆执行代码
			 				Pit1Ctr=0;//开启方向函数
			 			//	Ming=1;
			 			
			 			}
			 			
			 			if(Pit1Ctr_1==170)//圆的标志条件关闭时间
			 			{
			 				
			 				flag_B_B=0;
			 				Pit1Ctr_1=0;//关闭条件
			 				Motor_R_Back=0;
			 				Motor_R_Front=50;
			 				Pit1Ctr_2=0;
			 			//	Pit1Ctr_3=0;//关闭条件,
			 		//		Ming=1;//凤鸣停
			 			
			 	
			 			}
			 			
		 			
			 		}
			 		if(Pit1Ctr_2==2)//速度控制函数
			 		{
			 					
			 			
			 				Pit1Ctr_2=0;
			 				
			 				if(flag_B==1)
			 				{
			 					speed_control(230);
			 				}
			 				
			 				speed_control(370);
			 				}
			 				
   		     	}
			 		
   		     
       	///////////////////////////////////////////////////////////////
        	else if(K3==1)
   		     	{
   		     		LED0=0;
   		     		 kp=80+FeedBack/2.3;  
			      	 kd = (float)FeedBack*6;//kd= (float)FeedBack*30;
			      	 kp_1=250+FeedBack/2.8;
					 kd_1 =(float)FeedBack*7;//kd= (float)FeedBack*30; 
   		     		if(flag_B_B==1)
		 			{
		 			Pit1Ctr_1++;
		 		
		 		//	Ming=0;//凤鸣响起
			 		if(Pit1Ctr_1<10)//35 此处应该大于 _##_ 哪里的值
			 		{
			 			
			 			Angle = 3900;
			 		}
		 		
		 	//		Motor_R_Back=1000;//倒转减速 
		 			if(Pit1Ctr_1==5)//20  _##_
		 			{
		 				
		 				flag_B=1;//跳入圆执行代码
		 				Pit1Ctr=0;//开启方向函数
		 				Ming=1;
		 			
		 			}
		 			
		 			if(Pit1Ctr_1==180)//圆的标志条件关闭时间
		 			{
		 				
		 				flag_B_B=0;
		 				Pit1Ctr_1=0;//关闭条件
		 				Motor_R_Back=0;
		 				Motor_R_Front=50;
		 				Pit1Ctr_2=0;//开启速度
		 			//	Pit1Ctr_3=0;//关闭条件,
		 		//		Ming=1;//凤鸣停
		 			
		 	
		 			}
		 			
		 			
		 		}
		 		if(Pit1Ctr_2==2)//速度控制函数
		 		{
		 				Pit1Ctr_2=0;
		 				
		 				if(flag_B==1)
		 				{
		 					speed_control(300);
		 				}
		 				
		 				speed_control(400);
		 			
		 		}
   		     }
   		     ////////////////////////////////////////////////////////
   		     	else if(K4==1)
   		     	{
   		     		LED0=0;
   		     		 kp=130+FeedBack/2.3;  
			      	 kd = (float)FeedBack*4.8;//kd= (float)FeedBack*30;
			      	 kp_1=250+FeedBack/2.5;
					 kd_1 =(float)FeedBack*6.3;//kd= (float)FeedBack*30; 
   		     		if(flag_B_B==1)
		 			{
		 			Pit1Ctr_1++;
		 		
		 		//	Ming=0;//凤鸣响起
			 		if(Pit1Ctr_1<10)//35 此处应该大于 _##_ 哪里的值
			 		{
			 		
			 			Angle = 3900;
			 		}
		 		
		 	//		Motor_R_Back=1000;//倒转减速 
		 			if(Pit1Ctr_1==5)//20  _##_
		 			{
		 				
		 				flag_B=1;//跳入圆执行代码
		 				Pit1Ctr=0;//开启方向函数
		 				Ming=1;
		 			
		 			}
		 			
		 			if(Pit1Ctr_1==120)//圆的标志条件关闭时间
		 			{
		 				
		 				flag_B_B=0;
		 				Pit1Ctr_1=0;//关闭条件
		 				Motor_R_Back=0;
		 				Motor_R_Front=50;
		 				Pit1Ctr_2=0;//开启速度
		 			//	Pit1Ctr_3=0;//关闭条件,
		 		//		Ming=1;//凤鸣停
		 			
		 	
		 			}
		 			
		 			
		 		}
		 		if(Pit1Ctr_2==2)//速度控制函数
		 		{
		 				Pit1Ctr_2=0;
		 				
		 				if(flag_B==1)
		 				{
		 					speed_control(350);
		 				}
		 				
		 				speed_control(450);
		 			
		 		}
   		     }
		   /////////////////////////////////////////////////////    
   				if(Pit1Ctr==2)//方向控制函数
		        {
		          		 Pit1Ctr=0;
		          		 DirectionControl();	
		        }	      
    
}

/************************************************************/
/*                     软件中断4函数                        */
/************************************************************/
void SwIrq4ISR(void) 
{
  INTC.SSCIR[4].R = 1;		//清除中断标志 
}

void Tingche(void)//停车
{
	
     SIU.ISR.B.EIF10=1;                    //清行中断标志位
    if(jishi>=3000)
    {
    	PIT.CH[1].TCTRL.R = 0x000000000;    //关PIT中断
    	jishi=0;
    	Motor_R_Front=0;
        Motor_R_Back=1000;
    	delay_ms(150); 
	    for(;;)
	    {
	    	 DirectionControl();
	    	// delay_ms(100); 
	    	
	        Motor_R_Back=0;
	        
	     
	    	DirectionControl();
	    
	    }
    
    }
    
   
		
}

 