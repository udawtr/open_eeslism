#pragma once

//For COMPNT
#include "model/eepath.h"

//For EQSYS
#include "mc/eqptyp.h"

//For WDAT
#include "model/wthrd.h"

//For RMVLS
#include "model/build.h"

//For EXFS
#include "exs.h"

//For SIMCONTL
#include "model/simcon.h"

//BOI ボイラー
#include "mc/cmp/mcboi.h"

//REFA チラー、ヒートポンプチラー（空気熱源）
#include "mc/cmp/mcrefa.h"

//COL 太陽熱集熱器
#include "mc/cmp/mccoll.h"

//STANK 蓄熱槽
#include "mc/cmp/mcstank.h"

//HEX 熱交換器
#include "mc/cmp/mchex.h"

//THEX 全熱交換器
#include "mc/cmp/mcthex.h"

//HCC 冷温水コイル
#include "mc/cmp/mchcc.h"

//PIPE 配管
#include "mc/cmp/mcpipe.h"

//DUCT, PUMP ポンプ
#include "mc/cmp/mcpump.h"

//VAV VAVユニット
#include "mc/cmp/mcvav.h"

//STHEAT 電気蓄熱式暖房器
#include "mc/cmp/mcstheat.h"

//PV 太陽電池
#include "mc/cmp/mcpv.h"

//OMVAV
#include "mc/cmp/mcomvav.h"

//HCLD 空調機負荷仮想機器
#include "mc/cmp/hcload.h"

//VALV
#include "mc/cmp/mcvalv.h"

//DESI バッチ式デシカント空調機
// mcdesiccant.c  Satoh追加 2013/10/20
#include "mc/cmp/mcdesiccant.h"

//EVAC 気化冷却器
// mcevcooling.c Satoh追加 2013/10/26
#include "mc/cmp/mcevpcooling.h"

//C 合流要素
#include "mc/cmp/mccnvrg.h"

//QMEAS カロリーメータ
#include "mc/cmp/mcqmeas.h"

// 2.5.2 システム構成要素 SYSCMP


void Mecsinit(double dTM, EQSYS* Eqsys, SIMCONTL* Simc, int Ncompnt, COMPNT* Compnt, int Nexsf, EXSF* Exsf, WDAT* Wd, RMVLS* Rmvls);
void Mecscf(EQSYS* Eqsys);
void Mecsene(EQSYS* Eqsys);
