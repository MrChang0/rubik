#include "color.h"


void RGBtoHSL(uint16_t RGB,HSL_type* hsl)          //RGB 转换HSL  
{
	uint16_t R,G,B;
	uint16_t max, min;
	uint16_t Rdelta, Gdelta, Bdelta;
	
	
	R=(uint8_t)(RGB>>11);
	G=(uint8_t)((RGB & 0x7E0) >> 5);
	B=(uint8_t)RGB&0x1F;
	
	R=((float)R/31)*255;
	G=((float)G/63)*255;
	B=((float)B/31)*255;

	max = max(R, G, B);
	min = min(R, G, B);
	hsl->l = (((max + min)*HSLMAX) + RGBMAX) / (2 * RGBMAX);

	if (max == min)
	{
		hsl->s = 0;
		hsl->h = UNDEFINED;
	}
	else
	{
		if (hsl->l <= (HSLMAX / 2))
			hsl->s = (((max - min)*HSLMAX) + ((max + min) / 2)) / (max + min);
		else
			hsl->s = (((max - min)*HSLMAX) + ((2 * RGBMAX - max - min) / 2)) / (2 * RGBMAX - max - min);

		Rdelta = (((max - R)*(HSLMAX / 6)) + ((max - min) / 2)) / (max - min);
		Gdelta = (((max - G)*(HSLMAX / 6)) + ((max - min) / 2)) / (max - min);
		Bdelta = (((max - B)*(HSLMAX / 6)) + ((max - min) / 2)) / (max - min);

		if (R == max)
			hsl->h = Bdelta - Gdelta;
		else if (G == max)
			hsl->h = (HSLMAX / 3) + Rdelta - Bdelta;
		else
			hsl->h = ((2 * HSLMAX) / 3) + Gdelta - Rdelta;

		if (hsl->h < 0)
			hsl->h += HSLMAX;
		if (hsl->h > HSLMAX)
			hsl->h -= HSLMAX;
	}
}

void RGBtoYUV(uint16_t RGB,HSL_type* hsl)          //RGB 转换YUV色系  
{
	uint16_t R,G,B;
	
	
	R=(uint8_t)(RGB>>11);
	G=(uint8_t)((RGB & 0x7E0) >> 5);
	B=(uint8_t)RGB&0x1F;
	
	R=((float)R/31)*255;
	G=((float)G/63)*255;
	B=((float)B/31)*255;
	
	hsl->h = (0.257 * R) + (0.504 * G) + (0.098 * B) + 16;
	hsl->s= (0.439 * R) - (0.368 * G) - (0.071 * B) + 128;
	hsl->l = -(0.148 * R) - (0.291 * G) + (0.439 * B) + 128;
}

u16 RGBCompare(uint16_t RGB,uint16_t baseRGB)		//RGB偏移量
{
	uint16_t R, G, B,baseR,baseG,baseB;
	uint16_t Difference;
	R = (uint8_t)(RGB >> 11);
	G = (uint8_t)((RGB & 0x7E0) >> 5);
	B = (uint8_t)RGB & 0x1F;

	R = ((float)R / 31) * 31;
	G = ((float)G / 63) * 31;
	B = ((float)B / 31) * 31;

	baseR = (uint8_t)(baseRGB >> 11);
	baseG = (uint8_t)((baseRGB & 0x7E0) >> 5);
	baseB = (uint8_t)baseRGB & 0x1F;

	baseR = ((float)baseR / 31) * 31;
	baseG = ((float)baseG / 63) * 31;
	baseB = ((float)baseB / 31) * 31;

	Difference = (R - baseR)*(R - baseR) + (G - baseG)*(G - baseG) + (B - baseB)*(G - baseG);
	
	return Difference;
}

void outcolor(HSL_type* hsl)  //颜色判断
{
	if(hsl->h >100 && hsl->h<130)    //绿色  1
	{
		if(hsl->l<150)
			hsl->color=1;         
		else  								 //白色  6
			hsl->color=6;
	}
	if(hsl->h>10 && hsl->h<30)    //橙色 2
		hsl->color=2;
	if(hsl->h>0 && hsl->h<10)    //红色4
		hsl->color=4;
	if(hsl->h>30 && hsl->h<70)    //黄色 3
		hsl->color=3;
	if(hsl->h>130 && hsl->h<160)    
	{
		if(hsl->l<150)
			hsl->color=5;          //蓝色 5
		else  								 //白色  6
			hsl->color=6;
	}
}
