#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

#define ON 0
#define OFF 1

void LED_GPIO_Config(void);
void EXTI_PC13_Config(void);
void NVIC_Configuration(void);
void EXTI15_10_IRQHandler(void);

#endif
