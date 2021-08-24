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

/*  simcon.h  */

#pragma once

#include <stdio.h>
#include "common.h"
#include "eps.h"
#include "wthrd.h"

#define  EEVERSION  "ES4.6"

#define  PRTREV     "_re"
#define  PRTHROOM   "_rm"

#define  PRTPMV     "_pm"
#define  PRTQRM     "_rq"
#define  PRTRSF     "_sf"
#define	 PRTSFQ		"_sfq"
#define	 PRTSFA		"_sfa"
#define  PRTDYSF	"_dsf"
#define  PRTWAL     "_wl"
#define  PRTSHD     "_shd"
#define  PRTPCM     "_pcm"

#define  PRTPATH    "_sp"
#define  PRTCOMP    "_sc"

#define  PRTHRSTANK "_tk"

#define  PRTHWD     "_wd"

#define  PRTDYRM    "_dr"
#define  PRTMNRM	"_mr"
#define  PRTDYCOMP  "_dc"
#define  PRTMNCOMP  "_mc"
#define  PRTMTCOMP  "_mt"
#define  PRTDQR     "_dqr"
#define  PRTDWD     "_dwd"
#define  PRTMWD     "_mwd"

#define  PRTWK      "_wk"

#define  PRTHELM    "_rqe"
#define  PRTHELMSF  "_sfe"
#define  PRTDYHELM  "_dqe"

#define SYSV_EQV   'v'
#define LOAD_EQV   'L'

/**
 * @file 
 * @brief <入力データファイル>システム経路のモデルについて構造体の定義
 * @details
 *
 * 2.9 ファイル上のデータによる条件設定（VCFILE データ)
 *     (EESLISM7.2入力データ作成マニュアル.pdf)
 *
 * モデルの関連図
 *
 * *- VCFILE
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 * VCFILE:
 *
 * @sa Eeinput
 */


/**
 * @brief
 * @sa Simcinit
 */
typedef struct simcontl
{
	//! 入力データファイル名
	char* File;
	
	//! 題目、注釈
	char* title[SCHAR];

	//char* city[NCHAR];

	//! 気象データファイル名
	char* wfname;

	//! 計算結果出力ファイルセット (GDATA FILE -out)
	char* ofname;

	//! "t_C x_kg/kg r_% q_W e_W" で初期化される
	char* unit;

	//! "Q_kWh E_kWh" で初期化される
	char* unitdy;

	//! "MDT" で初期化される。
	char timeid[6];

	//! 要素別熱取得、熱損失計算 'y'
	char helmkey;

	//! 気象データファイル種別 'H':HASP標準形式　'E':VCFILE入力形式
	char wdtype;

	//! 周期定常計算の時'y'
	char perio;

	FILE* fwdata;
	FILE* fwdata2;
	FILE* ftsupw;

	//! 予備計算開始日
	int daystartx;

	//! 計算開始日
	int daystart;

	//! 計算終了日
	int dayend;

	//! 曜日
	int	daywk[366];

	//! 毎時計算結果出力日の指定。
	int dayprn[366];

	int Dayntime;

	int Ntimehrprt;
	int	Ntimedyprt;

	//! 要素別壁体表面温度出力壁体数
	int Nhelmsfpri;

	//! 読み込んだ境界条件、負荷入力用ファイルの数
	int Nvcfile;

	//! 境界条件・負荷設定用入力ファイルの動的配列
	struct vcfile *Vcfile;

	struct locat *Loc;
	struct wdpt  wdpt;

	//! 計算時間間隔[s] (GDATA RUN dTime)
	int dTm;

	//! 計算開始時刻(ttmm) 例)01:30 => 130 (GDATA RUN Stime)
	int sttmm;

	//! 最大収束回数
	int MaxIterate;

}  SIMCONTL;


typedef struct flout
{
	FILE *f;
	char *idn;
} FLOUT;


/**
 * @brief 境界条件・負荷設定用入力ファイル(VCFILE)
 */
typedef struct vcfile
{
	FILE	*fi;
	long	ad;
	int		ic;

	//! ファイル引用名 (VCFILE <Fname>)
	char* name;

	//! データファイル名 (VCFILE <Fname> -f <filename>)
	char *fname;

	//! シミュレーション結果に関する注釈
	struct estl  Estl;

	//! シミュレーション結果
	struct tlist *Tlist;
} VCFILE;


typedef  struct daytm
{
	//! 通日
	int day;

	//! 年
	int Year;

	//! 月
	int Mon;

	//! 日
	int Day;

	//! 日積算値出力
	int ddpri;

	double  time;
	int    ttmm;
	int tt;

} DAYTM;
