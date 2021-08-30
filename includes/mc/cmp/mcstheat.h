#pragma once

//STHEAT 電気蓄熱式暖房器

#include <stdio.h>

//For STHEATCA, STHEAT
#include "mc/eqptyp.h"

//For PCM
#include "model/build.h"

//For WDAT
#include "model/wthrd.h"

//For COMPNT
#include "model/eepath.h"

//For VPTR
#include "model/control.h"

//For SIMCONTL
#include "model/simcon.h"


// --------------------------------------------
// STHEAT 電気蓄熱式暖房器
// --------------------------------------------
/*---- Satoh Debug 電気蓄熱式暖房器 2001/1/20 ----*/

///@brief 電気蓄熱式暖房器(システム構成要素)
typedef struct stheat
{
	char* name;
	STHEATCA* cat;
	COMPNT* cmp;
	PCM* pcm;				// 電気蓄熱暖房器内臓PCMのスペック構造体
	double	cG,					/* 熱容量流量 [W/K] */
		Ts,						/* 蓄熱体温度 [℃] */
		Tsold,					/* 前時間砕石温度 [℃] */
		Tin,					/* 入口(吸込）温度 [℃] */
		Tout,					/* 出口(吹出）温度 [℃] */
		* Tenv,					/* 周囲温度 [℃] */
		xin,					/* 入口絶対湿度 [kg/kg'] */
		xout,					/* 出口絶対湿度 [kg/kg'] */
		Q,						/* 供給熱量 [W] */
		E,						/* 電気ヒーター消費電力 [W] */
		Qls,					/* 熱損失 [W] */
		Qsto,					/* 蓄熱量 [W] */
		Qlossdy,				/* 日積算熱損失 [kWh] */
		Qstody;				/* 日積算蓄熱量 [kWh] */
	double	mPCM;				// 電気蓄熱暖房器内臓PCMの容量[m3]
	double	Hcap;				// 熱容量(PCM潜熱も含む）
	ROOM* room;				/* 蓄熱暖房器設置室構造体 */
	SVDAY	Tidy,				/* 入口温度日集計 */
		Tody,					/* 出口温度日集計 */
		Tsdy;					/* 蓄熱体温度日集計 */
	QDAY	Qdy;				/* 室供給熱量日集計 */
	EDAY	Edy;
	//EDAY	mtEdy[12][24] ;
	SVDAY	mTidy,				/* 入口温度日集計 */
		mTody,					/* 出口温度日集計 */
		mTsdy;					/* 蓄熱体温度日集計 */
	QDAY	mQdy;				/* 室供給熱量日集計 */
	EDAY	mEdy;
	double	mQlossdy,				/* 日積算熱損失 [kWh] */
		mQstody;				/* 日積算蓄熱量 [kWh] */
	EDAY	mtEdy[12][24];		// 月別時刻別消費電力[kWh]
} STHEAT;


void Stheatint(int Nstheat, STHEAT *stheat, SIMCONTL *Simc, int Ncompnt, COMPNT *Compnt, WDAT *Wd, int Npcm, PCM *PCM);
void Stheatcfv(int Nstheat, STHEAT *stheat) ;
void Stheatene(int Nstheat, STHEAT *stheat) ;
//void Stheatene2(int Nstheat, STHEAT *stheat);
int  stheatvptr(char **key, STHEAT *Stheat, VPTR *vptr, VPTR *vpath) ;
void stheatprint(FILE *fo, int id, int Nstheat, STHEAT *stheat) ;
void stheatdyint(int Nstheat, STHEAT *stheat) ;
void stheatmonint(int Nstheat, STHEAT *stheat) ;
void stheatday(int Mon, int Day, int ttmm, int Nstheat, STHEAT *stheat, int Nday, int SimDayend) ;
void stheatdyprt(FILE *fo, int id, int Nstheat, STHEAT *stheat) ;
void stheatmonprt(FILE *fo, int id, int Nstheat, STHEAT *stheat) ;
void stheatmtprt(FILE *fo, int id, int Nstheat, STHEAT *stheat, int Mo, int tt) ;
