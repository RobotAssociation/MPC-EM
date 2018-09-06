#ifndef __NFR_H_
#define __NFR_H_
#include "MPC5604B_0M27V_0102.h"
#include "SPI.h"



void inerDelay_us(unsigned char n);
void Delay(unsigned int s);
uint16_t SPI_RW_Reg(uint8_t reg, uint8_t value);
uint16_t SPI_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t uchars);
uint16_t SPI_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t uchars);
void SetRX_Mode(void);
unsigned char nRF24L01_RxPacket(unsigned char* rx_buf);
void nRF24L01_TxPacket(unsigned char * tx_buf);
void init_NRF24L01_send(void);

#endif