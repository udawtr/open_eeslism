#pragma once

//DESI バッチ式デシカント空調機

// --------------------------------------------
// DESI バッチ式デシカント空調機
// --------------------------------------------
// Satoh追加　バッチ式デシカント空調機 2013/10/20

///@brief バッチ式デシカント空調機(機器カタログデータ）
typedef struct desiccantca
{
	char* name;			// カタログ名
	double	r,				// シリカゲル平均直径[cm]
		ms,				// シリカゲル質量[g]
		rows,			// シリカゲル充填密度[g/cm3]
		Uad,			// シリカゲル槽壁面の熱貫流率[W/m2K]
		A,				// シリカゲル槽表面積[m2]
		Vm,				// モル容量[cm3/mol]
		eps,			// シリカゲルの空隙率
		P0,				// シリカゲルの飽和吸湿量[kg(water)/kg(silica gel)]
		kp,				// Polanyi DR 定数[cm3/(mol K)2
		cps;			// シリカゲルの比熱[J/kgK]
} DESICA;

int  Desiccantdata(char* s, DESICA* Desica);
