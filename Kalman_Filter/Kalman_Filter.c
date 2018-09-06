#include "Kalman_Filter.h"
#include "Visual_data.h"
#include "ADC.h"
#include "MMA8451.h"
#include "L3G4200D.h"


int OutData[4] = {0};


float Gyro_offset;
float Gyro,Acc_z;
float Acc_z_Angle,Gyro_AngleSpeed;
float angle_dot,angle;
float CarAngleIntegral;
extern float Gyro_offset;




/************************************************************************************/
/*******************************求arccos(x)的函数************************************/
/*********************************利用泰勒展开式求***********************************/
/************************************************************************************/
float acos(double x)
{
	float angle = 0.0;
	angle = (5.0*x*x*x*x*x*x*x)/112.0 - (3.0*x*x*x*x*x)/40.0 - (x*x*x)/6.0 - x - 1.5708;
	return angle;		
}
/************************************************************************************/
/*******************************求arcsin(x)的函数************************************/
/*********************************利用泰勒展开式求***********************************/
/************************************************************************************/
float asin(double x)
{
	float angle = 0.0;
	angle = x + x*x*x/6 + (3*x*x*x*x*x)/40 + (5*x*x*x*x*x*x*x)/112;
	return angle;		
}

/**************Kalman滤波****************/
float angle, angle_dot;         //外部需要引用的变量
static const char C_0 = 1;
float Q_angle=0.0001, Q_gyro=0.003, R_angle=0.5,dt=0.005;
static float P[2][2] = {{ 1, 0 },{ 0, 1 }}; 
static float Pdot[4] ={0,0,0,0};
float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;
/**************Kalman滤波****************/
void Kalman_Filter(float angle_m,float gyro_m)  //gyro_m:gyro_measure
{
    angle+=(gyro_m-q_bias) * dt;
    angle_err = angle_m - angle;   
	 
    Pdot[0]=Q_angle - P[0][1] - P[1][0];
    Pdot[1]=- P[1][1];
    Pdot[2]=- P[1][1];
    Pdot[3]=Q_gyro;
    
    P[0][0] += Pdot[0] * dt;
    P[0][1] += Pdot[1] * dt;
    P[1][0] += Pdot[2] * dt;
    P[1][1] += Pdot[3] * dt;
     
    PCt_0 = C_0 * P[0][0];
    PCt_1 = C_0 * P[1][0];
    
    E = R_angle + C_0 * PCt_0;
    
    K_0 = PCt_0 / E;
    K_1 = PCt_1 / E;
    
    t_0 = PCt_0;
    t_1 = C_0 * P[0][1];

    P[0][0] -= K_0 * t_0;
    P[0][1] -= K_0 * t_1;
    P[1][0] -= K_1 * t_0;
    P[1][1] -= K_1 * t_1;
      
    angle   += K_0 * angle_err;
    q_bias  += K_1 * angle_err;
    angle_dot = gyro_m-q_bias;
}

/****************官方滤波****************/
void Official_filter()
{	
	float fDeltaValue;
	angle = CarAngleIntegral;
	fDeltaValue = (Acc_z_Angle - angle) / 2 ; //b=3不要太小
	CarAngleIntegral += (Gyro_AngleSpeed + fDeltaValue) / 200;
}
	

void Filter()
{
 
 // Gyro = Get_Adc_Average_ch1(20);
 // Gyro = Gyro - Gyro_offset;
 // Gyro_AngleSpeed =  Gyro * 7;    //(3300/4096)/（0.67*9.1） = 0.13214   7
  //OutData[0] = Gyro_AngleSpeed;
  	
  //Acc_z = Get_Adc_Average_ch2(20);    //180/(430-190)=0.75
 // Acc_z -= Acc_z_offset;
 // Acc_z_Angle = Acc_z*0.75;
 // OutData[1] = Acc_z_Angle*10;
  
  Gyro = READ_L3G4200D();
  OutData[0] = Gyro;
  Acc_z = (float)MMA845x_Read_Z();
  OutData[1]=  Acc_z;  
//  Acc_z_Angle = asin(Acc_z/8192);
 // Acc_z_Angle *= -57.29578 ;               //180/3.14159 = 57.29578 
//  OutData[2] = Acc_z_Angle * 10;

 /****************官方滤波****************/
//  Official_filter();
/****************官方滤波****************/

/**************Kalman滤波****************/
//  Kalman_Filter(Acc_z_Angle,Gyro_AngleSpeed);
 // OutData[0] = angle_dot;	
/**************Kalman滤波****************/ 

 // OutData[3] = angle*10;
  Visual_Data(OutData);//数据发回上位机  		
}