#pragma once

//STHEAT 電気蓄熱式暖房器

// --------------------------------------------
// STHEAT 電気蓄熱式暖房器
// --------------------------------------------
/*---- Satoh Debug 電気蓄熱式暖房器 2001/1/20 ----*/

///@brief 電気蓄熱式暖房器(機器カタログデータ）
typedef struct stheatca
{
	char* name;			/* 機器名 */
	double	Q,				/* 電気ヒーター容量 [W] */
		Hcap,				/* 熱容量 [J/K] */
		KA,					/* 熱損失係数 [W/K] */
		eff;				/* 温風吹出温度効率 [-] */
	char* pcmname;		// 電気蓄熱暖房器内臓PCMのスペック名称
} STHEATCA;



int  Stheatdata(char *s, STHEATCA *stheatca) ;
