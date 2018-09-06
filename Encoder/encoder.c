# include "Include.h"
  
  uint8_t  count=0;
  int FeedBack=0;

void Encoder_Init()
{
	  
     
	 SIU.PCR[32].R = 0x0100;               // 设置PC[0]输入
	 SIU.PCR[33].R = 0x0100;               // 设置PC[1]输入
	 SIU.PCR[34].R = 0x0100;               // 设置PC[2]输入
	 SIU.PCR[35].R = 0x0100;               // 设置PC[3]输入
	 SIU.PCR[36].R = 0x0100;               // 设置PC[4]输入
	 SIU.PCR[37].R = 0x0100;               // 设置PC[5]输入
     SIU.PCR[38].R = 0x0100;               // 设置PC[6]输入
     SIU.PCR[39].R = 0x0100;               // 设置PC[7]输入
           
     SIU.PCR[29].R  = 0x0201;               // 设置PB[13]弱上拉输出  计数器清零用的
     CLEAR=0;
}


void Encoder_count()
{

	  FeedBack = Counter;          //读编码器值	
	  CLEAR=1;                     //计数器清零
	  CLEAR=1;                
	  CLEAR=1;
	  CLEAR=1;
	  CLEAR=1;
	  CLEAR=1;
	  CLEAR=0;                      //开始计数
	 // SIU.GPDO[12].B.PDO=0;
	  //count=0;
}


 













