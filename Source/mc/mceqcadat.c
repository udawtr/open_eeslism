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

/* ----------------------------------------- */

/*  機器仕様入力       */

void Eqcadata (FILE *f, char *dsn, EQCAT *Eqcat)	      
{
    char	s[SCHAR], ss[SCHAR], *ce, E[SCHAR];
	int		N ;
	int		NBOI, NREFA, NCOL, NSTANK, NHCC, NHEX, NPIPE, NPUMP, NVAV, NSTHEAT, NTHEX, NPV, NDESI, NEVAC ;
	int		NOMVAV ;
    HCCCA	*Hccca;
    BOICA	*Boica;
    COLLCA	*Collca;
    REFACA  *Refaca;
    PIPECA  *Pipeca;
    STANKCA *Stankca;
    HEXCA	*Hexca;
    PUMPCA	*Pumpca;
	VAVCA	*vavca ;
	STHEATCA  *stheatca ;
	THEXCA	*Thexca ;
	PVCA	*PVca ;
	OMVAVCA	*OMvavca ;
	DESICA	*Desica ;
	EVACCA	*Evacca ;
    
    FILE *frf;

	//
	// 1) 機種ごとの定義数を確認
	//
    
	NBOI = NREFA = NCOL = NSTANK = NHCC = NHEX
		= NPIPE = NPUMP = NVAV = NSTHEAT = NTHEX = NPV = NOMVAV = NDESI = NEVAC = 0 ;

	//printf("1 %s\n", Room->trnx->nextroom->name) ;

	//機器種別ごとの仕様定義数を取得
	Eqpcount ( f, 
		&NBOI,		//ボイラー
		&NREFA,		//チラー、ヒートポンプチラー（空気熱源)
		&NCOL,		//太陽熱集熱器
		&NSTANK,	//蓄熱層
		&NHCC,		//冷温水コイル
		&NHEX,		//熱交換器(２流体式）
		&NPIPE,		//配管
		&NPUMP,		//ポンプ
		&NVAV,		//VAV ユニット
		&NSTHEAT,	//電気蓄熱式暖房器
		&NTHEX,		//全熱交換器
		&NPV,		//太陽電池
		&NOMVAV,	//??
		&NDESI,		//バッチ式デシカント空調機
		&NEVAC		//気化冷却器
	);


	//
	// 2) 機種ごとにメモリを確保
	//

	//printf("2 %s\n", Room->trnx->nextroom->name) ;

	// 2-1) 冷温水コイル
	N = NHCC ;
	Eqcat->Hccca = NULL ;
    if (N > 0 )
	{
		if ((Eqcat->Hccca = (HCCCA *)malloc(N * sizeof(HCCCA))) == NULL)
			Ercalloc(N, dsn);
	}

	// 2-2) ボイラー
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

	// 2-4) 太陽熱集熱器
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

	// 2-6) 配管
	N = NPIPE ;
	Eqcat->Pipeca = NULL ;
    if (N > 0 )
	{
		if ((Eqcat->Pipeca = (PIPECA *)malloc(N * sizeof(PIPECA))) == NULL)
			Ercalloc(N, dsn);
	}

	// 2-7) 蓄熱層
	N = NSTANK ;
	Eqcat->Stankca = NULL ;
    if (N > 0 )
	{
		if ((Eqcat->Stankca = (STANKCA *)malloc(N * sizeof(STANKCA))) == NULL)
			Ercalloc(N, dsn);
	}

	// 2-8) 熱交換器(２流体式）
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

	// 2-11) 電気蓄熱式暖房器
	N = NSTHEAT ;
	Eqcat->stheatca = NULL ;
	if (N > 0 )
	{
		if ((Eqcat->stheatca = (STHEATCA *)malloc(N * sizeof(STHEATCA))) == NULL)
			Ercalloc(N, dsn);
    }

	// 2-12) 全熱交換器
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

	// 2-14) バッチ式デシカント空調機
	// Satoh追加　2013/10/20
	N = NDESI ;
	Eqcat->Desica = NULL ;
	if (N > 0 )
	{
		if ((Eqcat->Desica = (DESICA *)malloc((N+1) * sizeof(DESICA))) == NULL)
			Ercalloc(N, dsn);
	}

	// 2-15) 気化冷却器
	// Satoh追加　2013/10/26
	N = NEVAC ;
	Eqcat->Evacca = NULL ;
	if (N > 0 )
	{
		if ((Eqcat->Evacca = (EVACCA *)malloc((N+1) * sizeof(EVACCA))) == NULL)
			Ercalloc(N, dsn);
	}

    if((frf = fopen("reflist.efl", "r")) == NULL)
		Eprint(" file ", "reflist.efl");

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

    Refcmpdat(frf, &Eqcat->Nrfcmp, Eqcat->Rfcmp);
    fclose (frf);

	if (( frf = fopen("pumpfanlst.efl", "r")) == NULL)
		Eprint(" file ", "pumpfanlst.efl") ;
	N = pflistcount (frf) ;
	if (N > 0 && (Eqcat->pfcmp = (PFCMP *)calloc(N, sizeof(PFCMP))) == NULL)
		Ercalloc(N, dsn) ;
	PFcmpInit(N, Eqcat->pfcmp) ;
	PFcmpdata(frf, &Eqcat->Npfcmp, Eqcat->pfcmp) ;
	fclose (frf) ;
    
    Hccca = Eqcat->Hccca;
    Boica = Eqcat->Boica;
    Collca = Eqcat->Collca;
    Refaca = Eqcat->Refaca;
    Pipeca = Eqcat->Pipeca;
    Stankca = Eqcat->Stankca;
    Hexca = Eqcat->Hexca;
    Pumpca = Eqcat->Pumpca;
	vavca = Eqcat->Vavca;
	PVca = Eqcat->PVca ;
	stheatca = Eqcat->stheatca ;

	Thexca = Eqcat->Thexca ;

	OMvavca = Eqcat->OMvavca ;
    
	// Satoh追加 2013/10/20
	Desica = Eqcat->Desica ;
    
	// Satoh追加 2013/10/26
	Evacca = Eqcat->Evacca ;

    sprintf (E, ERRFMT, dsn);
    
	//printf("3 %s\n", Room->trnx->nextroom->name) ;

    while (fscanf(f, "%s", s), s[0] != '*')
    {
		//printf("%s %s\n", s, Room->trnx->nextroom->name) ;

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
    Eqcat->Nhccca = (int)(Hccca - Eqcat->Hccca);
    Eqcat->Nboica = (int)(Boica - Eqcat->Boica);
    Eqcat->Ncollca = (int)(Collca - Eqcat->Collca);
    Eqcat->Nrefaca = (int)(Refaca - Eqcat->Refaca);
    Eqcat->Npipeca = (int)(Pipeca - Eqcat->Pipeca);
    Eqcat->Nstankca = (int)(Stankca - Eqcat->Stankca);
    Eqcat->Nhexca = (int)(Hexca - Eqcat->Hexca);
    Eqcat->Npumpca = (int)(Pumpca - Eqcat->Pumpca);
	Eqcat->Nvavca = (int)(vavca - Eqcat->Vavca) ;
	Eqcat->Nstheatca = (int)(stheatca - Eqcat->stheatca) ;
	Eqcat->Nthexca = (int)(Thexca - Eqcat->Thexca) ;
	Eqcat->Npvca = (int)(PVca - Eqcat->PVca) ;
	Eqcat->Nomvavca = (int)(OMvavca - Eqcat->OMvavca) ;

	// Satoh追加　デシカント空調機　2013/10/20
	Eqcat->Ndesica = (int)(Desica - Eqcat->Desica) ;

	// Satoh追加　気化冷却器　2013/10/26
	Eqcat->Nevacca = (int)(Evacca - Eqcat->Evacca) ;
}

/****************************************************************************/

/*
 * @brief 機器種別ごとの定義数を取得
 * @param[IN]  fi      読み込み元ファイルポインタ
 * @param[OUT] NBOI    ボイラーの定義数
 * @param[OUT] NREFA   チラー、ヒートポンプチラー（空気熱源)の定義数
 * @param[OUT] NCOL    太陽熱集熱器の定義数
 * @param[OUT] NSTANK  蓄熱層の定義数
 * @param[OUT] NHCC    冷温水コイルの定義数
 * @param[OUT] NHEX    熱交換器(２流体式）の定義数
 * @param[OUT] NPIPE   配管の定義数
 * @param[OUT] NPUMP   ポンプの定義数
 * @param[OUT] NVAV    VAV ユニットの定義数
 * @param[OUT] NSTHEAT 電気蓄熱式暖房器の定義数
 * @param[OUT] NTHEX   全熱交換器（換気の排気からの熱回収用の顕熱・潜熱熱交換器)の定義数
 * @param[OUT] NPV     太陽電池の定義数
 * @param[OUT] NOMVAV  ????の定義数
 * @param[OUT] NDESI   バッチ式デシカント空調機の定義数
 * @param[OUT] NEVAC   気化冷却器の定義数
 */
void	Eqpcount ( FILE *fi, int *NBOI, int *NREFA, int *NCOL, int *NSTANK, int *NHCC,
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

int	pflistcount ( FILE *fl )
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
