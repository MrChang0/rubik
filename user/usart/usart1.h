#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include <stdio.h>

#define USART_DR_BASE 0x40013804
#define SENDBUFF_SIZE 5000



void USART1_Config(void); 
void DMA_Config(void);
	
#endif
