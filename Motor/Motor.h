#ifndef __MOTOR_H_
#define __MOTOR_H_
#include "MPC5604B_0M27V_0102.h" /* Use proper include file */


 
 
#define    Motor_R_Front     EMIOS_0.CH[18].CBDR.R   //  PE2 用于电机正转
#define    Motor_R_Back      EMIOS_0.CH[19].CBDR.R   //  PE3 用于电机翻转

#define Angle                EMIOS_1.CH[19].CBDR.R   //  PE12//Angle值1~1250  +往左80  用于舵机控制
#define  MID_angle         3300//2800 //  //2750                   //中间值：2750/  左值：2217 右值：3245
#define  MAX_left_angle    600// 530// 533 
#define  MAX_right_angle   -600// -560//-495    
    

void PWM_Init(void); 
void car_direction(int angle);
void speed_control(int speed);

#endif