#ifndef __IIC_H_
#define __IIC_H_
#include "MPC5604B_0M27V_0102.h" /* Use proper include file */

#define  SDA	SIU.GPDO[10].B.PDO		//A10
#define  SCL	SIU.GPDO[11].B.PDO		//A11

void init_I2C(void);
void I2C_start();
uint8_t I2C_send(uint8_t data);
uint8_t I2C_receive(uint8_t txak);
void I2C_stop(void);
void I2C_restart(void);



#endif
