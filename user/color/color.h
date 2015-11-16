#ifndef	__COLOR_H
#define __COLOR_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"


#define HSLMAX 240
#define RGBMAX 255
#define UNDEFINED (HSLMAX*2/3)

#define max(a,b,c) ((a > ((b>c)?b:c)) ? a : ((b>c)?b:c))
#define min(a,b,c) ((a < ((b<c)?b:c)) ? a : ((b<c)?b:c))

typedef struct
{
	uint16_t h;
	uint16_t s;
	uint16_t l;
	uint8_t color;
}HSL_type;

typedef struct
{
	uint16_t x;
	uint16_t y;
}MidCoordinate_type;

void RGBtoHSL(uint16_t RGB,HSL_type* hsl );
void RGBtoYUV(uint16_t RGB,HSL_type* hsl);
void outcolor(HSL_type* hsl);
u16 RGBCompare(uint16_t RGB,uint16_t baseRGB);

#ifdef __cplusplus
}
#endif

#endif
