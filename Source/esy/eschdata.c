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

/*   schdata.c  */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "esize.h"
#include "lib/u_sun.h"
#include "fesy.h"
#include "fnesy.h"
#include "fnlib.h"
#include "winerror.h"

/**
 * @file
 * @brief 
 */

/* 曜日の設定  */

void Dayweek(FILE *fi, char *Ipath, int *daywk, int key)
{
	char  s[SCHAR], *ce;
	int   ds, de, dd, d, id=0, M, D;
	FILE	 *fw ;
	
	if (( fw = fopen (strcat(strcpy(s, Ipath), "week.ewk"), "r" )) == 0 )
	{
		Eprint ( "<Dayweek>", "week.ewk" ) ;

		preexit ( ) ;
		exit (EXIT_WEEK) ;
	}
	
	if ( key == 0 )
		fscanf(fi, "%d/%d=%s", &M, &D, s);
	else
	{
		fscanf ( fi, "%*s" ) ;
		
		fscanf ( fw, "%d/%d=%s", &M, &D, s);
	}
	
	for ( d = 0; d < 8; d++ )
	{
		if ( strcmp ( s, DAYweek(d)) == 0 )
			id = d;
	}
	if ( id == 8 )
		Eprint ( "<Dayweek>", s ) ;
	
	ds = FNNday ( M, D ) ;
	de = ds + 365;
	
	for ( dd = ds; dd < de; dd++ )
	{
		d = ( dd > 365 ? dd - 365 : dd ) ;
		daywk[d] = id ;
		id++ ;

		if (id > 6 )
			id = 0;
	}
	while (fscanf(fi, "%s", s), s[0] != ';')
	{
		if ((ce=strchr(s, ';')) != 0)
			*ce = '\0';
		if (strchr(s,'/') != 0)
		{
			sscanf(s, "%d/%d", &M, &D);
			d = FNNday(M, D);
			daywk[d] = 7;
		}
		if (ce) break;
	}
	
	fclose ( fw ) ;
}

/* ------------------------------------------------------------ */


/*
 * @brief SCHTB スケジュール表の読み込み 
 * @details
 * 2.8 スケジュールデータ
 * (1) 一日の設定値、切換スケジュールおよび季節、曜日の指定
 */
void Schtable (FILE *fi, char *dsn, SCHDL *Schdl )
{ 
	char		s[SCHAR], *ce, code, E[SCHAR];
	static int	is = -1, js, iw = -1, j, sc = -1, jsc, sw = -1, jsw, Nmod = 0 ;
	int			Ms, Ds, Me, De, *wday ;
	int			ssn, wkd, vl, swn, N, i ;
	static int	ic = 0 ;
	int			ssnmx, vlmx, swmx ;
	SEASN		*Seasn, *Sn ;
	WKDY		*Wkdy, *Wk ;
	DSCH		*Dsch, *Dh ;
	DSCW		*Dscw, *Dw ;
	
	Seasn = Sn = NULL ;
	Wkdy = Wk = NULL ;
	Dsch = Dh = NULL ;
	Dscw = Dw = NULL ;

	sprintf (E, ERRFMT, dsn);


	//
	// 1) スケジュ－ル表のメモリ確保
	//

	if ( ic == 0 )
	{
		Schdl->Dsch = NULL ;
		Schdl->Dscw = NULL ;
		Schdl->Seasn = NULL ;
		Schdl->Wkdy = NULL ;

		SchCount ( fi, &ssn, &wkd, &vl, &swn, &ssnmx, &vlmx, &swmx ) ;
		ssn++ ;
		wkd++ ;
		vl++ ;
		swn++ ;
		ssnmx++ ;
		vlmx++ ;
		swmx++ ;

		N = imax(1,ssn) ;
		if (N > 0 && ( Schdl->Seasn = ( SEASN * ) malloc(N * sizeof(SEASN))) == NULL)
			Ercalloc(ssn, "<Schtable> Seasn" ) ;

		if ( Schdl->Seasn != NULL )
		{
			Seasn = Schdl->Seasn ;

			for ( i = 0; i < N; i++, Seasn++ )
			{
				Seasn->name = NULL ;
				Seasn->N = Seasn->end = 0 ;

				Seasn->sday = icalloc ( ssnmx, "<Schtable>  Seasn->sday  alloc" ) ;
				Seasn->eday = icalloc ( ssnmx, "<Schtable>  Seasn->eday  alloc" ) ;
			}
		}

		N = imax(1,wkd) ;
		if (N > 0 && ( Schdl->Wkdy = ( WKDY * ) malloc(N * sizeof(WKDY))) == NULL)
			Ercalloc(wkd, "<Schtable> Wkdy" ) ;

		if ( Schdl->Wkdy != NULL )
		{
			Wkdy = Schdl->Wkdy ;

			for ( i = 0; i < N; i++, Wkdy++ )
			{
				Wkdy->name = NULL ;
				Wkdy->end = 0 ;
				
				wday = Wkdy->wday ;
				for ( j = 0; j < 8; j++, wday++ )
					*wday = 0 ;
			}
		}

		N = imax(1,vl) ;
		if (N > 0 && ( Schdl->Dsch = ( DSCH * ) malloc(N * sizeof(DSCH))) == NULL)
			Ercalloc(vl, "<Schtable> Dsch" ) ;

		if ( Schdl->Dsch != NULL )
		{
			Dsch = Schdl->Dsch ;

			for ( i = 0; i < N; i++, Dsch++ )
			{
				Dsch->name = NULL ;
				Dsch->N = Dsch->end = 0 ;
				
				Dsch->stime = icalloc ( vlmx, "<Schtable>  Dsch->stime  alloc" ) ;
				Dsch->etime = icalloc ( vlmx, "<Schtable>  Dsch->etime  alloc" ) ;
				Dsch->val = dcalloc ( vlmx, "<Schtable>  Dsch->val  alloc" ) ;
			}
		}

		N = imax(1,swn) ;
		if (N > 0 && ( Schdl->Dscw = ( DSCW * ) malloc(N * sizeof(DSCW))) == NULL)
			Ercalloc(swn, "<Schtable> Dscw" ) ;

		if ( Schdl->Dscw != NULL )
		{
			Dscw = Schdl->Dscw ;

			for ( i = 0; i < N; i++, Dscw++ )
			{
				Dscw->name = NULL ;
				Dscw->N = Dscw->end = Dscw->Nmod = 0 ;
				
				Dscw->stime = icalloc ( swmx, "<Schtable>  Dsch->stime  alloc" ) ;
				Dscw->etime = icalloc ( swmx, "<Schtable>  Dsch->etime  alloc" ) ;
				Dscw->mode = scalloc ( swmx, "<Schtable>  Dsch->mode  alloc" ) ;
			}
		}
		ic = 1 ;
	}
	

	//
	// 2) スケジュ－ル表の読み込み
	//

	Seasn = Schdl->Seasn ;
	Wkdy = Schdl->Wkdy ;
	Dsch = Schdl->Dsch ;
	Dscw = Schdl->Dscw ;
	
	while (fscanf(fi,"%s", s), s[0] != '*')
	{  
		// 季節指定
		// `-ssn sname mm/dd-mm/dd mm/dd-mm/dd ･････ ;`
		// 季節名 月 日 月 日
		if (strcmp(s, "-ssn") == 0 || strcmp(s, "SSN") == 0)
		{
			while (fscanf(fi,"%s", s), s[0] != ';')
			{
				if ((ce=strchr(s,';')) != 0)
					*ce='\0';
				
				if (strchr(s,'-') == 0)
				{
					is++ ;
					Sn = Seasn + is ;
					Sn->name = stralloc( s);
					js= -1;
				}
				else
				{ 
					sscanf(s, "%d/%d-%d/%d", &Ms, &Ds, &Me, &De); 
					js++ ;
					Sn->sday[js] = FNNday(Ms, Ds);
					Sn->eday[js] = FNNday(Me, De);
				}
				if (ce) break;
			}
			Sn->N= js+1;
		}

		// 曜日指定
		// `-wkd wname wday wday wday ･････ wday ;`
		// ex) -wkd Weekday Mon Tue Wed Thu Fri ;
		else if (strcmp(s, "-wkd") == 0 || strcmp(s, "WKD") == 0)
		{
			j=9;
			while (fscanf(fi,"%s", s), s[0] != ';')
			{ 
				if ((ce=strchr(s,';')) != 0)
					*ce='\0';
				
				if (j == 9)
				{
					iw++ ;
					Wk = Wkdy + iw ;

					//曜日名
					Wk->name = stralloc( s);

					j = 0 ;
				} 
				else
				{
					wday = Wk->wday ;
					for (j = 0; j < 8; j++, wday++)
					{
						if (strcmp(s, DAYweek(j)) == 0)
						{
							*wday = 1;
							break;
						}
					}
				}
				if (ce) break;
			}
		}

		// 設定値（温・湿度、風量 ･････ ）スケジュール定義
		// `-v vdname ttmm-(xxx)-ttmm ttmm-(xxx)-ttmm ･････ ;`
		// 切換設定名 切換値
		else if (strcmp(s, "-v") == 0 || strcmp(s, "VL") == 0)
		{
			while (fscanf(fi,"%s", s), s[0] != ';')
			{
				if ((ce=strchr(s,';')) != 0)
					*ce='\0';
				
				if (strchr(s,'(') == 0)
				{
					sc++ ;
					Dh = Dsch + sc ;
					Dh->name = stralloc ( s);
					/****************************
					printf ("<Schtable> [%d]name=%s\n"
						, sc, (Dsch+sc)->name) ;
						***********************/
					jsc = -1 ;
				}
				else
				{
					jsc++;
					
//					if ( jsc > SCDAYTMMAX )
//						printf ("<Schtable> Name=%s  MAX=%d  jsc=%d\n",
//						Dh->name, SCDAYTMMAX, jsc) ;

					sscanf(s,"%d-(%lf)-%d", &Dh->stime[jsc], &Dh->val[jsc], &Dh->etime[jsc] ) ;
				}
				if (ce) break;
			} 
			Dh->N = ++jsc ;
		}

		// 切換設定スケジュール定義
		// `-s wdname ttmm-(mode)-ttmm ttmm-(mode)-ttmm ･････ ;`
		// 設定値名 時分 設定値 時分
		else if (strcmp(s, "-s") == 0 || strcmp(s, "SW") == 0)
		{ 
			Nmod = 0;
			fscanf(fi, " %s ", s);

			sw++ ;
			Dw = Dscw + sw ;

			//設定値名
			Dw->name = stralloc ( s);

			jsw= -1; 
			
			while (fscanf(fi,"%s", s), s[0] != ';')
			{ 
				if ((ce=strchr(s,';')) != 0)
					*ce='\0';
				
				jsw++;

				//時分-設定値-時分
				sscanf(s,"%d-(%c)-%d", &Dw->stime[jsw], &code, &Dw->etime[jsw]);
				Dw->mode[jsw] = code ;
				
				//設定値の重複を除外して保持
				for ( j = 0; j < Nmod; j++)
				{
					if ( Dw->dcode[j] == code )
						break;
				}
				
				if ( j == Nmod )
				{
					Dw->dcode[Nmod] = code ;
					Nmod++ ;  
				}
				
				if (ce) break;
			}
			Dw->N = ++jsw ;
			Dw->Nmod = Nmod ;
		}
	}

	//季節設定の数の保存
	Schdl->Seasn->end = is + 1 ;

	//曜日設定の数の保存
	Schdl->Wkdy->end= iw + 1 ;

	//設定値（温・湿度、風量 ･････ ）スケジュール定義の数の保存
	Schdl->Dsch->end= sc + 1 ;

	//切換設定スケジュール定義の数の保存
	Schdl->Dscw->end= sw + 1 ;
}


/*
 * @brief SCHNM 季節、曜日によるスケジュ－ル表の組み合わせ
 * @details
 * 2.8 スケジュールデータ
 * （２）日スケジュールの季節、曜日による変更の定義
 */
void Schdata (FILE *fi, char *dsn, int *daywk, SCHDL *Schdl )
{
	char	s[SCHAR], ss[SCHAR], dmod, *ce, sname[SCHAR],wname[SCHAR],dname[SCHAR];
	char	err[SCHAR], E[SCHAR] ; 
	int		i, j, k, N, d, ds, de, day, is, iw, sc, sw ;
	int		dmax = 366, *day1 ;
//	int		sws, vl ;
	static int	ic = 0 ;
	SEASN	*Seasn, *Sn ;
	WKDY	*Wkdy ;
	DSCH	*Dsch ;
	DSCW	*Dscw ;
	SCH		*Sch, *Scw, *S ;
	
	Seasn = Schdl->Seasn ;
	Wkdy = Schdl->Wkdy ;
	Dsch = Schdl->Dsch ;
	Dscw = Schdl->Dscw ;
	Sch	= Schdl->Sch ;
	Scw = Schdl->Scw ;

//	SchCount ( fi, &i, &i, &vl, &sws ) ;

	sprintf (E, ERRFMT, dsn);
	i = Sch->end - 1;
	j = Scw->end - 1;
	
	while (fscanf(fi,"%s", s), s[0] != '*')
	{   
		if (strcmp(s, "-v") == 0 || strcmp(s, "VL") == 0)
		{
			dmod = 'v';
		}
		else
		{
			dmod = 'w';
		}
		
		fscanf(fi,"%s", s);
		
		if (dmod == 'v')
		{
			i++ ;
			S = Sch + i ;

			//設定名
			S->name = stralloc( s);

			day1 = S->day ;
			for (d = 0; d < dmax; d++, day1++)
			{
				*day1 = -1;
			}
		}
		else 
		{
			j++ ;
			S = Scw + j ;

			//切替設定名
			S->name = stralloc( s);

			day1 = S->day ;
			for (d = 0; d < dmax; d++, day1++)
			{
				*day1 = -1;
			}
		}
		
		while (fscanf(fi,"%s", s),  *s != ';')
		{
			if (( ce = strchr ( s, ';' )) != 0 )
				*ce = '\0' ;  
			*sname = *wname = '\0' ;
			is = iw = sc = sw = -1 ;
			
			sscanf ( s, "%[^:]:%s", dname, ss);
			if (strchr(ss, '-') == 0)
			{
				sscanf(ss, "%s", sname);
			}
			else
			{
				if (*ss == '-')
				{
					sscanf(&ss[1], "%s", wname);
				}
				else
				{
					sscanf(ss, "%[^-]-%s", sname, wname);
				}
			}
			
			/************************ 
			if ((st=strchr(s,'-')) == s)
			sscanf(s, "-%[^-]-%s", wname, dname);
			else if (*(st+1) == '-')
			sscanf(s, "%[^-]--%s", sname, dname);
			else 
			sscanf(s, "%[^-]-%[^-]-%s", sname, wname, dname);
			*****************/
			/*******************
			printf("-- dname:s,w,= %s  %s  %s\n",dname,sname,wname);
			********************/
			
			if (sname[0] != '\0')
			{
				//季節名から季節設定のインデックスを検索
				is = idssn(sname, Seasn, strcat(strcpy(err, E), sname));
			}

			if (wname[0] != '\0')
			{
				//曜日名から曜日設定のインデックスを検索
				iw = idwkd(wname, Wkdy, strcat(strcpy(err, E), wname));
			}

			if (dname[0] != '\0')
			{
				if (dmod == 'v')
				{
					//設定値名から設定値スケジュール定義のインデックスを検索
					sc = iddsc(dname, Dsch, strcat(strcpy(err, E), dname));
				}
				else
				{
					//切替設定名から切替設定スケジュール定義のインデックスを検索
					sw = iddsw(dname, Dscw, strcat(strcpy(err, E), dname));
				}
			}

			if (is >= 0)
			{
				N = (Seasn + is)->N;
			}
			else
			{
				N = 1;
			}

			for ( k = 0; k < N; k++ )
			{ 
				if (is >= 0)
				{
					Sn = Seasn + is ;
					ds = Sn->sday[k] ;
					de = Sn->eday[k] ;

					if ( ds > de )
						de += 365 ;
				}
				else
					ds = 1, de = dmax ;
				
				for ( day = ds; day <= de; day++ )
				{ 
					d = (day > 365 ? day-365 : day) ;

					if (iw < 0 || (Wkdy+iw)->wday[daywk[d]] == 1)
					{
						if (dmod == 'v')
							S->day[d] = sc ;
						else
							S->day[d] = sw ;
					}
				}
			}
			if (ce) break;
		}
	}
	
	// 設定値の年間スケジュールの数を保存
	Schdl->Sch->end = i + 1 ;
	
	// 切替設定の年間スケジュールの数を保存
	Schdl->Scw->end = j + 1 ;
}

/* ------------------------------------------------------------ */

/*  季節、曜日によるスケジュ－ル表の組み合わせ名へのスケジュ－ル名の追加  */


void Schname (char *Ipath, char *dsn, SCHDL *Schdl )
{
	int		sc, sw, d,  i,  j, N ;
	static int	ind=0, sco= 0, swo= 0;
	char	E[SCHAR], s[SCHAR]; 
	const int dmax = 366;
	int		*day ;
	int		vl, sws ;
	SCH		*Sch, *Scw ;
	DSCH	*Dsch ;
	DSCW	*Dscw ;
	FILE	*fi ;
	int		ssnmx, vlmx, swmx ;

	if (( fi = fopen (strcat(strcpy(s, Ipath), "schnma.ewk"), "r" )) == 0 )
	{
		Eprint ( "<Schname>", "schnma.ewk" ) ;

		preexit ( ) ;
		exit(EXIT_SCHTB);
	}


	//
	// 1) スケジュール用にメモリを確保、初期化
	//

	SchCount ( fi, &i, &j, &vl, &sws, &ssnmx, &vlmx, &swmx ) ;
	/*****************/
	vl++ ;
	sws++ ;
	ssnmx++ ;
	vlmx++ ;
	swmx++ ;
	/***********************/

	fclose ( fi ) ;

	Dsch = Schdl->Dsch ;
	Dscw = Schdl->Dscw ;

	if (ind == 0)
	{
		Schdl->Sch = NULL ;
		Schdl->Scw = NULL ;

		// 1-1) 切換設定の年間スケジュール

		//メモリ確保
		N = imax (Dsch->end + vl,1) ;
		Schdl->Sch = ( SCH * ) malloc ( N * sizeof(SCH)) ;
		if ( Schdl->Sch == NULL )
			Ercalloc(N, "<Schname> Sch" ) ;
		Sch = Schdl->Sch ;

		//初期化
		for ( i = 0; i < N; i++, Sch++ )
		{
			Sch->name = NULL ;
			Sch->end = 0 ;
			day = Sch->day ;
			for (j = 0; j < 366; j++, day++)
			{
				*day = 0;
			}
		}

		// 1-2) 切換設定の年間スケジュール

		//メモリ確保
		N = imax ( Dscw->end + sws, 1) ;
		if (( Schdl->Scw = ( SCH * ) malloc( N * sizeof(SCH))) == NULL)
			Ercalloc(N, "<Schname> Scw" ) ;
		Scw = Schdl->Scw ;
		
		//初期化
		for (i=0; i<N; i++, Scw++)
		{
			Scw->name = NULL ;
			Scw->end = 0 ;
			day = Scw->day ;
			for (j = 0; j < 366; j++, day++)
			{
				*day = 0;
			}
		}

		ind=1;
	}


	//
	// 2) 
	//

	// 2-1) 設定値の年間スケジュール

	i = Schdl->Sch->end ;

	N = Dsch->end ;
	Sch = Schdl->Sch + i ;

	sprintf (E, ERRFMT, dsn);

	for ( sc = sco; sc < N; sc++, Sch++ )
	{
		i++ ;

		//スケジュール名(設定値名)
		Sch->name = stralloc ( (Dsch+sc)->name ) ;


		day = Sch->day ;
		for (d = 0; d < dmax; d++, day++)
		{
			*day = sc;
		}
	}
	sco = sc ;
	Schdl->Sch->end = i ;	

	// 2-2) 切換設定の年間スケジュール

	j = Schdl->Scw->end ;
	Scw = Schdl->Scw + j ;
	N = Dscw->end ;
	for ( sw = swo; sw < N; sw++, Scw++ )
	{
		j++ ;

		//スケジュール名(切替設定名)
		Scw->name = stralloc ( (Dscw+sw)->name );

		day = Scw->day ;
		for (d = 0; d < dmax; d++, day++)
		{
			*day = sw;
		}
	}
	swo=sw;
	Schdl->Scw->end = j;
}

/****  スケジュールの数を数える  ****/

void	SchCount ( FILE *fi, int *ssn, int *wkd, int *vl, int *sw,
				  int *ssnmx, int *vlmx, int *swmx )
{
	char	s[SCHAR] ;
	long	a ;
	int		i ;

	*ssnmx = *vlmx = *swmx = 0 ;

	a = ftell ( fi ) ;

	if ( a != 0L )
		rewind ( fi ) ;

	*ssn = *wkd = *vl = *sw = 0 ;

	while ( fscanf ( fi, "%s", s ), *s != '*' )
	{
		if ( strcmp ( s, "-ssn" ) == 0 || strcmp ( s, "SSN" ) == 0 )
		{
			(*ssn)++ ;
			i = Schcmpcount ( fi ) ;
			*ssnmx = imax ( i, *ssnmx ) ;
		}
		else if ( strcmp ( s, "-wkd" ) == 0 || strcmp ( s, "WKD" ) == 0 )
			(*wkd)++ ;
		else if ( strcmp ( s, "-v" ) == 0 || strcmp ( s, "VL" ) == 0 )
		{
			(*vl)++ ;
			i = Schcmpcount ( fi ) ;
			*vlmx = imax ( i, *vlmx ) ;
		}
		else if ( strcmp ( s, "-s" ) == 0 || strcmp ( s, "SW" ) == 0 )
		{
			(*sw)++ ;
			i = Schcmpcount ( fi ) ;
			*swmx = imax ( i, *swmx ) ;
		}
	}

	rewind ( fi ) ;
}

/***************************************************************************/

int		Schcmpcount ( FILE *fi )
{
	int		N ;
	char	s[SCHAR] ;
	
	N = 0 ;
	while ( fscanf ( fi, "%s", s ) != EOF )
	{
		if ( *s == ';' )
			break ;
		N++ ;
	}

	return ( N -1 ) ;
}
