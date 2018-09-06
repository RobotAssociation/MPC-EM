# include "Include.h"
unsigned char receive;
unsigned char PD=0;
 uint8_t SPEED1 =60;
/************************************************************/
/*                       初始化uart0                        */
/************************************************************/
void LINFlex0_init(void)
{
//配置LINFlex
  SIU.PCR[18].R = 0x0600;    // 将PB[2]设置为LINFlex_0.TxDA
  SIU.PCR[19].R = 0x0100;    // 将PB[3]设置为LINFlex_0.RxDA
  LINFLEX_0.LINCR1.B.INIT   = ENABLE;   // 请求初始化
  LINFLEX_0.LINCR1.B.SLEEP  = DISABLE;  // 禁止睡眠模式
  LINFLEX_0.LINCR1.B.BF     = DISABLE;  // 如果ID不匹配不产生中断

  LINFLEX_0.UARTCR.B.UART   = 1;        // 进入UART模式
  LINFLEX_0.UARTCR.B.RXEN   = ENABLE;   // 允许接收
  LINFLEX_0.UARTCR.B.TXEN   = ENABLE;   // 允许发送
  LINFLEX_0.UARTCR.B.WL     = 1;        // 8位数据位
//  LINFLEX_0.UARTCR.B.OP     = 1;      // 偶校验
  LINFLEX_0.UARTCR.B.PCE    = DISABLE;  // 禁止奇偶校验
  LINFLEX_0.UARTCR.B.TDFL   = 0;        // 发送缓冲区为1个字节
  LINFLEX_0.UARTCR.B.RDFL   = 0;        // 接收缓冲区为1个字节

//设置波特率为9600
//波特率=外设时钟1/(16*LFDIV)
//DIV_M定义LFDIV的整数部分。(DIV_F/16)定义LFDIV的小数部分。
//LINFLEX_0.LINIBRR.B.DIV_M = 1666;     // Baud Rate = 2400, In Case fipg_clock_lin = 64 MHz
//LINFLEX_0.LINFBRR.B.DIV_F = 11;       // Baud Rate = 2400, In Case fipg_clock_lin = 64 MHz
//LINFLEX_0.LINIBRR.B.DIV_M = 833;      // Baud Rate = 4800, In Case fipg_clock_lin = 64 MHz
//LINFLEX_0.LINFBRR.B.DIV_F = 11;       // Baud Rate = 4800, In Case fipg_clock_lin = 64 MHz
  LINFLEX_0.LINIBRR.B.DIV_M = 416;      // Baud Rate = 9600, In Case fipg_clock_lin = 64 MHz
  LINFLEX_0.LINFBRR.B.DIV_F = 11;       // Baud Rate = 9600, In Case fipg_clock_lin = 64 MHz
//LINFLEX_0.LINIBRR.B.DIV_M = 208;      // Baud Rate = 19200, In Case fipg_clock_lin = 64 MHz
//LINFLEX_0.LINFBRR.B.DIV_F = 5;        // Baud Rate = 19200, On Case fipg_clock_lin = 64 MHz
//LINFLEX_0.LINIBRR.B.DIV_M = 104;      // Baud Rate = 38400, In Case fipg_clock_lin = 64 MHz
//LINFLEX_0.LINFBRR.B.DIV_F = 3;        // Baud Rate = 38400, In Case fipg_clock_lin = 64 MHz
//LINFLEX_0.LINIBRR.B.DIV_M = 69;       // Baud Rate = 57600, In Case fipg_clock_lin = 64 MHz
//LINFLEX_0.LINFBRR.B.DIV_F = 7;        // Baud Rate = 57600, In Case fipg_clock_lin = 64 MHz
//LINFLEX_0.LINIBRR.B.DIV_M = 34;       // Baud Rate = 115200, In Case fipg_clock_lin = 64 MHz
//LINFLEX_0.LINFBRR.B.DIV_F = 12;       // Baud Rate = 115200, In Case fipg_clock_lin = 64 MHz

//配置中断，使能中断功能
  LINFLEX_0.LINIER.B.DRIE   = ENABLE;   // 数据接收完成中断
//LINFLEX_0.LINIER.B.DTIE   = ENABLE;   // 数据发送完成中断
//LINFLEX_0.LINIER.B.DBFIE  = ENABLE;   // 数据缓冲器满中断
//LINFLEX_0.LINIER.B.DBEIE  = ENABLE;   // 数据缓冲器空中断

//配置中断，禁止中断功能
//LINFLEX_0.LINIER.R        = 0;        // 禁止所有中断
//LINFLEX_0.LINIER.B.DRIE   = DISABLE;  // 数据接收完成中断
//LINFLEX_0.LINIER.B.DTIE   = DISABLE;  // 数据发送完成中断
//LINFLEX_0.LINIER.B.DBFIE  = DISABLE;  // 数据缓冲器满中断
//LINFLEX_0.LINIER.B.DBEIE  = DISABLE;  // 数据缓冲器空中断

  LINFLEX_0.UARTSR.B.DRF    = 1;        // 清除接收完成标志
  LINFLEX_0.UARTSR.B.DTF    = 1;        // 清除发送完成标志
  INTC.PSR[79].R = 0x03;                //设置UART0的中断优先级为3

  LINFLEX_0.LINCR1.B.INIT   = DISABLE;  // 变为正常模式
}



/************************************************************/
/*                    UART0发送一字节                       */
/************************************************************/
void UART0_TX(unsigned char data)
{
  LINFLEX_0.BDRL.B.DATA0 = data;        // 写入需发送的数据
  while(LINFLEX_0.UARTSR.B.DTF == 0) {} // 等待发送完成
  LINFLEX_0.UARTSR.B.DTF = 1;           // 清除发送完成标志位
}

/************************************************************/
/*                    UART0接收一字节                       */
/************************************************************/
unsigned char UART0_RX(void)
{
  unsigned char datain;
  datain=LINFLEX_0.BDRM.B.DATA4;        // 读取接收到的数据
  LINFLEX_0.UARTSR.B.DRF = 1;           // 清除接收完成标志位
  return datain;
}


/************************************************************/
/*                    UART0中断函数                         */
/************************************************************/
void UART0iner(void) 
{
	static uint8_t FLAG=0;
	receive=UART0_RX();

 	if(receive==0xff)
 	{
 		FLAG = 1;		
 	}
 	if(FLAG == 1 )
 	{
 		if(receive!=0xff)
 		{
 			SPEED1 = (uint8_t)receive;
 			LED3=~LED3;
 		}
 	}
	
    
	
}

































