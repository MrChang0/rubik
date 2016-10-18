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
{20,335,655,950,400,546},
{20,335,650,950,130,280},
{30,340,660,970,507,631},
{30,340,650,960,560,700},

}; 							//  主舵机转180  -90°   原始位置    90°     副舵机收  伸
void left90(uint8_t _ID) 
{
	char ID=2*_ID-1;
	ClockWise(ID,0,number[_ID-1][med]);
	ClockWise(ID,0,number[_ID-1][med]);
	while(JudgeToGO(ID,number[_ID-1][med])!=1);
	
	ClockWise(ID+1,0,number[_ID-1][_high]-8);
	while(JudgeToGO(ID+1,number[_ID-1][_high]-8)!=1);
	
	ClockWise(ID,0,number[_ID-1][high]);
 	while(JudgeToGO(ID,number[_ID-1][high])!=1);
	
  ClockWise(ID+1,0,number[_ID-1][_low]);
	while(JudgeToGO(ID+1,number[_ID-1][_low])!=1);
	
	ClockWise(ID,0,number[_ID-1][med]);
	while(JudgeToGO(ID,number[_ID-1][med])!=1);
	
	ClockWise(ID+1,0,number[_ID-1][_high]);
	while(JudgeToGO(ID+1,number[_ID-1][_high])!=1);
}
void right90(uint8_t _ID)  
{
	char ID=2*_ID-1;
	ClockWise(ID,0,number[_ID-1][med]);
	while(JudgeToGO(ID,number[_ID-1][med])!=1);
	ClockWise(ID+1,0,number[_ID-1][_high]-8);
	while(JudgeToGO(ID+1,number[_ID-1][_high]-8)!=1);
	
	ClockWise(ID,0,number[_ID-1][low]);
 	while(JudgeToGO(ID,number[_ID-1][low])!=1);
	
  ClockWise(ID+1,0,number[_ID-1][_low]);
	while(JudgeToGO(ID+1,number[_ID-1][_low])!=1);
	
	ClockWise(ID,0,number[_ID-1][med]);
	while(JudgeToGO(ID,number[_ID-1][med])!=1);
	
	ClockWise(ID+1,0,number[_ID-1][_high]);
	while(JudgeToGO(ID+1,number[_ID-1][_high])!=1);
}

void turn180(uint8_t _ID) 
{
	char ID=2*_ID-1;
	
	ClockWise(ID,0,number[_ID-1][med]);
	while(JudgeToGO(ID,number[_ID-1][med])!=1);
	ClockWise(ID+1,0,number[_ID-1][_high]-8);
	while(JudgeToGO(ID+1,number[_ID-1][_high]-8)!=1);
	
	ClockWise(ID,0,number[_ID-1][zero]);
 	while(JudgeToGO(ID,number[_ID-1][zero])!=1);
	
  ClockWise(ID+1,0,number[_ID-1][_low]);
	while(JudgeToGO(ID+1,number[_ID-1][_low])!=1);
	
	ClockWise(ID,0,number[_ID-1][med]);
	while(JudgeToGO(ID,number[_ID-1][med])!=1);
	
	ClockWise(ID+1,0,number[_ID-1][_high]);
	while(JudgeToGO(ID+1,number[_ID-1][_high])!=1);
}

void allleft90()               /* 整体逆时针90  */
{
	REG_Write(8,0,number[3][_low]);
	REG_Write(8,0,number[3][_low]);
	REG_Write(4,0,number[1][_low]);
	Action();
	while(JudgeToGO(4,number[1][_low])!=1);
	
	REG_Write(5,0,number[2][high]);
	REG_Write(1,0,number[0][low]);
	Action();
	while(JudgeToGO(1,number[0][low])!=1);
	
	REG_Write(4,0,number[1][_high]);
	REG_Write(8,0,number[3][_high]);
	Action();
	while(JudgeToGO(8,number[3][_high])!=1);
	
	REG_Write(6,0,number[2][_low]);
	REG_Write(2,0,number[0][_low]);
	Action();
	while(JudgeToGO(2,number[0][_low])!=1);
	
	REG_Write(1,0,number[0][med]);
	REG_Write(5,0,number[2][med]);
	Action();
	while(JudgeToGO(5,number[2][med])!=1);
	
	REG_Write(2,0,number[0][_high]);
	REG_Write(6,0,number[2][_high]);
	Action();
	while(JudgeToGO(6,number[2][_high])!=1);
}

void allright90()              /* 整体顺时针90  */
{
//	REG_Write(4,0,number[1][_low]);
//	REG_Write(4,0,number[1][_low]);
//	REG_Write(8,0,number[3][_low]);
//	Action();
//	while(JudgeToGO(8,number[3][_low])!=1);
//	
//	REG_Write(1,0,number[0][high]);
//	REG_Write(5,0,number[2][low]);
//	Action();
//	while(JudgeToGO(5,number[2][low])!=1);
//	
//	REG_Write(4,0,number[1][_high]);
//	REG_Write(8,0,number[3][_high]);
//	Action();
//	while(JudgeToGO(8,number[3][_high])!=1);
//	
//	REG_Write(6,0,number[2][_low]);
//	REG_Write(2,0,number[0][_low]);
//	Action();
//	while(JudgeToGO(2,number[0][_low])!=1);
//	
//	REG_Write(1,0,number[0][med]);
//	REG_Write(5,0,number[2][med]);
//	Action();
//	while(JudgeToGO(5,number[2][med])!=1);
//	
//	REG_Write(2,0,number[0][_high]);
//	REG_Write(6,0,number[3][_high]);
//	Action();
//	while(JudgeToGO(6,number[3][_high])!=1);

	REG_Write(2,0,number[0][_low]);
	REG_Write(2,0,number[0][_low]);
	REG_Write(6,0,number[2][_low]);
	Action();
	while(JudgeToGO(6,number[2][_low])!=1);
	
	REG_Write(1,0,number[0][low]);
	REG_Write(5,0,number[2][high]-15);
	Action();
	while(JudgeToGO(5,number[2][high])!=1);
	
	REG_Write(2,0,number[0][_high]);
	REG_Write(6,0,number[2][_high]-5);
	Action();
	while(JudgeToGO(6,number[2][_high]-5)!=1);

	REG_Write(4,0,number[1][_low]);
	REG_Write(8,0,number[3][_low]);
	Action();
	while(JudgeToGO(8,number[3][_low])!=1);
	
	REG_Write(1,0,number[0][med]);
	REG_Write(5,0,number[2][med]);
	Action();
	while(JudgeToGO(5,number[2][med])!=1);
	
	REG_Write(4,0,number[1][_high]);
	REG_Write(8,0,number[3][_high]);
	Action();
	while(JudgeToGO(8,number[3][_high])!=1);
}


void Delayms(uint16_t time)
{
	uint16_t j;
	while(time--)
	{
		j=8000;
		while(j--);
	}
}

void start()
{
	ClockWise(1,0,number[0][med]);
	ClockWise(1,0,number[0][med]);
	ClockWise(1,0,number[0][med]);
	ClockWise(3,0,number[1][med]);
	ClockWise(5,0,number[2][med]);
	ClockWise(7,0,number[3][med]);
	while(JudgeToGO(7,number[3][med])!=1);
	
	ClockWise(2,0,number[0][_high]);
	while(JudgeToGO(2,number[0][_high])!=1);
	REG_Write(4,0,number[1][_high]);
	REG_Write(8,0,number[3][_high]);
	Action();
	while(JudgeToGO(8,number[3][_high])!=1);
	ClockWise(6,0,number[2][_high]);
	while(JudgeToGO(6,number[2][_high])!=1);
}

void end()
{
	REG_Write(1,0,number[0][med]);
	REG_Write(1,0,number[0][med]);
	REG_Write(3,0,number[1][med]);
	REG_Write(5,0,number[2][med]);
	REG_Write(7,0,number[3][med]);
	REG_Write(2,0,number[0][_low]);
	REG_Write(4,0,number[1][_low]);
	REG_Write(8,0,number[3][_low]);
	REG_Write(6,0,number[2][_low]);
	Action();
	while(JudgeToGO(6,number[2][_low])!=1);
}

void U()
{
	REG_Write(2,0,number[0][_low]);
	REG_Write(2,0,number[0][_low]);
	REG_Write(6,0,number[2][_low]);
	Action();
	while(JudgeToGO(6,number[2][_low])!=1);
	REG_Write(3,0,number[1][low]);
	REG_Write(7,0,number[3][high]);
	Action();
	while(JudgeToGO(7,number[3][high])!=1);
}

void D()
{
	REG_Write(3,0,number[1][high]);
	REG_Write(7,0,number[3][low]);
	Action();
	while(JudgeToGO(7,number[3][low])!=1);
}

void L()
{
	REG_Write(3,0,number[1][med]);
	REG_Write(3,0,number[1][med]);
	REG_Write(7,0,number[3][med]);
	Action();
	while(JudgeToGO(7,number[3][med])!=1);
	
	REG_Write(2,0,number[0][_high]);
	REG_Write(6,0,number[2][_high]-5);
	Action();
	while(JudgeToGO(6,number[2][_high])!=1);
	
	REG_Write(4,0,number[1][_low]);
	REG_Write(8,0,number[3][_low]);
	Action();
	while(JudgeToGO(8,number[3][_low])!=1);
	
	REG_Write(1,0,number[0][high]);
	REG_Write(5,0,number[2][low]);
	Action();
	while(JudgeToGO(5,number[2][low])!=1);
}

void R()
{
	REG_Write(1,0,number[0][low]);
	REG_Write(1,0,number[0][low]);
	REG_Write(5,0,number[2][high]);
	Action();
	while(JudgeToGO(5,number[2][high])!=1);
}

void B()
{
	REG_Write(4,0,number[1][_high]);
	REG_Write(4,0,number[1][_high]);
	REG_Write(8,0,number[3][_high]);
	Action();
	while(JudgeToGO(8,number[3][_high])!=1);
	
	REG_Write(2,0,number[0][_low]);
	REG_Write(6,0,number[3][_low]);
	Action();
	while(JudgeToGO(6,number[3][_low])!=1);
	
	REG_Write(1,0,number[0][med]);
	REG_Write(5,0,number[2][med]);
	Action();
	while(JudgeToGO(5,number[2][med])!=1);
	
	REG_Write(2,0,number[0][_high]);
	REG_Write(6,0,number[3][_high]);
	Action();
	while(JudgeToGO(6,number[3][_high])!=1);
	
	REG_Write(4,0,number[1][_low]);
	REG_Write(8,0,number[3][_low]);
	Action();
	while(JudgeToGO(8,number[3][_low])!=1);
	
	REG_Write(1,0,number[0][low]);
	REG_Write(5,0,number[2][high]);
	Action();
	while(JudgeToGO(5,number[2][high])!=1);
}

void Retn()
{
	REG_Write(1,0,number[0][med]);
	REG_Write(1,0,number[0][med]);
	REG_Write(5,0,number[2][med]);
	Action();
	while(JudgeToGO(5,number[2][med])!=1);
	
	REG_Write(4,0,number[1][_high]);
	REG_Write(8,0,number[3][_high]);
	Action();
	while(JudgeToGO(8,number[3][_high])!=1);
	
	REG_Write(2,0,number[0][_low]);
	REG_Write(6,0,number[2][_low]);
	Action();
	while(JudgeToGO(6,number[2][_low])!=1);
	
	REG_Write(1,0,number[0][low]);
	REG_Write(5,0,number[2][high]-5);
	Action();
	while(JudgeToGO(5,number[2][high])!=1);
	
	REG_Write(2,0,number[0][_high]);
	REG_Write(6,0,number[3][_high]);
	Action();
	while(JudgeToGO(6,number[3][_high])!=1);
	
	REG_Write(4,0,number[1][_low]);
	REG_Write(8,0,number[3][_low]);
	Action();
	while(JudgeToGO(8,number[3][_low])!=1);
	
	REG_Write(1,0,number[0][med]);
	REG_Write(5,0,number[2][med]);
	Action();
	while(JudgeToGO(5,number[2][med])!=1);
	
	REG_Write(4,0,number[1][_high]);
	REG_Write(8,0,number[3][_high]);
	Action();
	while(JudgeToGO(8,number[3][_high])!=1);
	
	REG_Write(2,0,number[0][_low]);
	REG_Write(6,0,number[3][_low]);
	Action();
	while(JudgeToGO(6,number[3][_low])!=1);
	
	REG_Write(2,0,number[0][_high]);
	REG_Write(6,0,number[3][_high]);
	Action();
	while(JudgeToGO(6,number[3][_high])!=1);
}

void Correction()
{
	REG_Write(2,0,number[0][_low]);
	REG_Write(2,0,number[0][_low]);
	REG_Write(6,0,number[3][_low]);
	Action();
	while(JudgeToGO(2,number[0][_low])!=1);
	while(JudgeToGO(6,number[3][_low])!=1);
	
	REG_Write(2,0,number[0][_high]);
	REG_Write(6,0,number[3][_high]);
	Action();
	while(JudgeToGO(2,number[0][_high])!=1);
	while(JudgeToGO(6,number[3][_high])!=1);
}

void rubikStep(char *step)
{
	u8 m=0;
	for(m=0;step[m]!=0;m++)
	{
		switch(step[m])
		{
			case 7:allright90();break;
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
	}
}

void Optimization(char *step)    //步骤优化
{
	int i = 0,n=0;
	int Number = 0;
	while (step[Number] != 0)
		Number++;
	while (step[n] != 0)
	{
		if (step[n] / 10 == 1 || step[n] / 10 == 2)
		{
			for (i = Number; i > n; i--)
				step[i] = step[i - 1];
			step[n + 1] = step[n] + 20;
			step[n] = 7;
			Number++;
			i = n+1;
			while (step[i] != 0)
			{
				i++;
				switch (step[i] / 10)
				{
				case 1:step[i] += 20; break;
				case 2:step[i] += 20; break;
				case 3:step[i] -= 10; break;
				case 4:step[i] -= 30; break;
				default:break;
				}
			}
		}
		n++;
	}
}
void ChangeStep(char *step)
{
	int n = 0, i = 0;
	int Number = 0;
	while (step[Number] != 0)
		Number++;
	while (step[n] != 0)
	{
		if (step[n] % 10 == 2)
		{
			for (i = Number; i > n; i--)
			{
				step[i] = step[i - 1];
			}
			step[n] = step[n]--;
			step[n + 1] = step[n];
			Number++;
		}
		if (step[n] / 10 == 1 || step[n] / 10 == 2)
		{
			for (i = Number; i > n; i--)
			{
				step[i] = step[i - 1];
			}
			step[n] = 10;
			step[n + 1] = step[n] + 20;
			Number++;
		}
		n++;
	}
}

char RubikColorJudge(char rubik[6][9])
{
	char i = 0, j = 0, color[6]={0};
	for (i = 0; i < 6; i++)
		for (j = 0; j < 9; j++)
			switch (rubik[i][j])
			{
			case 1:color[0]++; break;
			case 2:color[1]++; break;
			case 3:color[2]++; break;
			case 4:color[3]++; break;
			case 5:color[4]++; break;
			case 6:color[5]++; break;
			default:break;
			}
	if (color[0]==9&&color[1]==9&&color[2]==9&&color[3]==9&&color[4]==9&&color[5]==9)
		return 1;
	else
		return 0;
}
