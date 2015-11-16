#ifndef __MOFANG_H_
#define __MOFANG_H_


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
#include "stm32f10x.h"
#include "USART1.h"
#include "control.h"

void Delayms(uint16_t time);
void left90(uint8_t ID);
void right90(uint8_t ID);
void turn180(uint8_t ID);
void allleft90(void);
void allright90(void);
void all180(void);
void start(void);
void end(void);
void U(void);
void D(void);
void L(void);
void R(void);
void B(void);
void Retn(void);
void Correction(void);
void Optimization(char *step);
void rubikStep(char *step);
void ChangeStep(char *step);
char RubikColorJudge(char rubik[6][9]);

#define U1() left90(3);
#define U3() right90(3);
#define U2() turn180(3);

#define R1() left90(2);
#define R3() right90(2);
#define R2() turn180(2);

#define L1() left90(4);
#define L3() right90(4);
#define L2() turn180(4);

#define D1() left90(1);
#define D3() right90(1);
#define D2() turn180(1);

#define F1() allright90();R1();
#define F2() allright90();R2();
#define F3() allright90();R3();

#define B1() allright90();L1();
#define B2() allright90();L2();
#define B3() allright90();L3();



#endif
