# include "Include.h"
  
  uint8_t  count=0;
  int FeedBack=0;

void Encoder_Init()
{
	  
     
	 SIU.PCR[32].R = 0x0100;               // ����PC[0]����
	 SIU.PCR[33].R = 0x0100;               // ����PC[1]����
	 SIU.PCR[34].R = 0x0100;               // ����PC[2]����
	 SIU.PCR[35].R = 0x0100;               // ����PC[3]����
	 SIU.PCR[36].R = 0x0100;               // ����PC[4]����
	 SIU.PCR[37].R = 0x0100;               // ����PC[5]����
     SIU.PCR[38].R = 0x0100;               // ����PC[6]����
     SIU.PCR[39].R = 0x0100;               // ����PC[7]����
           
     SIU.PCR[29].R  = 0x0201;               // ����PB[13]���������  �����������õ�
     CLEAR=0;
}


void Encoder_count()
{

	  FeedBack = Counter;          //��������ֵ	
	  CLEAR=1;                     //����������
	  CLEAR=1;                
	  CLEAR=1;
	  CLEAR=1;
	  CLEAR=1;
	  CLEAR=1;
	  CLEAR=0;                      //��ʼ����
	 // SIU.GPDO[12].B.PDO=0;
	  //count=0;
}


 













