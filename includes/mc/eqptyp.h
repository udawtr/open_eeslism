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

/* eqptyp.h  */

#pragma once

#include "model/daysum.h"
#include "model/build.h"
#include "model/eepath.h"

/** 
 * @file 
 * @brief <入力データファイル>設備機器データのモデルについて構造体の定義
 * @details
 *
 * 2.5 設備機器データ (EESLISM7.2入力データ作成マニュアル.pdf)
 *
 * モデルの関連図
 *
 * *- EQPCAT --+-- BOI(CA)
 * |           +-- REFA(CA)
 * |           +-- COL(CA)
 * |           +-- STANK(CA)
 * |           +-- HEX(CA)
 * |           +-- THEX(CA)
 * |           +-- HCC(CA)
 * |           +-- PIPE(CA)
 * |           +-- DUCT(CA)
 * |           +-- PUMP(CA)
 * |           +-- FAN(CA)
 * |           +-- VAV(CA)
 * |           +-- STHEAT(CA)
 * |           +-- PV(CA)
 * |           +-- OAVAV(CA)
 * |           +-- DESICCANT(CA)
 * |           +-- EVPCOOLING(CA)
 * |
 * +- SYSCMP --+-- BOI
 *             +-- REFA
 *             +-- COL
 *             +-- STANK
 *             +-- HEX
 *             +-- THEX
 *             +-- HCC
 *             +-- PIPE
 *             +-- DUCT
 *             +-- PUMP
 *             +-- FAN
 *             +-- VAV
 *             +-- STHEAT
 *             +-- PV
 *             +-- OAVAV
 *             +-- DESICCANT
 *             +-- EVPCOOLING
 *             +-- HCLD
 *             +-- QMEAS
 * 
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * EQPCAT:    機器仕様(機器カタログデータ）
 * BOI:       ボイラー
 * REFA:      チラー、ヒートポンプチラー(空気熱源)
 * COL:       太陽熱集熱器
 * STANK:     蓄熱層
 * HEX:       熱交換器(２流体式）
 * THEX:      全熱交換器(換気の排気からの熱回収用の顕熱・潜熱熱交換器)
 * HCC:       冷温水コイル
 * PIPE:      配管
 * DUCT:      ダクト
 * PUMP:      ポンプ
 * FAN:       ファン(送風機）
 * VAV:       VAV ユニット
 * STHEAT:    電気蓄熱式暖房器
 * PV:        太陽電池
 * OAVAV:     屋根一体型空気集熱器の出口温度設定変風量制御ユニット
 * SYSCMP:    システムシミュレーションの対象となるシステム構成要素を定義
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 * 機器ごとに機器カタログデータとシステム構成用と2つずつ構造体があります。
 * 例) ポンプ   pump=システム構成用, pumpca=機器カタログデータ
 * 　　カタログを示すために語尾に `ca` が付与されています。
 *
 * @sa Eeinput, Eqcadata
 */

#include "mc/ca/mcevpcoolingca.h"
#include "mc/ca/mcdesiccantca.h"
#include "mc/ca/mcthexca.h"
#include "mc/ca/mcstheatca.h"
#include "mc/ca/mcvavca.h"
#include "mc/ca/mcomvavca.h"
#include "mc/ca/mchccca.h"
#include "mc/ca/mcboica.h"
#include "mc/ca/mcrefaca.h"
#include "mc/ca/mccollca.h"
#include "mc/ca/mcpipeca.h"
#include "mc/ca/mcstankca.h"
#include "mc/ca/mchexca.h"
#include "mc/ca/mcpumpca.h"
#include "mc/ca/mcpvca.h"


/*
 * @brief 機器仕様データ一覧
 * @sa Eqcadata, Eqsysinit
 */
typedef struct eqcat
{
	//============ 係数類 ============//

	//------ 標準圧縮機特性 ------
	//@sa _Refcmpdat

	//! 標準圧縮機特性のデータ数
	int   Nrfcmp;

	//! 標準圧縮機特性の動的配列
	RFCMP* Rfcmp;

	//------ ポンプ・ファンの部分負荷特性の近似式係数 ------
	//@sa PFcmpdata

	//! ポンプ・ファンの部分負荷特性の近似式係数のデータ数
	int   Npfcmp;

	//! ポンプ・ファンの部分負荷特性の近似式係数の動的配列
	PFCMP* pfcmp;


	//============ 機器仕様 ============//

	//------ 1) HCC 冷温水コイル ------

	//! 冷温水コイルのデータ数
	int   Nhccca;

	//! 冷温水コイルの動的配列
	HCCCA* Hccca;

	//------ 2) BOI ボイラー ------

	//! ボイラーのデータ数
	int   Nboica;

	//! ボイラーの動的配列
	BOICA* Boica;

	//------ 3) REFA チラー、ヒートポンプチラー(空気熱源) ------

	//! チラー、ヒートポンプチラー(空気熱源) のデータ数
	int   Nrefaca;

	//! チラー、ヒートポンプチラー(空気熱源) の動的配列
	REFACA* Refaca;

	//------ 4) COL,ACOL 太陽熱集熱器 -----

	//! 太陽熱集熱器のデータ数
	int   Ncollca;

	//! 太陽熱集熱器の動的配列
	COLLCA* Collca;

	//------ 5) 太陽電池 ------

	//! 太陽電池のデータ数
	int   Npvca;

	//! 太陽電池の動的配列
	PVCA* PVca;

	//------ 6) PIPE,DUCT 配管とダクト -----

	//! 配管とダクトのデータ数
	int   Npipeca;

	//! 配管とダクトの動的配列
	PIPECA* Pipeca;

	//------ 7) STANK 蓄熱層 ------

	//! 蓄熱層のデータ数
	int   Nstankca;

	//! 蓄熱層の動的配列
	STANKCA* Stankca;

	//------ 8) HEX 熱交換器(２流体式）------

	//! 熱交換器のデータ数
	int   Nhexca;

	//! 熱交換器の動的配列
	HEXCA* Hexca;

	//------ 9) PUMP,FAN ポンプ・ファン ------

	//! ポンプ・ファンのデータ数
	int   Npumpca;

	//! ポンプ・ファンの動的配列
	PUMPCA* Pumpca;

	//------ 10) VAV,VWV VAVユニット ------

	/*---- Satoh Debug VAV  2000/10/30 ----*/
	//! VAV ユニットのデータ数
	int	  Nvavca;

	//! VAV ユニットの動的配列
	VAVCA* Vavca;

	//------ 11) STHEAT 電気蓄熱式暖房器 ------

	/*---- Satoh Debug 電気蓄熱式暖房器 2001/1/21 ----*/
	//! 電気蓄熱式暖房器のデータ数
	int   Nstheatca;

	//! 電気蓄熱式暖房器の動的配列
	STHEATCA* stheatca;

	//------ 12) THEX 全熱交換器 ------

	//! 全熱交換器のデータ数
	int	  Nthexca;

	//! 全熱交換器の動的配列
	THEXCA* Thexca;

	//------ 13) 屋根一体型空気集熱器の出口温度設定変風量制御ユニット ------

	// Satoh OMVAV  2010/12/16
	int   Nomvavca;
	OMVAVCA* OMvavca;

	//------ 14) DESICCANT バッチ式デシカント空調機 ------

	// Satoh追加 2013/10/20
	//! バッチ式デシカント空調機のデータ数
	int		Ndesica;

	//! バッチ式デシカント空調機の動的配列
	DESICA* Desica;

	//------ 15) EVPCOOLING 気化冷却器 ------

	// Satoh追加 2013/10/26
	//! 気化冷却器のデータ吸う
	int		Nevacca;

	//! 気化冷却器の動的配列
	EVACCA* Evacca;
} EQCAT;


// --------------------------------------------
// EQCAT  機器仕様(機器カタログデータ)
// SYSCMP システム構成要素
// --------------------------------------------

#include "mc/cmp/mchcc.h"
#include "mc/cmp/mcboi.h"
#include "mc/cmp/mcrefa.h"
#include "mc/cmp/mccoll.h"
#include "mc/cmp/mcpv.h"
#include "mc/cmp/mcpipe.h"
#include "mc/cmp/mcstank.h"
#include "mc/cmp/mchex.h"
#include "mc/cmp/mcpump.h"
#include "mc/cmp/mcvav.h"
#include "mc/cmp/mcstheat.h"
#include "mc/cmp/mcthex.h"
#include "mc/cmp/mcomvav.h"
#include "mc/cmp/mcdesiccant.h"
#include "mc/cmp/mcevpcooling.h"
#include "mc/cmp/hcload.h"
#include "mc/cmp/mcqmeas.h"
#include "mc/cmp/mcflin.h"

/**
 * @brief システム使用機器データ一覧 
 * @sa Eqsysinit, Eqsysfree, mecsxprint
 */
typedef struct eqsys
{
	//------ 1) 冷温水コイル ------
	int   Nhcc;
	HCC  *Hcc;

	//------ 2) ボイラー ------
	int   Nboi;
	BOI  *Boi;
	
	//------ 3) ヒートポンプ ------
	int   Nrefa;
	REFA *Refa;
	
	//------ 4) 太陽熱集熱器 ------
	int   Ncoll;
	COLL *Coll;

	//------ 5) 太陽電池 ------
	int		Npv;
	PV* PVcmp;

	//------ 6) 配管・ダクト ------
	int   Npipe;
	PIPE *Pipe;
	
	//------ 7) 蓄熱槽 ------
	int   Nstank;
	STANK *Stank;
	
	//------ 8) 熱交換器 ------
	int   Nhex;
	HEX *Hex;
	
	//------ 9) ポンプ・ファン ------
	int   Npump;
	PUMP *Pump;
	
	//------ 10) VAVユニット ------
	/*---- Satoh Debug VAV  2000/10/30 ----*/
	int   Nvav;
	VAV	  *vav;

	//------ 11) 電気蓄熱式暖房器 ------
	/*---- Satoh Debug 電気蓄熱式暖房器 2001/1/21 ----*/
	int   Nstheat ;
	STHEAT	*stheat ;

	//------ 12) 全熱交換器 ------
	int	  Nthex ;
	THEX	*Thex ;

	//------ 13) 屋根一体型空気集熱器の出口温度設定変風量制御ユニット ------
	int		Nomvav ;
	OMVAV	*OMvav ;

	//------ 14) バッチ式デシカント空調機 ------
	// Satoh追加 2013/10/20
	int		Ndesi ;
	DESI	*Desi ;

	//------ 15) 気化冷却器 ------
	// Satoh追加 2013/10/26
	int		Nevac ;
	EVAC	*Evac ;


	int		Nvalv;
	VALV* Valv;

	int   Ncnvrg;
	COMPNT** Cnvrg;

	//------ カロリーメータ ------
	int		Nqmeas;
	QMEAS* Qmeas;

	//============ 仮想装置 ============//

	//------ 境界条件設定用仮想機器 ------
	int   Nflin;
	FLIN* Flin;

	//------ 空調機負荷仮想機器 ------
	int   Nhcload;
	HCLOAD* Hcload;

} EQSYS;
