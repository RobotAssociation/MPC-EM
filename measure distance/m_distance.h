#ifndef __M_DISTANCE_H__
#define __M_DISTANCE_H__

#include "MPC5604B_0M27V_0102.h"

 extern uint16_t range_left,range_right;


void write_byte(uint8_t address,uint8_t reg,uint8_t command);
uint8_t read_byte(uint8_t address,uint8_t reg);
uint16_t Change_Addr(uint8_t addr_old,uint8_t addr_new);
uint16_t detect(uint8_t address,uint8_t command);
uint8_t Ultrasonic_detect(void);

#endif