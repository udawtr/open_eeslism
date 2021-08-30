#pragma once

//DESI バッチ式デシカント空調機

#include <stdio.h>

#include "model/simcon.h"
#include "model/control.h"
#include "model/daysum.h"
#include "model/build.h"

// --------------------------------------------
// DESI バッチ式デシカント空調機
// --------------------------------------------
// Satoh追加　バッチ式デシカント空調機 2013/10/20

///@brief バッチ式デシカント空調機(システム構成要素)
typedef struct desiccant
{
	char* name;			// 機器名称
	DESICA* cat;			// 機器仕様
	COMPNT* cmp;
	double	Tain, Taout,	// 空気の出入口温度[℃]
		xain, xaout,	// 空気の出入口絶対湿度[kg/kg']
		UA,				// デシカント槽の熱損失係数[W/K]
		Asa,			// シリカゲルと槽内空気の熱伝達面積[m2]
		//Ts,				// シリカゲル温度[℃]
		//Xs,				// シリカゲル表面の絶対湿度[kg/kg']
		Tsold, Xsold,	// 前時刻の状態値
		Ta,				// デシカント槽内空気温度[℃]
		Xa,				// デシカント槽内絶対湿度[kg/kg']
		RHold,			// 前時刻の相対湿度状態値
		Pold,			// 前時刻の吸湿量[kg(water)/kg(silica gel)]
		cG,
		Qloss,			// デシカント槽表面からの熱損失[W]
		Qs, Ql, Qt,		// 顕熱、潜熱、全熱[W]
		* Tenv;			// 周囲温度のポインタ[℃]
	double* UX, * UXC;
	//double	d, e, f, g ;	// 係数
	ROOM* room;			// デシカント槽設置室構造体
	SVDAY	Tidy, xidy,			// 入口温度日集計
		Tody, xody,			// 出口温度日集計
		Tsdy, xsdy;			// 蓄熱体温度日集計
	QDAY	Qsdy, Qldy, Qtdy, Qlsdy;			// 熱量日集計
	//SVDAY	mTidy,				/* 入口温度日集計 */
	//	mTody,					/* 出口温度日集計 */
	//	mTsdy ;					/* 蓄熱体温度日集計 */
	//QDAY	mQdy ;				/* 室供給熱量日集計 */
} DESI;

void Desiint(int NDesi, DESI* Desi, SIMCONTL* Simc, int Ncompnt, COMPNT* Compnt, WDAT* Wd);
void Desicfv(int NDesi, DESI* Desi);
void Desiene(int NDesi, DESI* Desi);
int  Desivptr(char** key, DESI* Desi, VPTR* vptr);
void Desielm(int Ndesi, DESI* Desi);
void Desiprint(FILE* fo, int id, int Ndesi, DESI* Desi);
void Desidyprt(FILE* fo, int id, int Ndesi, DESI* Desi);
void Desiday(int Mon, int Day, int ttmm, int Ndesi, DESI* Desi, int Nday, int SimDayend);
void Desidyint(int Ndesi, DESI* Desi);
