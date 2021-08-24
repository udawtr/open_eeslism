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

/* eps.h */

#pragma once

#define EPOS_PROG 0

#define VTYPEMAX 50
#define CATNMMAX 50

#if EPOS_PROG

#define IDFO     ".efv"
#define STOTALMAX 20
#define MAXPARM   20
#define PNAMEMAX  20
#define NREQMAX   30
#define NPREQMAX  30


typedef struct rmprt
{
	char *name;
	int  Ndat, Nrm, Nld, Nasp, Nrp;
} RMPRT;

#endif


/**
 * @brief シミュレーション結果に関する注釈
 */
typedef struct estl
{
	//! ファイル種別記号
	char* flid;

	//! 標題(題目)
	char* title;

	//! 気象データファイル名
	char* wdatfile;
	
	//! 入力データ種別  h:時刻別  d:日別  M:月別
	char tid;

	char* unit[VTYPEMAX];

	//! 時刻データ表示  [Y]MD[W]T
	char* timeid;

	//! 地名(地域情報　地名　緯度　経度など) (wdloc)
	char* wdloc;

	struct catnm *catnm;
	
	//! 時刻データ表示字数
	int ntimeid;

	//! 項目ごとの全データ数
	int Ntime;

	//! 計算時間間隔[s]
	int dtm;
	int Nunit;
	int Nrqlist; 
	int Nvreq;
	int Npreq;
	int Npprd;

	//! 各時刻ごとのデータ個数 (Ndata)
	int Ndata;
	
	struct rqlist  *Rq;
	struct prqlist *Prq;
	char vreq[VTYPEMAX];
} ESTL;


/**
 * @brief 要素カタログ名データ
 */
typedef struct catnm
{
	char *name;
	int  N,             /* 機器数 */
        Ncdata;        /* 全データ項目数 = 機器数 x 機器データ項目数 */
} CATNM;


/**
 * @brief 年、月、日、曜日、時刻データ
 */
typedef struct tmdt
{
	char year[3],
        mon[3], 
		day[3],
		wkday[3],
        time[10],
		*dat[5];  /* 年、月、日、曜日、時刻のポインター */
	
	int  Year,
        Mon,
		Day,
		Time;
} TMDT;

/** 
 * @brief シミュレーション結果
 */
typedef struct tlist 
{
	char* cname;
	char* name;
	char* id;
	char* unit;

	//! データ種別
	//! t:温度  x:絶対湿度  r:相対湿度
	//! T:平均温度  X:平均絶対湿度  R:平均相対湿度
	//! h:発生時刻  H:積算時間 q:熱量 Q:積算熱量
	//! e:エネルギー E:積算エネルギー量
	char vtype;

	//! データ処理種別 t:積算値  a:平均値  n:最小値  m;最大値
	char stype; 

	//! データ型  c:文字型  d:整数型  f:実数型
	char ptype;
	char req;
	
	//! 実数型の計算結果配列
	double* fval;
	double* fstat;

	//! 整数型の計算結果配列
	int* ival;
	int* istat;

	//! 文字型の計算結果配列
	char* cval;
	char* cstat;

	//! 出力時の書式
	//! see: fofmt
	char* fmt;
	
	struct tlist *pair;  
} TLIST;


/**
 * @brief 選択項目
 */
typedef struct rqlist
{
	char *rname,
        *name,
        *id;
} RQLIST;

#if EPOS_PROG
typedef struct statc  /* 集計期間 */
{
	char *name;
	int  yrstart,
        mostart,
		daystart, 
        yrend,
		moend,
		dayend,
		nday;
	char dymrk[366];
} STATC;

typedef struct prqlist /* 作表項目・期間指定 */
{
	char mark,
        *prname[PNAMEMAX],
		*prid[PNAMEMAX];
	int  Npname, Npid;
} PRQLIST;

#endif
