#include "control.h"
#include "USART1.h"

void Delayus(uint32_t time);

u8 Sum=0;
u8 speed_L=0;
u8 speed_H=0;
u8 angle_L=0;
u8 angle_H=0;

void Reset_Config(uint8_t ID)                   /*   复位一个舵机 从电机模式后要复位  */
{ 
	USART1_Config();
	
	Delayus(10000);
	
	Send(0xFF);
	Send(0xFF);
	Send(ID);
	Send(0x02);
	Send(0x06);
  Sum=~(ID+0x02+0x06);
	Send(Sum);
	
  RECEIVE_Config();
	
	Delayus(10000);
}
void RetnMode(uint8_t ID,u8 Mode)
{
	USART1_Config();
	
	Delayus(10000);
	Send(0xFF);
	Send(0xFF);
	Send(ID);
	Send(0x04);
	Send(0x03);
	Send(0x10);
	Send(Mode);
	Sum=0xFF+0xFF+ID+0x04+0x03+0x10+Mode;
	Send(Sum);
}
void ChangeID(uint8_t ID)        /* 改变舵机的ID 断电保存   0<= ID <=255   */
{
	USART1_Config();
	
	Delayus(10000);
	
	Send(0xFF);
	Send(0xFF);
	Send(0xFE);
	Send(0x04);
	Send(0x03);
	Send(0x03);
	Send(ID);
  Sum=~(0xFE+0x04+ID+0x03+0x03);
	Send(Sum);
	
  RECEIVE_Config();
	
	Delayus(10000);
}


void Baud_Config(uint16_t ID,uint32_t baud)     /*  前六个波特率断电保存   */
{
	uint32_t rate;
	rate=baud;
	
	switch(rate)
	{
		case 1000000 : baud=1;break;
		case 500000 : baud=3;break;
		case 250000 : baud=7;break;
		case 115200 : baud=16;break;
		case 57600 : baud=34;break;
		case 19200 : baud=103;break;
		default:baud=2000000/rate-1;break;
	}
	
	USART1_Config();
	
	Delayus(10000);
	
	Send(0xFF);
	Send(0xFF);
	Send(ID);
	Send(0x03);
	Send(0x03);
	Send(0x04);
	Send(baud);
  Sum=~(0x03+0x07+ID+baud);
	Send(Sum);
	
  RECEIVE_Config();
	
	Delayus(10000);	
}


void ClockWise(uint16_t ID,uint16_t speed,uint16_t angle)      /* 舵机模式  0<= speed<= 100 0<= angle<=1023   */
{ 
	uint16_t buf2,buf1;
	buf1=700;
	speed_H=(uint8_t)(buf1>>8);
	speed_L=(uint8_t)buf1;
	
	buf2=angle;
	angle_H=(u8)(buf2>>8);
	angle_L=(u8)buf2;
	
	
	
 	USART1_Config();
	Delayus(10000);
	Send(0xFF);
	Send(0xFF);
	Send(ID);
	Send(0x07);
	Send(0x03);
	Send(0x1E);
	Send(angle_L);
	Send(angle_H);
	Send(speed_L);
	Send(speed_H);
  Sum=~(ID+0x07+0x03+0x1E + angle_H+angle_L+speed_L+speed_H);
	Send(Sum);
	
  RECEIVE_Config();
	
	Delayus(10000);
}
void Dynamo_Config(uint16_t ID,uint16_t speed)           //最高转速
{
	speed_H=(u8)(speed>>8);
	speed_L=(u8)speed;
	
 	USART1_Config();
	Delayus(10000);
	Send(0xFF);
	Send(0xFF);
	Send(ID);
	Send(0x07);
	Send(0x03);
	Send(0X06);	
	Send(0);
	Send(0);	
	Send(0);
	Send(0);		
	Sum=~(ID+0x07+0x09);
	Send(Sum);
 RECEIVE_Config();
	
	Delayus(10000);

 	USART1_Config();
	Delayus(10000);
	Send(0xFF);
	Send(0xFF);
	Send(ID);
	Send(0x07);
	Send(0x03);
	Send(0X20);
	Send(speed_L);
	Send(speed_H);  
  Sum=~(ID+0x07+0x03+0x20+speed_H+speed_L);
	Send(Sum);
	RECEIVE_Config();
}

void REG_Write(uint8_t ID,uint16_t speed,uint16_t angle)   //同时启动   配置运行模式后 用Action()  启动
{
	float buf2,buf1;
	buf1=speed;
	speed_H=(u8)((uint16_t)buf1>>8);
	speed_L=(u8)(uint16_t)buf1;
	
	buf2=angle;
	angle_H=(u8)((uint16_t)buf2>>8);
	angle_L=(u8)(uint16_t)buf2;
	
 	USART1_Config();
	Delayus(10000);
	Send(0xFF);
	Send(0xFF);
	Send(ID);
	Send(0x07);
	Send(0x04);
	Send(0x1E);
	Send(angle_L);
	Send(angle_H);
	Send(speed_L);
	Send(speed_H);
	Sum=~(ID+0x07+0x04+0x1E +angle_H+angle_L+speed_L+speed_H);
	Send(Sum);
	
	
	RECEIVE_Config();
}
void Action()                 //启动REG_Write函数 
{
	USART1_Config();
	Delayus(10000);
	Send(0xFF);
	Send(0xFF);
	Send(0xFE);
	Send(0x02);
	Send(0x05);
	Send(0xFA);
	
	RECEIVE_Config();
}
void DianJi(uint8_t ID)                         //电机模式打开 
{
	USART1_Config();
	Delayus(10000);
	Send(0xFF);
	Send(0xFF);
	Send(ID);
	Send(0x07);
	Send(0x03);
	Send(0x06);
	Send(0x00);
	Send(0x00);
	Send(0x00);
	Send(0x00);
	Sum=~(ID+0x07+0x03+0x06);
	Send(Sum);
	RECEIVE_Config();
	Delayus(100);
}
void DuoJi(uint8_t ID)                         //舵机模式打开 
{
	USART1_Config();
	Delayus(10000);
	Send(0xFF);
	Send(0xFF);
	Send(ID);
	Send(0x07);
	Send(0x03);
	Send(0x06);
	Send(0xff);
	Send(0x03);
	Send(0xff);
	Send(0x03);
	Sum=~(ID+0x07+0x03+0x06+0xff+0x03+0xff+0x03);
	Send(Sum);
	RECEIVE_Config();
	Delayus(100);
}
void speedtest(uint8_t ID,uint8_t ch,uint16_t speed)     //ID选取舵机ID   ch取0或1  是转方向  speed 速度  < 1023   
{
	uint8_t speed_H,speed_L;
	if(speed>1023)
	{
		speed=1023;
	}	
	
	speed |= (ch<<10);
	speed_H=(uint8_t)(speed>>8);
	speed_L=(uint8_t)speed;
	
	USART1_Config();
	
	Delayus(10000);
	Send(0xFF);
	Send(0xFF);
	Send(ID);
	Send(0x05);
	Send(0x03);
	Send(0x20);
	Send(speed_L);
	Send(speed_H);
  Sum=~(ID+0x05+0x03+0x20+speed_H+speed_L);
	Send(Sum);
	
	RECEIVE_Config();
	
}
u8 read_current_location(uint16_t ID,u8 address)																												
{
	int num=0;
	if (address==0x24)
		num=0;
	if (address==0x25)
		num=1;
	USART1_Config();
	
	Delayus(10000);
	Send(0xFF);
	Send(0xFF);
	Send(ID);
	Send(0x04);
	Send(0x02);
	Send(address);
	Send(0x01);
	Sum=~(ID+0x04+0x02+address+0x01);
	Send(Sum);
																																							
	 RECEIVE_Config();
	 Delayus(2000);																																//串口中断接收返回指令
	
	return Receiving(num);																										//返回当前角 把0~1023的数据转换成0~300
}
u16 read_location(u8 ID)
{
		u8 i=0;
		u8 location_L,location_H=0;
		u16 location=0;
	
	u16 a[5];
	u16 k=0;
	
	for(i=0;i<5;i++)
	{
			location_L=read_current_location(ID,0x24);															//读当前档位 并处理  num
			Delayus(10000);
			location_H=read_current_location(ID,0x25);
			location=(u16)location_H<<8|(u16)location_L;
			a[i]=location;		
			Delayus(10000);
	}
	for(i=0;i<5;i++)
	{
			if(k<a[i])	
			{
				k=a[i];
			}
	}
	return k;
}
void Delayus(uint32_t time)
{
	uint32_t i;
	
	while(time--)
	{
		i=8;
		while(i--);
	}
}
u8 JudgeToGO(u8 ID,u16 Angle)
{
	int16_t temp=0;
	while(1)
	{
		temp=read_location(ID)-Angle;
		if(temp<0)
			temp=0-temp;
		if(temp<60)
			return 1;
	}
}
