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

/*    ee_gndata.c      */

#define _CRT_SECURE_NO_WARNINGS
#define FLDELIM  '/'
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
/*************
#include "wthrd.h"
******************/
#include "fesy.h"
#include "fnfio.h"
#include "lib/u_sun.h"
#include "fnlib.h"

/*   ファイル、計算期間、出力日の入力        */

//------------------------------------------------------------------
//GDAT (P.17)
//計算指定：計算期間や出力期間、使用する気象データファイルなどの指定
//------------------------------------------------------------------


/**
 * @fn
 * 入力データファイルの計算していGDATAの読み取り P.17
 * @param[in]     fi         読み取り元ファイルポインタ
 * @param[in]     dsn        fiで読み取った GDATA宣言の先頭行の文字列??
 * @param[in]     File       入力データファイル名
 * @param[out]    wfname     気象データファイル名 (GDATA FILE -w)
 * @param[out]    ofname     計算結果出力ファイルセット (GDATA FILE -out)
 * @param[out]    dtm        計算時間間隔[s] (GDATA RUN dTime)
 * @param[out]    sttmm      計算開始時刻(ttmm) 例)01:30 => 130 (GDATA RUN Stime)
 * @param[out]    dayxs      予備計算開始日
 * @param[out]    days       計算開始日
 * @param[out]    daye       計算終了日
 * @param[out]    Tini       初期温度 (GDATA RUN Tinit)
 * @param[out]    pday       毎時計算結果出力日の指定。出力日のインデックスには1が指定される。
 * @param[out]    wdpri      気象データの出力指定 (GDATA PRINT *wd)
 * @param[out]    revpri     室内熱環境データの出力指定 (GDATA PRINT *rev)
 * @param[out]    pmvpri     室内の PMV の出力指定 (GDATA PRINT *pmv)
 * @param[out]    helmkey    負荷要素の出力指定 (GDATA PRINT *helm)
 * @param         MaxIterate
 * @param[in,out] Daytm      計算開始初期日が設定される
 * @param[in,out] Wd         気象データ
 * @param[out]    perio      周期定常計算フラグ
 */
void Gdata (FILE *fi, char *dsn, char *File, char **wfname, char **ofname,
			int *dtm, int *sttmm, int *dayxs, int *days, int *daye, double *Tini, int *pday,
			int *wdpri, int *revpri, int *pmvpri, char *helmkey, int *MaxIterate, DAYTM *Daytm, WDAT *Wd, char *perio)
{
	char	s[SCHAR], ss[SCHAR], *ce, *st, E[SCHAR], dd[SCHAR];
	int		Ms, Ds, Mxs=0, Dxs=0, Me, De, n, ns, ne, i;
	int		logprn = 0 ;
	
	*dtm = 3600;
	*sttmm = -1;
	
	*wfname = NULL;
	
	sprintf (E, ERRFMT, dsn);
	
	*ofname = stralloc( File);

	for (i=1; i<366; i++)
		pday[i] = 0;

	/*****************
	printf ( "%s\n", ofname ) ;
	*****************************/
	
	if ((st = strrchr(*ofname, '.')) != NULL)
		*st = '\0';
	
	while (fscanf(fi, "%s", s), s[0] != '*')
	{ 
		//------------------------------------
		//FILE
		//------------------------------------
		if (strcmp(s, "FILE") == 0)
		{ 
		/********
		strcpy(ofname, File);
		if ((st = strrchr(ofname, '.')) != NULL)
		*st = '\0';
			*******/
			
			while (fscanf(fi, "%s", s), s[0] != ';')
			{
				if ((ce=strchr(s, ';')) != 0)
					*ce = '\0';
				
				if (strcmp(s, "-skyrd") == 0)
				{
					// 気象データは夜間放射量で定義されている
					Wd->RNtype = 'R';
				}
				else if (strcmp(s, "-intgtsupw") == 0)
				{
					// 給水温度を補間する
					Wd->Intgtsupw = 'Y';
				}
				else
				{
					st=strchr(s, '=');
					*st = '\0';
					if (strcmp(s, "w") == 0)
					{
						//気象データファイル名
						sscanf(st+1, "%s", dd);
						*wfname= stralloc( dd ) ;
					}
					else if (strcmp(s, "out") == 0)
					{
						//計算結果出力ファイルセット
						sscanf(st+1, "%s", ss);
						if (strrchr(ss, FLDELIM) == NULL)
						{
							free ( *ofname) ;
							
							*ofname = stralloc( File);
							
							if ((st = strrchr(*ofname, FLDELIM)) != NULL)
								strcpy(st + 1, ss);
						}
						else
						{
							free ( *ofname ) ;
							*ofname= stralloc ( ss);
						}
					}
					else
						Eprint ( "<Gdata>", s );
				}
				
				if ( ce )
					break;
			}
		}

		//------------------------------------
		//RUN
		//------------------------------------
		else if (strcmp(s, "RUN") == 0)
		{
			*Tini=15.0;
			
			while (fscanf(fi, "%s", s), s[0] != ';')
			{
				if ((ce=strchr(s, ';')) != 0)
					*ce = '\0';

				if (s[0] == 'T')
				{
					//初期温度
					sscanf(s, "%*[^=]=%lf", Tini);
				}
				else if ((st = strchr(s, '=')) != NULL)
				{
					*st = '\0';
					if (strcmp(s, "dTime") == 0)
					{
						//計算時間間隔[s]
						*dtm = atoi(st + 1);
					}
					else if (strcmp(s, "Stime") == 0)
					{
						//計算開始時刻(ttmm)
						*sttmm = atoi(st + 1) * 100;
					}
					else if (strcmp(s, "MaxIterate") == 0)
					{
						//(マニュアル未記載)
						*MaxIterate = atoi(st + 1);
					}
					else if (strcmp(s, "RepeatDays") == 0)	// 周期定常計算の繰り返し日数の取得
					{
						//(マニュアル未記載)
						int Ndays;
						Ndays = atoi(st + 1);
						if (*perio != 'y')
							printf("周期定常計算の指定がされていません\n");
						*daye = *days + Ndays - 1;
					}
				}
				else if (s[0] == '(')
				{
					//予備計算開始日
					sscanf(s, "(%d/%d)", &Mxs, &Dxs);
					*dayxs = FNNday(Mxs, Dxs);
				}
				else if (strcmp(s, "-periodic") == 0)
				{
					// 周期定常計算への対応
					*perio = 'y';			// 周期定常計算フラグの変更
					fscanf(fi, "%s", s);	// 計算する日付の読み込み
					sscanf(s, "%d/%d", &Ms, &Ds);	// 計算する日付の取得
					*days = FNNday(Ms, Ds);
					*dayxs = *days;
					Daytm->Mon = Ms;
					Daytm->Day = Ds;
				}
				else if (strchr(s,'-') != 0)
				{
					//計算開始 - 計算終了
					sscanf(s, "%d/%d-%d/%d", &Ms,&Ds,&Me,&De);
					*days = FNNday(Ms, Ds);
					*daye = FNNday(Me, De);
					if (Mxs == 0)
					{
						//予備計算なしの場合
						*dayxs = *days;
						Daytm->Mon = Ms;
						Daytm->Day = Ds;
					}
					else
					{
						//予備計算ありの場合
						Daytm->Mon = Mxs;
						Daytm->Day = Dxs;
					}		  
				}
				else
					Eprint ( "<Gdata>", s ) ;

				if ( ce )
					break;
			}
			printf("<<Gdata>> dtm=%d\n", *dtm);
		}

		//------------------------------------
		//PRINT
		//------------------------------------
		else if (strcmp(s, "PRINT") == 0)
		{
			while (fscanf(fi, "%s", s), s[0] != ';')
			{
				if ((ce=strchr(s, ';')) != 0)
					*ce = '\0';

				if (strcmp(s, "*wd") == 0)
				{
					//気象データの出力指定
					*wdpri = 1;
				}
				else if (strcmp(s, "*rev") == 0)
				{
					//室内熱環境データの出力指定
					*revpri = 1;
				}
				else if (strcmp(s, "*pmv") == 0)
				{
					//室内の PMV の出力指定
					*pmvpri = 1;
				}
				else if (strcmp(s, "*helm") == 0)
				{
					//負荷要素の出力指定
					*helmkey = 'y';
				}
				else if (strcmp(s, "*log") == 0)
				{
					//プログラムの実行による処理経過をファイルに出力
					logprn = 1;
				}
				else if (strcmp(s, "*debug") == 0)
				{
					//計算の経過をファイルに出力
					EnterDebugMode();
				}
				else if (strchr(s, '-') == 0)
				{
					//毎時計算結果出力日(mm/dd)
					sscanf(s, "%d/%d", &Ms, &Ds);
					pday[ FNNday(Ms, Ds) ] = 1;
				}
				else
				{
					//毎時計算結果出力日(mm/dd-mm/dd)
					sscanf(s, "%d/%d-%d/%d", &Ms, &Ds, &Me, &De);
					ns = FNNday(Ms, Ds);
					ne = (ns < (n=FNNday(Me, De)) ? n : n+365);
					for (n=ns; n <= ne; n++)
						pday[ (n > 365 ? n-365 : n) ] = 1;
				}
				
				if ( ce )
					break;
			}
		}
		else
			Eprint ( "<Gdata>", s );
   }

   strcat ( strcpy ( s, *ofname ), ".log" ) ;
   ferr = fopen ( s, "w" ) ;

   if ( logprn == 0 )
   {
	   fclose ( ferr ) ;
	   ferr = NULL ;
   }
}
