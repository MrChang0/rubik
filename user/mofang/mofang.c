#include "mofang.h"
#include "control.h"
void Delayms(uint16_t time);
/* 主要舵机是范围  0---330-----650------954*/  //290
/* 小舵机 范围   500----630*/
#define high 3
#define low 1
#define med 2
#define zero 0

#define _high 5
#define _low 4

int number[4][6]={
{20,335,650,950,400,542},
{20,335,650,950,130,234},
{30,340,660,970,507,633},
{30,340,650,960,560,720},
}; 							//  主舵机转180  -90°   原始位置    90°     副舵机收  伸

//void open()
//{
//	uint8_t i;
//	
//	for(i=2;i<9;i=i+2)
//	{
//		ClockWise(i,0,_low);
//	}
//}
//void close()
//{
//		uint8_t i;
//	
//	for(i=0;i<9;i=i+2)
//	{
//		ClockWise(i,0,_high);
//	}
//}
void left90(uint8_t _ID) 
{
	char ID=2*_ID-1;
	ClockWise(ID,0,number[_ID-1][med]);
	Delayms(100);
	ClockWise(ID+1,0,number[_ID-1][_high]);
	Delayms(100);
	ClockWise(ID,0,number[_ID-1][high]);
 	Delayms(2000);
  ClockWise(ID+1,0,number[_ID-1][_low]);
	Delayms(2000);
	ClockWise(ID,0,number[_ID-1][med]);
	Delayms(2000);
	ClockWise(ID+1,0,number[_ID-1][_high]);
	Delayms(2000);
}
void right90(uint8_t _ID)  
{
	char ID=2*_ID-1;
	ClockWise(ID,0,number[_ID-1][med]);
	ClockWise(ID+1,0,number[_ID-1][_high]);
	ClockWise(ID,0,number[_ID-1][low]);
 	Delayms(2000);
  ClockWise(ID+1,0,number[_ID-1][_low]);
	Delayms(2000);
	ClockWise(ID,0,number[_ID-1][med]);
	Delayms(2000);
	ClockWise(ID+1,0,number[_ID-1][_high]);
	Delayms(2000);
}
void turn180(uint8_t _ID) 
{
	char ID=2*_ID-1;
	REG_Write(ID,0,number[_ID-1][med]);
	REG_Write(ID+1,0,number[_ID-1][_high]);
	Action();
	Delayms(200);
	ClockWise(ID,0,number[_ID-1][zero]);
 	Delayms(2000);
  ClockWise(ID+1,0,number[_ID-1][_low]);
	Delayms(2000);
	ClockWise(ID,0,number[_ID-1][med]);
	Delayms(2000);
	ClockWise(ID+1,0,number[_ID-1][_high]);
	Delayms(2000);
}

void allleft90()               /* 整体逆时针90  */
{
	REG_Write(8,0,number[3][_low]);
	REG_Write(8,0,number[3][_low]);
	REG_Write(4,0,number[1][_low]);
	Action();
	Delayms(2000);
	REG_Write(5,0,number[2][high]);
	REG_Write(1,0,number[0][low]);
	Action();
	Delayms(2000);
	REG_Write(4,0,number[1][_high]);
	REG_Write(8,0,number[3][_high]);
	Action();
	Delayms(2000);
	REG_Write(6,0,number[2][_low]);
	REG_Write(2,0,number[0][_low]);
	Action();
	Delayms(2000);
	REG_Write(1,0,number[0][med]);
	REG_Write(5,0,number[2][med]);
	Action();
	Delayms(2000);
	REG_Write(2,0,number[0][_high]);
	REG_Write(6,0,number[2][_high]);
	
	Delayms(2000);
}
void allright90()              /* 整体顺时针90  */
{
	REG_Write(4,0,number[1][_low]);
	REG_Write(4,0,number[1][_low]);
	REG_Write(8,0,number[3][_low]);
	Action();
	Delayms(2000);
	REG_Write(1,0,number[0][high]);
	REG_Write(5,0,number[2][low]);
	Action();
	Delayms(2000);
	REG_Write(4,0,number[1][_high]);
	REG_Write(8,0,number[3][_high]);
	Action();
	Delayms(2000);
	REG_Write(6,0,number[2][_low]);
	REG_Write(2,0,number[0][_low]);
	Action();
	Delayms(2000);
	REG_Write(1,0,number[0][med]);
	REG_Write(5,0,number[2][med]);
	Action();
	Delayms(2000);
	REG_Write(2,0,number[0][_high]);
	REG_Write(6,0,number[3][_high]);
	Action();
	Delayms(2000);
}
//void all180() 
//{
//	allleft90();
//	Delayms(2000);
//	allleft90();
//}

void Delayms(uint16_t time)
{
	uint16_t j;
	while(time--)
	{
		j=8000;
		while(j--);
	}
}

void rubikStep(char *step)
{
	u8 m=0;
	for(m=0;step[m]!=0;m++)
	{
		switch(step[m])
		{
			case 11:F1();break;
			case 12:F2();break;
			case 13:F3();break;
			case 21:B1();break;
			case 22:B2();break;
			case 23:B3();break;
			case 31:R1();break;
			case 32:R2();break;
			case 33:R3();break;
			case 41:L1();break;
			case 42:L2();break;
			case 43:L3();break;
			case 51:U1();break;
			case 52:U2();break;
			case 53:U3();break;
			case 61:D1();break;
			case 62:D2();break;
			case 63:D3();break;
			default:break;
		}
		Delayms(2000);
	}
}
void start()
{
	ClockWise(1,0,number[0][med]);
	ClockWise(1,0,number[0][med]);
	ClockWise(3,0,number[1][med]);
	ClockWise(5,0,number[2][med]);
	ClockWise(7,0,number[3][med]);
	Delayms(2000);
	ClockWise(2,0,number[0][_high]);
	Delayms(2000);
	REG_Write(4,0,number[1][_high]);
	REG_Write(8,0,number[3][_high]);
	Action();
	Delayms(2000);
	ClockWise(6,0,number[2][_high]);
}
void end()
{
	ClockWise(2,0,number[0][_low]);
	ClockWise(2,0,number[0][_low]);
	ClockWise(4,0,number[1][_low]);
	ClockWise(6,0,number[2][_low]);
	ClockWise(8,0,number[3][_low]);
	ClockWise(1,0,number[0][med]);
	ClockWise(3,0,number[1][med]);
	ClockWise(5,0,number[2][med]);
	ClockWise(7,0,number[3][med]);
	Action();
}
void U()
{
	REG_Write(2,0,number[0][_low]);
	REG_Write(2,0,number[0][_low]);
	REG_Write(6,0,number[2][_low]);
	Action();
	Delayms(2000);
	REG_Write(3,0,number[1][low]);
	REG_Write(7,0,number[3][high]);
	Action();
}
void D()
{
	REG_Write(3,0,number[1][high]);
	REG_Write(7,0,number[3][low]);
	Action();
}
void L()
{
	REG_Write(3,0,number[1][med]);
	REG_Write(3,0,number[1][med]);
	REG_Write(7,0,number[3][med]);
	Action();
	Delayms(2000);
	REG_Write(2,0,number[0][_high]);
	REG_Write(6,0,number[2][_high]);
	Action();
	Delayms(2000);
	REG_Write(4,0,number[1][_low]);
	REG_Write(8,0,number[3][_low]);
	Action();
	Delayms(2000);
	REG_Write(1,0,number[0][high]);
	REG_Write(5,0,number[2][low]);
	Action();
}
void R()
{
	REG_Write(1,0,number[0][low]);
	REG_Write(1,0,number[0][low]);
	REG_Write(5,0,number[2][high]);
	Action();
	Delayms(2000);

}
void B()
{
	REG_Write(4,0,number[1][_high]);
	REG_Write(4,0,number[1][_high]);
	REG_Write(8,0,number[3][_high]);
	Action();
	Delayms(2000);
	REG_Write(2,0,number[0][_low]);
	REG_Write(6,0,number[3][_low]);
	Delayms(2000);
	Action();
	REG_Write(1,0,number[0][med]);
	REG_Write(5,0,number[2][med]);
	Delayms(2000);
	Action();
	REG_Write(2,0,number[0][_high]);
	REG_Write(6,0,number[3][_high]);
	Delayms(2000);
	Action();
	REG_Write(4,0,number[1][_low]);
	REG_Write(8,0,number[3][_low]);
	Delayms(2000);
	Action();
	REG_Write(1,0,number[0][low]);
	REG_Write(5,0,number[2][high]);
}
void Retn()
{
	REG_Write(1,0,number[0][med]);
	REG_Write(1,0,number[0][med]);
	REG_Write(5,0,number[2][med]);
	Action();
	Delayms(2000);
	REG_Write(4,0,number[1][_high]);
	REG_Write(8,0,number[3][_high]);
	Action();
	Delayms(2000);
	REG_Write(2,0,number[0][_low]);
	REG_Write(6,0,number[2][_low]);
	Action();
	Delayms(2000);
	REG_Write(1,0,number[0][low]);
	REG_Write(5,0,number[2][high]);
	Action();
	Delayms(2000);
	REG_Write(2,0,number[0][_high]);
	REG_Write(6,0,number[3][_high]);
	Action();
	Delayms(2000);
	REG_Write(4,0,number[1][_low]);
	REG_Write(8,0,number[3][_low]);
	Action();
	Delayms(2000);
	REG_Write(1,0,number[0][med]);
	REG_Write(5,0,number[2][med]);
	Action();
	Delayms(2000);
	REG_Write(4,0,number[1][_high]);
	REG_Write(8,0,number[3][_high]);
	Action();
}
