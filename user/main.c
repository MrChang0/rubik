
#include "stm32f10x.h"
#include "bsp_ov7725.h"
#include "bsp_ili9341_lcd.h"
#include "color.h"
#include "bsp_TiMbase.h"
#include "mofang.h"
#include "rubik.h"

extern uint32_t time;

extern u8 page;
extern HSL_type hsl_l[9];
extern char flag;
extern char flag2;
extern uint8_t Ov7725_vsync;
extern 	MidCoordinate_type  Mid[9];
//extern	uint16_t HorizontalL[40];     //横
//extern	uint16_t HorizontalR[40];     //横
//extern	uint16_t VerticalU[40];       //竖
//extern	uint16_t VerticalD[40];       //竖
//extern u8 Judgerubik;
void displaystep(char* step);
void init(void);
/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void) 	
{
	u8 i,temp=0;
	char rubik[6][9]=
	{ 0
//		{ 3,4,5,1,6,2,3,6,1 },//F 0
//		{ 2,1,1,2,1,5,2,5,4 },//U 1
//		{ 4,5,6,3,5,1,3,3,1 },//D 2
//		{ 5,3,5,4,4,2,1,4,5 },//L 3
//		{ 6,3,4,5,2,6,2,4,4 },//R 4
//		{ 6,6,6,2,3,6,3,1,2 },//B 5
	};
	char step[40]={0};
	end();
	init();
//	Mid[4].x=160;
//	Mid[4].y=120;
//	start();
	while(1)
	{
		if( Ov7725_vsync == 2 )
		{
			LCD_OpenWindow(0, 0, 320, 240);
			LCD_ILI9341_CMD(0X2C);	
			FIFO_PREPARE;  			/*FIFO准备*/					
			ImagDisp();					/*采集并显示*/
			Dispaly_H();
//			if(temp==0)
//			{
//				flag=0;
//				time=0;
//				if(flag==1)
//					start();
//				temp=1;
//				time=0;
//				flag=0;
//			}
			if(page/2 <6)
			{
				for(i=0;i<9;i++)
					rubik[page/2][i]=hsl_l[i].color;
			}
			if(page/2==8)
			{
				start();
				page++;
			}
			if(page/2==9)
			{
				Rubik(rubik,step);
				Optimization(step);
				rubikStep(step);
				end();
				page=0;
				temp=2;
			}
//					switch (page)
//					{		
//						case 0:U();break;
//						case 1:D();break;
//						case 2:L();break;
//						case 3:R();break;
//						case 4:B();break;
//						case 5:Retn();break;
//					}
//			flag=0;
//			time=0;
			Ov7725_vsync = 0;
		}

		  displaystep(step);
	}
}

void init()
{
	/* 液晶初始化 */
	LCD_Init();

	/* ov7725 gpio 初始化 */
	Ov7725_GPIO_Config();
	
	/* ov7725 寄存器配置初始化 */
	while(Ov7725_Init() != SUCCESS);
	
	/* ov7725 场信号线初始化 */
	VSYNC_Init();
	
	Ov7725_vsync = 0;
	
//	/* TIM2 定时配置 */	
//  TIM2_Configuration();
//	
//	/* 实战定时器的中断优先级 */
//	TIM2_NVIC_Configuration();

//	/* TIM2 重新开时钟，开始计时 */
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	
}
void displaystep(char* step)
{
	int i=0;
	while(step[i] != 0)
	{
		if(i<20)
			LCD_DisNum(10+i*15,140,step[i],WHITE);
		else
			LCD_DisNum(10+(i-20)*15,160,step[i],WHITE);
		i++;
	}
}
/*********************************************END OF FILE**********************/

