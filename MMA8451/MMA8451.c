#include "MMA8451.h"
#include "math.h"  
#include "LED.h" 
#include "IIC.h"



//��ʼ��MMA845x.
//����ֵ:0,��ʼ���ɹ�;1,��ʼ��ʧ��.
void MMA845x_init()
{	
//	u8 v=0;
	init_I2C();
//	MMA845x_writebyte(0x2A,0x01);
	MMA845x_writebyte(MMA845x_IIC_ADDRESS,CTRL_REG1,ASLP_RATE_20MS+DATA_RATE_5MS);	
	MMA845x_writebyte(MMA845x_IIC_ADDRESS,XYZ_DATA_CFG_REG, FULL_SCALE_2G); //2G
	MMA845x_writebyte(MMA845x_IIC_ADDRESS,CTRL_REG1, (ACTIVE_MASK+ASLP_RATE_20MS+DATA_RATE_5MS)&(~FREAD_MASK)); //����״̬   14bit
 //   v= MMA845x_readbyte(WHO_AM_I_REG);
//	if(v == MMA8451Q_ID) 
  // 	 	LED0 = 1;
}

/************************************************************************************/
/*********************��MMA8451д������dat��д��ļĴ�����ַΪadd********************/
/******************************д��ɹ�����0��ʧ���򷵻�1****************************/
/************************************************************************************/
uint8_t MMA845x_writebyte(u8 SlaveAddress,u8 address, u8 thedata)//
{
	I2C_start();		//����  
	
	if(I2C_send(SlaveAddress));	//д���豸ID��д�ź�//MMA845x_IIC_ADDRESS
	{
		I2C_stop();
		return 1;
	}	  
	if(I2C_send(address));	//X��ַ
	{
		I2C_stop();
		return 1;
	}	  	
	if(I2C_send(thedata));  //
	{
		I2C_stop();
		return 1;
	}	 
	I2C_stop();
	return 0;
}
/************************************************************************************/
/**********************��MMA8451��ȡ8λ���ݣ���ȡ�ļĴ�����ַΪadd*******************/
/************************************************************************************/
uint8_t MMA845x_readbyte(uint8_t SlaveAddress,uint8_t address)//
{
    uint8_t data = 0;
	 
	I2C_start();		//���� 
	if(I2C_send(SlaveAddress))	//д���豸ID��д�ź�MMA845x_IIC_ADDRESS
	{
		I2C_stop();
		return ;
	}	 
	if(I2C_send(address))	//X��ַ
	{
		I2C_stop();
		return ;
	}
		
	I2C_restart();        //��������	  
		
	if(I2C_send(SlaveAddress+1))  //д���豸ID������MMA845x_IIC_ADDRESS
	{
		I2C_stop();
		return ;
	}
		 
	data = I2C_receive(1);     //��ȡ����
	I2C_stop();
	return data;	
}





//��Z�������  Z����������
int MMA845x_Read_Z()
{
    uint8_t  z=0;
    int  wz=0; 
   	z = MMA845x_readbyte(MMA845x_IIC_ADDRESS,OUT_Z_MSB_REG); //
  	wz = ((MMA845x_readbyte(MMA845x_IIC_ADDRESS,OUT_Z_LSB_REG))|z<<8);  	///	
    if(z>0x7f) //����������ٶ�ԭʼ��Ӧ��ֵ
	 {			          
		 wz=(~(wz>>2) + 1)&0X3FFF ; //��λȡ����һ��ȥ����Ч�ַ� 
		 wz=-wz;		    
	 }
    else
      {		
	    wz=(wz>>2)&0x3FFF ; 	//��λ��ȥ����Ч�ַ� 
	   
      }   
	return  wz;
}  

/**********************************
**�������ƣ�Z_Average
**���� : m Ҫƽ���Ĵ���
          
**�����ƽ�����ֵ 
**��������:	��ƽ��ֵ
***********************************/
s16 Z_Average(u8 times)
{
	u8 i = 0;
	s16 k = 0 ;
	s32 all=0;
	for(i=0;i<times;i++)
	{
		all += MMA845x_Read_Z();	
	}
	k = (s16)(all /times);
	return (k);
}


//��Z��ļ��ٶ�  
float MMA8451x_GZ_Value()
{
    float G_Value=0,wz;
	wz=MMA845x_Read_Z();
    G_Value=wz*0.00025;
	return(G_Value);
}





