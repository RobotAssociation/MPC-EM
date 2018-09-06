#include "MPC5604B_0M27V_0102.h"
#include "SPI.h"


/************************************************************/
/*                       初始化DSPI0                        */
/************************************************************/
void DSPI0_init(void) 
{
  	SIU.PCR[11].R = 0x0220;        //设置PA[11]为开漏输出，CE
    SIU.PCR[7].R = 0x0220;        //中断接口
	SIU.PCR[13].R = 0x0604;        //设置PA[13]为SOUT接口
	SIU.PCR[12].R = 0x0103;        //设置PA[12]为SIN接口
	SIU.PCR[14].R = 0x0604;        //设置PA[14]为SCK接口
	SIU.PCR[15].R = 0x0223;        //设置PA[15]为开漏输出，作为CS，使能内部上拉电阻
    DSPI_0.MCR.R = 0x80013001;     //设置DSPI0为主模式，CS信号低有效，禁止FIFO
    DSPI_0.CTAR[0].R = 0x38087725; //配置CTAR[0]，设置为每帧数据为8位，高位在前，波特率为1MHz
    DSPI_0.MCR.B.HALT = 0x0;	     //DSPI0处于运行状态
}


/************************************************************/
/*                   DSPI0发送和接收                        */
/************************************************************/
uint8_t DSPI0_send_receive(uint8_t data)
{
	uint8_t input;
	DSPI_0.PUSHR.R = 0x08000000|data;    //赋值需要发送的数据		
	while(DSPI_0.SR.B.TCF==0)            //等待发送完成
	{}
	DSPI_0.SR.B.TCF=1;                   //清除发送完成标志位
	while(DSPI_0.SR.B.RFDF==0)           //等待接收到数据
	{}
	input=(uint8_t)(DSPI_0.POPR.R);      //读取接收到的数据
	DSPI_0.SR.B.RFDF=1;                  //清除接收标志位

	return(input);      //返回接收到的数据
}

