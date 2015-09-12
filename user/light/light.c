#include "led.h"

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;  //结构体
	
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);    // 外设时钟ABP2
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init (GPIOB,&GPIO_InitStructure);   //初始化地址 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	
	GPIO_Init (GPIOC,&GPIO_InitStructure); 
	
	GPIO_SetBits (GPIOB,GPIO_Pin_0);  //关闭gpiob的灯
	
	GPIO_SetBits (GPIOC,GPIO_Pin_3); //关闭gpioc的灯
	
	GPIO_SetBits (GPIOC,GPIO_Pin_4);
}
