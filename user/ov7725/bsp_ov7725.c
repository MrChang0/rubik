#include "bsp_ov7725.h"
#include "bsp_sccb.h"
#include "bsp_ili9341_lcd.h"
#include "color.h"
#include "mofang.h"
uint16_t MidColorData[3][3];

u8 area[10]={'F', 'U', 'D', 'L', 'R', 'B','0','0','1','2'};

HSL_type hsl_l[9];

u8 page=0;

uint16_t MidColorData[3][3];

u8 HR=1,HL=1,VU=1,VD=1;

MidCoordinate_type  Mid[9];
u16 Radius;
uint16_t HorizontalL[pointNum];     //横左
uint16_t HorizontalR[pointNum];     //横右
uint16_t VerticalU[pointNum];       //竖上
uint16_t VerticalD[pointNum];       //竖下

u8 Judgerubik=0;
u8 n=0;
char flag2;

typedef struct Reg
{
	uint8_t Address;			       /*寄存器地址*/
	uint8_t Value;		           /*寄存器值*/
}Reg_Info;

/* 寄存器参数配置 */
Reg_Info Sensor_Config[] =
{
	{CLKRC,     0x00}, /*clock config*/
	{COM7,      0x46}, /*QVGA RGB565 */
  {HSTART,    0x3f},
	{HSIZE,     0x50},
	{VSTRT,     0x03},
	{VSIZE,     0x78},
	{HREF,      0x00},
	{HOutSize,  0x50},
	{VOutSize,  0x78},
	{EXHCH,     0x00},

	/*DSP control*/
	{TGT_B,     0x7f},
	{FixGain,   0x09},
	{AWB_Ctrl0, 0xe0},
	{DSP_Ctrl1, 0xff},
	{DSP_Ctrl2, 0x20},
	{DSP_Ctrl3,	0x00},
	{DSP_Ctrl4, 0x00},

	/*AGC AEC AWB*/
	{COM8,		  0xf0},
	{COM4,		  0x81}, /*Pll AEC CONFIG*/
	{COM6,		  0xc5},
	{COM9,		  0x21},
	{BDBase,	  0xFF},
	{BDMStep,	  0x01},
	{AEW,		    0x34},
	{AEB,		    0x3c},
	{VPT,		    0xa1},
	{EXHCL,		  0x00},
	{AWBCtrl3,  0xaa},
	{COM8,		  0xff},
	{AWBCtrl1,  0x5d},

	{EDGE1,		  0x0a},
	{DNSOff,	  0x01},
	{EDGE2,		  0x01},
	{EDGE3,		  0x01},

	{MTX1,		  0x5f},
	{MTX2,		  0x53},
	{MTX3,		  0x11},
	{MTX4,		  0x1a},
	{MTX5,		  0x3d},
	{MTX6,		  0x5a},
	{MTX_Ctrl,  0x1e},

	{BRIGHT,	  0x00},
	{CNST,		  0x25},
	{USAT,		  0x65},
	{VSAT,		  0x65},
	{UVADJ0,	  0x81},
	{SDE,		    0x06},
	
    /*GAMMA config*/
	{GAM1,		  0x0c},
	{GAM2,		  0x16},
	{GAM3,		  0x2a},
	{GAM4,		  0x4e},
	{GAM5,		  0x61},
	{GAM6,		  0x6f},
	{GAM7,		  0x7b},
	{GAM8,		  0x86},
	{GAM9,		  0x8e},
	{GAM10,		  0x97},
	{GAM11,		  0xa4},
	{GAM12,		  0xaf},
	{GAM13,		  0xc5},
	{GAM14,		  0xd7},
	{GAM15,		  0xe8},
	{SLOP,		  0x20},

	{HUECOS,	  0x80},
	{HUESIN,	  0x80},
	{DSPAuto,	  0xff},
	{DM_LNL,	  0x00},
	{BDBase,	  0x99},
	{BDMStep,	  0x03},
	{LC_RADI,	  0x00},
	{LC_COEF,	  0x13},
	{LC_XC,		  0x08},
	{LC_COEFB,  0x14},
	{LC_COEFR,  0x17},
	{LC_CTR,	  0x05},
	
	{COM3,		  0xd0},/*Horizontal mirror image*/

	/*night mode auto frame rate control*/
	{COM5,		0xf5},	 /*在夜视环境下，自动降低帧率，保证低照度画面质量*/
	//{COM5,		0x31},	/*夜视环境帧率不变*/
};

u8 OV7725_REG_NUM = sizeof(Sensor_Config)/sizeof(Sensor_Config[0]);	  /*结构体数组成员数目*/

uint8_t Ov7725_vsync = 0;	 /* 帧同步信号标志，在中断函数和main函数里面使用 */


/************************************************
 * 函数名：FIFO_GPIO_Config
 * 描述  ：FIFO GPIO配置
 * 输入  ：无
 * 输出  ：无
 * 注意  ：无
 ************************************************/
static void FIFO_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | 
	                          RCC_APB2Periph_GPIOB | 
	                          RCC_APB2Periph_GPIOC | 
	                          RCC_APB2Periph_GPIOD |
                            RCC_APB2Periph_AFIO	, ENABLE);
	
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	  GPIO_Init (GPIOC,&GPIO_InitStructure);
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13); 
	
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	

		/* 1W LED 灯控制 */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
		//GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
	
		/*PD3(FIFO_WEN--FIFO写使能)*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
	
		/*PB5(FIFO_WRST--FIFO写复位)*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		/*PA2(FIFO_RRST--FIFO读复位) PA3(FIFO_OE--FIFO输出使能)*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 

		/*PC5(FIFO_RCLK-FIFO读时钟)*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /*PB8-PB15(FIFO_DATA--FIFO输出数据)*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    FIFO_CS_L();	  					/*拉低使FIFO输出使能*/
    FIFO_WE_H();   						/*拉高使FIFO写允许*/
}

void Ov7725_GPIO_Config(void)
{
	SCCB_GPIO_Config();
	FIFO_GPIO_Config();
}

/************************************************
 * 函数名：VSYNC_GPIO_Configuration
 * 描述  ：OV7725 GPIO配置
 * 输入  ：无
 * 输出  ：无
 * 注意  ：无
 ************************************************/
static void VSYNC_GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	  /*PA0---VSYNC*/
	
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/************************************************
 * 函数名：VSYNC_NVIC_Configuration
 * 描述  ：VSYNC中断配置
 * 输入  ：无
 * 输出  ：无
 * 注意  ：无
 ************************************************/
static void VSYNC_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	  NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	  NVIC_Init (&NVIC_InitStructure);
}

/************************************************
 * 函数名：VSYNC_EXTI_Configuration
 * 描述  ：OV7725 VSYNC中断管脚配置
 * 输入  ：无
 * 输出  ：无
 * 注意  ：无
 ************************************************/
/*               ___                            ___
 * VSYNC:     __|   |__________________________|   |__     
 */
static void VSYNC_EXTI_Configuration(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    //EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising ; /*上升沿触发*/
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling ; 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    EXTI_GenerateSWInterrupt(EXTI_Line0);	/*中断挂到 EXTI_Line0  线*/
}
void EXTI_PC13_Config(void)
{
		EXTI_InitTypeDef EXTI_InitStructure;
		
		EXTI_InitStructure.EXTI_Line=EXTI_Line13;
		EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
		
		EXTI_InitStructure.EXTI_LineCmd=ENABLE;
		
		EXTI_Init(&EXTI_InitStructure);
}
/************************************************
 * 函数名：VSYNC_Init
 * 描述  ：OV7725 VSYNC中断相关配置
 * 输入  ：无
 * 输出  ：无
 * 注意  ：无
 ************************************************/
void VSYNC_Init(void)
{
    VSYNC_GPIO_Configuration();
    VSYNC_EXTI_Configuration();
    VSYNC_NVIC_Configuration();
	  EXTI_PC13_Config();
}

/************************************************
 * 函数名：Sensor_Init
 * 描述  ：Sensor初始化
 * 输入  ：无
 * 输出  ：返回1成功，返回0失败
 * 注意  ：无
 ************************************************/
ErrorStatus Ov7725_Init(void)
{
	uint16_t i = 0;
	uint8_t Sensor_IDCode = 0;	
	
	//DEBUG("ov7725 Register Config Start......");
	
	if( 0 == SCCB_WriteByte ( 0x12, 0x80 ) ) /*复位sensor */
	{
		//DEBUG("sccb write data error");		
		return ERROR ;
	}	

	if( 0 == SCCB_ReadByte( &Sensor_IDCode, 1, 0x0b ) )	 /* 读取sensor ID号*/
	{
		//DEBUG("read id faild");		
		return ERROR;
	}
	//DEBUG("Sensor ID is 0x%x", Sensor_IDCode);	
	
	if(Sensor_IDCode == OV7725_ID)
	{
		for( i = 0 ; i < OV7725_REG_NUM ; i++ )
		{
			if( 0 == SCCB_WriteByte(Sensor_Config[i].Address, Sensor_Config[i].Value) )
			{                
				//DEBUG("write reg faild", Sensor_Config[i].Address);
				return ERROR;
			}
		}
	}
	else
	{
		return ERROR;
	}
	//DEBUG("ov7725 Register Config Success");
	
	return SUCCESS;
}
/*       320
 * -------------------
 *|                   |
 *|                   |
 *|                   |  240
 *|                   |
 *|                   |
 * -------------------
 */
void ImagDisp(void)
{
	
	uint16_t i, j,m=0;
	uint16_t Camera_Data;
	HR=1;HL=1;VU=1;VD=1;
	for(i = 0; i < 240; i++)
	{
		for(j = 0; j < 320; j++)
		{
			READ_FIFO_PIXEL(Camera_Data);		/* 从FIFO读出一个rgb565像素到Camera_Data变量 */
//			if(i==Mid[4].y&&j>Mid[4].x&&j<=Mid[4].x+pointNum)
//				HorizontalR[j-Mid[4].x]=Camera_Data;
//			if(i==Mid[4].y&&j<Mid[4].x&&j>=Mid[4].x-pointNum)
//				HorizontalL[Mid[4].x-j]=Camera_Data;
//			if(j==Mid[4].x&&i>=Mid[4].y-pointNum&&i<Mid[4].y)
//				VerticalU[Mid[4].y-i]=Camera_Data;
//			if(j==Mid[4].x&&i>Mid[4].y&&i<=Mid[4].y+pointNum)
//				VerticalD[i-Mid[4].y]=Camera_Data;
			
			if(i==80&&j==80)
			{
				MidColorData[0][0]=Camera_Data;
				Camera_Data=0;
			}
			if(i==80&&j==120)
			{
				MidColorData[0][1]=Camera_Data;
				Camera_Data=0;
			}
			if(i==80&&j==160)
			{ 	
				MidColorData[0][2]=Camera_Data;
				Camera_Data=0;
			}
			
			if(i==120&&j==80)
			{
				MidColorData[1][0]=Camera_Data;
				Camera_Data=0;
			}
			if(i==120&&j==120)
			{
				MidColorData[1][1]=Camera_Data;
				Camera_Data=0;
			}
			if(i==120&&j==160)
			{
				MidColorData[1][2]=Camera_Data;
				Camera_Data=0;
			}
			
			if(i==160&&j==80)
			{
				MidColorData[2][0]=Camera_Data;
				Camera_Data=0;
			}
			if(i==160&&j==120)
			{
				MidColorData[2][1]=Camera_Data;
				Camera_Data=0;
			}
			if(i==160&&j==160)
			{
				MidColorData[2][2]=Camera_Data;
				Camera_Data=0;
			}
			if(i==Mid[4].y&&j==Mid[4].x)
			{
				MidColorData[1][1]=Camera_Data;
				Camera_Data=0;
			}
			LCD_WR_Data(Camera_Data);
		}
	}
	m=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			RGBtoHSL(MidColorData[i][j],hsl_l+m);
			outcolor( hsl_l+m);
			m++;
		}
	}
//	while(RGBCompare(VerticalU[VU],0)>30&&VU<=pointNum)
//		VU++;	
//	while(RGBCompare(VerticalD[VD],0)>30&&VD<=pointNum)
//		VD++;
//	while(RGBCompare(HorizontalL[HL],0)>30&&HL<=pointNum)
//		HL++;
//	while(RGBCompare(HorizontalR[HR],0)>30&&HR<=pointNum)
//		HR++;
//	if(VD<40&&VU<40&&HL<40&&HR<40)
//	{
//		Judgerubik=1;
//		Mid[4].x=(Mid[4].x*2+HR-HL)/2;
//		Mid[4].y=(Mid[4].y*2-VU+VD)/2;
//		Radius=(HL+HR+VD+VU)/4;
//	}
//	else 
//		Judgerubik=0;
}
void EXTI0_IRQHandler(void)
{
    if ( EXTI_GetITStatus(EXTI_Line0) != RESET ) 	//检查EXTI_Line0线路上的中断请求是否发送到了NVIC 
    {
        if( Ov7725_vsync == 0 )
        {
            FIFO_WRST_L(); 	                      //拉低使FIFO写(数据from摄像头)指针复位
            FIFO_WE_H();	                        //拉高使FIFO写允许
            
            Ov7725_vsync = 1;	   	
            FIFO_WE_H();                          //使FIFO写允许
            FIFO_WRST_H();                        //允许使FIFO写(数据from摄像头)指针运动
        }
        else if( Ov7725_vsync == 1 )
        {
            FIFO_WE_L();                          //拉低使FIFO写暂停
            Ov7725_vsync = 2;
        }        
        EXTI_ClearITPendingBit(EXTI_Line0);		    //清除EXTI_Line0线路挂起标志位        
    }    
}
void EXTI15_10_IRQHandler(void)        //按键中断  点亮闪光灯    PC13    PA8
{
	u16 i=5000;
	if(EXTI_GetITStatus (EXTI_Line13)!=RESET)
	{
		if(n==0)
		{
			while(i--);
			n++;
			EXTI_ClearITPendingBit (EXTI_Line13);
		}
		if(n==1)
		{
			n=0;
			page++;
		}
	}
		
//	GPIO_WriteBit(GPIOA,GPIO_Pin_8,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_8)));
	
	EXTI_ClearITPendingBit (EXTI_Line13);
}
void Dispaly_H(void)
{
	LCD_DisNum(10, 10, hsl_l[0].h ,WHITE);	
	LCD_DisNum(35, 10, hsl_l[1].h ,WHITE);	
	LCD_DisNum(60, 10, hsl_l[2].h ,WHITE);	
	LCD_DisNum(10, 30, hsl_l[3].h ,WHITE);	
	LCD_DisNum(35, 30, hsl_l[4].h ,WHITE);	
	LCD_DisNum(60, 30, hsl_l[5].h ,WHITE);	
	LCD_DisNum(10, 50, hsl_l[6].h ,WHITE);	
	LCD_DisNum(35, 50, hsl_l[7].h ,WHITE);	
	LCD_DisNum(60, 50, hsl_l[8].h ,WHITE);	
	
	LCD_DisNum(10, 80, hsl_l[0].s ,WHITE);	
	LCD_DisNum(35, 80, hsl_l[1].s ,WHITE);	
	LCD_DisNum(60, 80, hsl_l[2].s ,WHITE);	
	LCD_DisNum(10, 100, hsl_l[3].s ,WHITE);	
	LCD_DisNum(35, 100, hsl_l[4].s ,WHITE);	
	LCD_DisNum(60, 100, hsl_l[5].s ,WHITE);	
	LCD_DisNum(10, 120, hsl_l[6].s ,WHITE);	
	LCD_DisNum(35, 120, hsl_l[7].s ,WHITE);	
	LCD_DisNum(60, 120, hsl_l[8].s ,WHITE);	
	
	LCD_DisNum(10, 160, hsl_l[0].l ,WHITE);	
	LCD_DisNum(35, 160, hsl_l[1].l ,WHITE);	
	LCD_DisNum(60, 160, hsl_l[2].l ,WHITE);	
	LCD_DisNum(10, 180, hsl_l[3].l ,WHITE);	
	LCD_DisNum(35, 180, hsl_l[4].l ,WHITE);	
	LCD_DisNum(60, 180, hsl_l[5].l ,WHITE);	
	LCD_DisNum(10, 200, hsl_l[6].l ,WHITE);	
	LCD_DisNum(35, 200, hsl_l[7].l ,WHITE);	
	LCD_DisNum(60, 200, hsl_l[8].l ,WHITE);	
	
	
	LCD_DisNum(210, 160, hsl_l[0].color ,WHITE);	
	LCD_DisNum(235, 160, hsl_l[1].color ,WHITE);	
	LCD_DisNum(260, 160, hsl_l[2].color ,WHITE);	
	LCD_DisNum(210, 180, hsl_l[3].color ,WHITE);	
	LCD_DisNum(235, 180, hsl_l[4].color ,WHITE);	
	LCD_DisNum(260, 180, hsl_l[5].color ,WHITE);	
	LCD_DisNum(210, 200, hsl_l[6].color ,WHITE);	
	LCD_DisNum(235, 200, hsl_l[7].color ,WHITE);	
	LCD_DisNum(260, 200, hsl_l[8].color ,WHITE);	
	
	
	LCD_DisColor(210, 10, hsl_l[0].color );	
	LCD_DisColor(235, 10, hsl_l[1].color );	
	LCD_DisColor(260, 10, hsl_l[2].color );	
	LCD_DisColor(210, 30, hsl_l[3].color );	
	LCD_DisColor(235, 30, hsl_l[4].color );	
	LCD_DisColor(260, 30, hsl_l[5].color );	
	LCD_DisColor(210, 50, hsl_l[6].color );	
	LCD_DisColor(235, 50, hsl_l[7].color );	
	LCD_DisColor(260, 50, hsl_l[8].color );	

  LCD_DispChar(210,70,area[page/2],WHITE);
}
