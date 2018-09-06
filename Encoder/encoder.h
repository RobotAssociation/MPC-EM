#ifndef __ENCODER_H_
#define __ENCODER_H_
#include "MPC5604B_0M27V_0102.h" /* Use proper include file */



 
#define Counter     SIU.PGPDI1.B.PCL
        
#define CLEAR            SIU.GPDO[29].R


#define OPTICAL_ENCODE_CONSTANT   200   //�������̵Ŀ̲�����
#define SPEED_CONTROL_PERIOD	    10  //�ٶȿ������ڣ�ms
#define CAR_SPEED_CONSTANT        1      //��λת������ֵ 


extern uint8_t count;
extern int FeedBack;

void Encoder_Init();
void Encoder_count();
 





#endif