#include "rubik.h"
#include "mofang.h"
/*
           5 
  -------- 6-------------
 |                       |
 |                       |
 |                       |
 |                       |
7 8                     4 3
 |                       |
 |                       |
 |                       |
 |                       |
 |                       |
  ---------2-------------
           1
魔方机器人 舵机编号
*/
void UL()
{
	left90(5);
}
void UR()
{
	right90(5);
}
void UT()
{
	turn180(5);
}
void RL()
{
	left90(3);
}
void RR()
{
	right90(3);
}
void RT()
{
	turn180(3);
}
void LL()
{
	left90(7);
}
void LR()
{
	right90(7);
}
void LT()
{
	turn180(7);
}
