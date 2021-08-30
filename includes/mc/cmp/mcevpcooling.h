#pragma once

//EVAC 気化冷却器

#include <stdio.h>

//For EVACCA, EVAC
#include "mc/eqptyp.h"


// --------------------------------------------
// EVAC 気化冷却器
// --------------------------------------------
// Satoh追加　気化冷却器　2013/10/25


///@brief 気化冷却器(システム構成要素)
typedef struct EvaCooling
{
	char* name;			// 機器名称
	EVACCA* cat;			// 機器仕様
	COMPNT* cmp;
	double	Tdryi, Tdryo,	// Dry側出入口温度[℃]
		Tweti, Tweto,	// Wet側出入口温度[℃]
		xdryi, xdryo,	// Dry側出入口絶対湿度[kg/kg']
		xweti, xweto,	// Wet側出入口絶対湿度[kg/kg']
		RHdryi, RHdryo,	// Dri側出入口相対湿度[%]
		RHweti, RHweto,	// Wet側出入口相対湿度[%]
		Gdry, Gwet,		// Dry側、Wet側風量[kg/s]
		* M, * kx,		// i層蒸発量[kg/m2 s]、物質移動係数[kg/m2 s (kg/kg')]
		* Tdry, * Twet,	// Dry側、Wet側の空気温度[℃]
		* xdry, * xwet,	// Dry側、Wet側の空気絶対湿度[kg/kg']
		* xs,			// 濡れ面近傍の絶対湿度(境界面温度における飽和絶対湿度）[kg/kg']
		* Ts,			// 境界面の表面温度[℃](Wet側、Dry側は同じ温度）
		* RHwet, * RHdry,	// Dry側、Wet側の相対湿度[%]
		Qsdry, Qldry, Qtdry,
		// Dry側顕熱、潜熱、全熱[W]
		Qswet, Qlwet, Qtwet;
	// Wet側顕熱、潜熱、全熱[W]
	double* UX, * UXC;
	int		count;			// 計算回数。１ステップで最低２回は計算する
	//double	*UXdry, *UXwet, *UXC ;
							// 状態値計算用行列
	SVDAY	Tdryidy, Tdryody, Twetidy, Twetody;
	QDAY	Qsdrydy, Qldrydy, Qtdrydy, Qswetdy, Qlwetdy, Qtwetdy;
} EVAC;

void	Evacint ( int Nevac, EVAC *Evac ) ;
void	LinearSatx(double Ts, double *a, double *b) ;
void	Evacelm(int Nevac, EVAC *Evac) ;
void	Evacelm(int Nevac, EVAC *Evac) ;
void	Evaccfv(int Nevac, EVAC *Evac) ;
void	Evacene(int Nevac, EVAC *Evac, int *Evacreset) ;
void Evacprint(FILE *fo, int id, int Nevac, EVAC *Evac) ;
void	Evaccountreset(int Nevac, EVAC *Evac) ;
double	Evacu(double G, double T, double H, double W, int N) ;
double Evachcc(double de, double L, double T, double H, double W, int N, double G, int Flg) ;
double	EvacNu(double AR, double Re) ;
