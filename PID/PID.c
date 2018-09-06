/******************************************************************
*
*PID闭环控制模块
*******************************************************************/



# include "Include.h"

   #define  Vkp    30
  #define  Vki    0.006
  #define  Vkd    10
 /* #define  Vkp     30
  #define  Vki     0.02
  #define  Vkd     10*/
  int sum_error=0;
  int  PWM_Wish=0;
 
   
 
 
 
/******************位置式*****************/
void PID_speed(uint8_t Pulse)   //期望脉冲
{
     
   static int last_error;
       int    dlast_error;
       int    error;
 	error = Pulse - FeedBack;  //期望值-实际值
 	
 	if(abs(error)<=2)                   //偏差
 	    error=0;         
 	    
 	sum_error+=error;
 	 //  if(sum_error>=3000) 
 	  // sum_error=3000;               //积分
 	dlast_error = error - last_error;   //微分
  
 	last_error = error; 
 	
    
   PWM_Wish=(int)( Vkp*error+Vki*sum_error+ Vkd*dlast_error);
   
   if(PWM_Wish>=2000)
   		PWM_Wish=2000;
   else if(PWM_Wish<=0)  
   		PWM_Wish=0;
   
    //DATA[3]=PWM_Wish;
   speed_control(PWM_Wish);
 }       
     
     
      /******************增量式****************
      
void PID_speed(uint8_t Pulse)   //期望脉冲
{
     
   static int last_error,dd_error;
       int    dlast_error;
       int    ddlast_error;
       int    error;
        
 	error = Pulse - FeedBack;  //期望值-实际值
 	
 	if(abs(error)<=2)                   //偏差
 	    error=0;         
 	    
 //	sum_error+=error;
 	 //  if(sum_error>=3000) 
 	  // sum_error=3000;               //积分
 	dlast_error = error - last_error;   //微分
    ddlast_error=dlast_error-dd_error;
 	
 	last_error = error; 
 	dd_error=dlast_error ;
    
   PWM_Wish+=(int)( Vkp*dlast_error +Vki*error+Vkd* ddlast_error);
   
   if(PWM_Wish>=2000) PWM_Wish=2000;
   else if(PWM_Wish<=0)   PWM_Wish=0;
   
    //DATA[3]=PWM_Wish;
   speed_control(PWM_Wish);
 }  */
       	    
      	 