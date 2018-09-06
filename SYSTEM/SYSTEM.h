#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#include "MPC5604B_0M27V_0102.h" /* Use proper include file */

void SWT_DisableWatchDog(void);
void SYSTEM_Init(void);
void delay_ms(int ms);
void delay_us(int us);
void System_init();

#endif



