#pragma once

//PUMP ポンプ


// --------------------------------------------
// PUMP/FUN ポンプ・ファン
// --------------------------------------------

///@brief ポンプ・ファンの部分負荷特性の近似式係数
typedef struct pfcmp
{
	char	pftype,		/* 'P' ポンプ  'F' ファン */
		* type;		/* ポンプ・ファンのタイプ */
	double	dblcoeff[5];
} PFCMP;

///@brief ポンプ・ファン機器仕様(機器カタログデータ）
typedef struct pumpca
{
	char* name,
		pftype,   /* 'P' ポンプ  'F' ファン */
		* type;     /* 'C' 定流量　　'P' 太陽電池駆動　*/

	double  Wo,       /* モーター入力 */
		Go,       /* 定格流量 */
		qef,      /* 発熱比率(流体加熱量= gef * Wo）*/
		* val;     /* 特性式係数など */
	struct pfcmp* pfcmp;
} PUMPCA;

int    Pumpdata (char *cattype, char *s, PUMPCA *Pumpca, int Npfcmp, PFCMP *pfcmp) ;
