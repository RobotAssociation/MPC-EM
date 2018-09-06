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
/*                       ��ʼ���ж�����                     */
/************************************************************/
asm void initIrqVectors(void) {
  lis	   r3, __IVPR_VALUE@h   /* IVPR value is passed from link file */
  ori      r3, r3, __IVPR_VALUE@l 
  mtivpr   r3									 
}


/************************************************************/
/*                         �����ж�                         */
/************************************************************/
void initINTC(void) 
{	
  INTC.MCR.B.HVEN = 0;       //����Ϊ����ж�
  INTC.MCR.B.VTES = 0;       //�����������СΪ4�ֽ�
  INTC.IACKR.R = (uint32_t) &IntcIsrVectorTable[0];    //�����ж����������ַ
}
/************************************************************/
/*                      ��ʼ��PITģ��                       */
/************************************************************/
void initPIT(void) 
{
                            
  PIT.PITMCR.R = 0x00000000;       //ʹ��PITģ�飬������debugģʽ�¼�������
  PIT.CH[1].LDVAL.R = 320000;    //���ü���ֵΪ320000��ϵͳʱ��Ϊ64MHz�������ʱ��Ϊ5ms
  PIT.CH[1].TCTRL.R = 0x000000003; //ʹ��PIT1��������ʹ���ж� 
  INTC.PSR[60].R = 0x01;           //����PIT1���ж����ȼ�Ϊ1
}

void EX_Interrupt(void)
{
	
    
    /*INTC.MCR.B.HVEN = 1;               //Ӳ������ģʽ  ������ַ4���ֽ�
   SIU.IRER.B.EIRE8    = 0;           //EIRQ[8]��ֹ
     SIU.IFEER.B.IFEE8 = 1;             //�ж�������ʹ�ܼĴ���--1�ڣ�PC14���½�����Ч�����ж�    
   SIU.PCR[46].R = 0X0103;            //����PC[14]����ΪEIRQ8����--IRQ1�� 
    INTC.PSR[42].R = 0x04;  
   SIU.IRER.B.EIRE8    = 1;           //ʹ���ж� 
   */
   
   INTC.MCR.B.HVEN = 1;               //Ӳ������ģʽ  ������ַ1���ֽ�
    SIU.IRER.B.EIRE10    = 0;           //EIRQ[10]��ֹ
    
   // SIU.IREER.B.IREE10 = 1;             //�ж�������ʹ�ܼĴ���--0�ڣ�PA14����������Ч,���ж�
    SIU.IFEER.B.IFEE10 = 1;             //�ж��½���
    SIU.PCR[74].R = 0X0103;            //����PC[14]����ΪEIRQ8����--IRQ1�� H	
    INTC.PSR[42].R = 0x04;               //�ⲿ�ж�42���ȼ�Ϊ4
    SIU.IRER.B.EIRE10    = 1;           //ʹ���ж�    
                     	
}
/************************************************************/
/*               			       ��ʼ������ж�        	              */
/************************************************************/
/*void initSwIrq4(void) 
{
  INTC.PSR[4].R = 2;		//����ж�4���ȼ�Ϊ2
}
*/
/************************************************************/
/*                        ʹ���ж�                          */
/************************************************************/
void enableIrq(void) 
{
  INTC.CPR.B.PRI = 0;          //���õ�ǰ�����ȼ�
  asm(" wrteei 1");	    	   //ʹ���ⲿ�ж�
}

/************************************************************/
/*                     PIT1�жϺ���                         */
/************************************************************/
void PIT1inter(void) 
{
  static float A_Value=0;
  PIT.CH[1].TFLG.B.TIF = 1;   //����жϱ�־λ  
  Pit1Ctr++;                 //PIT�жϴ���������1

  Pit1Ctr_2++;
  jishi++;
  			
  			//		�� 		��
   			//K1		270		350
   			//K2		230		320
  
  						
   		     	Encoder_count();
   
   		     	if(K1==1&&K2!=1)//��ǣ����ȶ� Բ��	kp=200+FeedBack/2.8;kd =(float)FeedBack*8;
   		     	{
   		     	
   		     		 kp=200+FeedBack/2.3;  
			      	 kd = (float)FeedBack*3.8;//4.7//kd= (float)FeedBack*30;
			      	 kp_1=250+FeedBack/2.8;
				 kd_1 =(float)FeedBack*8;//kd= (float)FeedBack*30; 
				
   		     		if(flag_B_B==1)
		 			{
		 			
		 				Pit1Ctr_1++;
		 		
		 			
		 			
			 			if(Pit1Ctr_1<35)//35 �˴�Ӧ�ô��� _##_ �����ֵ
			 			{		
			 				/*
				 			if(K3!=1)
				 			Angle = 2700;//ֱ�Ӹ�ֵ��ת
				 			else if(K3==1)
				 			*/
				 			
				 			Angle = 3900;
				 			
				 			
			 			}
			 		
			 		
			 	//		Motor_R_Back=1000;//��ת���� 
			 			if(Pit1Ctr_1==20)//20  _##_
			 			{
			 				
			 				flag_B=1;//����Բִ�д���
			 		//		Pit1Ctr=0;//����������
			 				Ming=1;
			 			
			 			}
			 			
			 			if(Pit1Ctr_1==60)
			 			Pit1Ctr=0;
		 			
			 			if(Pit1Ctr_1==150)//Բ�ı�־�����ر�ʱ��
			 			{
			 				
			 				flag_B_B=0;
			 				Pit1Ctr_1=0;//�ر�����
			 				Motor_R_Back=0;
			 				Motor_R_Front=50;
			 				Pit1Ctr_2=0;//�����ٶ�
			 		
			 			}
		 			
		 			
		 			}
			 		if(Pit1Ctr_2==2)//�ٶȿ��ƺ���
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
        	else if(K2==1&&K1!=1)//��ǣ����ȶ� Բ��	kp=200+FeedBack/2.8;kd =(float)FeedBack*8;
   		     	{
   		     	
   		     		 kp=300+FeedBack/3;  
			      	 kd = (float)FeedBack*2.5;//kd= (float)FeedBack*30;
			     	 kp_1=160+FeedBack/2.8;
				 kd_1 =(float)FeedBack*6;//kd= (float)FeedBack*30; 
	
   		     		if(flag_B_B==1)
		 			{
		 				 
		 				Pit1Ctr_1++;
		 		
			 		//	Ming=0;//��������
				 		if(Pit1Ctr_1<25)//35 �˴�Ӧ�ô��� _##_ �����ֵ
				 		{
				 		/*
				 			if(K3!=1)
				 			Angle = 2700;//ֱ�Ӹ�ֵ��ת
				 			else if(K3==1)
				 		*/
				 			Angle = 3900;
				 		}
			 		
			 	//		Motor_R_Back=1000;//��ת���� 
			 			if(Pit1Ctr_1==20)//20  _##_
			 			{
			 				
			 				flag_B=1;//����Բִ�д���
			 				Pit1Ctr=0;//����������
			 			//	Ming=1;
			 			
			 			}
			 			
			 			if(Pit1Ctr_1==170)//Բ�ı�־�����ر�ʱ��
			 			{
			 				
			 				flag_B_B=0;
			 				Pit1Ctr_1=0;//�ر�����
			 				Motor_R_Back=0;
			 				Motor_R_Front=50;
			 				Pit1Ctr_2=0;
			 			//	Pit1Ctr_3=0;//�ر�����,
			 		//		Ming=1;//����ͣ
			 			
			 	
			 			}
			 			
		 			
			 		}
			 		if(Pit1Ctr_2==2)//�ٶȿ��ƺ���
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
		 		
		 		//	Ming=0;//��������
			 		if(Pit1Ctr_1<10)//35 �˴�Ӧ�ô��� _##_ �����ֵ
			 		{
			 			
			 			Angle = 3900;
			 		}
		 		
		 	//		Motor_R_Back=1000;//��ת���� 
		 			if(Pit1Ctr_1==5)//20  _##_
		 			{
		 				
		 				flag_B=1;//����Բִ�д���
		 				Pit1Ctr=0;//����������
		 				Ming=1;
		 			
		 			}
		 			
		 			if(Pit1Ctr_1==180)//Բ�ı�־�����ر�ʱ��
		 			{
		 				
		 				flag_B_B=0;
		 				Pit1Ctr_1=0;//�ر�����
		 				Motor_R_Back=0;
		 				Motor_R_Front=50;
		 				Pit1Ctr_2=0;//�����ٶ�
		 			//	Pit1Ctr_3=0;//�ر�����,
		 		//		Ming=1;//����ͣ
		 			
		 	
		 			}
		 			
		 			
		 		}
		 		if(Pit1Ctr_2==2)//�ٶȿ��ƺ���
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
		 		
		 		//	Ming=0;//��������
			 		if(Pit1Ctr_1<10)//35 �˴�Ӧ�ô��� _##_ �����ֵ
			 		{
			 		
			 			Angle = 3900;
			 		}
		 		
		 	//		Motor_R_Back=1000;//��ת���� 
		 			if(Pit1Ctr_1==5)//20  _##_
		 			{
		 				
		 				flag_B=1;//����Բִ�д���
		 				Pit1Ctr=0;//����������
		 				Ming=1;
		 			
		 			}
		 			
		 			if(Pit1Ctr_1==120)//Բ�ı�־�����ر�ʱ��
		 			{
		 				
		 				flag_B_B=0;
		 				Pit1Ctr_1=0;//�ر�����
		 				Motor_R_Back=0;
		 				Motor_R_Front=50;
		 				Pit1Ctr_2=0;//�����ٶ�
		 			//	Pit1Ctr_3=0;//�ر�����,
		 		//		Ming=1;//����ͣ
		 			
		 	
		 			}
		 			
		 			
		 		}
		 		if(Pit1Ctr_2==2)//�ٶȿ��ƺ���
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
   				if(Pit1Ctr==2)//������ƺ���
		        {
		          		 Pit1Ctr=0;
		          		 DirectionControl();	
		        }	      
    
}

/************************************************************/
/*                     ����ж�4����                        */
/************************************************************/
void SwIrq4ISR(void) 
{
  INTC.SSCIR[4].R = 1;		//����жϱ�־ 
}

void Tingche(void)//ͣ��
{
	
     SIU.ISR.B.EIF10=1;                    //�����жϱ�־λ
    if(jishi>=3000)
    {
    	PIT.CH[1].TCTRL.R = 0x000000000;    //��PIT�ж�
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

 