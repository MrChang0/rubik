#ifndef __USART_H
#define __USART_H
#include"stm32f10x.h"


void USART1_Config(void);
void RECEIVE_Config(void);
void Send(uint8_t Data);
void USART1_IRQHandler(void);
u8 Receiving(u8 num);

#endif
