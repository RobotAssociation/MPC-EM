 //////////////////////////////									//
//		   //				//							      	//
//	 	  //				//							//////////////////////	
//		  //				//							     //	//
//	\\	  //	   //		//						       //	//
//	 \\	  //	  //		//				              //	//
//		  //				//							 //		//			
//		  //				//							/////////////////////////		
//		  //				//									//
//////////////////////////////									//		
		 //														//
 		 //														//
		 //								       //////////////////////////////////////				
	////////////////											//
		 //														//
		 //														//
//////////////////////////////									//	
//         \\         \\          \\ 							//



/***************************************************************************
*
*AD值处理及路径处理模块
***************************************************************************/

# include "Include.h"
# include "math.h"
#define   N   10
#define  lostline_value  100    //原值100
#define  all_lostline_value  15 

 uint16_t AD_value[6]={0};
 int DATA[4]={0};
 uint16_t  max_ad[4]={270,270,270,270};
 uint16_t  min_ad[4]={40,40,40,40};
 uint16_t AD_max=0;
 int  direction=0, last_direction=0,t=0;
 uint16_t AD_data[6][N];
 int  fvalue=0 ,last_fvalue=0;
 float  last_err=0;
 char a=0;
 float ferror=0;
 uint16_t AD_he=0;
 
 
 uint16_t flag_xiaoyuan_1=0;
 uint16_t flag_xiaoyuan_0=0;
 uint16_t flag_dayuan=0;
 uint8_t flag_speed_1=0;
 uint8_t flag_A=0;
 uint8_t flag_B=0;
 uint8_t flag_B_B=0;
 uint8_t flag_B_Q=0;
 float kp=0;
 float kd=0;
 float kp_1=0;
 float kd_1=0;
 
 
/************************************对AD值进行处理*************************************************/ 
 void AD_zhi()
{
    
		int i=0,j=0,k=0;
		uint16_t AD_temp=0,AD_sum[6];
	
		for(j=0;j<N;j++)
		{
			//电感从左往右排序
      		AD_data[0][j]=Get_Adc_Average_ch6(5);//D14 AD1       //每个通道取N次值  此时N=10
      		AD_data[1][j]=Get_Adc_Average_ch5(5);//D13 AD2
      		AD_data[2][j]=Get_Adc_Average_ch4(5);//D12 AD3
      		AD_data[3][j]=Get_Adc_Average_ch3(5);//B11 AD4

      		AD_data[4][j]=Get_Adc_Average_ch7(5);//D15 AD0 ok	 接最左边电感
      		AD_data[5][j]=Get_Adc_Average_ch2(5);//B10 AD5 ok    接最右边电感
       
		}
	
		/******************冒泡排序*************************/
		for(i=0;i<6;i++)
		{
			for(j=0;j<N;j++)
			{
		 	   for(k=0;k<N-j;k++)
		  	  {
		      	 if(AD_data[i][k]>AD_data[i][k+1])
		      	 {
		      	 	AD_temp=AD_data[i][k];
		       		AD_data[i][k]=AD_data[i][k+1];
		       		AD_data[i][k+1]=AD_temp;
		      	 }
		    	}
			}
		}
	
		/****************去掉最大值最小值，求平均值*******************/
		for(i=0;i<6;i++)
		{
			AD_sum[i]=AD_data[i][1]+AD_data[i][2]+AD_data[i][3]+AD_data[i][4]+AD_data[i][5]+AD_data[i][6]+AD_data[i][7]+AD_data[i][8]; 
        
		}
	
 
     	//求平均值
 	   	AD_value[0] = AD_sum[0]/8; //前面N取10，然后去掉最大和最小，所以这里除以8
   	 	AD_value[1] = AD_sum[1]/8;
   		AD_value[2] = AD_sum[2]/8;
    	AD_value[3] = AD_sum[3]/8;
   		AD_value[4] = AD_sum[4]/8;
   	 	AD_value[5] = AD_sum[5]/8; 
   
     
       	//设置AD的最小取值限度 
  		for(i=0;i<4;i++)
  		{
      		if( AD_value[i]<=40)
          	AD_value[i]=40; 	
 		}
  
     		AD_value[0]=400 * ( AD_value[0]-min_ad[0])/(max_ad[0]-min_ad[0]);
      		AD_value[1]=400 * ( AD_value[1]-min_ad[1])/(max_ad[1]-min_ad[1]);
      		AD_value[2]=400 * ( AD_value[2]-min_ad[2])/(max_ad[2]-min_ad[2]);
      		AD_value[3]=400 * ( AD_value[3]-min_ad[3])/(max_ad[3]-min_ad[3]);
      
      
      
      
   		for(i=0;i<4;i++)
  		{
      		if( AD_value[i]<=2)
          	AD_value[i]=2;
        //if( AD_value[i]>=450)
          // AD_value[i]=450;   
  		}     
      
}
/******************************************************************************************************************************/ 
 /***************绝对值函数**************/
    uint16_t abs(int  x)
	{
	    if(x<0)  return - x;
	    else     return x;
	}

    float abs_f(float x)
	{
	    if(x<0)  return - x;
	    else     return x;
	}



/**************************************************************************************************************************/
/*******************************控制方向函数******************************************************************/
void DirectionControl(void)
{
			      char  k=0;
			      char  ADvalue_n,noADvalue_n,all_noADvalue_n;
			      char  flag0=0,flag3=0;
			      
			      //float ferror=0;
			     // uint16_t AD_he=0;
			    //  float  kp=0,kd=0 ;
			      float  ad12=0,ad03=0,ad45=0;
			      
			      //int  fvalue=0;
			      int ad_mid;
		
			      AD_zhi();
			     //	 求差  比  和 
			    ad12=(float)(AD_value[1]-AD_value[2])/(AD_value[1]+AD_value[2]);
			    ad03=(float)(AD_value[0]-AD_value[3])/(AD_value[0]+AD_value[3]);
			    ad45=(float)(AD_value[4]-AD_value[5])/(AD_value[4]+AD_value[5]);
			      
			    ad_mid=(int)((AD_value[1]+AD_value[2])/20);
			    AD_he=AD_value[0]+AD_value[1]+AD_value[2]+AD_value[3]; 
			    ferror = (float)(AD_value[2]+AD_value[3]-AD_value[1]-AD_value[0])/AD_he;
			    
			     //  kp=50+FeedBack/2.3;  
			       //kd = (float)FeedBack*6.8;//kd= (float)FeedBack*30;
			    
			 	 
				  
			     ADvalue_n=0;
			     noADvalue_n=0;
			    all_noADvalue_n=0;
			     
			 /***************判断电感丢线个数*****************/  
			 #if 0 
			    if(AD_value[0]<=lostline_value)//lostline_vlaue=100
			    {
			    	noADvalue_n++;
			        //flag0=1;	 
			     
			     }
			      
			     if(AD_value[0]<=all_lostline_value)//all_lostline_value=15
			     {
			          all_noADvalue_n++;
			    	 
			     
			     }
			         
			       
			           
			    
			    for(k=1;k<=3;k++)
			    {   
			       if(AD_value[k]<=all_lostline_value)
			       {
			           	  all_noADvalue_n++;
			           	 // flag3=k; 
			       }
			       
			       if(AD_value[k]<=lostline_value)
			       {
			           	  noADvalue_n++;
			           	   
			       }
			           
			     } 
			      
      	#endif
 
   /***********************BBBBBBBBBBBBBBBBBBBBBBBBB******************************************
   *                                用于圆形
   *******************************************************************************************/
	if(flag_B==1)
	{
	
	
	

		LED0=1;
		
		LED2=0;

		LED1=1;
				////////////////////PD////////////////////////////////
			//	kp_1=200+FeedBack/2.8;
			//	kd_1 =(float)FeedBack*8;//kd= (float)FeedBack*30; 
	
			 if(AD_he<=1000&&AD_he>=200&&abs_f(ad45)>=0.5&&Angle<=3320&&Angle>=3240)//Angle<=2970&&Angle>=2890
			  {
						  
					if(AD_value[4]>AD_value[5]&&(AD_value[4]+AD_value[5])>=150)//最左电感值>最右电感值
					{

							fvalue = MAX_right_angle ;//	#define  MAX_right_angle    -495 
							     
					}
							    
					else if(AD_value[5]>AD_value[4]&&(AD_value[4]+AD_value[5])>=150 )//最右电感值>最左电感值
					{
									
							 fvalue = MAX_left_angle;	//#define  MAX_left_angle     533 
							     
					}
				    else 
						     fvalue = last_fvalue;
				       
			  }
	         
			  
			  else if(AD_he<400&&AD_value[4]<100&&AD_value[5]>100&&AD_value[0]<AD_value[1]<AD_value[2]<AD_value[3]&&AD_value[0]>20&&AD_value[0]<100&&
			  AD_value[1]>20&&AD_value[1]<100&&AD_value[2]>20&&AD_value[2]<100&&AD_value[3]>20&&AD_value[3]<120)
			  {
			  		fvalue = MAX_right_angle;
			  }
			  else if(AD_he<400&&AD_value[4]>100&&AD_value[5]<100&&AD_value[0]>AD_value[1]>AD_value[2]>AD_value[3]&&AD_value[0]>20&&AD_value[0]<120&&
			  AD_value[1]>20&&AD_value[1]<100&&AD_value[2]>20&&AD_value[2]<100&&AD_value[3]>20&&AD_value[3]<100)
			  {
			  		fvalue = MAX_left_angle;
			  }
			  
			  
			  if(AD_he<=50)
			  {
			  	
			  	 if(AD_value[4]<90&&AD_value[5]<90&&AD_value[4]+AD_value[5]<=100)
			  	 {
			  
			  		if(AD_value[4]>=AD_value[5]&&(AD_value[0]+AD_value[1])>=(AD_value[2]+AD_value[3]))
			  		{
			  		
			  		  	fvalue=MAX_right_angle;
			  		
			  		}
			  		else if(AD_value[4]<AD_value[5]&&(AD_value[0]+AD_value[1])<(AD_value[2]+AD_value[3]))
			  		
			  		{	
			  	
			  			fvalue=MAX_left_angle;								
			  		}
			  		else 
			  		fvalue = last_fvalue;
			  	
			  	}
			  
			  
			  }
			  
	
			  ///////////////////////////////////////////////////////
			 
			  	else  
		     	{
					 fvalue = (int)(kp_1*ferror + kd_1*(ferror-last_err));
			
	        	} 
	        
		       last_err = ferror; 
		       last_fvalue = fvalue;
		       if(fvalue>MAX_left_angle )     
		       fvalue=MAX_left_angle ;
		       else	if(fvalue<MAX_right_angle)     
		       fvalue=MAX_right_angle;
		         
		      	if(AD_value[0]==2&&AD_value[1]==2&&AD_value[2]==2&&AD_value[3]==2)
    			{
    			if(AD_value[4]>AD_value[5])
    				{
    				fvalue=MAX_right_angle;
    			
    				}
    			
    			else if(AD_value[5]>AD_value[4])
    				fvalue=MAX_left_angle;
    			else
    				fvalue=last_fvalue;
    			}
     
	      
	      		 car_direction(fvalue);
			 /////////////////////////////////
			 
			 if(AD_he>650&&AD_value[4]>100&&AD_value[5]>100)
			 {
				flag_B=0;
		
				Ming=1;
				LED3=0;
				LED2=1;
				LED0=0;
				
		 
		 	 }
		 
			 /////////////////////////////////////////////////////
	 } 

	 /****************************************BBB**********************************************/
	 ///////////////////////////////////////////////////////////////////////////////////////////

     

    /*****************************AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA************************************
    *											用于一般路径
    *************************************************************************************************************/
  
  	
			  /////////////////////////////////////////////////////
		
			  
	
		  else if(AD_value[0]<100&&AD_value[1]<100&&AD_value[2]<100&&AD_value[3]<100&&AD_value[0]>30&&AD_value[1]>35&&
		  AD_value[2]>35&&AD_value[3]>30&&AD_value[4]<150&&AD_value[5]<150&&AD_value[4]>60&&AD_value[5]>60&&AD_he<420&&
		  AD_value[4]+AD_value[5]>150&&abs(AD_value[4]-AD_value[5])<80&&AD_value[5]-AD_value[4]<40)
		  {
		  		
		  		if(AD_value[3]>AD_value[2]>AD_value[1]>AD_value[0]&&AD_value[5]>AD_value[4])
		  		fvalue = MAX_left_angle;
		  		else if(AD_value[5]>AD_value[4]>AD_value[3]>AD_value[2]&&AD_value[1]>AD_value[0])
		  		fvalue=MAX_right_angle;
		  		
		  		else
		  		{
		  		
		  				LED1=0;
					 	Pit1Ctr=100;//关闭方向函数
					 	Pit1Ctr_2=100;//关闭速度
				  		Ming=0;
				  		
						 /* 		
				  		if(K3!=1)
				  		{
				  		if(K1!=1)
				  		{
				  			
				 		Angle =2700;//直接给值左转
				 		delay_ms(150);
				  		}
				  		else if(K1==1)
				  			{
				  				Angle=2700;
				  			}
				  		}
				 		else if(K3==1)
				 		*/
				 		
				 		Angle=3900;
				 		
				 		
				 				
				 		
					 	speed_control(0);
					 	
					 
				
				//		Motor_R_Back=1000;
					
				 		
					  
					  	flag_B_B=1;
					  	LED3=1;
					  	
					
		  		}
			  
		  }
			  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
			  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
			  //HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH//
/*			  #if 0
			  else if(noADvalue_n>=3)
			  {
			  	
		       
			     if(AD_value[4]>AD_value[5]&&(AD_value[4]+AD_value[5])>=150)//左转，一般情况
				 {
				 		
				 		fvalue = MAX_right_angle;//左转,  必须写在下面的if语句前面，不然if条件起不到作用.
				 
				     	
				 }
				
				 else if(AD_value[4]>AD_value[5]&&(AD_value[4]+AD_value[5])<100)//串道,左转
				 {	
				 	
				 	fvalue = MAX_right_angle;//左转
			
				 }
				    
				 else if(AD_value[4]<AD_value[5]&&(AD_value[4]+AD_value[5])>=150)//右转,一般情况
				 {	
				 			LED0=0;
				      fvalue = MAX_left_angle; //右转
					    
				 }
				 
				 else if(AD_value[4]<AD_value[5]&&AD_value[4]+AD_value[5]<100)
				 {
				 		fvalue = MAX_left_angle;//右转
				 }
				 else if(abs(AD_value[4]-AD_value[5])<40&&AD_value[0]<100&&
				 AD_value[1]>50&&AD_value[1]<100&&AD_value[1]>50&&AD_value[2]<100&&
				 AD_value[2]>50&&AD_value[3]>100&&AD_value[3]>50)
				 {	
				 		fvalue = MAX_right_angle;//左
				 }
				 
				
				
			     else 
			     	fvalue = last_fvalue;
			        
			     if(all_noADvalue_n>=3)
			        
			        fvalue = last_fvalue; 
		        
		         
		   	} 
		   	#endif
		   	////////////////////////////////////////////////////////////////////////////
		   	#if 0
		   		else if(AD_value[0]==2&&AD_value[1]==2&&AD_value[2]==2&&AD_value[3]==2&&AD_value[4]<24&&AD_value[5]<24)
		   		{
		   			if(AD_value[4]>AD_value[5])
		   				fvalue=MAX_left_angle;
		   			else
		   				fvalue = MAX_right_angle;
		   			if(AD_value[4]<23&&AD_value[5]<23)
		   				fvalue = last_fvalue;
		   			
		   		}
		   		#endif
	   	*/
		   	else if(AD_he<=50)
			  {
			  	
			  	
			  	 if(AD_value[0]==2&&AD_value[1]==2&&AD_value[2]==2&&AD_value[3]==2)
		   		{
		   			if(AD_value[4]<30&&AD_value[4]>25&&AD_value[5]>62&&AD_value[5]<67)
					fvalue=620;
		   			
		   	/*		if(AD_value[4]<30&&AD_value[4]>25&&AD_value[5]>70&&AD_value[5]<75||(AD_value[4]<45&&AD_value[4]>40&&AD_value[5]>123&&AD_value[5]<127))
		   			fvalue=MAX_left_angle;
		   			else if(AD_value[4]>AD_value[5])
		   				fvalue=MAX_right_angle;
		   			else
		   				fvalue = MAX_right_angle;
		   				*/	
		   		}
			  	
			  	
			  	
			  	else if(AD_value[4]<90&&AD_value[5]<90&&AD_value[4]+AD_value[5]<=100)
			  	 {
			  
			  		if(AD_value[4]>=AD_value[5]&&(AD_value[0]+AD_value[1])>=(AD_value[2]+AD_value[3]))
			  		{
			  		
			  		  	fvalue=MAX_right_angle;
			  		
			  		}
			  		else if(AD_value[4]<AD_value[5]&&(AD_value[0]+AD_value[1])<=(AD_value[2]+AD_value[3]))
			  		
			  		{	
			  	
			  			fvalue=MAX_left_angle;								
			  		}
			  		
			  	
			  		
			  		else 
			  		fvalue =620;
			  	}
			  
			  
			  }

	
		  /***************AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA**************/
	   	  /////////////////////////////////////////////////////////////////////////////////////////

        /***************舵机方向控制*****************/	 
    	else  
     	{
		    fvalue = (int)(kp*ferror + kd*(ferror-last_err));
		
	    } 
	
  /*  	if(AD_value[0]==2&&AD_value[1]==2&&AD_value[2]==2&&AD_value[3]==2)
    	{
    		fvalue = last_fvalue;
    	}
     */
       
        
       
	       last_err = ferror; 
	       last_fvalue = fvalue;
	       if(fvalue>MAX_left_angle)     
	       fvalue=MAX_left_angle ;
	       else	if(fvalue<MAX_right_angle)     
	       fvalue=MAX_right_angle;
/*	         
        if(AD_he>=250&&AD_value[0]>AD_value[1]&&AD_value[3]>AD_value[2])        
        {
     	  fvalue = last_fvalue; 
        } 
   */   
       	   car_direction(fvalue);
     
    
         
   }








