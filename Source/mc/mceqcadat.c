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

/*  eqcadat.c  */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esize.h"
#include "fesy.h"
#include "fnmcs.h"
#include "fnlib.h"

/**
 * @file
 * @brief 機器カタログデータの読み込み関数の定義
 */


//------ プライベート関数の宣言 ------

void _Eqpcount(FILE* fi, int* NBOI, int* NREFA, int* NCOL, int* NSTANK, int* NHCC,
	int* NHEX, int* NPIPE, int* NPUMP, int* NVAV, int* NSTHEAT, int* NTHEX, int* NPV, int* NOMVAV, int* NDESI, int* NEVAC);
int	_pflistcount(FILE* fl);

//------------------------------------


/*
 * @brief 機器カタログデータの読み込み
 * @param[IN]  f     読込元ファイルポインタ
 * @param[IN]  dsn
 * @param[OUT] Eqcat 機器カタログデータの動的配列
 */
void Eqcadata (FILE *f, char *dsn, EQCAT *Eqcat)	      
{
    char	s[SCHAR], ss[SCHAR], *ce, E[SCHAR];
	int		N ;
	int		NBOI, NREFA, NCOL, NSTANK, NHCC, NHEX, NPIPE, NPUMP, NVAV, NSTHEAT, NTHEX, NPV, NDESI, NEVAC ;
	int		NOMVAV ;

    
    FILE *frf;

	//
	// 1) 機種ごとの定義数を確認
	//
    
	NBOI = NREFA = NCOL = NSTANK = NHCC = NHEX
		= NPIPE = NPUMP = NVAV = NSTHEAT = NTHEX = NPV = NOMVAV = NDESI = NEVAC = 0 ;

	//printf("1 %s\n", Room->trnx->nextroom->name) ;

	//機器種別ごとの仕様定義数を取得
	_Eqpcount ( f, 
		&NBOI,		//2) BOI ボイラー
		&NREFA,		//3) REFA チラー、ヒートポンプチラー（空気熱源)
		&NCOL,		//4) COL,ACOL 太陽熱集熱器
		&NSTANK,	//7) STANK 蓄熱層
		&NHCC,		//1) HCC 冷温水コイル
		&NHEX,		//8) HEX 熱交換器(２流体式）
		&NPIPE,		//6) PIPE,DUCT 配管
		&NPUMP,		//9) PUMP,FAN ポンプ
		&NVAV,		//10) VAV,VWV VAVユニット
		&NSTHEAT,	//11) STHEAT 電気蓄熱式暖房器
		&NTHEX,		//12)THEX 全熱交換器
		&NPV,		//5) PV 太陽電池
		&NOMVAV,	//?? OMVAV,OAVAV ?????
		&NDESI,		//14) DESICCANT バッチ式デシカント空調機
		&NEVAC		//15) EVPCOOLING 気化冷却器
	);


	//
	// 2) 機種ごとにメモリを確保
	//

	//printf("2 %s\n", Room->trnx->nextroom->name) ;

	// 2-1) HCC 冷温水コイル
	N = NHCC ;
	Eqcat->Hccca = NULL ;
    if (N > 0 )
	{
		if ((Eqcat->Hccca = (HCCCA *)malloc(N * sizeof(HCCCA))) == NULL)
			Ercalloc(N, dsn);
	}

	// 2-2) BOI ボイラー
	N = NBOI ;
	Eqcat->Boica = NULL ;
    if (N > 0 )
	{
		if ((Eqcat->Boica = (BOICA *)malloc(N * sizeof(BOICA))) == NULL)
			Ercalloc(N, dsn);
	}

	// 2-3) チラー、ヒートポンプチラー（空気熱源)
	N = NREFA ;
	Eqcat->Refaca = NULL ;
    if (N > 0 )
	{
		if ((Eqcat->Refaca = (REFACA *)malloc(N * sizeof(REFACA))) == NULL)
			Ercalloc(N, dsn);
	}

	// 2-4) COL,ACOL 太陽熱集熱器
	N = NCOL ;
	Eqcat->Collca = NULL ;
    if (N > 0 )
	{
		if ((Eqcat->Collca = (COLLCA *)malloc(N * sizeof(COLLCA))) == NULL)
			Ercalloc(N, dsn);
	}

	// 2-5) 太陽電池
	N = NPV ;
	Eqcat->PVca = NULL ;
    if (N > 0 )
	{
		if ((Eqcat->PVca = (PVCA *)malloc(N * sizeof(PVCA))) == NULL)
			Ercalloc(N, dsn);
	}

	// 2-6) PIPE 配管
	N = NPIPE ;
	Eqcat->Pipeca = NULL ;
    if (N > 0 )
	{
		if ((Eqcat->Pipeca = (PIPECA *)malloc(N * sizeof(PIPECA))) == NULL)
			Ercalloc(N, dsn);
	}

	// 2-7) STANK 蓄熱層
	N = NSTANK ;
	Eqcat->Stankca = NULL ;
    if (N > 0 )
	{
		if ((Eqcat->Stankca = (STANKCA *)malloc(N * sizeof(STANKCA))) == NULL)
			Ercalloc(N, dsn);
	}

	// 2-8) HEX 熱交換器(２流体式）
	N = NHEX ;
	Eqcat->Hexca = NULL ;
    if (N > 0 )
	{
		if ((Eqcat->Hexca = (HEXCA *)malloc(N * sizeof(HEXCA))) == NULL)
			Ercalloc(N, dsn);
	}

	// 2-9) ポンプ
	N = NPUMP ;
	Eqcat->Pumpca = NULL ;
    if (N > 0 )
	{
		if ((Eqcat->Pumpca = (PUMPCA *)malloc(N * sizeof(PUMPCA))) == NULL)
			Ercalloc(N, dsn);
	}

	// 2-10) VAV ユニット
	N = NVAV ;
	Eqcat->Vavca = NULL ;
	if (N > 0 )
	{
		if ((Eqcat->Vavca = (VAVCA *)malloc(N * sizeof(VAVCA))) == NULL)
			Ercalloc(N, dsn);
	}

	// 2-11) STHEAT 電気蓄熱式暖房器
	N = NSTHEAT ;
	Eqcat->stheatca = NULL ;
	if (N > 0 )
	{
		if ((Eqcat->stheatca = (STHEATCA *)malloc(N * sizeof(STHEATCA))) == NULL)
			Ercalloc(N, dsn);
    }

	// 2-12) THEX 全熱交換器
	N = NTHEX ;
	Eqcat->Thexca = NULL ;
	if (N > 0 )
	{
		if ((Eqcat->Thexca = (THEXCA *)malloc(N * sizeof(THEXCA))) == NULL)
			Ercalloc(N, dsn);
    }

	// 2-13) ?????
	N = NOMVAV ;
	Eqcat->OMvavca = NULL ;
	if (N > 0 )
	{
		if ((Eqcat->OMvavca = (OMVAVCA *)malloc((N+1) * sizeof(OMVAVCA))) == NULL)
			Ercalloc(N, dsn);
	}

	// 2-14) DESICCANT バッチ式デシカント空調機
	// Satoh追加　2013/10/20
	N = NDESI ;
	Eqcat->Desica = NULL ;
	if (N > 0 )
	{
		if ((Eqcat->Desica = (DESICA *)malloc((N+1) * sizeof(DESICA))) == NULL)
			Ercalloc(N, dsn);
	}

	// 2-15) EVPCOOLING 気化冷却器
	// Satoh追加　2013/10/26
	N = NEVAC ;
	Eqcat->Evacca = NULL ;
	if (N > 0 )
	{
		if ((Eqcat->Evacca = (EVACCA *)malloc((N+1) * sizeof(EVACCA))) == NULL)
			Ercalloc(N, dsn);
	}


	//
	// 3) 圧縮式冷凍機定格特性を読み込む
	//

	// 3-1) 圧縮機特性リストファイルを開く
    if((frf = fopen("reflist.efl", "r")) == NULL)
		Eprint(" file ", "reflist.efl");

	// 3-2) メモリ確保と初期化
	N = RFCMPLSTMX ;
	Eqcat->Rfcmp = NULL ;
    if (N > 0 && (Eqcat->Rfcmp = (RFCMP *)malloc(N * sizeof(RFCMP))) == NULL)
	{
		Ercalloc(N, dsn);    
	}
	else
	{
		RFCMP	*Rf ;
		int		i, j ;
		Rf = Eqcat->Rfcmp ;
		for ( i = 0; i < N; i++, Rf++ )
		{
			Rf->cname = NULL ;
			for ( j = 0; j < 4; j++ )
				Rf->d[j] = Rf->e[j] = Rf->w[j] = 0.0 ;
			Rf->Meff = 0.0 ;
			Rf->name = NULL ;
			for ( j = 0; j < 2; j++ )
				Rf->Tco[j] = Rf->Teo[j] = 0. ;
		}
	}

	// 3-3) 圧縮式冷凍機定格特性を読み込む
	_Refcmpdat(frf, &Eqcat->Nrfcmp, Eqcat->Rfcmp);
    fclose (frf);


	//
	// 4) ポンプ・ファンの部分負荷特性の近似式係数の読み込み
	//

	// 4-1) ポンプ・ファンの部分負荷特性の近似式係数ファイルを開く
	if (( frf = fopen("pumpfanlst.efl", "r")) == NULL)
		Eprint(" file ", "pumpfanlst.efl") ;

	// 4-2) メモリ確保と初期化
	N = _pflistcount (frf) ;
	if (N > 0 && (Eqcat->pfcmp = (PFCMP *)calloc(N, sizeof(PFCMP))) == NULL)
		Ercalloc(N, dsn) ;
	PFcmpInit(N, Eqcat->pfcmp) ;

	// 4-3) ポンプ・ファンの部分負荷特性の近似式係数の読み込み
	PFcmpdata(frf, &Eqcat->Npfcmp, Eqcat->pfcmp) ;
	fclose (frf) ;


	//
	// 5) 機器カタログデータの読み込み
	//

	HCCCA* Hccca = Eqcat->Hccca;
	BOICA* Boica = Eqcat->Boica;
	COLLCA* Collca = Eqcat->Collca;
	REFACA* Refaca = Eqcat->Refaca;
	PIPECA* Pipeca = Eqcat->Pipeca;
	STANKCA* Stankca = Eqcat->Stankca;
	HEXCA* Hexca = Eqcat->Hexca;
	PUMPCA* Pumpca = Eqcat->Pumpca;
	VAVCA* vavca = Eqcat->Vavca;
	PVCA* PVca = Eqcat->PVca ;
	STHEATCA* stheatca = Eqcat->stheatca ;

	THEXCA* Thexca = Eqcat->Thexca ;

	OMVAVCA* OMvavca = Eqcat->OMvavca ;
    
	// Satoh追加 2013/10/20
	DESICA* Desica = Eqcat->Desica ;
    
	// Satoh追加 2013/10/26
	EVACCA* Evacca = Eqcat->Evacca ;

    sprintf (E, ERRFMT, dsn);
    
	//printf("3 %s\n", Room->trnx->nextroom->name) ;

    while (fscanf(f, "%s", s), s[0] != '*')
    {
		//printf("%s %s\n", s, Room->trnx->nextroom->name) ;

		// 5-1) HCC 冷温水コイル
		if (strcmp(s, HCCOIL_TYPE) == 0)
		{ 
			Hccca->name = NULL ;

			while (fscanf(f, "%s", s), s[0] != ';')
			{
				if ((ce=strchr(s,';')) != 0)
					*ce=  '\0';	     
				if (Hccdata(s, Hccca))
					printf ("%s %s\n", E, s);
				if (ce) break;
			}
			Hccca++;
		}

		// 5-2) BOI ボイラー
		else if (strcmp(s, BOILER_TYPE) == 0)
		{ 
			Boica->name = NULL ;

			while (fscanf(f, "%s", s), s[0] != ';')
			{
				if ((ce=strchr(s,';')) != 0)
					*ce=  '\0';
				if (Boidata(s, Boica))
					printf ("%s %s\n", E, s);
				if (ce) break;
			}
			Boica++;
		}

		// 5-4) COL,ACOL 太陽熱集熱器
		else if (strcmp(s, COLLECTOR_TYPE) == 0 || strcmp(s, ACOLLECTOR_TYPE) == 0)
		{ 
			Collca->name = NULL ;
			Collca->Fd = 0.9 ;

			while (fscanf(f, "%s", ss), ss[0] != ';')
			{
				if ((ce=strchr(ss,';')) != 0)
					*ce=  '\0';
				if (Colldata(s, ss, Collca))
					printf ("%s %s\n", E, s);
				if (ce) break;
			}
			Collca++;
		}

		// 5-5) PV 太陽電池
		else if (strcmp(s, PV_TYPE) == 0)
		{ 
			PVca->name = NULL ;

			while (fscanf(f, "%s", ss), ss[0] != ';')
			{
				if ((ce=strchr(ss,';')) != 0)
					*ce=  '\0';
				if (PVcadata(ss, PVca))
					printf ("%s %s\n", E, ss);
				if (ce) break;
			}
			PVca++;
		}

		// 5-3) REFA チラー、ヒートポンプチラー（空気熱源)
		else if (strcmp(s, REFACOMP_TYPE) == 0)
		{ 
			Refaca->name = NULL ;

			while (fscanf(f, "%s", s), s[0] != ';')
			{
				if ((ce=strchr(s,';')) != 0)
					*ce=  '\0';
				if (Refadata (s, Refaca, Eqcat->Nrfcmp, Eqcat->Rfcmp))
					printf ("%s %s\n", E, s);
				if (ce) break;
			}
			Refaca++;
		}

		// 5-6) PIPE,DUCT 配管とダクト
		else if (strcmp(s, PIPEDUCT_TYPE) == 0 ||
		          strcmp(s, DUCT_TYPE) == 0)
		{ 
			Pipeca->name = NULL ;
			
			while (fscanf(f, "%s", ss), ss[0] != ';')
			{
				if ((ce=strchr(ss,';')) != 0)
					*ce=  '\0';
				if (Pipedata (s, ss, Pipeca))
					printf ("%s %s\n", E, ss);
				if (ce) break;
			}
			Pipeca++;
		} 

		// 5-7) STANK 蓄熱層	
		else if (strcmp(s, STANK_TYPE) == 0)
		{ 
			Stankca->name = NULL ;

			while (fscanf(f, "%s", s), s[0] != ';')
			{
				if ((ce=strchr(s,';')) != 0)
					*ce=  '\0';
				if (Stankdata (f, s, Stankca))
					printf ("%s %s\n", E, s);
				if (ce) break;
			}
			Stankca++;
		}

		// 5-8) HEX 熱交換器(２流体式）
		else if (strcmp(s, HEXCHANGR_TYPE) == 0)
		{ 
			Hexca->name = NULL ;

			while (fscanf(f, "%s", s), s[0] != ';')
			{
				if ((ce=strchr(s,';')) != 0)
					*ce=  '\0';
				if (Hexdata (s, Hexca))
					printf ("%s %s\n", E, s);
				if (ce) break;
			}
			Hexca++;
		}

		// 5-9) PUMP,FAN ポンプ・ファン
		else if (strcmp(s, PUMP_TYPE) == 0 || strcmp(s, FAN_TYPE) == 0)
		{ 
			Pumpca->name = NULL ;
			Pumpca->type = NULL ;
			Pumpca->val = NULL ;
			Pumpca->pfcmp = NULL ;

			while (fscanf(f, "%s", ss), ss[0] != ';')
			{
				if ((ce=strchr(ss,';')) != 0)
					*ce=  '\0';
				if (Pumpdata (s, ss, Pumpca, Eqcat->Npfcmp, Eqcat->pfcmp))
					printf ("%s %s\n", E, ss);
				if (ce) break;
			}
			Pumpca++;
		}

		// 5-10) VAV,VWV VAVユニット
		/*---- Satoh Debug VAV  2000/10/30 ----*/
		else if (strcmp(s, VAV_TYPE) == 0 || strcmp(s, VWV_TYPE) == 0)
		{ 
			vavca->dTset = -999.0 ;
			vavca->name = NULL ;

			while (fscanf(f, "%s", ss), ss[0] != ';')
			{
				if ((ce=strchr(ss,';')) != 0)
					*ce=  '\0';

				if (VAVdata (s, ss, vavca))
					Eprint ("<Eqcadata> VAV", ss);

				if (ce) break;
			}
			vavca++;
		}

		// 5-13) ?????
		/*---- Satoh OMVAV  2010/12/16 ----*/
		else if (strcmp(s, OMVAV_TYPE) == 0 || strcmp(s, OAVAV_TYPE) == 0)
		{ 
			OMvavca->name = NULL ;
			//printf("3 %s\n", Room->trnx->nextroom->name) ;
			OMvavca->Gmax = -999.0 ;
			//printf("4 %s\n", Room->trnx->nextroom->name) ;
			OMvavca->Gmin = -999.0 ;

			//printf("5 %s\n", Room->trnx->nextroom->name) ;
			while (fscanf(f, "%s", ss), ss[0] != ';')
			{
				//printf("%s %s\n", ss, Room->trnx->nextroom->name) ;
				if ((ce=strchr(ss,';')) != 0)
					*ce=  '\0';

				if (OMVAVdata (ss, OMvavca))
					Eprint ("<Eqcadata> OMVAV", ss);

				if (ce) break;
			}
			OMvavca++;
		}

		// 5-11) STHEAT 電気蓄熱式暖房器
		/*---- Satoh Debug 電気蓄熱式暖房器 2001/1/20 ----*/
		else if (strcmp(s, STHEAT_TYPE) == 0 )
		{
			stheatca->name = NULL ;
			stheatca->pcmname = NULL;

			while (fscanf(f, "%s", s), s[0] != ';')
			{
				if ((ce = strchr(s, ';')) != 0)
					*ce = '\0' ;

				if (Stheatdata (s, stheatca))
					Eprint ( "<Eqcadata> STHEAT", s);

				if (ce) break ;
			}
			stheatca++ ;
		}

		// 5-12) THEX 全熱交換器
		/*---- Satoh Debug 全熱交換器 2001/8/22 ----*/
		else if (strcmp(s, THEX_TYPE) == 0)
		{
			Thexca->name = NULL ;
			Thexca->et = -999.0 ;
			Thexca->eh = -999.0 ;

			while ( fscanf ( f, "%s", s), *s != ';')
			{
				if (( ce = strchr(s, ';')) != 0)
					*ce = '\0' ;

				if ( Thexdata ( s, Thexca ))
					Eprint ( "<Eqcadata> THEX", s ) ;

				if ( ce )
					break ;
			}
			Thexca++ ;
		}

		// 5-14) DESICCANT バッチ式デシカント空調機
		/*---- Satoh追加 デシカント空調機 2013/10/20 ----*/
		else if (strcmp(s, DESI_TYPE) == 0 )
		{
			Desica->name = NULL ;

			while (fscanf(f, "%s", s), s[0] != ';')
			{
				if ((ce = strchr(s, ';')) != 0)
					*ce = '\0' ;

				if (Desiccantdata (s, Desica))
					Eprint ( "<Eqcadata> DESICCANT", s);

				if (ce) break ;
			}
			Desica++ ;
		}

		// 5-15) EVPCOOLING 気化冷却器
		/*---- Satoh追加 気化冷却器 2013/10/26 ----*/
		else if (strcmp(s, EVAC_TYPE) == 0 )
		{
			Evacca->name = NULL ;

			while (fscanf(f, "%s", s), s[0] != ';')
			{
				if ((ce = strchr(s, ';')) != 0)
					*ce = '\0' ;

				if (Evacdata (s, Evacca))
					Eprint ( "<Eqcadata> EVAC", s);

				if (ce) break ;
			}
			Evacca++ ;
		}
		else
			printf ("%s %s\n", E, s);
    }


	//
	// 6) 読み込んだ機種データの数を保存
	//

    Eqcat->Nhccca    = (int)(Hccca    - Eqcat->Hccca);		//1) HCC 冷温水コイル
    Eqcat->Nboica    = (int)(Boica    - Eqcat->Boica);		//2) BOI ボイラー
    Eqcat->Nrefaca   = (int)(Refaca   - Eqcat->Refaca);		//3) REFA チラー、ヒートポンプチラー（空気熱源)
    Eqcat->Ncollca   = (int)(Collca   - Eqcat->Collca);		//4) COL,ACOL 太陽熱集熱器
	Eqcat->Npvca     = (int)(PVca     - Eqcat->PVca);		//5) PV 太陽電池
    Eqcat->Npipeca   = (int)(Pipeca   - Eqcat->Pipeca);		//6) PIPE,DUCT 配管
    Eqcat->Nstankca  = (int)(Stankca  - Eqcat->Stankca);	//7) STANK 蓄熱層
    Eqcat->Nhexca    = (int)(Hexca    - Eqcat->Hexca);		//8) HEX 熱交換器(２流体式）
    Eqcat->Npumpca   = (int)(Pumpca   - Eqcat->Pumpca);		//9) PUMP,FAN ポンプ
	Eqcat->Nvavca    = (int)(vavca    - Eqcat->Vavca);		//10) VAV,VWV VAVユニット
	Eqcat->Nstheatca = (int)(stheatca - Eqcat->stheatca);	//11) STHEAT 電気蓄熱式暖房器
	Eqcat->Nthexca   = (int)(Thexca   - Eqcat->Thexca);		//12)THEX 全熱交換器
	Eqcat->Nomvavca  = (int)(OMvavca  - Eqcat->OMvavca);	//??????

	// Satoh追加　デシカント空調機　2013/10/20
	Eqcat->Ndesica   = (int)(Desica   - Eqcat->Desica);		//14) DESICCANT バッチ式デシカント空調機

	// Satoh追加　気化冷却器　2013/10/26
	Eqcat->Nevacca   = (int)(Evacca   - Eqcat->Evacca);		//15) EVPCOOLING 気化冷却器
}

/****************************************************************************/


/*
 * @brief 機器種別ごとの定義数を取得
 * @param[IN]  fi      読み込み元ファイルポインタ
 * @param[OUT] NBOI    BOI ボイラーの定義数
 * @param[OUT] NREFA   REFA チラー、ヒートポンプチラー（空気熱源)の定義数
 * @param[OUT] NCOL    COL,COLA 太陽熱集熱器の定義数
 * @param[OUT] NSTANK  STANK 蓄熱層の定義数
 * @param[OUT] NHCC    HCC 冷温水コイルの定義数
 * @param[OUT] NHEX    HEX 熱交換器(２流体式）の定義数
 * @param[OUT] NPIPE   PIPE,DUCT 配管の定義数
 * @param[OUT] NPUMP   PUMP,FAN ポンプの定義数
 * @param[OUT] NVAV    VAV,VWV VAVユニットの定義数
 * @param[OUT] NSTHEAT STHEAT 電気蓄熱式暖房器の定義数
 * @param[OUT] NTHEX   THEX 全熱交換器（換気の排気からの熱回収用の顕熱・潜熱熱交換器)の定義数
 * @param[OUT] NPV     PV 太陽電池の定義数
 * @param[OUT] NOMVAV  ????の定義数
 * @param[OUT] NDESI   DESICCANT バッチ式デシカント空調機の定義数
 * @param[OUT] NEVAC   EVPCOOLING 気化冷却器の定義数
 */
void _Eqpcount ( FILE *fi, int *NBOI, int *NREFA, int *NCOL, int *NSTANK, int *NHCC,
				  int *NHEX, int *NPIPE, int *NPUMP, int *NVAV, int *NSTHEAT, int *NTHEX, int *NPV, int *NOMVAV, int *NDESI, int *NEVAC )
{
	char	s[2048] ;
	long	ad ;

	ad = ftell ( fi ) ;		// 読み込み位置を覚えておく

	while ( fscanf ( fi, "%s", s ) !=EOF && *s != '*' )
	{
		if (strcmp(s, HCCOIL_TYPE) == 0)	// 機器仕様のキーワードが見つかったら個数をインクリメント
			(*NHCC)++;
		else if (strcmp(s, BOILER_TYPE) == 0)
			(*NBOI)++;
		else if (strcmp(s, COLLECTOR_TYPE) == 0 || strcmp(s, ACOLLECTOR_TYPE) == 0)
			(*NCOL)++;
		else if (strcmp(s, REFACOMP_TYPE) == 0)
			(*NREFA)++;
		else if (strcmp(s, PIPEDUCT_TYPE) == 0 ||
		          strcmp(s, DUCT_TYPE) == 0)
			(*NPIPE)++;
		else if (strcmp(s, STANK_TYPE) == 0)
			(*NSTANK)++;
		else if (strcmp(s, HEXCHANGR_TYPE) == 0)
			(*NHEX)++;
		else if (strcmp(s, PUMP_TYPE) == 0 || strcmp(s, FAN_TYPE) == 0)
			(*NPUMP)++;
		else if (strcmp(s, VAV_TYPE) == 0 || strcmp(s, VWV_TYPE) == 0)
			(*NVAV)++;
		else if (strcmp(s, STHEAT_TYPE) == 0 )
			(*NSTHEAT)++ ;
		else if (strcmp(s, THEX_TYPE) == 0 )
			(*NTHEX)++ ;
		else if (strcmp(s, PV_TYPE) == 0 )
			(*NPV)++ ;
		else if (strcmp(s, OMVAV_TYPE) == 0 || strcmp(s, OAVAV_TYPE) == 0 )
			(*NOMVAV)++ ;
		else if (strcmp(s, DESI_TYPE) == 0)
			(*NDESI)++ ;
		else if (strcmp(s, EVAC_TYPE) == 0)
			(*NEVAC)++ ;

		fscanf ( fi, "%*[^;] %*c" ) ;
	}

	fseek ( fi, ad, SEEK_SET ) ;	// 読み込み位置を元に戻す
}


/*
 * @brief ポンプ・ファンの部分負荷特性の近似式係数のデータ数を数える
 * @param[IN] fl ファイルポインタ
 * @return データ数
 */
int	_pflistcount ( FILE *fl )
{
	int		N = 0 ;
	char	s[SCHAR], c ;
	
	while ( fscanf ( fl, "%s", s ) != EOF, *s != '*' )
	{
		if ( strcmp(s,"!") == 0)
		{
			while ( fscanf ( fl,"%c", &c), c != '\n' )
				;
		}
		else if (strcmp(s, ";") == 0)
			N++ ;
	}
	
	rewind ( fl ) ;
	return ( N ) ;
}
