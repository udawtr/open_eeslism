//This file is part of EESLISM.
//
//Foobar is free software : you can redistribute itand /or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 3 of the License; or
//(at your option) any later version.
//
//Foobar is distributed in the hope that it will be useful;
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with Foobar.If not; see < https://www.gnu.org/licenses/>.

/*   sched.h    */

#pragma once

/*
 * @brief <入力データファイル>スケジュールのモデルについて構造体の定義
 * @details
 *
 * 2.8 スケジュールデータ (EESLISM7.2入力データ作成マニュアル.pdf)
 *
 * モデルの関連図
 *
 * *- SCHTB
 * +- SCHNM
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 * SCHTB:  一日の設定値、切換スケジュールおよび季節、曜日の指
 * SCHNM: 日スケジュールの季節、曜日による変更の定義
 *
 * @sa Eeinput
 */


//
// SCHDL --+-- SEASN 季節設定
//         |
//         +-- WKDY  曜日設定
//         |
//         +-- DSCH 設定値（温・湿度、風量 ･････ ）スケジュール
//         |
//         +-- DSCW 切換設定スケジュール
//         |
//         +-- SCH(for DSCH)  スケジュール (SEASN, WKDYを展開し、DSCHへの参照のリストへ)
//         |
//         +-- SCH(for DSCW)  スケジュール (SEASN, WKDYを展開し、DSCWへの参照のリストへ)
// 
// スケジュ－ル表 = {季節,曜日,設定値,切替設定}
//


//@brief 季節設定 (`-ssn`)
typedef struct seasn
{
	//! 季節名
	char    *name;

	//! 定義数(sday,edayの配列長)
	int		N;

	//! 開始年間通日
	int* sday;

	//! 終了年間通日
	int* eday;

	//! 季節設定の数
	int     end;
} SEASN ;


//@brief 曜日設定 (`-wkd`)
typedef struct wkdy
{
	//! 曜日名
	char    *name;

	//TODO: 配列長さは8で良いと思われる。
	//! 月火水木金土日休 の8パターンで、指定された曜日のインデッスには 1がセットされる。
	int     wday[15];

	//! 曜日設定の数
	int     end;
} WKDY ;


//@brief 設定値（温・湿度、風量 ･････ ）スケジュール定義 (`-v`)
typedef struct dsch
{
	//! 設定値名
	char    *name;

	//! 定義数(stime,val,etimeの配列長)
	int     N;

	//! 開始時分の配列
	int* stime;

	//! 終了時分の配列
	int* etime;

	//! 設定値の配列
	double	*val ;

	//! 設定値（温・湿度、風量 ･････ ）スケジュール定義の数
	int     end;
} DSCH ;


//@brief 切換設定スケジュール定義 (`-s`)
typedef struct dscw
{
	//! 切換設定名
	char* name;

	//! 重複を除外した切替値の配列 (see: Nmod)
	char dcode[10];

	//! 定義数(stime,mode,etimeの配列長)
	int     N;

	//! 開始時分の配列
	int *stime;

	//! 切替値の配列
	char* mode;

	//! 終了時分の配列
	int *etime;

	//! 重複を除外した切替値の配列の長さ
	int Nmod;

	//! 切換設定スケジュール定義の数
	int     end;
} DSCW ;


//@brief スケジュ－ル
typedef struct sch
{
	//! スケジュール名
	char* name;
	char type;

	//! 設定値または切替設定スケジュール定義のインデックスの配列
	int     day[366];

	//! スケジュールの数
	int     end;
} SCH;


/*
 * @brief スケジュール (SCHTB, SCHNM) 
 * @detail
 * スケジュール表および展開されたスケジュール
 * @sa Schtable, Schdata
 */
typedef struct schdl
{
	//------SCHTB スケジュール表 ------//

	//! 季節設定の動的配列
	SEASN   *Seasn ;

	//! 曜日設定の動的配列
	WKDY    *Wkdy ;

	//! 設定値（温・湿度、風量 ･････ ）スケジュール定義の動的配列
	DSCH    *Dsch ;

	//! 切換設定スケジュール定義の動的配列
	DSCW    *Dscw ;

	//------SCHNM スケジュール ------//

	//! 設定値（温・湿度、風量 ･････ ）の年間スケジュールの動的配列
	SCH* Sch;

	//! 切換設定の年間スケジュールの動的配列
	SCH* Scw;

	//! 設定値（温・湿度、風量 ･････ ）の年間スケジュールの数
	int    Nsch;

	//! 切換設定の年間スケジュールの数
	int    Nscw;


	double   *val;

	char    *isw;
} SCHDL;
