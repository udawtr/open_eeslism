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

typedef struct simcontl
{
	//! 入力データファイル名
	char* File;
	
	//! 題目、注釈
	char* title[SCHAR];

	//char* city[NCHAR];

	//! 気象データファイル名
	char* wfname;
	char* ofname;
	char* unit;
	char* unitdy;
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

	int daystartx;
	int daystart;
	int dayend;
	int	daywk[366];
	int dayprn[366];

	int Dayntime;

	int Ntimehrprt;
	int	Ntimedyprt;

	//! 要素別壁体表面温度出力壁体数
	int Nhelmsfpri;

	//! 境界条件、負荷入力用ファイル
	int Nvcfile;
	struct vcfile *Vcfile;

	struct locat *Loc;
	struct wdpt  wdpt;

	int dTm;
	int sttmm;

	int MaxIterate;			// 最大収束回数

}  SIMCONTL;


typedef struct flout
{
	FILE *f;
	char *idn;
} FLOUT;


typedef struct vcfile  /* 境界条件・負荷設定用入力ファイル */
{
	FILE	*fi;
	long	ad;
	int		ic;
	char	*name, *fname;
	struct estl  Estl;
	struct tlist *Tlist;
} VCFILE;


typedef  struct daytm
{
	int    day,   /*通日*/
	Year,  /*年  */
	Mon,   /*月  */
	Day,   /*日  */

	ddpri; /*日積算値出力*/

	double  time;
	int    ttmm,
		tt;

} DAYTM;
