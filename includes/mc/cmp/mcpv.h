#pragma once

//PV 太陽電池

#include <stdio.h>

//For PVCA
#include "mc/ca/mcpvca.h"

//For WDAT
#include "model/wthrd.h"

//For EXFS
#include "exs.h"

//For COMPNT
#include "model/eepath.h"

// --------------------------------------------
// PV 太陽電池
// --------------------------------------------


///@brief 太陽電池(システム構成要素)
typedef struct pv
{
	char* name;
	COMPNT * cmp;
	PVCA* cat;
	double	KTotal,					// 太陽電池の総合設計係数[-]
		KConst,					// 温度補正係数以外の補正係数の積(温度補正係数以外は時々刻々変化しない）
		KPT;					// 温度補正係数[-]
	double	TPV;					// 太陽電池温度[℃]
	double	Power;					// 発電量[W]
	double	Eff;					// 発電効率[-]
	double	Iarea;					// 太陽電池入射日射量[W]
	double	PVcap;					// 太陽電池設置容量[W]
	double	Area;					// アレイ面積[m2]
	double* Ta, * V, * I;			// 外気温、風速、日射量[W/m2]
	struct  exsf* sol;			// 設置方位
	struct  qday	Edy;			// 日積算発電量[kWh]
	struct	eday	Soldy;
	struct  qday	mEdy;			// 日積算発電量[kWh]
	struct  eday	mtEdy[12][24];
	struct	eday	mSoldy;
} PV;


void PVint(int Npv, PV *PV, int Nexsf, EXSF *Exs, WDAT *Wd) ;
void PVene(int Npv, PV *PV) ;
void PVprint(FILE *fo, int id, int Npv, PV *PV) ;
void PVdyint(int Npv, PV *PV) ;
void PVmonint(int Npv, PV *PV) ;
void PVday(int Mon, int Day, int ttmm, int Npv, PV *PV, int Nday, int SimDayend) ;
void PVdyprt(FILE *fo, int id, int Npv, PV *PV) ;
void PVmonprt(FILE *fo, int id, int Npv, PV *PV) ;
void PVmtprt(FILE *fo, int id, int Npv, PV *PV, int Mo, int tt);
