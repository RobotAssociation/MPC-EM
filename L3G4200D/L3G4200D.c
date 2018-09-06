#include "L3G4200D.h"
#include "MMA8451.h"
#include "IIC.h"

 //************初始化L3G4200D*********************************
void Init_L3G4200D(void)
{
    init_I2C();
	MMA845x_writebyte(L3G4200_Addr,CTRL_REG11, 0x0f);
	MMA845x_writebyte(L3G4200_Addr,CTRL_REG22, 0x00);
	MMA845x_writebyte(L3G4200_Addr,CTRL_REG33, 0x08);
	MMA845x_writebyte(L3G4200_Addr,CTRL_REG44, 0x30);	//+-2000dps
	MMA845x_writebyte(L3G4200_Addr,CTRL_REG55, 0x00);
}	
//******读取L3G4200D数据****************************************
int READ_L3G4200D(void)
{
   unsigned char BUF[2];
   int T_X=0; 
   BUF[0]= MMA845x_readbyte(L3G4200_Addr,OUT_X_L);
   BUF[1]= MMA845x_readbyte(L3G4200_Addr,OUT_X_H);
   T_X = (BUF[1]<<8)|BUF[0];
   
  // BUF[2]=Single_Read(L3G4200_Addr,OUT_Y_L);
  // BUF[3]=Single_Read(L3G4200_Addr,OUT_Y_H);
  // T_Y=	(BUF[3]<<8)|BUF[2];
  

 //  BUF[4]=Single_Read(L3G4200_Addr,OUT_Z_L);
 //  BUF[5]=Single_Read(L3G4200_Addr,OUT_Z_H);
 //  T_Z=	(BUF[5]<<8)|BUF[4];
   return T_X;
}