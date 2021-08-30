#pragma once

//EVAC 気化冷却器


// --------------------------------------------
// EVAC 気化冷却器
// --------------------------------------------
// Satoh追加　気化冷却器　2013/10/25

///@brief 気化冷却器(機器カタログデータ）
typedef struct EvaCoolingca
{
	char* name;			// カタログ名
	int		N;				// 気化冷却器分割数
	double	Awet, Adry,		// Wet側、Dry側の境界壁接触面積[m2]
		hwet, hdry;	// Wet側、Dry側の境界壁の対流熱伝達率[W/m2K]
	int		Nlayer;		// 積層数
} EVACCA;

int		Evacdata ( char *s, EVACCA *Evacca ) ;
