#ifndef __DEAL_H_
#define __DEAL_H_
//# include "Include.h" 

extern uint16_t AD_value[6];
extern int DATA[4];
extern  uint16_t AD_max;
extern  char a;

extern float ferror ;
extern int fvalue,last_fvalue ;
extern uint16_t AD_he ;
extern uint16_t flag_xiaoyuan_1;
extern uint8_t flag_speed_1;
extern uint8_t flag_A;
extern uint8_t flag_B;
extern uint8_t flag_B_B;
extern uint8_t flag_B_Q;
extern uint32_t Pit1Ctr;
extern uint16_t Pit1Ctr_2;
extern uint16_t Pit1Ctr_3;
extern float kp;
extern float kd;
extern float kp_1;
extern float kd_1;
void AD_zhi();
 
void deal();
void DirectionControl(void);

#endif
