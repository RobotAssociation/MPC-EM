#ifndef  __Kalman_Filter_H_
#define  __Kalman_Filter_H_




#define Acc_z_offset    335;



	     



extern float angle, angle_dot;   
extern float CarAngleIntegral;
extern float Gyro_offset;
extern float Gyro,Acc_z;
extern float Acc_z_Angle,Gyro_AngleSpeed;

void Filter();


#endif
