#ifndef __ENCODER_H_
#define __ENCODER_H_
#include "MPC5604B_0M27V_0102.h" /* Use proper include file */



 
#define Counter     SIU.PGPDI1.B.PCL
        
#define CLEAR            SIU.GPDO[29].R


#define OPTICAL_ENCODE_CONSTANT   200   //光电编码盘的刻槽数量
#define SPEED_CONTROL_PERIOD	    10  //速度控制周期，ms
#define CAR_SPEED_CONSTANT        1      //单位转化比例值 


extern uint8_t count;
extern int FeedBack;

void Encoder_Init();
void Encoder_count();
 





#endif