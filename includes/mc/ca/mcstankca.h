#pragma once

//STANK 蓄熱槽

#include <stdio.h>


// --------------------------------------------
// STANK 蓄熱槽
// --------------------------------------------

///@brief 蓄熱槽(機器カタログデータ）
typedef struct stankca
{
	char* name,
		type,      /* 形状  既定値 'C': 縦型 */
		* tparm;     /* 槽分割、流入口、流出口入力データ */
	double   Vol,
		KAside,
		KAtop,
		KAbtm,
		gxr;
} STANKCA;


int  Stankdata(FILE *f, char *s, STANKCA *Stankca);
