#ifndef __USART_H_
#define __USART_H_



#define   DISABLE             0         // Bit-Field Is Disabled
#define   ENABLE              1         // Bit-Field Is Enabled

extern unsigned char PD;
extern uint8_t SPEED1;


void LINFlex0_init(void);
void UART0_TX(unsigned char data);
void send_string(unsigned char *putchar);




#endif