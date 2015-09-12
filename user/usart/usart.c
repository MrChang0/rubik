#include "usart.h"

uint16_t buf[240][320];

void USART1_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1,ENABLE);
}

void DMA_Config()
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART_DR_BASE;
	
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)buf;
	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	
	DMA_InitStructure.DMA_BufferSize = 320*240*2;
	
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	DMA_Init(DMA1_Channel4,&DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel4,ENABLE);
	
}

int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(unsigned int)ch);
	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)== RESET);
	
	return(ch);
}
