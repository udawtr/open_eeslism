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


// ---------------------------------
// 1.2.2 出力データファイル
// ---------------------------------

//------ 時間別計算値 -----

/**
 * @def   PRTHROOM
 * @brief 毎時出力／建物シミュレーション結果 (室温、湿度、室内表面温度、熱負荷) - 放射パネルの出力
 */
#define  PRTHROOM   "_rm"

/**
 * @def   PRTREV
 * @brief 毎時出力／建物シミュレーション結果 (室温、湿度、平均表面温度、相対湿度) - 毎時室温、MRTの出力
 */
#define  PRTREV     "_re"

/**
 * @def   PRTRSF
 * @brief 毎時出力／建物シミュレーション結果 (室内表面温度) [OPTION] - 室内表面温度の出力
 */
#define  PRTRSF     "_sf"

/**
 * @def
 * @brief 壁体内温度
 */
#define  PRTWAL     "_wl"

/**
 * @def   PRTSFQ
 * @brief 毎時出力／建物シミュレーション結果 (室内表面熱流) [OPTION]
 */
#define	 PRTSFQ		"_sfq"

 /**
 * @def   PRTSFA
 * @brief 毎時出力／建物シミュレーション結果 (室内表面熱伝達率) [OPTION]
 */
#define	 PRTSFA		"_sfa"

/**
 * @def   PRTQRM
 * @brief 毎時出力／建物シミュレーション結果 (日射および室内発熱、すきま風による熱取得要素) [OPTION] - 室の熱取得要素の出力
 */
#define  PRTQRM     "_rq"

/**
 * @def   PRTPMV
 * @brief 毎時出力／建物シミュレーション結果 (室温、湿度、室内表面温度、熱負荷) [OPTION] - PMV計算結果の出力
 */
#define  PRTPMV     "_pm"

/**
 * @def   PRTCOMP
 * @brief 毎時出力／機器ごとのシミュレーション結果(入口・出口水温、各種熱量、エネルギー消費量など)
 */
#define  PRTCOMP    "_sc"

/**
 * @def   PRTPATH
 * @brief 毎時出力／システム要素の流量、機器出入口温度をシステム経路に沿った出力
 */
#define  PRTPATH    "_sp"

/**
 * @def   PRTHWD
 * @brief 毎時出力／気象データ(外気温、方位別日射量などの気象データ) [OPTION]
 */
#define  PRTHWD     "_wd"



//------ 日集計出力 ------

/**
 * @def   PRTDYRM
 * @brief 日集計出力／建物シミュレーション結果(室温、湿度、室内表面温度、熱負荷日集計値)
 */
#define  PRTDYRM    "_dr"

/**
 * @def   PRTDQR
 * @brief 日集計出力／建物シミュレーション結果(日射および室内発熱熱取得要素日積算値) [OPTION]
 */
#define  PRTDQR     "_dqr"

/**
* @def   PRTDYCOMP
* @brief 日集計出力／機器ごとのシミュレーション結果(入口・出口水温、各種熱量、エネルギー消費量などの日集計値)
*/
#define  PRTDYCOMP  "_dc"

/**
 * @def   PRTDWD
 * @brief 日集計出力／気象データ(気象データ日平均、日積算値) [OPTION]
 */
#define  PRTDWD     "_dwd"


//------ 月集計出力 ------

/**
 * @def   PRTMNRM
 * @brief 月集計出力／建物シミュレーション結果(月積算値、平均値、最高・最低値)
 */
#define  PRTMNRM	"_mr"

/**
 * @def   PRTMNCOMP
 * @brief 月集計出力／機器ごとのシミュレーション結果(月積算値、平均値、最高・最低値)
 */
#define  PRTMNCOMP  "_mc"

/**
 * @def   PRTMWD
 * @brief 月集計出力／気象データ(月積算値、平均値、最高・最低値) [OPTION]
 */
#define  PRTMWD     "_mwd"

/**
 * @def   PRTMTCOMP
 * @brief 月・時刻集計値出力／機器ごとのシミュレーション結果（エネルギー消費量の月・時刻集計値）
 */
#define  PRTMTCOMP  "_mt"




/**
 * @def   PRTDYSF
 * @brief 日積算壁体貫流熱取得の出力
 */
#define  PRTDYSF	"_dsf"

/**
 * @def   PRTSHD
 * @brief 毎時出力／日よけの影面積出力
 */
#define  PRTSHD     "_shd"

/**
 * @def   PRTPCM
 * @brief (マニュアル未記載)
 */
#define  PRTPCM     "_pcm"

/**
 * @def   PRTHRSTANK
 * @brief 毎時出力／蓄熱槽内温度分布の出力
 */
#define  PRTHRSTANK "_tk"

/**
 * @def   PRTWK
 * @brief 月・日・通日・曜日の出力
 */
#define  PRTWK      "_wk"

/**
 * @def   PRTHELM
 * @brief (マニュアル未記載) 毎時出力／要素別熱取得、熱損失計算
 */
#define  PRTHELM    "_rqe"

/**
 * @def   PRTHELMSF
 * @brief (マニュアル未記載) 毎時出力／要素別熱取得、熱損失計算
 */
#define  PRTHELMSF  "_sfe"

/**
 * @def   PRTDYHELM
 * @brief (マニュアル未記載) 日集計出力／要素別熱取得、熱損失計算
 */
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

	/**
	 * @brief `wfname`で定義される気象データファイルの読み取り専用ファイルポインタ
	 * @sa eeflopen
	 */
	FILE* fwdata;

	/**
	 * @brief `wfname`で定義される気象データファイルの読み取り専用ファイルポインタ
	 * @sa eeflopen
	 */
	FILE* fwdata2;

	/**
	 * @brief `supw.efl` ファイルの読み取り専用ファイルポインタ
	 * @sa eeflopen
	 */
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

	LOCAT *Loc;
	WDPT wdpt;

	//! 計算時間間隔[s] (GDATA RUN dTime)
	int dTm;

	//! 計算開始時刻(ttmm) 例)01:30 => 130 (GDATA RUN Stime)
	int sttmm;

	//! 最大収束回数
	int MaxIterate;

}  SIMCONTL;


/**
 * @brief 出力ファイルの一覧
 */
typedef struct flout
{
	FILE *f;

	//! @brief 出力ファイル種別 ex) "_sp"
	//! 
	//! 1.2.2 出力データファイル (EESLISM7.2入力データ作成マニュアル.pdf)
	//! ref: #define PRTxxxxxxx
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


/**
 * @brief 
 */
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
