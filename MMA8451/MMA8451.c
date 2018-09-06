#include "MMA8451.h"
#include "math.h"  
#include "LED.h" 
#include "IIC.h"



//初始化MMA845x.
//返回值:0,初始化成功;1,初始化失败.
void MMA845x_init()
{	
//	u8 v=0;
	init_I2C();
//	MMA845x_writebyte(0x2A,0x01);
	MMA845x_writebyte(MMA845x_IIC_ADDRESS,CTRL_REG1,ASLP_RATE_20MS+DATA_RATE_5MS);	
	MMA845x_writebyte(MMA845x_IIC_ADDRESS,XYZ_DATA_CFG_REG, FULL_SCALE_2G); //2G
	MMA845x_writebyte(MMA845x_IIC_ADDRESS,CTRL_REG1, (ACTIVE_MASK+ASLP_RATE_20MS+DATA_RATE_5MS)&(~FREAD_MASK)); //激活状态   14bit
 //   v= MMA845x_readbyte(WHO_AM_I_REG);
//	if(v == MMA8451Q_ID) 
  // 	 	LED0 = 1;
}

/************************************************************************************/
/*********************向MMA8451写入数据dat，写入的寄存器地址为add********************/
/******************************写入成功返回0，失败则返回1****************************/
/************************************************************************************/
uint8_t MMA845x_writebyte(u8 SlaveAddress,u8 address, u8 thedata)//
{
	I2C_start();		//启动  
	
	if(I2C_send(SlaveAddress));	//写入设备ID及写信号//MMA845x_IIC_ADDRESS
	{
		I2C_stop();
		return 1;
	}	  
	if(I2C_send(address));	//X地址
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
/**********************从MMA8451读取8位数据，读取的寄存器地址为add*******************/
/************************************************************************************/
uint8_t MMA845x_readbyte(uint8_t SlaveAddress,uint8_t address)//
{
    uint8_t data = 0;
	 
	I2C_start();		//启动 
	if(I2C_send(SlaveAddress))	//写入设备ID及写信号MMA845x_IIC_ADDRESS
	{
		I2C_stop();
		return ;
	}	 
	if(I2C_send(address))	//X地址
	{
		I2C_stop();
		return ;
	}
		
	I2C_restart();        //重新启动	  
		
	if(I2C_send(SlaveAddress+1))  //写入设备ID及读信MMA845x_IIC_ADDRESS
	{
		I2C_stop();
		return ;
	}
		 
	data = I2C_receive(1);     //读取数据
	I2C_stop();
	return data;	
}





//读Z轴的数据  Z读到的数据
int MMA845x_Read_Z()
{
    uint8_t  z=0;
    int  wz=0; 
   	z = MMA845x_readbyte(MMA845x_IIC_ADDRESS,OUT_Z_MSB_REG); //
  	wz = ((MMA845x_readbyte(MMA845x_IIC_ADDRESS,OUT_Z_LSB_REG))|z<<8);  	///	
    if(z>0x7f) //补码求出加速度原始对应数值
	 {			          
		 wz=(~(wz>>2) + 1)&0X3FFF ; //移位取反加一再去掉无效字符 
		 wz=-wz;		    
	 }
    else
      {		
	    wz=(wz>>2)&0x3FFF ; 	//移位再去掉无效字符 
	   
      }   
	return  wz;
}  

/**********************************
**函数名称：Z_Average
**输入 : m 要平均的次数
          
**输出：平均后的值 
**功能描述:	求平均值
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


//读Z轴的加速度  
float MMA8451x_GZ_Value()
{
    float G_Value=0,wz;
	wz=MMA845x_Read_Z();
    G_Value=wz*0.00025;
	return(G_Value);
}





