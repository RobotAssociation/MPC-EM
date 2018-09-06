/****************************************************************
*³¬Éù²¨²â¾àÄ£¿é
*
****************************************************************/



# include "Include.h"
uint16_t range_left=0,range_right=0;

/**************Íù¼Ä´æÆ÷ÀïÃæĞ´*********************/
void write_byte(uint8_t address,uint8_t reg,uint8_t command)
{
   uint8_t ak;
   I2C_start();
   while(I2C_send(address));  
   while(I2C_send(reg));
   ak=I2C_send(command);
   //while(!ak);
   I2C_stop();
   delay_ms(1);
}

uint8_t read_byte(uint8_t address,uint8_t reg)
{
   uint8_t dat;
   I2C_start();    
   /*while(I2C_send(address)); 
   while(I2C_send(reg));*/
   while(I2C_send(address+1)); 
   dat=I2C_receive(1);
   I2C_stop();
   delay_ms(1);
   return dat;

}
/*******************¸Ä±äµØÖ·º¯Êı******************************/
uint16_t Change_Addr(uint8_t addr_old,uint8_t addr_new)
{
   	delay_ms(2000);
   	write_byte(addr_old,2,0x9a);
   	delay_ms(1);
   	write_byte(addr_old,2,0x92);
   	delay_ms(1); 
   	write_byte(addr_old,2,0x9e);
   	delay_ms(1);
   	write_byte(addr_old,2,addr_new);
   	delay_ms(500);   	 	
}



uint16_t detect(uint8_t address,uint8_t command)
{    
	uint16_t distance=0,count1;
	write_byte(address,2,command);
 // while(!SCL);
    delay_ms(10);
	count1=800;
	while(--count)
	{
	}
	distance=read_byte(address,2);
    distance <<= 8;
    distance += read_byte(address,3);
  	distance=distance/58;
   
	return distance;
	
}

/*******************³¬Éù²¨Ì½²âº¯Êı**************************/
uint8_t Ultrasonic_detect(void)
{
	range_left  = detect(0xe8,0x14);
	//if(range_left>40)
//	range_left=40;
    //range_right = detect(0xe6,0x14);
}

/*int main(void)
{
   init_system();     //ÏµÍ³³õÊ¼»¯   
   module_init();

   //delay_ms(1000);	
   while(1)
   {
   
   //dianji_pwm(10,0);
    range = detect(0xe8,0x0a);
  //0xe8 is the address; 0xb0 is the command.you just need the only one sentence to get the range.
    DATA[0]=range;
    DATA[1]=100;
    Visual_Data(DATA);
   }
   
}
*/