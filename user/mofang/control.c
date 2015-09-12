#include "control.h"
#include "USART1.h"

void Delayus(uint32_t time);

u8 Sum=0;
u8 speed_L=0;
u8 speed_H=0;
u8 angle_L=0;
u8 angle_H=0;

void Reset_Config(uint8_t ID)                   /*   ��λһ����� �ӵ��ģʽ��Ҫ��λ  */
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
	
void ChangeID(uint8_t ID)        /* �ı�����ID �ϵ籣��   0<= ID <=255   */
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


void Baud_Config(uint16_t ID,uint32_t baud)     /*  ǰ���������ʶϵ籣��   */
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


void ClockWise(uint16_t ID,uint16_t speed,uint16_t angle)      /* ���ģʽ  0<= speed<= 100 0<= angle<=1023   */
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
void Dynamo_Config(uint16_t ID,uint16_t speed)           //���ת��
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

void REG_Write(uint8_t ID,uint16_t speed,uint16_t angle)   //ͬʱ����   ��������ģʽ�� ��Action()  ����
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
void Action()                 //����REG_Write���� 
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
void DianJi(uint8_t ID)                         //���ģʽ�� 
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
void DuoJi(uint8_t ID)                         //���ģʽ�� 
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
void speedtest(uint8_t ID,uint8_t ch,uint16_t speed)     //IDѡȡ���ID   chȡ0��1  ��ת����  speed �ٶ�  < 1023   
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
void Delayus(uint32_t time)
{
	uint32_t i;
	
	while(time--)
	{
		i=8;
		while(i--);
	}
}
