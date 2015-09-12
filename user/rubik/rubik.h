#ifndef __RUBIK_H_
#define __RUBIK_H_

#include "stm32f10x.h"
#include <string.h>
#include <stdlib.h>

#define SWAP(a,b) TEMP=a;a=b;b=TEMP;
#define CHAROFFSET 65

#define swap(a) switch (a)\
{case 0:a='F';break;\
case 1:a='U';break;\
case 2:a='D';break;\
case 3:a='L';break;\
case 4:a='R';break;\
case 5:a='B';break;\
default:break;}


void* memset1(void* s, int c, int n);
void Rubik(char rubikdeal[][9], char* step);  																																							 // ÐÞ¸Ä3

#endif
