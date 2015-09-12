#ifndef __control_h
#define __control_h
#include "stm32f10x.h"

void ChangeID(uint8_t ID);
void Baud_Config(uint16_t ID,uint32_t baud);
void ClockWise(uint16_t ID,uint16_t speed,uint16_t angle);
void Dynamo_Config(uint16_t ID,uint16_t speed);
void Reset_Config(uint8_t ID);
void REG_Write(uint8_t ID,uint16_t speed,uint16_t angle);
void Action(void);
void DuoJi(uint8_t ID);
void DianJi(uint8_t ID);
void speedtest(uint8_t ID,uint8_t ch,uint16_t speed);
void Delayus(uint32_t time);

#endif
