#pragma once

//STANK 蓄熱槽

#include <stdio.h>

//For SIMCONTL
#include "model/simcon.h"

//For WDAT
#include "model/wthrd.h"

//For STANKCA, STANK
#include "mc/eqptyp.h"


// --------------------------------------------
// STANK 蓄熱槽
// --------------------------------------------

/**
 * @brief
 * @sa stankdyint
 */
typedef struct stkday
{
	SVDAY  Tidy, Tsdy;
	QDAY   Qdy;
} STKDAY;


///@brief 蓄熱槽 (システム構成要素)
typedef struct stank
{
	char* name,
		batchop;     /* バッチ操作有　給水:'F'  排出:'D'  停止:'-'
		バッチ操作無:'n' */
	struct stankca* cat;
	struct compnt* cmp;
	int     Ndiv,      /* 分割層数 */
		Nin,       /* 流入口、流出口数 */
		* Jin,
		* Jout,
		Jva,
		Jvb;
	int	Ncalcihex;	// 内径と長さから計算される内蔵熱交のモデルの数
	char* pthcon,
		** batchcon, /* バッチ給水、排出スケジュール　'F':給水 'D':排出 */
		* ihex,    /* 内蔵熱交換器のある経路のとき ihex[i]='y' */
		cfcalc;   /* cfcalc = 'y':要素モデル係数の計算する。
				  'n':要素モデル係数の計算しない。
(温度分布の逆転時再計算指定のときに使用*/
	double* B,
		* R,
		* d,
		* Fg,           /* Fg 要素機器の係数 [Ndiv x Nin] */
		* Tss;

	char* dtankF;        /* 分割した槽内の状態　'F':満水　'E':空 */
	char* KAinput;		// 内蔵熱交換器の温度効率が入力されていたら'N'
							// KAが入力されていたら'Y'
							// 内径と長さが入力されていたら'C'
	double	dbld0,			// 内蔵熱交の内径[m]
		dblL,			// 内蔵熱交の長さ[m]
		dblTw,			// 熱伝達率計算用の配管内温度[℃]
		dblTa;			// 熱伝達率計算用タンク温度[℃]
	double* Tssold,
		* dvol,
		* Mdt,
		* KS,

		* KA,			// 内蔵熱交換器のKA[W/K]
		* ihxeff,       /* 内蔵熱交換器の熱交換器有効率　サイズは[Nin] */
		* cGwin,        /* cGwin, *EGwin, Twin, Q のサイズは[Nin] */
		* EGwin,        /* EGwin = eff * cGwin  */
		* Twin,
		* Q,

		Qloss,          /* 槽熱損失　*/
		Qsto,           /*  槽蓄熱量 */

		* Tenv;         /* 周囲温度のアドレス */
	STKDAY* stkdy;
	STKDAY* mstkdy;
	double Qlossdy;
	double Qstody;
	double mQlossdy;
	double mQstody;
} STANK;

int  Stankdata(FILE *f, char *s, STANKCA *Stankca);
