#include"USART1.h"

void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	USART_TypeDef USART_Structure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	

	USART_InitStructure.USART_BaudRate=19230;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_Init(USART1,&USART_InitStructure);
	

//  USART1->CR3 |= 1 << 3;
//	USART1->CR3 &= ~(1 << 5);
//	USART1->CR3 &= ~(1 << 1);
//	USART1->CR2 &= ~(1 << 14);
//	USART1->CR2 &= ~(1 << 11);
	
	
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
	
}


void Send(uint8_t Data)
{
	
	
	USART_SendData(USART1,Data);
	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
}


void RECEIVE_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
