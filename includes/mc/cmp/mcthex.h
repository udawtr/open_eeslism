#pragma once

#include "MODEL.h"

#include <stdio.h>

//For THEXCA , THEX
#include "mc/eqptyp.h"


// --------------------------------------------
// THEX 全熱交換器
// --------------------------------------------
/*---- Satoh Debug 熱交換換気  2001/8/22 ----*/

///@brief 全熱交換器(システム構成要素)
typedef struct thex
{
	char* name,			/* 機器名称 */
		type;				/* t:顕熱交換型　h：全熱交換型 */
	THEXCA* cat;
	COMPNT* cmp;
	double	et,				/* 温度効率 */
		eh;				/* エンタルピ効率 */
	double	cGe,			/* 還気側熱容量流量 [W/K] */
		Ge,					/* 還気側流量 [kg/s] */
		cGo,				/* 外気側熱容量流量 [W/K] */
		Go,					/* 外気側流量 [kg/s] */
		Tein,				/* 還気側入口温度 [℃] */
		Teout,				/* 還気側出口温度 [℃] */
		Toin,				/* 外気側入口温度 [℃] */
		Toout,				/* 外気側出口温度 [℃] */
		xein,				/* 還気側入口絶対湿度 [kg/kg'] */
		xeout,				/* 還気側出口絶対湿度 [kg/kg'] */
		xoin,				/* 外気側入口絶対湿度 [kg/kg'] */
		xoout,				/* 外気側出口絶対湿度 [kg/kg'] */
		hein,				/* 還気側入口エンタルピー [J/kg] */
		heout,				/* 還気側出口エンタルピー [J/kg] */
		hoin,				/* 外気側入口エンタルピー [J/kg] */
		hoout,				/* 外気側出口エンタルピー [J/kg] */
		xeinold,
		xeoutold,
		xoinold,
		xooutold,
		Qes,				/* 交換顕熱 [W] */
		Qel,				/* 交換潜熱 [W] */
		Qet,				/* 交換全熱 [W] */
		Qos,				/* 交換顕熱 [W] */
		Qol,				/* 交換潜熱 [W] */
		Qot;				/* 交換全熱 [W] */
	SVDAY	Teidy,			/* 還気側入口温度日集計 */
		Teody,				/* 還気側出口温度日集計 */
		xeidy,
		xeody,
		Toidy,
		Toody,
		xoidy,
		xoody,
		heidy,
		heody,
		hoidy,
		hoody;
	QDAY	Qdyes, Qdyel, Qdyet, Qdyos, Qdyol, Qdyot;
	SVDAY	mTeidy,			/* 還気側入口温度日集計 */
		mTeody,				/* 還気側出口温度日集計 */
		mxeidy,
		mxeody,
		mToidy,
		mToody,
		mxoidy,
		mxoody,
		mheidy,
		mheody,
		mhoidy,
		mhoody;
	QDAY	mQdyes, mQdyel, mQdyet, mQdyos, mQdyol, mQdyot;
} THEX;


void	Thexint ( int Nthex, THEX *Thex ) ;
void	Thexcfv ( int Nthex, THEX *Thex ) ;
void	Thexelm(int NThex, THEX *Thex) ;
void	Thexene ( int Nthex, THEX *Thex ) ;
void	Thexprint(FILE *fo, int id, int Nthex, THEX *Thex ) ;
void	Thexdyint(int Nthex, THEX *Thex) ;
void	Thexmonint(int Nthex, THEX *Thex) ;
void	Thexday(int Mon, int Day, int ttmm, int Nthex, THEX *Thex, int Nday, int SimDayend) ;
void	Thexdyprt(FILE *fo, int id, int Nthex, THEX *Thex) ;
void	Thexmonprt(FILE *fo, int id, int Nthex, THEX *Thex) ;
