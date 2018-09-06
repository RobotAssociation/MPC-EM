#ifndef _LED_H_
#define _LED_H_
#include "MPC5604B_0M27V_0102.h" /* Use proper include file */


#define  D5		SIU.GPDO[7].B.PDO
#define  D4		SIU.GPDO[10].B.PDO
#define  D3		SIU.GPDO[11].B.PDO
#define  D2		SIU.GPDO[9].B.PDO

#define  Ming  SIU.GPDO[5].B.PDO //·äÃùÆ÷

#define  LED0	SIU.GPDO[12].B.PDO
#define  LED1	SIU.GPDO[13].B.PDO
#define  LED2	SIU.GPDO[14].B.PDO
#define  LED3	SIU.GPDO[15].B.PDO

#define  K1		SIU.GPDI[16].B.PDI //B0
#define  K2	    SIU.GPDI[17].B.PDI //B1
#define  K3		SIU.GPDI[42].B.PDI	//C10
#define  K4		SIU.GPDI[0].B.PDI  //A0

#define  T1     SIU.GPDI[74].B.PDI //E10 

void LED_Init(void);



#endif