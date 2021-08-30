#pragma once

//BOI ボイラー

#include "model/sched.h"
#include "model/control.h"
#include "model/simcon.h"

//For WDAT
#include "model/wthrd.h"


// --------------------------------------------
// BOI ボイラー
// --------------------------------------------

///@brief ボイラ－(機器カタログデータ）
typedef struct boica
{
	//! 名称
	char* name;

	//! 使用燃料　G:ガス、O:灯油、E:電気
	char ene;

	//! エネルギー計算で機器容量上限無いとき 'y'
	char unlimcap;

	//! 最小出力以下の時にOFFかONかを指示
	//!       ON : ON_SW    OFF : OFF_SW
	//! ただし、Qmin > 0 の時のみ有効
	char belowmin;

	//! 部分負荷特性コ－ド
	char plf;

	//! 温熱源の時は 'H'、冷熱源の時は 'C'
	//char	mode;

	//! 定格能力条件
	char* Qostr;

	//! 定格加熱能力(Qo<0 の場合は冷水チラー)
	double* Qo;

	//!
	double	Qmin;

	//! *ボイラ－効率　
	double	eff;

	//! 温水ポンプ動力 [W]
	double	Ph;
} BOICA;

int  Boidata(char* s, BOICA* Boica);
void Boicaint(int NBoica, BOICA* Boica, SIMCONTL* Simc, int Ncompnt, COMPNT* Compnt, WDAT* Wd, EXSFS* Exsf, SCHDL* Schdl);

