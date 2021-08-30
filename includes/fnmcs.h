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

//EQPCAT 機器カタログ
#include "mc/mceqpcat.h"

//SYSCMP システム使用機器(システム構成要素)
#include "mc/mcmecsys.h"

//BOI ボイラー
#include "mc/mcboiler.h"

//REFA チラー、ヒートポンプチラー（空気熱源）
#include "mc/mcrefas.h"

//COL 太陽熱集熱器
#include "mc/mcsolrcol.h"

//STANK 蓄熱槽
#include "mc/mcstank.h"

//HEX 熱交換器
#include "mc/mchexchgr.h"

//THEX 全熱交換器
#include "mc/mcthex.h"

//HCC 冷温水コイル
#include "mc/mchccoil.h"

//PIPE 配管
#include "mc/mcpipe.h"

//DUCT, PUMP ポンプ
#include "mc/mcpump.h"

//VAV VAVユニット
#include "mc/mcvav.h"

//STHEAT 電気蓄熱式暖房器
#include "mc/mcstheat.h"

//PV 太陽電池
#include "mc/mcpv.h"

//OMVAV
#include "mc/mcomvav.h"

//HCLD 空調機負荷仮想機器
#include "mc/hcload.h"

//VALV
#include "mc/mcvalv.h"

//DESI バッチ式デシカント空調機
// mcdesiccant.c  Satoh追加 2013/10/20
#include "mc/mcdesiccant.h"

//EVAC 気化冷却器
// mcevcooling.c Satoh追加 2013/10/26
#include "mc/mcevcooling.h"

//C 合流要素
#include "mc/mccnvrg.h"

//QMEAS カロリーメータ
#include "mc/mcqmeas.h"
