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

/*  eepath.h  */
#pragma once


/** 
 * @file 
 * @brief <入力データファイル>システム経路のモデルについて構造体の定義
 * @details
 *
 * 2.6 システム経路 (EESLISM7.2入力データ作成マニュアル.pdf)
 *
 * モデルの関連図
 *
 * *- SYSPTH
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * 
 * SYSPTH: 
 *
 * @sa Eeinput
 */



#define  ROOM_TYPE        "ROOM"
#define  RDPANEL_TYPE     "RPNL"
//#define  AIRFLOW_TYPE     "AIRFLOW"

///@brief 冷温水コイル
#define  HCCOIL_TYPE      "HCC"

///@brief 
//(マニュアル未定義)
#define  DXCOIL_TYPE      "DXC"

///@brief ボイラー
#define  BOILER_TYPE      "BOI"

///@brief 太陽熱集熱器
#define  COLLECTOR_TYPE   "COL"

///@brief 
//(マニュアル未定義)
#define  ACOLLECTOR_TYPE   "ACOL"


#define  COLLECTOR_PDT    'w'
#define  ACOLLECTOR_PDT   'a'

///@brief チラー、ヒートポンプチラー（空気熱源)
#define  REFACOMP_TYPE    "REFA"

///@brief 蓄熱層
#define  STANK_TYPE       "STANK"

///@brief 熱交換器(２流体式）
#define  HEXCHANGR_TYPE   "HEX"

///@brief 電気蓄熱式暖房器
#define  STHEAT_TYPE      "STHEAT"

///@brief 全熱交換器（換気の排気からの熱回収用の顕熱・潜熱熱交換器)
#define	 THEX_TYPE		  "THEX"

///@brief カロリ―メータ
#define  QMEAS_TYPE		  "QMEAS"

///@brief 温水弁の制御???
#define  VALV_TYPE		  "V"

///@brief 温調弁の制御
#define  TVALV_TYPE		  "VT"

///@brief バッチ式デシカント(マニュアル未定義)
// Satoh追加 2013/10/20
#define  DESI_TYPE		"DESICCANT"

///@brief 気化冷却器(マニュアル未定義)
// Satoh追加 2013/10/26
#define  EVAC_TYPE		"EVPCOOLING"

/*---- Satoh Debug VAV  2000/10/30 ----*/

///@brief VAV ユニット
#define  VAV_TYPE		  "VAV"

///@brief 
//(マニュアル未定義)
#define  VWV_TYPE		  "VWV"

#define	 VAV_PDT		  'A'
#define  VWV_PDT		  'W'

///@brief 配管
#define  PIPEDUCT_TYPE    "PIPE"

///@brief ダクト
#define  DUCT_TYPE        "DUCT"

#define   PIPE_PDT        'P'
#define   DUCT_PDT        'D'

///@brief ポンプ
#define  PUMP_TYPE        "PUMP"

///@brief ファン（送風機）
#define  FAN_TYPE	  "FAN"
#define  PUMP_PF	  'P'
#define  FAN_PF	 	  'F'

#define  PUMP_C			"C"
#define  PUMP_Vv		"Vv"
#define  PUMP_Vr		"Vr"

#define	 FAN_C			"C"
#define  FAN_Vd			"Vd"
#define  FAN_Vs			"Vs"
#define  FAN_Vp			"Vp"
#define  FAN_Vr			"Vr"

#define  PV_TYPE		"PV"

#define  DIVERG_TYPE      "B"
#define  CONVRG_TYPE      "C"
#define  DIVGAIR_TYPE     "BA"
#define  CVRGAIR_TYPE     "CA"

#define  DIVERGCA_TYPE    "_B"
#define  CONVRGCA_TYPE    "_C"

#define  FLIN_TYPE      "FLI"
#define  GLOAD_TYPE     "GLD"

#define  HCLOAD_TYPE     "HCLD"
#define  HCLOADW_TYPE     "HCLDW"
#define  RMAC_TYPE		 "RMAC"
#define  RMACD_TYPE		"RMACD"

#define  OMVAV_TYPE       "OMVAV"
#define  OAVAV_TYPE       "OAVAV"

#define  OUTDRAIR_NAME    "_OA"
#define  OUTDRAIR_PARM    "t=Ta x=xa *"

#define  CITYWATER_NAME   "_CW"
#define  CITYWATER_PARM   "t=Twsup *"

#define  AIR_FLD   'A'
#define  AIRa_FLD  'a'
#define  AIRx_FLD  'x'
#define  WATER_FLD 'W'

#define  HEATING_SYS  'a'
#define  HVAC_SYS     'A'
#define  DHW_SYS      'W'

#define  THR_PTYP  'T'
#define  CIR_PTYP  'C'
#define  BRC_PTYP  'B'

#define  DIVERG_LPTP  'b'
#define  CONVRG_LPTP  'c'
#define  IN_LPTP      'i'
#define  OUT_LPTP     'o'

#define  OFF_SW  'x'
#define  ON_SW   '-'
#define  LOAD_SW 'F'
#define  FLWIN_SW 'I'
#define  BATCH_SW 'B'

#define  COOLING_LOAD 'C'
#define  HEATING_LOAD 'H'
#define  HEATCOOL_LOAD 'L'

#define  COOLING_SW 'C'
#define  HEATING_SW 'H'

#define  TANK_FULL  'F'
#define  TANK_EMPTY 'E'
#define  TANK_EMPTMP  -777.0
#define  BTFILL  'F'
#define  BTDRAW  'D'

#define SYSV_EQV   'v'
#define LOAD_EQV   'L'


/**
 * @brief
 * @sa Compinit
 */
typedef struct compnt
{
	//!@brief 機器名称
	char *name;

	//!@brief 機器の設置室名称（-room）
	char	*roomname;

	//!@brief 機器タイプ（"PIPE"など）
	char	*eqptype;

	//!@brief 配管等の周囲条件名称（-env）
	char	*envname;		
	
	//!@brief 方位名称
	char	*exsname;

	//!@brief VWV制御するときの制御対象熱交換器名称
	char* hccname;

	//!@brief VWV制御するときの制御対象床暖房（未完成）
	char	*rdpnlname;

	//!@brief 入口の識別記号
	char	*idi;

	//!@brief 出口の識別記号（熱交換器の'C'、'H'や全熱交換器の'E'、'O'など）
	char	*ido;

	//!@brief SYSCMPで定義された"-S"や"-V"以降の文字列を収録する
	char	*tparm;

	//!@brief 湿りコイルの除湿時出口相対湿度の文字列を収録
	char	*wetparm;

	char	*omparm;		// 
	//char	//*pcmname;		// 電気蓄熱暖房器内臓PCMのスペック名称

	//!@brief 空気経路の場合は'Y'（湿度経路用にpathをコピーする）
	char	airpathcpy;

	//! @brief 制御情報???
    char    control;

	//! @brief 機器特有の構造体へのポインタ
	void *eqp;

	int  neqp;
	int    ncat;

	//! @brief 出口の数
	int	Nout;

	//! @brief 入口の数
	int	Nin;

	int    nivar;
	
	//! @brief 集熱器面積[m2]
	double Ac ;

	//! @brief 太陽電池容量[W]
	double PVcap ;

	//! @brief 太陽電池アレイ面積[m2]
	double Area ;

	double *ivparm;

	//! @brief 
	double eqpeff;

	//! @brief 機器出口の構造体へのポインタ（Nout個）
	struct elout *elouts;

	//!@brief 機器入口の構造体へのポインタ（Nin個）
	struct elin  *elins;

	//	struct valv	*valv ;
	struct compnt *valvcmp ;
						// 三方弁の対となるValvのCOMPNTへのポインタ
	//					/* バルブ用機器構造体 */
	//double	x,			/* バルブ開度 */
	//		xinit ;
	//char	org ;		/* CONTRLで指定されているとき'y' それ以外は'n' */
	//char	*OMfanName ;	// Valvが参照するファン風量

	//! @brief VALVで分岐などを流量比率で行う場合の観測対象のPlist名称
	char	*monPlistName ;

	//! @brief 電気蓄熱暖房器内臓PCMの容量[m3]
	double	mPCM;
}  COMPNT;


/**
 * @brief 機器の出口構造体
 * @sa Eloutinit
 */
typedef struct elout
{
	//@brief 出口の識別番号（熱交換器の'C'、'H'や全熱交換器の'E'、'O'など）
	char   id;

	//!@brief 終端の割り当てが完了していれば '-'; そうでなければ 'x'
	char	Pelmoid;

	//! @brief 通過する流体の種類（a:空気（温度）、x:空気（湿度）、W:水））
	//! @sa AIRa_FLD, AIRx_FLD, WATER_FLD 
	char	fluid;			

	//!@brief 経路の制御
	char	control;

	//!@brief 負荷を計算する場合は'y'、成り行きの場合は'n'
	char	sysld;

	//!@brief 流量
	double  G;

	//!@brief 熱量
	double	Q;

	//! @breif 連立方程式の答え
	double	sysv;
	double	load;

	//! @brief 連立方程式の定数
	double	Co;

	//! @brief 出口の係数
	double	coeffo;

	//!@brief 入口の係数（入口複数の場合はそれぞれの係数）
	double	*coeffin;

	//@brief 
	int    Ni;

	int	sv;				

	int	sld;

	//!@brief 機器出口の構造体が属する機器
	struct compnt  *cmp;

	//!@brief 機器出口の構造体が関連する機器入口
	struct elin    *elins;

	//!@brief 機器出口が属する末端経路
	struct plist   *lpath;
	
	struct elout   *eldobj, *emonitr;
}  ELOUT;


/**
 * @brief 機器の入口構造体
 * @sa Elininit
 */
typedef struct elin
{
	//! @brief 入口の識別番号（熱交換器の'C'、'H'や全熱交換器の'E'、'O'など）
	char   id;

	//! @brief 連立方程式の答え
	double  sysvin;

	//! @brief 上流の機器の出口
	struct elout  *upo, *upv;

	//! @brief 機器入口が属する末端経路
	struct plist  *lpath;
}  ELIN;


/**
 * @brief SYSPTHに記載の機器
 * @sa Pelminit
 */
typedef struct pelm
{
	char  co;
	char  ci;

	//! @brief SYSPTH記載の機器の構造体
	struct compnt *cmp;

//	struct pelm *Pelmx ;

	// @brief 機器の出口
	struct elout  *out; 

	// @brief 機器の入口
	struct elin   *in;
}  PELM;


/**
 * @brief 末端経路 (`>`)
 * @sa Plistinit
 */
typedef struct plist
{
	//!@brief 末端経路が流量未知なら1、既知なら0
	int	UnknownFlow;

	char* name;

	//!@brief 貫流経路か循環経路かの判定
	char  type;

	//!@brief 経路の制御情報
	char  control;

	//!@brief バッチ運転を行う蓄熱槽のあるとき'y'、無いとき 'n'
	char  batch;

	//!@brief 入力された経路のとき'y', 複写された経路（空気系統の湿度経路）のとき'n'
	char  org;

	//!@brief 末端経路の名前
	char	*plistname ;

	//@brief 末端経路内の機器の数
	int   Nelm;

	int	lvc;

	//@brief 経路中のバルブ数
	int	Nvalv;

	//int Npump ,

	/*---- Satoh Debug VAV  2000/12/6 ----*/

	//!@brief 経路中のVAVユニットの数 */
	int Nvav;

	//!@brief OM用変風量制御ユニット数
	int NOMVAV;

	//!@brief 流量計算の時の番号
	int n ;

	double* Go;

	//!@brief 温調弁によって計算された流量を記憶する変数
	double Gcalc;

	//!@brief  負荷計算用設定値???
	double G;

	//!@brief 流量分配比
	double	*rate ;
	
	//struct pump  *Pump ;		// ポンプ、ファン構造体へのポインタ
	struct pelm  *pelm,			// 末端経路内の機器
		*plmvb;	
	struct plist *lpair;

	//!@brief 空気系当時の温度系統
	struct plist* plistt; 

	//!@brief 空気系当時の湿度系統
	struct plist* plistx;

	struct valv	*valv ;

	struct mpath *Mpath ;

	struct plist* upplist;

	struct plist* dnplist;

	struct omvav *OMvav ;
}  PLIST;


/**
 * @brief SYSPTHにおける';'で区切られる経路
 * @sa Mpathinit
 */
typedef struct mpath
{
	//! @brief 経路名称
	char* name;
	char* sys;
	char* type;
	char* fluid;

	//! @brief 経路の制御情報??
	char* control;

	//! @brief 経路要素の動的配列の要素数
	int   Nlpath;

	int   NGv;

	int   NGv2;

	int   Ncv;

	int   lvcmx;

	//! @brief 経路要素の動的配列
	struct plist* plist;
						// 末端経路
//		*pl[PLMAX] ;
	struct plist **pl ;
	
	//!@ brief 流量比率が入力されている経路なら'Y'
	char	rate ;
	
	//! @brief 流量比率設定時の既知流量へのポインタ
	double	*G0 ;

	struct mpath	*mpair;

	//	struct compnt  *cbcmp[CBCMPMX] ;

	//! @brief 流量連立方程式を解くときに使用する分岐・合流機器
	struct compnt	**cbcmp ;
} MPATH;


/**
 * @brief バルブ
 */
typedef struct valv
{
	char	*name ;
	int		count ;

	//! @brief バルブ開度
	//! 初期値=-999.0
	double	x;

	//!@ brief バルブ開度の初期値
	double	*xinit ;

	//!@brief CONTRLで指定されているとき'y' それ以外は'n'
	char	org ;

	struct compnt *cmp, *cmb, *mon ;

	double	*Tin, *Tset, *Tout ;

	double	*MGo ;

	PLIST	*Plist, *monPlist ;
	//struct omvav	*OMfan ;
	//char	*OMfanName ;
} VALV ;
