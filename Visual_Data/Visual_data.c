# include "Include.h"

typedef unsigned int u16;
typedef unsigned char  u8;
/**********************************
**�������ƣ� RCR_CHECK
**���룺  buf ҪУ�������
          len ҪУ������ݳ���
**�����  У��ֵ
**����������CRC��16ѭ������У��
***********************************/
u16 CRC_CHECK(u8 *buf, u8 len)
{
	u8 i,j;
	u16 CRC_Temp=0xffff;						
	for(i=0;i<len;i++)
		{
			CRC_Temp ^=	buf[i];
			for(j=0;j<8;j++)
			{
				if(CRC_Temp & 0x01)
					CRC_Temp = (CRC_Temp >> 1) ^ 0xa001;//0xa001��ֵ�ǹ��ʱ�׼
				else
					CRC_Temp = CRC_Temp >> 1; 
			}
		}	
		return (CRC_Temp);
}
/**********************************
**�������ƣ� Visual_Data
**���룺Ҫ������ݵ�ָ��  
          
**����� �� 
**���������������ݷ�����λ��
***********************************/
void Visual_Data(int *data)
{
  int temp[4] = {0};
  unsigned int temp1[4] = {0};
  unsigned char databuf[10] = {0};	  //   
  unsigned char i;
  unsigned short CRC16 = 0;
 
  for(i=0;i<4;i++)
   {
    
    temp[i]  = (int)data[i];
    temp1[i] = (unsigned int)temp[i];
    
   }
   
  for(i=0;i<4;i++) 
  {
    databuf[i*2]   = (unsigned char)(temp1[i]%256);
    databuf[i*2+1] = (unsigned char)(temp1[i]/256);
  }
  
  CRC16 = CRC_CHECK(databuf,8);
  databuf[8] = CRC16%256;
  databuf[9] = CRC16/256;

  for(i=0;i<10;i++)
  {
      UART0_TX(databuf[i]);
  }
  
}

