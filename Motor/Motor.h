#ifndef __MOTOR_H_
#define __MOTOR_H_
#include "MPC5604B_0M27V_0102.h" /* Use proper include file */


 
 
#define    Motor_R_Front     EMIOS_0.CH[18].CBDR.R   //  PE2 ���ڵ����ת
#define    Motor_R_Back      EMIOS_0.CH[19].CBDR.R   //  PE3 ���ڵ����ת

#define Angle                EMIOS_1.CH[19].CBDR.R   //  PE12//Angleֵ1~1250  +����80  ���ڶ������
#define  MID_angle         3300//2800 //  //2750                   //�м�ֵ��2750/  ��ֵ��2217 ��ֵ��3245
#define  MAX_left_angle    600// 530// 533 
#define  MAX_right_angle   -600// -560//-495    
    

void PWM_Init(void); 
void car_direction(int angle);
void speed_control(int speed);

#endif