# include "Include.h"


void LED_Init(void)
{
//�Ĵ������ã��ο�MPC560XPRM�Ĵ����ο��ֲ�.pdf��280ҳ�Ĵ���˵������
//PCR:pad configuration register
//��100�ŵķ�װ�У���PCR[0..78]
//PCR[0:15]=port A;     PA0......PA15
//PCR[16:31]=port B;    PB0......PB15
//PCR[32:47]=port C     PC0......PC15
//PCR[48:63]=port D     PD0......PD15
//PCR[64:76]=port E     PE0......PE12
//PCR[77:78]=port H     PH9��PH10
//PB[4:7]��PC[0:11] ��ADC��ڣ�����ΪADCʱ��Ҫ��������
  SIU.PCR[7].R = 0x0220;               // ����PA[7]Ϊ��©��� 
  SIU.PCR[9].R = 0x0220;               // ����PA[9]Ϊ��©���
  SIU.PCR[10].R = 0x0220;               // ����PA[10]Ϊ��©���
  SIU.PCR[11].R = 0x0220;               // ����PA[11]Ϊ��©���
  
  SIU.PCR[5].R = 0x0220;//������
  
  SIU.PCR[12].R = 0x0220;               // ����PA[12]Ϊ��©���
  SIU.PCR[13].R = 0x0220;               // ����PA[13]Ϊ��©���
  SIU.PCR[14].R = 0x0220;               // ����PA[14]Ϊ��©���
  SIU.PCR[15].R = 0x0220;               // ����PA[15]Ϊ��©��� 
   
  SIU.PCR[0].R = 0x0103;	            // ����PA[0]Ϊ��©����,����ѡ������ʹ��  
  SIU.PCR[16].R = 0x0103;				// ����PB[0]Ϊ��©����  
  SIU.PCR[17].R = 0x0103; 				// ����PB[1]Ϊ��©����  
  SIU.PCR[42].R = 0x0103;				// ����PC[10]Ϊ��©����
  
  SIU.PCR[74].R = 0x0100; 				//����PE[10]Ϊ��©����
  
    		
  LED0 = 1;
  LED1 = 1;		
  LED2 = 1;	
  LED3 = 1;	
  
  

  Ming=1;
}