//This file is part of EESLISM.
//
//Foobar is free software : you can redistribute itand /or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//Foobar is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with Foobar.If not, see < https://www.gnu.org/licenses/>.

#pragma once

// 2.5 設備機器データ処理関数群

//HCC 冷温水コイル
#include "mc/mcaclib.h"

//REFA ??? 圧縮式冷凍機
#include "mc/mcreflib.h"

//BOI ボイラー
#include "mc/mcboiler.h"

//COL 太陽熱集熱器
#include "mc/mcsolrcol.h"

//PV 太陽電池
#include "mc/mcpv.h"

//REFA チラー、ヒートポンプチラー（空気熱源） ---- 機器仕様入力
#include "mc/mcrefas.h"

//HCC 冷温水コイル
#include "mc/mchccoil.h"

//PIPE 配管
#include "mc/mcpipe.h"

//STANK 蓄熱槽
#include "mc/mcstank.h"

/* mcstanklb.c  */
#include "mc/mcstanklb.h"

//HEX 熱交換器
#include "mc/mchexchgr.h"

//PUMP ポンプ
#include "mc/mcpump.h"

/*  hcload.c  */
#include "mc/hcload.h"

/* mcvalv.c */
#include "mc/mcvalv.h"

//VAV VAVユニット
#include "mc/mcvav.h"

// mcomvav.c
#include "mc/mcomvav.h"

//STHEAT 電気蓄熱式暖房器
#include "mc/mcstheat.h"

/* mcthex.c */
#include "mc/mcthex.h"

/* mc_cnvrg.c  */
#include "mc/mccnvrg.h"

/*  mceqcadat.c  */
#include "mc/mceqcadat.h"

/*  mceqpcat.c  */
#include "mc/mceqpcat.h"

/*  mcmecsys.c  */ 
#include "mc/mcmecsys.h"

/* mcxprmcs.c */
#include "mc/mcxprmcs.h"

/* mcqmeas.c */
#include "mc/mcqmeas.h"

//DESI バッチ式デシカント空調機
// mcdesiccant.c  Satoh追加 2013/10/20
#include "mc/mcdesiccant.h"

//EVAC 気化冷却器
// mcevcooling.c Satoh追加 2013/10/26
#include "mc/mcevcooling.h"
