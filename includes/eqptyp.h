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

#include "daysum.h"
#include "build.h"
#include "eepath.h"

/*
 * @brief <入力データファイル>設備機器データのモデルについて構造体の定義
 * @details
 *
 * 2.5 設備機器データ (EESLISM7.2入力データ作成マニュアル.pdf)
 *
 * モデルの関連図
 *
 * *- EQPCAT --+-- BOI
 * |           +-- REFA
 * |           +-- COL
 * |           +-- STANK
 * |           +-- HEX
 * |           +-- THEX
 * |           +-- HCC
 * |           +-- PIPE
 * |           +-- DUCT
 * |           +-- PUMP
 * |           +-- FAN
 * |           +-- VAV
 * |           +-- STHEAT
 * |           +-- PV
 * |           +-- OAVAV
 * +- SYSCMP
 * 
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * EQPCAT:    機器仕様（機器カタログデータ）
 * BOI:       ボイラー
 * REFA:      チラー、ヒートポンプチラー（空気熱源)
 * COL:       太陽熱集熱器
 * STANK:     蓄熱層
 * HEX:       熱交換器(２流体式）
 * THEX:      全熱交換器（換気の排気からの熱回収用の顕熱・潜熱熱交換器)
 * HCC:       冷温水コイル
 * PIPE:      配管
 * DUCT:      ダクト
 * PUMP:      ポンプ
 * FAN:       ファン（送風機）
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

typedef struct qmeas
{
	char	fluid ;
	int		id ;
	char	*name ;
	COMPNT	*cmp ;
	double	*Th, *Tc, *G, *xh, *xc ;
	PLIST	*PlistG, *PlistTh, *PlistTc, *Plistxh, *Plistxc ;
	double	Qs, Ql, Qt ;
	SVDAY	Thdy, Tcdy, xhdy, xcdy ;
	QDAY	Qdys, Qdyl, Qdyt ;
	SVDAY	mThdy, mTcdy, mxhdy, mxcdy ;
	QDAY	mQdys, mQdyl, mQdyt ;
//	PELM	*Pelmh, *Pelmc ;
	char	idh, idc ;
//	COMPNT	*cmph, *cmpc ;
	int		Nelmh, Nelmc ;
	//PLIST	*Plist ;
} QMEAS ;

typedef struct acs 
{
	double  w, t, x, C;
} ACS;


// --------------------------------------------
// EVAC 気化冷却器
// --------------------------------------------
// Satoh追加　気化冷却器　2013/10/25

//@brief 気化冷却器（機器カタログデータ）
typedef struct EvaCoolingca
{
	char	*name ;			// カタログ名
	int		N ;				// 気化冷却器分割数
	double	Awet, Adry,		// Wet側、Dry側の境界壁接触面積[m2]
			hwet, hdry ;	// Wet側、Dry側の境界壁の対流熱伝達率[W/m2K]
	int		Nlayer ;		// 積層数
} EVACCA ;

//@brief 気化冷却器(システム構成要素)
typedef struct EvaCooling
{
	char	*name ;			// 機器名称
	EVACCA	*cat ;			// 機器仕様
	COMPNT	*cmp ;
	double	Tdryi, Tdryo,	// Dry側出入口温度[℃]
			Tweti, Tweto,	// Wet側出入口温度[℃]
			xdryi, xdryo,	// Dry側出入口絶対湿度[kg/kg']
			xweti, xweto,	// Wet側出入口絶対湿度[kg/kg']
			RHdryi, RHdryo,	// Dri側出入口相対湿度[%]
			RHweti, RHweto,	// Wet側出入口相対湿度[%]
			Gdry, Gwet,		// Dry側、Wet側風量[kg/s]
			*M, *kx,		// i層蒸発量[kg/m2 s]、物質移動係数[kg/m2 s (kg/kg')]
			*Tdry, *Twet,	// Dry側、Wet側の空気温度[℃]
			*xdry, *xwet,	// Dry側、Wet側の空気絶対湿度[kg/kg']
			*xs,			// 濡れ面近傍の絶対湿度（境界面温度における飽和絶対湿度）[kg/kg']
			*Ts,			// 境界面の表面温度[℃]（Wet側、Dry側は同じ温度）
			*RHwet, *RHdry,	// Dry側、Wet側の相対湿度[%]
			Qsdry, Qldry, Qtdry,
							// Dry側顕熱、潜熱、全熱[W]
			Qswet, Qlwet, Qtwet ;
							// Wet側顕熱、潜熱、全熱[W]
	double	*UX, *UXC ;
	int		count ;			// 計算回数。１ステップで最低２回は計算する
	//double	*UXdry, *UXwet, *UXC ;
							// 状態値計算用行列
	SVDAY	Tdryidy, Tdryody, Twetidy, Twetody ;
	QDAY	Qsdrydy, Qldrydy, Qtdrydy, Qswetdy, Qlwetdy, Qtwetdy ;
} EVAC ;


// --------------------------------------------
// DESI バッチ式デシカント空調機
// --------------------------------------------
// Satoh追加　バッチ式デシカント空調機 2013/10/20

//@brief バッチ式デシカント空調機（機器カタログデータ）
typedef struct desiccantca
{
	char	*name ;			// カタログ名
	double	r,				// シリカゲル平均直径[cm]
			ms,				// シリカゲル質量[g]
			rows,			// シリカゲル充填密度[g/cm3]
			Uad,			// シリカゲル槽壁面の熱貫流率[W/m2K]
			A,				// シリカゲル槽表面積[m2]
			Vm,				// モル容量[cm3/mol]
			eps,			// シリカゲルの空隙率
			P0,				// シリカゲルの飽和吸湿量[kg(water)/kg(silica gel)]
			kp,				// Polanyi DR 定数[cm3/(mol K)2
			cps ;			// シリカゲルの比熱[J/kgK]
} DESICA ;

//@brief バッチ式デシカント空調機(システム構成要素)
typedef struct desiccant
{
	char	*name ;			// 機器名称
	DESICA	*cat ;			// 機器仕様
	COMPNT	*cmp ;
	double	Tain, Taout,	// 空気の出入口温度[℃]
			xain, xaout,	// 空気の出入口絶対湿度[kg/kg']
			UA,				// デシカント槽の熱損失係数[W/K]
			Asa,			// シリカゲルと槽内空気の熱伝達面積[m2]
			//Ts,				// シリカゲル温度[℃]
			//Xs,				// シリカゲル表面の絶対湿度[kg/kg']
			Tsold, Xsold,	// 前時刻の状態値
			Ta,				// デシカント槽内空気温度[℃]
			Xa,				// デシカント槽内絶対湿度[kg/kg']
			RHold,			// 前時刻の相対湿度状態値
			Pold,			// 前時刻の吸湿量[kg(water)/kg(silica gel)]
			cG,
			Qloss,			// デシカント槽表面からの熱損失[W]
			Qs, Ql, Qt,		// 顕熱、潜熱、全熱[W]
			*Tenv ;			// 周囲温度のポインタ[℃]
	double	*UX, *UXC ;
	//double	d, e, f, g ;	// 係数
	ROOM	*room ;			// デシカント槽設置室構造体
	SVDAY	Tidy, xidy,			// 入口温度日集計
			Tody, xody,			// 出口温度日集計
			Tsdy, xsdy ;			// 蓄熱体温度日集計
	QDAY	Qsdy, Qldy, Qtdy, Qlsdy ;			// 熱量日集計
	//SVDAY	mTidy,				/* 入口温度日集計 */
	//	mTody,					/* 出口温度日集計 */
	//	mTsdy ;					/* 蓄熱体温度日集計 */
	//QDAY	mQdy ;				/* 室供給熱量日集計 */
} DESI ;


// --------------------------------------------
// THEX 全熱交換器
// --------------------------------------------
/*---- Satoh Debug 熱交換換気  2001/8/22 ----*/

//@brief 全熱交換器（機器カタログデータ）
typedef struct thexca
{
	char	*name ;			/* カタログ名 */
//		type ;				/* t:顕熱交換型　h：全熱交換型 */
	double	et,				/* 温度効率 */
		eh ;				/* エンタルピ効率 */
} THEXCA ;

//@brief 全熱交換器(システム構成要素)
typedef struct thex
{
	char	*name,			/* 機器名称 */
		type ;				/* t:顕熱交換型　h：全熱交換型 */
	THEXCA	*cat ;
	COMPNT	*cmp ;
	double	et,				/* 温度効率 */
		eh ;				/* エンタルピ効率 */
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
		Qot ;				/* 交換全熱 [W] */
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
		hoody ;
	QDAY	Qdyes, Qdyel, Qdyet, Qdyos, Qdyol, Qdyot ;
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
		mhoody ;
	QDAY	mQdyes, mQdyel, mQdyet, mQdyos, mQdyol, mQdyot ;
} THEX ;


// --------------------------------------------
// STHEAT 電気蓄熱式暖房器
// --------------------------------------------
/*---- Satoh Debug 電気蓄熱式暖房器 2001/1/20 ----*/

//@brief 電気蓄熱式暖房器（機器カタログデータ）
typedef struct stheatca
{
	char	*name ;			/* 機器名 */
	double	Q,				/* 電気ヒーター容量 [W] */
		Hcap,				/* 熱容量 [J/K] */
		KA,					/* 熱損失係数 [W/K] */
		eff ;				/* 温風吹出温度効率 [-] */
	char	*pcmname;		// 電気蓄熱暖房器内臓PCMのスペック名称
} STHEATCA ;

//@brief 電気蓄熱式暖房器(システム構成要素)
typedef struct stheat
{
	char	*name ;
	STHEATCA	*cat ;
	COMPNT	*cmp ;
	PCM		*pcm;				// 電気蓄熱暖房器内臓PCMのスペック構造体
	double	cG,					/* 熱容量流量 [W/K] */
		Ts,						/* 蓄熱体温度 [℃] */
		Tsold,					/* 前時間砕石温度 [℃] */
		Tin,					/* 入口（吸込）温度 [℃] */
		Tout,					/* 出口（吹出）温度 [℃] */
		*Tenv,					/* 周囲温度 [℃] */
		xin,					/* 入口絶対湿度 [kg/kg'] */
		xout,					/* 出口絶対湿度 [kg/kg'] */
		Q,						/* 供給熱量 [W] */
		E,						/* 電気ヒーター消費電力 [W] */
		Qls,					/* 熱損失 [W] */
		Qsto,					/* 蓄熱量 [W] */
		Qlossdy,				/* 日積算熱損失 [kWh] */
		Qstody ;				/* 日積算蓄熱量 [kWh] */
	double	mPCM;				// 電気蓄熱暖房器内臓PCMの容量[m3]
	double	Hcap;				// 熱容量（PCM潜熱も含む）
	ROOM	*room ;				/* 蓄熱暖房器設置室構造体 */
	SVDAY	Tidy,				/* 入口温度日集計 */
		Tody,					/* 出口温度日集計 */
		Tsdy ;					/* 蓄熱体温度日集計 */
	QDAY	Qdy ;				/* 室供給熱量日集計 */
	EDAY	Edy ;
	//EDAY	mtEdy[12][24] ;
	SVDAY	mTidy,				/* 入口温度日集計 */
		mTody,					/* 出口温度日集計 */
		mTsdy ;					/* 蓄熱体温度日集計 */
	QDAY	mQdy ;				/* 室供給熱量日集計 */
	EDAY	mEdy ;
	double	mQlossdy,				/* 日積算熱損失 [kWh] */
		mQstody ;				/* 日積算蓄熱量 [kWh] */
	EDAY	mtEdy[12][24] ;		// 月別時刻別消費電力[kWh]
} STHEAT ;


// --------------------------------------------
// VAV VAV ユニット
// --------------------------------------------
/*---- Satoh Debug VAV  2000/10/30 ----*/

//@brief VAV ユニット（機器カタログデータ）
typedef struct vavca
{
	char* name,			/* カタログ名 */
		type;				/* A:VAV  W:VWV */
	double	Gmax,			/* 最大風量 [kg/s] */
		Gmin,			/* 最小風量 [kg/s] */
		dTset;				/* VWV用設定温度差　[℃] */
} VAVCA;

//@brief VAV ユニット(システム構成要素)
typedef struct vav
{
	char	chmode ;		/* 冷房用、暖房用の設定 */
	char	*name ;			/* 機器名 */
	char	mon ;			/* 制御対象が
							　　コイルの時：c
							　　仮想空調機の時：h
							　　床暖房の時：f
							**************************/
	VAVCA	*cat ;			/* VAVカタログ構造体 */
	struct hcc		*hcc ;	/* VWVの時の制御対象コイル */
	struct hcload	*hcld ;	/* VWVの時の制御対象仮想空調機 */
	RDPNL	*rdpnl ;		/* VWVの時の制御対象放射パネル */
	//ROOM	*room ;			/* 制御室構造体 */
	double	G,				/* 風量 [kg/s] */
			cG,				/* 熱容量流量 [W/K] */
			Q,				/* 再熱計算時の熱量 [W] */
			Qrld,
			Tin, Tout ;		/* 入口、出口空気温度 */
	int		count ;			/* 計算回数 */
	COMPNT	*cmp ;
} VAV ;


// --------------------------------------------
// OAVAV 屋根一体型空気集熱器の出口温度設定変風量制御ユニット
// --------------------------------------------
// Satoh OMVAV  2010/12/16

//@breif 屋根一体型空気集熱器の出口温度設定変風量制御ユニット（機器カタログデータ）
typedef struct omvavca
{
	char* name;
	double	Gmax,			// 最大風量[kg/s]
		Gmin;			// 最小風量[kg/s]
} OMVAVCA;

//@brief 屋根一体型空気集熱器の出口温度設定変風量制御ユニット(システム構成要素)
typedef struct omvav
{
	char	*name ;
	OMVAVCA	*cat ;
	RMSRF	*omwall ;		// 制御対象とする集熱屋根
	COMPNT	*cmp ;
	PLIST	*Plist ;
	double	G ;
	RDPNL	*rdpnl[4] ;
	int		Nrdpnl ;
} OMVAV ;


// --------------------------------------------
// HCC 冷温水コイル
// --------------------------------------------

//@brief 冷温水コイル（機器カタログデータ）
typedef struct hccca
{
	char    *name;
	double   et,               /*定格温度効率　　　　　　*/
		KA,
		eh;               /*定格エンタルピ効率　　　*/
} HCCCA;

//@brief 冷温水コイル(システム構成要素)
typedef struct hcc
{ 
	char    *name, 
		wet;
	char	etype ;			/* 温度効率の入力方法
							　　e:et
								k:KA	*/
	struct hccca  *cat;
	struct compnt  *cmp;
	double   et,               /*温度効率　　　　　　*/
		eh;               /*エンタルピ効率　　　*/      
	struct  acs  Et, 
		Ex, 
		Ew;      
	double   cGa,
		Ga,
		cGw,
		Gw,
		Tain,
		Taout,
		xain,
		Twin,
		Twout,
		Qs,
		Ql,
		Qt;
	struct svday  Taidy, xaidy, Twidy;
	struct qday   Qdys, Qdyl, Qdyt;
	struct svday  mTaidy, mxaidy, mTwidy;
	struct qday   mQdys, mQdyl, mQdyt;
} HCC;


// --------------------------------------------
// BOI ボイラー
// --------------------------------------------

//@brief ボイラ－（機器カタログデータ）
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

//@brief ボイラ－(システム構成要素)
typedef struct boi
{
	char* name;

	//! 負荷制御以外での運転モード
	//! 最大能力：M  最小能力：m
	char mode;

	//! 冷房モート゛、暖房モード
	char HCmode;

	char *load;

	struct boica *cat;

	struct compnt  *cmp;

	double  Do, D1;
	double cG;
	double Tin;
	double Toset;
	double  Q, E, Ph;
	struct svday  Tidy;
	struct qday   Qdy;
	struct eday   Edy, Phdy;
	struct eday   mtEdy[12][24], mtPhdy[12][24] ;
	struct svday  mTidy;
	struct qday   mQdy;
	struct eday   mEdy, mPhdy;
} BOI;


// --------------------------------------------
// REFA チラー、ヒートポンプチラー（空気熱源
// --------------------------------------------

//@brief 標準圧縮機特性
typedef struct rfcmp
{
	//! 名称
	char* name;

	//! 圧縮機タイプ説明
	char *cname;

	//! 蒸発器係数
	double e[4];

	//! 凝縮器係数
	double d[4];

	//! 軸動力係数
	double w[4];

	//! 蒸発温度範囲
	double Teo[2];

	//! 凝縮温度範囲
	double Tco[2];

	//! モ－タ－効率
	double Meff;
} RFCMP;  

//@brief ヒートポンプ定格能力
typedef struct hpch
{
	//! 定格冷却能力（加熱能力）
	double  Qo;

	//! 定格冷（温）水量、風量
	double	Go;

	//! 定格冷（温）水出口温度（チラ－）
	double	Two;

	//! 定格水冷却（加熱）器、空調機コイル温度効率
	double	eo;

	//! 定格排出（採取）熱量
	double	Qex;

	//! 定格冷却風量、水量
	double	Gex;

	//! 定格外気温（冷却水入口水温）
	double	Tex;

	//! 定格凝縮器（蒸発器）温度効率
	double	eex;

	//! 定格軸動力
	double	Wo;
} HPCH;

//@brief ヒートポンプ（機器カタログデータ）
typedef struct refaca
{ 
	//! 名称
	char* name;

	//! 空冷（空気熱源）=a、冷却塔使用=w
	char awtyp;

	//! 部分負荷特性コ－ド
	char plf;

	//! エネルギー計算で機器容量上限無いとき 'y'
	char unlimcap;

	//! 冷房運転: C、暖房運転時: H
	char mode[2];

	//! mode[]の数。1 のとき冷房専用または暖房専用。2 のとき冷・暖 切換運転。
	int Nmode;

	struct rfcmp *rfc;

	//! 定格冷温水ポンプ動力 [W]
	double Ph;
	
	//! 冷房運転時定格能力
	struct hpch* cool;

	//! 暖房運転時定格能力
	struct hpch *heat;
} REFACA;

//@brief ヒートポンプ (システム構成要素)
typedef struct refa
{ 
	//! 名称
	char* name;

	char* load;

	//! 冷房運転: C、暖房運転時: H
	char	chmode; 

	struct refaca  *cat;

	struct compnt  *cmp;

	struct room    *room ;

	//! 冷房運転時蒸発器係数
	double c_e[4];

	//! 冷房運転時熱源側（凝縮器係数）
	double c_d[4];

	//! 冷房運転時軸動力係数
	double c_w[4];

	//! 暖房運転時凝縮器係数
	double	h_e[4];

	//! 暖房運転時熱源側（蒸発器係数）
	double	h_d[4];

	//! 暖房運転時軸動力係数
	double	h_w[4];

	//! 運転時能力特性式係数
	double	Ho, He;

	//! 外気温度
	double	*Ta;
	double	Do, D1;
	double	cG;
	
	//! 運転時蒸発温度
	double	Te;

	//! 運転時凝縮温度
	double	Tc;
		
	double	Tin;
	double	Toset;
	double	Q; 
	double	Qmax;
	double	E;

	//! 冷温水ポンプ動力 [W]
	double	Ph;

	struct svday  Tidy;
	struct qday   Qdy;
	struct eday   Edy, Phdy;
	EDAY		  mtEdy[12][24], mtPhdy[12][24] ;
	struct svday  mTidy;
	struct qday   mQdy;
	struct eday   mEdy, mPhdy;
	
} REFA;


// --------------------------------------------
// COL 太陽熱集熱器
// --------------------------------------------

//@brief 太陽熱集熱器（機器カタログデータ）
typedef struct collca
{
	char* name;

	//! 水熱源：w、空気熱源：a
	char type ;
	
	double   b0, b1;

	//! 集熱器効率係数（=Kc / Ko）
	double Fd;

	//! 総合熱損失係数[W/(m2･K)]
	double Ko;

	double Ac;

	double Ag;
} COLLCA;

//@brief 太陽熱集熱器 (システム構成要素)
typedef struct coll
{
	char     *name;
	
	struct collca  *cat;       
	struct  exsf   *sol;
	struct compnt  *cmp;
	double    *Ta;
	double    Do, D1, 
		ec,
		Te,					// 相当外気温度
		Tcb,				// 集熱板温度
		//Ko,					// 総合熱損失係数[W/(m2･K)]
		//Fd,					// 集熱器効率係数（=Kc / Ko）
		Tin,				// 入口温度
		Q,					// 集熱量[W]
		Ac,					// 集熱器面積
		Sol;				// 集熱面日射量[W]（短波のみ）
	struct svday  Tidy;
	struct qday   Qdy;
	struct eday   Soldy;
	struct svday  mTidy;
	struct qday   mQdy;
	struct eday   mSoldy;
} COLL;


// --------------------------------------------
// PIPE 配管
// --------------------------------------------

//@brief 配管・ダクト仕様
typedef struct pipeca
{ 
	char* name;

	//! 配管のとき P、ダクトのときD
	char type;

	double  Ko;
} PIPECA;

//@brief システム使用配管・ダクト
typedef struct pipe
{
	char   *name,
		*loadt,
		*loadx;
	//char	type ;
	struct pipeca  *cat;
	struct compnt  *cmp;
	struct room    *room ;
	double   L,
	       Ko,
		   *Tenv,
		   ep,
		   Do, D1,
		   Tin,
		   Q,
		   Tout,
		   hout,
		   xout,
		   RHout,
		   
		   Toset,
		   Xoset;
	struct svday  Tidy;
	struct qday   Qdy;
	struct svday  mTidy;
	struct qday   mQdy;
} PIPE;


// --------------------------------------------
// STANK 蓄熱槽
// --------------------------------------------

//@brief 蓄熱槽（機器カタログデータ）
typedef struct stankca
{
	char    *name,
		type,      /* 形状  既定値 'C': 縦型 */
		*tparm;     /* 槽分割、流入口、流出口入力データ */
	double   Vol,
		KAside,
		KAtop,
		KAbtm,
		gxr;
} STANKCA;

//@brief 蓄熱槽 (システム構成要素)
typedef struct stank
{
	char    *name,
	batchop;     /* バッチ操作有　給水:'F'  排出:'D'  停止:'-' 
	バッチ操作無:'n' */ 
	struct stankca  *cat;
	struct compnt   *cmp;
	int     Ndiv,      /* 分割層数 */
		Nin,       /* 流入口、流出口数 */
		*Jin,
		*Jout,
		Jva,
		Jvb;
	int	Ncalcihex ;	// 内径と長さから計算される内蔵熱交のモデルの数
	char    *pthcon,
		**batchcon, /* バッチ給水、排出スケジュール　'F':給水 'D':排出 */
		*ihex,    /* 内蔵熱交換器のある経路のとき ihex[i]='y' */
				  cfcalc;   /* cfcalc = 'y':要素モデル係数の計算する。
							'n':要素モデル係数の計算しない。
	(温度分布の逆転時再計算指定のときに使用*/
	double  *B,
		*R,
		*d,
		*Fg,           /* Fg 要素機器の係数 [Ndiv x Nin] */
		*Tss;
	
	char    *dtankF;        /* 分割した槽内の状態　'F':満水　'E':空 */
	char	*KAinput ;		// 内蔵熱交換器の温度効率が入力されていたら'N'
							// KAが入力されていたら'Y'
							// 内径と長さが入力されていたら'C'
	double	dbld0,			// 内蔵熱交の内径[m]
			dblL,			// 内蔵熱交の長さ[m]
			dblTw,			// 熱伝達率計算用の配管内温度[℃]
			dblTa ;			// 熱伝達率計算用タンク温度[℃]
	double   *Tssold,
		*dvol,
		*Mdt,
		*KS,
		
		*KA,			// 内蔵熱交換器のKA[W/K]
		*ihxeff,       /* 内蔵熱交換器の熱交換器有効率　サイズは[Nin] */
		*cGwin,        /* cGwin, *EGwin, Twin, Q のサイズは[Nin] */
		*EGwin,        /* EGwin = eff * cGwin  */
		*Twin,   
		*Q,
		
		Qloss,          /* 槽熱損失　*/
		Qsto,           /*  槽蓄熱量 */
		
		*Tenv;         /* 周囲温度のアドレス */
	struct stkday  *stkdy;
	struct stkday  *mstkdy;
	double   Qlossdy,
		Qstody;
	double   mQlossdy,
		mQstody;
} STANK;

typedef struct stkday
{
	struct svday  Tidy, Tsdy;
	struct qday   Qdy;
} STKDAY;


// --------------------------------------------
// HEX 熱交換器
// --------------------------------------------

//@brief 熱交換器（機器カタログデータ）
typedef struct hexca
{
	char   *name;

	//! 熱交換器有効率
	double  eff;

	double	KA ;
} HEXCA;

//@brief 熱交換器 (システム構成要素)
typedef struct hex
{
	int		id ;
	char   *name;

	//! 温度効率の入力方法 e:et  k:KA
	char	etype ;

	struct hexca  *cat;
	struct compnt *cmp;
	double  eff,
		eCGmin,
		CGc, CGh,
		Tcin,
		Thin,
		Qci, Qhi;
	struct svday  Tcidy, Thidy;
	struct qday   Qcidy, Qhidy;
	struct svday  mTcidy, mThidy;
	struct qday   mQcidy, mQhidy;
} HEX;


// --------------------------------------------
// PUMP/FUN ポンプ・ファン
// --------------------------------------------

//@brief ポンプ・ファンの部分負荷特性の近似式係数
typedef struct pfcmp
{
	char	pftype,		/* 'P' ポンプ  'F' ファン */
			*type ;		/* ポンプ・ファンのタイプ */
	double	dblcoeff[5] ;
} PFCMP ;

//typedef struct compostca	// コンポスト機器仕様
//{
//	char* name;
//	double	UA,			// 熱損失係数[W/(m2･K)]
//		Mos,		// 初期有機物量[kg]
//		Mmo,		// 初期微生物量[kg]
//		Mw,			// 初期水分量[kg]
//		Mu;			// 初期灰分量[kg]
//}COMPOSTCA;
//
//typedef struct compost
//{
//	char* name;
//	double	UA,			// 熱損失係数[W/(m2･K)]
//		Mosi,			// 初期有機物量[kg]
//		Mmoi,			// 初期微生物量[kg]
//		Mwi,			// 初期水分量[kg]
//		Mui;			// 初期灰分量[kg]
//	char* type;			// 投入物の種類（P:糞尿、G:ごみ）
//	double* hos,		// 単位質量当たりの発熱量[J/kg]
//		* Mpoo;			// 投入量[kg]
//	int* B;				// ブリストルスケール
//	double	Tcm,		// 内部温度[℃]
//		xs,				// 内部絶対湿度[kg/kg']
//		Mw,				// 槽内水分量[kg]
//		Mmo,			// 槽内微生物量[kg]
//		Mos;			// 槽内有機物量[kg]
//	double* U, * C;
//}COMPOST;

//@brief ポンプ・ファン機器仕様（機器カタログデータ）
typedef struct pumpca
{
	char   *name,
		pftype,   /* 'P' ポンプ  'F' ファン */
		*type;     /* 'C' 定流量　　'P' 太陽電池駆動　*/
	
	double  Wo,       /* モーター入力 */
		Go,       /* 定格流量 */
		qef,      /* 発熱比率（流体加熱量= gef * Wo）*/
		*val;     /* 特性式係数など */	 
	struct pfcmp  *pfcmp ;
} PUMPCA;

//@brief ポンプ・ファン (システム構成要素)
typedef struct pump
{
	char   *name;
	struct pumpca *cat;
	struct compnt *cmp;
	//struct pfcmp  *pfcmp ;
	struct exsf   *sol;
	double  Q,
		G,
		cG,
		Tin,
		E; 
	double	PLC ;		// 部分負荷特性を考慮した入力率
	struct eday Qdy, Gdy, Edy;
	EDAY		mtEdy[12][24] ;
	struct eday mQdy, mGdy, mEdy;
} PUMP;

/* -------------------------------------------- */ 

typedef struct flin    /*  境界条件設定用仮想機器 */
{
	char *name,     
        *namet,   /* 変数名（温度、顕熱） */   
		*namex,   /* 変数名（湿度、潜熱） */   
				  awtype;   /* 'W':１変数のとき（nametの変数名のみ使用）、 
	'A':２変数のとき（namexの変数も使用） */
	double *vart,   /* nametで示された変数の値 */
		*varx;   /* namexで示された変数の値 */
	
	struct compnt *cmp;
} FLIN;

/* -------------------------------------------- */ 

typedef struct hcload   /* 空調機負荷仮想機器　*/
{ 
	char    *name,
		*loadt,
		*loadx,
		RMACFlg,		// ルームエアコンなら'Y'
		chmode,			// スケジュール等によって設定されている運転モード
//		opmode,			// 実際の運転時のモード
		type,    /* 'D':直膨コイル想定
		'W':冷温水コイル想定　*/
		wetmode,	/* 実際のコイル状態 */
		wet;     /*'y': wet coil  'n':dry coil */
	
	double   cGa,
		Ga,	     
		Tain,
		xain,
		Toset,
		Xoset,

		/*---- Roh Debug for a constant outlet humidity model of wet coil  2003/4/25 ----*/
		RHout,
		
		cGw,
		Gw,
		Twin,
		Twout,
		
		Qfusoku,
		Ele,
		COP,

		Qs,
		Ql,
		Qt;
	double	Qcmax, Qhmax, Qc, Qh, Qcmin, Qhmin,
		COPc, COPh,					// COP（定格）
		Ec, Eh, Ecmax, Ecmin,		// 消費電力[W]
		COPcmax, COPcmin,			// COP（最大能力時、最小能力時
		Gi, Go ;					// 室内機、室外機風量[kg/s]
	double	COPhmax, COPhmin, Ehmin, Ehmax ;
	double	Rc[3], Rh[3],			// 理論COPと実働COPの比の2次式回帰係数
		Pcc, Pch ;					// ファン等消費電力[W]
	double	BFi, BFo ;				// 室内機、室外機のバイパスファクタ
	double	rh, rc ;	// 定格能力と最大能力の比
	struct svday  Taidy, xaidy;
	struct qday   Qdys, Qdyl, Qdyt;
	struct qday	  Qdyfusoku, Edy ;
	EDAY		  mtEdy[12][24] ;
	struct svday  mTaidy, mxaidy;
	struct qday   mQdys, mQdyl, mQdyt;
	struct qday	  mQdyfusoku, mEdy ;
	
	struct compnt *cmp;      
} HCLOAD;

typedef struct gload  /* 入力負荷仮想機器 */
{
	char *name,
        *nameqs,
		*nameql,
		*nameQt;
	double *Qs,
		*Ql,
		*Qt;
	
	struct compnt *cmp;
} GLOAD;


// --------------------------------------------
// PV 太陽電池
// --------------------------------------------

//@brief 太陽電池（機器カタログデータ）
typedef struct pvca
{
	char	*name ;
	double	PVcap,					// 太陽電池容量[W]
			Area,					// アレイ面積[m2]
			KHD,					// 日射量年変動補正係数[-]
			KPD,					// 経時変化補正係数[-]
			KPM,					// アレイ負荷整合補正係数[-]
			KPA,					// アレイ回路補正係数[-]
			effINO ;				// インバータ実行効率[-]
	double	apmax ;					// 最大出力温度係数[-]
	double	ap ;					// 太陽電池裏面の熱伝達率[W/m2K]
	char	type ;					// 結晶系：'C'  アモルファス系：'A'
	double	A, B ;					// 設置方式別の太陽電池アレイ温度計算係数
	char	InstallType ;			// 太陽電池パネル設置方法
									// 'A':架台設置形、'B':屋根置き形、'C':屋根材形（裏面通風構造があるタイプ）
	//double	PVcap ;					// 太陽電池設置容量[W]
} PVCA ;


//@brief 太陽電池(システム構成要素)
typedef struct pv
{
	char	*name ;
	struct compnt  *cmp;
	PVCA	*cat ;
	double	KTotal,					// 太陽電池の総合設計係数[-]
			KConst,					// 温度補正係数以外の補正係数の積（温度補正係数以外は時々刻々変化しない）
			KPT ;					// 温度補正係数[-]
	double	TPV ;					// 太陽電池温度[℃]
	double	Power ;					// 発電量[W]
	double	Eff ;					// 発電効率[-]
	double	Iarea ;					// 太陽電池入射日射量[W]
	double	PVcap ;					// 太陽電池設置容量[W]
	double	Area ;					// アレイ面積[m2]
	double	*Ta, *V, *I ;			// 外気温、風速、日射量[W/m2]
	struct  exsf   *sol;			// 設置方位
	struct  qday	Edy ;			// 日積算発電量[kWh]
	struct	eday	Soldy ;
	struct  qday	mEdy ;			// 日積算発電量[kWh]
	struct  eday	mtEdy[12][24] ;
	struct	eday	mSoldy ;
} PV ;


// --------------------------------------------
// EQCAT  機器仕様(機器カタログデータ)
// SYSCMP システム構成要素
// --------------------------------------------

/*
 * @brief 機器仕様データ一覧
 */
typedef struct eqcat   /**/
{
	int   Nrfcmp;
	struct rfcmp *Rfcmp;
	
	int   Npfcmp ;
	struct pfcmp *pfcmp ;
	
	int   Nhccca;

	//! 冷温水コイルの動的配列
	struct hccca  *Hccca;
	
	int   Nboica;

	//! ボイラーの動的配列
	struct boica  *Boica;
	
	int   Nrefaca;
	struct refaca *Refaca;
	
	int   Ncollca;
	struct collca *Collca;
	
	int   Npipeca;
	struct pipeca *Pipeca;
	
	int   Nstankca;
	struct stankca *Stankca;
	
	int   Nhexca;
	struct hexca *Hexca;
	
	int   Npumpca;
	struct pumpca *Pumpca;

	/*---- Satoh Debug VAV  2000/10/30 ----*/
	int	  Nvavca ;

	//! VAV ユニットの動的配列
	VAVCA	  *Vavca ;

	/*---- Satoh Debug 電気蓄熱式暖房器 2001/1/21 ----*/
	int   Nstheatca ;

	//! 電気蓄熱式暖房器の動的配列
	STHEATCA  *stheatca ;

	int	  Nthexca ;

	//! 全熱交換器の動的配列
	THEXCA	*Thexca ;

	int   Npvca ;
	PVCA		*PVca ;

	// Satoh OMVAV  2010/12/16
	int   Nomvavca ;
	OMVAVCA	*OMvavca ;

	// Satoh追加 2013/10/20
	int		Ndesica ;

	//! バッチ式デシカント空調機の動的配列
	DESICA	*Desica ;

	// Satoh追加 2013/10/26
	int		Nevacca ;

	//! 気化冷却器の動的配列
	EVACCA	*Evacca ;

	// Satoh追加 2019/8/29
	//int		Ncompost;
	//COMPOSTCA* Compostca;
} EQCAT;

/*
 * @brief システム使用機器データ一覧 
 */
typedef struct eqsys
{
	int   Ncnvrg;
	struct compnt **Cnvrg;
	
	
	int   Nhcc;
	struct hcc  *Hcc;
	
	int   Nboi;
	struct boi  *Boi;
	
	int   Nrefa;
	struct refa *Refa;
	
	int   Ncoll;
	struct coll *Coll;
	
	int   Npipe;
	struct pipe *Pipe;
	
	int   Nstank;
	struct stank *Stank;
	
	int   Nhex;
	struct hex *Hex;
	
	int   Npump;
	struct pump *Pump;
	
	int   Nflin;
	struct flin *Flin;
	
	int   Nhcload;
	struct hcload *Hcload;
	
	int   Ngload;
	struct gload *Gload;
	
	/*---- Satoh Debug VAV  2000/10/30 ----*/
	int   Nvav;
	VAV	  *vav;

	/*---- Satoh Debug 電気蓄熱式暖房器 2001/1/21 ----*/
	int   Nstheat ;
	STHEAT	*stheat ;

	int	  Nthex ;
	THEX	*Thex ;

	int		Nvalv ;
	VALV	*Valv ;

	int		Nqmeas ;
	QMEAS	*Qmeas ;

	int		Npv ;
	struct pv	*PVcmp ;

	int		Nomvav ;
	OMVAV	*OMvav ;

	// Satoh追加 2013/10/20
	int		Ndesi ;
	DESI	*Desi ;

	// Satoh追加 2013/10/26
	int		Nevac ;
	EVAC	*Evac ;
} EQSYS;
