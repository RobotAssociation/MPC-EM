# include "Include.h"






void PWM_Init(void)
{
	SIU.PCR[66].R = 0x0600;               // ����PE[2]ΪeMIOS_0��18ͨ��	�����ת	
	SIU.PCR[67].R = 0x0600;               // ����PE[3]ΪeMIOS_0��19ͨ�� �����ת
	SIU.PCR[76].R = 0x0A00;               // ����PE[12]ΪeMIOS_1��19ͨ�� ���	
	
    EMIOS_0.MCR.B.GPRE  = 1;        // ���÷�Ƶϵ��Ϊ2,��ƵΪ32MHz
    EMIOS_0.MCR.B.GPREN = 1;         // ʹ��eMIOSʱ��
    EMIOS_0.MCR.B.GTBE  = 1;         // ʹ��ȫ��ʱ��
    EMIOS_0.MCR.B.FRZ   = 1;         // �ڶ���ģʽ��ֹͣͨ��
  

   EMIOS_1.MCR.B.GPRE   =31;   //��Ƶϵ��128.f=0.5MHZ=0.2us
   EMIOS_1.MCR.B.GPREN   = 0x1;   //ȫ��Ԥ��Ƶʹ��  
      
  //  EMIOS_1.MCR.B.GPRE  = 0;        // ���÷�Ƶϵ��Ϊ1,����ƵΪ64MHz
  //  EMIOS_1.MCR.B.GPREN = 1;         // ʹ��eMIOSʱ��
    EMIOS_1.MCR.B.GTBE  = 1;         // ʹ��ȫ��ʱ��
    EMIOS_1.MCR.B.FRZ   = 1;         // �ڶ���ģʽ��ֹͣͨ�� 
    		
 //����18ͨ��������100us��
    EMIOS_0.CH[18].CADR.R      = 0;      // �����ױ��ص�ƥ��ֵ
    EMIOS_0.CH[18].CBDR.R      = 1;      // ����β���ص�ƥ��ֵ   
    EMIOS_0.CH[18].CCR.B.BSL   = 0x0;     // ʹ��ͨ��23���ɵ�Bus A
    EMIOS_0.CH[18].CCR.B.EDPOL = 1;       // ���ü��ԣ�Aƥ��ʱ��1��Bƥ��ʱ��0
    EMIOS_0.CH[18].CCR.B.MODE  = 0x60;    // ѡ��OPWMBģʽ
//����19ͨ��������100us��
    EMIOS_0.CH[19].CADR.R      = 0;      // �����ױ��ص�ƥ��ֵ
    EMIOS_0.CH[19].CBDR.R      = 1;      // ����β���ص�ƥ��ֵ   
    EMIOS_0.CH[19].CCR.B.BSL   = 0x0;     // ʹ��Bus A
    EMIOS_0.CH[19].CCR.B.EDPOL = 1;       // ���ü��ԣ�Aƥ��ʱ��1��Bƥ��ʱ��0
    EMIOS_0.CH[19].CCR.B.MODE  = 0x60;    // ѡ��OPWMBģʽ 
 
  
    //����23ͨ������Ϊ18,19,20,21��ʱ��Bus A
    EMIOS_0.CH[23].CADR.R      = 2133;    //��������Ϊ800=100us  
    EMIOS_0.CH[23].CCR.B.MODE  = 0x50;   //����Ϊ����ģ��������ģʽMCB
    EMIOS_0.CH[23].CCR.B.BSL   = 0x3;    //ʹ��64MHz���ڲ���������Ϊʱ��Դ
    EMIOS_0.CH[23].CCR.B.UCPEN = 1;      //ʹ�ܷ�Ƶ��
    EMIOS_0.CH[23].CCR.B.FREN  = 1;      //�ڶ���ģʽ��ֹͣ���� 
    
    
    
    
    
 //����EMIOS_1��19ͨ��������20ms
    EMIOS_1.CH[19].CADR.R      = 0;      // �����ױ��ص�ƥ��ֵ
    EMIOS_1.CH[19].CBDR.R      = 1;      // ����β���ص�ƥ��ֵ   
    EMIOS_1.CH[19].CCR.B.BSL   = 0x0;     // ʹ��ͨ��23���ɵ�Bus A
    EMIOS_1.CH[19].CCR.B.EDPOL = 1;       // ���ü��ԣ�Aƥ��ʱ��1��Bƥ��ʱ��0
    EMIOS_1.CH[19].CCR.B.MODE  = 0x60;    // ѡ��OPWMBģʽ
 //����23ͨ������ΪEMIOS_1��19��ʱ��Bus A
    EMIOS_1.CH[23].CADR.R      = 10000;    //��������Ϊ10000=20ms  
    EMIOS_1.CH[23].CCR.B.MODE  = 0x50;   //����Ϊ����ģ��������ģʽMCB
    EMIOS_1.CH[23].CCR.B.BSL   = 0x3;    //ʹ��64MHz���ڲ���������Ϊʱ��Դ

    EMIOS_1.CH[23].CCR.B.UCPEN = 1;      //ʹ�ܷ�Ƶ��
    EMIOS_1.CH[23].CCR.B.FREN  = 1;      //�ڶ���ģʽ��ֹͣ����   
    
    
   // Angle =700;	//�����ʼ��     //�м�ֵ800
  			
}


void car_direction(int angle)
 {
    Angle = MID_angle + angle;    // ֻ��Ҫ����ƫ�ƽǶ�
 }

void speed_control(int speed)
 {
       	Motor_R_Front = speed;  
 }







