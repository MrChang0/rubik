#include "rubik.h"
char
*faces = "RLFBUD",
*order = "AECGBFDHIJKLMSNTROQP",
*bithash = "TdXhQaRbEFIJUZfijeYV",
*perm = "AIBJTMROCLDKSNQPEKFIMSPRGJHLNTOQAGCEMTNSBFDHORPQ",

pos[20], ori[20], val[20], TEMP, *tables[8];

int move1[20], moveamount[20], phase = 0,

tablesize[] = {1,4096,6561,4096,256,1536,13824,576};

int MidCompared(int a, int* b)
{
	int i = 0;
	while (a != b[i])
		i++;
	return i;
}

void display(int* buf, char cube[][4])
{
	int i = 0, a = 0, b = 0, c = 0;
	for (i = 0; i < 12; i++)
	{
		a = buf[i] / 10;
		b = buf[i] - a * 10;
		swap(a);
		swap(b);
		cube[i + 1][0] = a;
		cube[i + 1][1] = b;
		cube[i + 1][2] = '\0';
	}
	for (; i < 20; i++)
	{
		a = buf[i] / 100;
		b = (buf[i] - a * 100) / 10;
		c = buf[i] - a * 100 - b * 10;
		swap(a);
		swap(b);
		swap(c);
		cube[i + 1][0] = a;
		cube[i + 1][1] = b;
		cube[i + 1][2] = c;
		cube[i + 1][3] = '\0';
	}
}

void cycle(char*p, char*a)
{
	SWAP(p[*a - CHAROFFSET], p[a[1] - CHAROFFSET]);
	SWAP(p[*a - CHAROFFSET], p[a[2] - CHAROFFSET]);
	SWAP(p[*a - CHAROFFSET], p[a[3] - CHAROFFSET]);
}

void twist(int i, int a)
{
	i -= CHAROFFSET;
	ori[i] = (ori[i] + a + 1) % val[i];
}

void reset()
{
	int i = 0;
	for (i = 0; i<20; pos[i] = i, ori[i++] = 0);
}

int permtonum(char* p)
{
	int n = 0, a = 0, b = 0;
	for (a = 0; a<4; a++)
	{
		n *= 4 - a;
		for (b = a; ++b<4; )
			if (p[b]<p[a]) n++;
	}
	return n;
}

void numtoperm(char* p, int n, int o)
{
	int a = 0, b = 0;
	p += o;
	p[3] = o;
	for (a = 3; a--;)
	{
		p[a] = n % (4 - a) + o;
		n /= 4 - a;
		for (b = a; ++b<4; )
			if (p[b] >= p[a]) p[b]++;
	}
}

int getposition(int t)
{
	int i = -1, n = 0;
	int corn[8], j = 0, k = 0, l = 0, corn2[4];
	switch (t) {
	case 1:
		for (; ++i<12;) n += ori[i] << i;
		break;
	case 2:
		for (i = 20; --i>11;) n = n * 3 + ori[i];
		break;
	case 3:
		for (; ++i<12;) n += (pos[i] & 8) ? (1 << i) : 0;
		break;
	case 4:
		for (; ++i<8;) n += (pos[i] & 4) ? (1 << i) : 0;
		break;
	case 5:
		k = j = 0;
		for (; ++i<8;)
			if ((l = pos[i + 12] - 12) & 4)
			{
				corn[l] = k++;
				n += 1 << i;
			}
			else corn[j++] = l;
			for (i = 0; i<4; i++) corn2[i] = corn[4 + corn[i]];
			for (; --i;) corn2[i] ^= corn2[0];

			n = n * 6 + corn2[1] * 2 - 2;
			if (corn2[3]<corn2[2])n++;
			break;
	case 6:
		n = permtonum(pos) * 576 + permtonum(pos + 4) * 24 + permtonum(pos + 12);
		break;
	case 7:
		n = permtonum(pos + 8) * 24 + permtonum(pos + 16);
		break;
	}
	return n;
}

void setposition(int t, int n)
{
	int i = 0, j = 12, k = 0;
	char *corn = "QRSTQRTSQSRTQTRSQSTRQTSR";
	reset();
	switch (t)
	{
	case 1:
		for (; i<12; i++, n >>= 1) ori[i] = n & 1;
		break;
	case 2:
		for (i = 12; i<20; i++, n /= 3) ori[i] = n % 3;
		break;
	case 3:
		for (; i<12; i++, n >>= 1) pos[i] = 8 * n & 8;
		break;
	case 4:
		for (; i<8; i++, n >>= 1) pos[i] = 4 * n & 4;
		break;
	case 5:
		corn += n % 6 * 4;
		n /= 6;
		for (; i<8; i++, n >>= 1)
			pos[i + 12] = n & 1 ? corn[k++] - CHAROFFSET : j++;
		break;
	case 6:
		numtoperm(pos, n % 24, 12); n /= 24;
		numtoperm(pos, n % 24, 4); n /= 24;
		numtoperm(pos, n, 0);
		break;
	case 7:
		numtoperm(pos, n / 24, 8);
		numtoperm(pos, n % 24, 16);
		break;
	}
}

void domove(int m)
{
	char *p = perm + 8 * m, i = 8;
	cycle(pos, p);
	cycle(ori, p);
	cycle(pos, p + 4);
	cycle(ori, p + 4);
	if (m<4)
		for (; --i>3;) twist(p[i], i & 1);
	if (m<2)
		for (i = 4; i--;) twist(p[i], 0);
}

void filltable(int ti)
{
	int n = 1, l = 1, tl = tablesize[ti], i = 0, f = 0, q = 0, r = 0;
	char* tb = tables[ti] = (char*)malloc(tl*sizeof(char));
	memset(tb, 0, tl);
	reset();
	tb[getposition(ti)] = 1;

	while (n)
	{
		n = 0;
		for (i = 0; i<tl; i++)
		{
			if (tb[i] == l)
			{
				setposition(ti, i);
				for (f = 0; f<6; f++)
				{
					for (q = 1; q<4; q++)
					{
						domove(f);
						r = getposition(ti);
						if ((q == 2 || f >= (ti & 6)) && !tb[r])
						{
							tb[r] = l + 1;
							n++;
						}
					}
					domove(f);
				}
			}
		}
		l++;
	}
}

int searchphase(int movesleft, int movesdone, int lastmove)
{
	int i = 0, j = 0;
	if (tables[phase][getposition(phase)] - 1 > movesleft || tables[phase + 1][getposition(phase + 1)] - 1 > movesleft)
		return 0;

	if (!movesleft) return 1;

	for (i = 6; i--;)
	{
		if (i - lastmove && (i - lastmove + 1 || i | 1))
		{
			move1[movesdone] = i;
			for (j = 0; ++j<4;)
			{
				domove(i);
				moveamount[movesdone] = j;
				if ((j == 2 || i >= phase) && searchphase(movesleft - 1, movesdone + 1, i))
					return 1;
			}
			domove(i);
		}
	}
	return 0;
}

void Rubikout(char argv[][4], char* Step)                                                  
{
	int f = 0, i = 0, j = 0, k = 0, pc = 0, mor = 0,m=0;
	for (; k<20; k++) val[k] = k<12 ? 2 : 3;
	for (; j<8; j++) filltable(j);

	for (; i<20; i++) {
		f = pc = k = mor = 0;
		for (; f<val[i]; f++) {
			j = strchr(faces, argv[i + 1][f]) - faces;
			if (j>k) { k = j; mor = f; }
			pc += 1 << j;
		}
		for (f = 0; f<20; f++)
			if (pc == bithash[f] - 64) break;
		pos[order[i] - CHAROFFSET] = f;
		ori[order[i] - CHAROFFSET] = mor%val[i];
	}

	for (; phase<8; phase += 2)
	{
		for (j = 0; !searchphase(j, 0, 9); j++);
		for (i = 0; i < j; i++)
		{
			Step[m] = (move1[i] + 1) * 10 + moveamount[i];
			m++;
		}
	}
	Step[m + 1] = 0;
}

void Rubik(char rubikdeal[][9], char* step)        																				
{
	char MCube[21][4];
	int i = 0, t1 = 0, t2 = 0, t3 = 0;
	int buf[20];
	int mid[6];

	for (i = 0; i < 6; i++)
		mid[i] = rubikdeal[i][4];

	t1 = MidCompared(rubikdeal[1][7], mid);
	t2 = MidCompared(rubikdeal[0][1], mid);
	buf[0] = t1 * 10 + t2;          //UF


	t1 = MidCompared(rubikdeal[1][5], mid);
	t2 = MidCompared(rubikdeal[4][1], mid);
	buf[1] = t1 * 10 + t2;			//UR


	t1 = MidCompared(rubikdeal[1][1], mid);
	t2 = MidCompared(rubikdeal[5][1], mid);
	buf[2] = t1 * 10 + t2;			//UB

	t1 = MidCompared(rubikdeal[1][3], mid);
	t2 = MidCompared(rubikdeal[3][1], mid);
	buf[3] = t1 * 10 + t2;			//UL

	t1 = MidCompared(rubikdeal[2][1], mid);
	t2 = MidCompared(rubikdeal[0][7], mid);
	buf[4] = t1 * 10 + t2;			//DF

	t1 = MidCompared(rubikdeal[2][5], mid);
	t2 = MidCompared(rubikdeal[4][7], mid);
	buf[5] = t1 * 10 + t2;         //DR

	t1 = MidCompared(rubikdeal[2][7], mid);
	t2 = MidCompared(rubikdeal[5][7], mid);
	buf[6] = t1 * 10 + t2;			//DB

	t1 = MidCompared(rubikdeal[2][3], mid);
	t2 = MidCompared(rubikdeal[3][7], mid);
	buf[7] = t1 * 10 + t2;			//DL

	t1 = MidCompared(rubikdeal[0][5], mid);
	t2 = MidCompared(rubikdeal[4][3], mid);
	buf[8] = t1 * 10 + t2;			//FR

	t1 = MidCompared(rubikdeal[0][3], mid);
	t2 = MidCompared(rubikdeal[3][5], mid);
	buf[9] = t1 * 10 + t2;			//FL

	t1 = MidCompared(rubikdeal[5][3], mid);
	t2 = MidCompared(rubikdeal[4][5], mid);
	buf[10] = t1 * 10 + t2;			//BR

	t1 = MidCompared(rubikdeal[5][5], mid);
	t2 = MidCompared(rubikdeal[3][3], mid);
	buf[11] = t1 * 10 + t2;         //BL

	t1 = MidCompared(rubikdeal[1][8], mid);
	t2 = MidCompared(rubikdeal[0][2], mid);
	t3 = MidCompared(rubikdeal[4][0], mid);
	buf[12] = t1 * 100 + t2 * 10 + t3;			//UFR

	t1 = MidCompared(rubikdeal[1][2], mid);
	t2 = MidCompared(rubikdeal[4][2], mid);
	t3 = MidCompared(rubikdeal[5][0], mid);
	buf[13] = t1 * 100 + t2 * 10 + t3;			//URB

	t1 = MidCompared(rubikdeal[1][0], mid);
	t2 = MidCompared(rubikdeal[5][2], mid);
	t3 = MidCompared(rubikdeal[3][0], mid);
	buf[14] = t1 * 100 + t2 * 10 + t3;			//UBL

	t1 = MidCompared(rubikdeal[1][6], mid);
	t2 = MidCompared(rubikdeal[3][2], mid);
	t3 = MidCompared(rubikdeal[0][0], mid);
	buf[15] = t1 * 100 + t2 * 10 + t3;			//ULF

	t1 = MidCompared(rubikdeal[2][2], mid);
	t2 = MidCompared(rubikdeal[4][6], mid);
	t3 = MidCompared(rubikdeal[0][8], mid);
	buf[16] = t1 * 100 + t2 * 10 + t3;			//DRF

	t1 = MidCompared(rubikdeal[2][0], mid);
	t2 = MidCompared(rubikdeal[0][6], mid);
	t3 = MidCompared(rubikdeal[3][8], mid);
	buf[17] = t1 * 100 + t2 * 10 + t3;			//DFL

	t1 = MidCompared(rubikdeal[2][6], mid);
	t2 = MidCompared(rubikdeal[3][6], mid);
	t3 = MidCompared(rubikdeal[5][8], mid);
	buf[18] = t1 * 100 + t2 * 10 + t3;			//DLB

	t1 = MidCompared(rubikdeal[2][8], mid);
	t2 = MidCompared(rubikdeal[5][6], mid);
	t3 = MidCompared(rubikdeal[4][8], mid);
	buf[19] = t1 * 100 + t2 * 10 + t3;			//DBR

	display(buf, MCube);

	Rubikout(MCube,step);

}
