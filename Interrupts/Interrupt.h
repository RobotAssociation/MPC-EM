#ifdef    __INTERRUPT_H_
#define   __INTERRUPT_H_
#include "MPC5604B_0M27V_0102.h" /* Use proper include file */   //包在这里好像没用要包在里面


asm void initIrqVectors(void);




extern uint8_t SPEED1;
extern uint32_t Pit1Ctr;
extern uint16_t Pit1Ctr_2;
//extern uint8_t flag_B_B;
//extern uint8_t flag_B;
void EX_Interrupt(void);

void PIT1inter(void);
void initINTC(void);
void initPIT(void) ;

extern uint8_t flag_speed_1; 
#endif 
