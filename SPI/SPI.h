#include "MPC5604B_0M27V_0102.h"

#define  MOSI  	SIU.GPDO[13].B.PDO
#define  MISO  	SIU.GPDO[12].B.PDO
#define  IRQ  	SIU.GPDO[10].B.PDO
#define  CS  	SIU.GPDO[15].B.PDO
#define  CE  	SIU.GPDO[11].B.PDO
#define  SCK  	SIU.GPDO[14].B.PDO

void DSPI0_init(void) ;
uint8_t DSPI0_send_receive(uint8_t data);
