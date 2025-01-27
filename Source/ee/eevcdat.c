﻿//This file is part of EESLISM.
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

/* eevcdat.c */

#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <stdlib.h>
#include "common.h"
#include "fesy.h"
#include "fnesy.h"
#include "fnfio.h"
#include "fnlib.h"
#include "winerror.h"

/**
 * @file
 * @brief 境界条件・負荷仮想機器の要素機器データ入力ファイル設定
 */

void Vcfdata(FILE *fi, SIMCONTL *Simcon)
{
	VCFILE  *Vcfile, *V;
	TLIST	*T ;
	int		i, N, j ;
	char     s[SCHAR], Err[SCHAR], E[SCHAR*3+128];
	
	sprintf(Err, ERRFMT, "(vcfileint)");
	
	//N = VCFILEMAX ;
	N = VCFcount ( fi ) ;
	if (N > 0 )
	{
		if ((Simcon->Vcfile = (VCFILE *)malloc(N * sizeof(VCFILE))) == NULL)
			Ercalloc(N, Err); 

		V = Simcon->Vcfile ;
		for ( i = 0; i < N; i++, V++ )
		{
			V->name = V->fname = NULL ;
			V->ad = -999L ;
			V->ic = 0 ;
			V->Tlist = NULL ;
			V->fi = NULL ;
			V->Estl.flid = V->Estl.title = V->Estl.wdatfile = NULL ;
			V->Estl.timeid = V->Estl.wdloc = NULL ;
			V->Estl.catnm = NULL ;
			V->Estl.ntimeid = V->Estl.Ntime = V->Estl.dtm = 0 ;
			V->Estl.Nunit = V->Estl.Nrqlist = V->Estl.Nvreq = 0 ;
			V->Estl.Npreq = V->Estl.Npprd = V->Estl.Ndata = 0 ;
			V->Estl.Rq = NULL ;
			V->Estl.Prq = NULL ;
			strcpy ( V->Estl.vreq, "" ) ;

			for ( j = 0; j < VTYPEMAX; j++ )
				V->Estl.unit[j] = NULL ;
		}
	}

	Vcfile = Simcon->Vcfile;
	while (fscanf(fi, "%s", s), *s != '*')
	{
		Vcfile->name = stralloc(s);
		while (fscanf(fi, "%s", s), *s != ';')
		{
			if (strcmp(s, "-f") == 0)
			{
				fscanf(fi, "%s", s);
				Vcfile->fname = stralloc(s);
			}
			else
			{
				sprintf ( E, "Vcfile=%s  %s %s", Vcfile->name, Err, s);
				Eprint ( "<Vcfdata>", E ) ;
			}
		}
		Vcfile++;
	}
	
	Simcon->Nvcfile = (int)(Vcfile - Simcon->Vcfile);
	Vcfile = Simcon->Vcfile;
	
	/****printf("<<Vcfdata>> Nvcfile=%d\n", Simcon->Nvcfile);
	********/
	
	for (i = 0; i < Simcon->Nvcfile; i++, Vcfile++)
	{
		if((Vcfile->fi = fopen(Vcfile->fname, "r")) == 0)
		{
			Eprint ( "<Vcfdata>", Vcfile->fname ) ;

			preexit ( ) ;
			exit(EXIT_VCFILE);
		}
		
		//printf("<<Vcfdata>> i=%d\n", i);
		
		esondat(Vcfile->fi, &Vcfile->Estl);
		
		N = Vcfile->Estl.Ndata ;
		if (N > 0 && (Vcfile->Tlist = (TLIST *)malloc(N * sizeof(TLIST))) == NULL)
			Ercalloc(Vcfile->Estl.Ndata, Err); 
		
		if ( Vcfile->Tlist != NULL )
		{
			T = Vcfile->Tlist ;

			for ( j = 0; j < N; j++, T++ )
			{
				T->cname = T->name = T->id = T->unit = NULL ;
				T->fval = T->fstat = NULL ;
				T->ival = T->istat = NULL ;
				T->cval = T->cstat = T->fmt = NULL ;
				T->pair = NULL ;
			}
		}

		/******printf("<<Vcfdata>> esoint i=%d\n", i);****/
		
		esoint(Vcfile->fi, "esoint", 1, &Vcfile->Estl, Vcfile->Tlist);
		Vcfile->ad = ftell ( Vcfile->fi ) ;
		
		/****printf("<Vcfdata>> wdtype=%c\n", Simcon->wdtype);****/
		
		if (Simcon->wdtype == 'E')
		{
			Simcon->wfname = stralloc ( Vcfile->fname ) ;
			wdflinit(Simcon, &Vcfile->Estl, Vcfile->Tlist);
		}
		/****printf("<< Vcfdata>> wfname=%s\n", Simcon->wfname);****/      
		/**** printf("<<Vcfdata>> i=%d\n", i);****/
	}
}

/***** VCFILEの定義数を数える ******/

int	VCFcount ( FILE *fi )
{
	int		N = 0 ;
	long	ad ;
	char	s[SCHAR] ;

	ad = ftell ( fi ) ;

	while ( fscanf ( fi, " %s ", s ), s[0] != '*' )
	{
		if ( strcmp ( s, "-f" ) == 0 )
			N++ ;
	}

	fseek ( fi, ad, SEEK_SET ) ;
	return ( N ) ;
}


/* 境界条件・負荷仮想機器のファイル入力データのポインター */

int vcfptr(char **key, SIMCONTL *Simc, VPTR *vptr)
{
	VCFILE *Vcfile;   
	int j, k, Ndata, err = 1;
	TLIST *Tlist;
	
	Vcfile = Simc->Vcfile;
	
	/***********  
	for (j = 0; j < 3; j++)
	printf("<<vcfptr>> j=%d key=%s\n", j, key[j]);
	**********/
	
	for (j = 0; j < Simc->Nvcfile; j++, Vcfile++)
	{
	/**** printf("<<vcfptr>> ============= key[0]=%s  Vcfile=%s\n",
		key[0], Vcfile->name);****/
		
		if (strcmp(key[0], Vcfile->name) == 0)
		{
			Ndata = Vcfile->Estl.Ndata;
			Tlist = Vcfile->Tlist;
			for (k = 0; k < Ndata; k++, Tlist++)
			{
				if (strcmp(key[1], Tlist->name) == 0 &&
					strcmp(key[2], Tlist->id) == 0)
				{
				/*** printf("<<vcfptr>> ================== %s %s\n",
					Tlist->name, Tlist->id);****/
					
					vptr->ptr = Tlist->fval;
					vptr->type = VAL_CTYPE;
					err = 0;
					break;
				}
			}
			
		}
	}
	return err;
}

/* -------------------------------------------------- */	    

/* 境界条件・負荷仮想機器のデータファイル入力 */

void Vcfinput(DAYTM *Daytm, int Nvcfile, VCFILE *Vcfile, char perio)
{
	static int Mon, Day, Time;
	TMDT	Tmdt;
	int		i, idend=0, iderr=0;
	char	E[SCHAR] ;
	
	TMDTinit ( &Tmdt ) ;

	for (i = 0; i < Nvcfile; i++, Vcfile++)
	{
		iderr = 0;
		if (Vcfile->Estl.tid == 'M' && Mon != Daytm->Mon)
		{
			idend = tmdata(Vcfile, &Tmdt, Daytm, perio) ;
			if ( idend )
			{
				if (Daytm->Mon == Tmdt.Mon)
					esdatgt(Vcfile->fi, 0, Vcfile->Estl.Ndata, Vcfile->Tlist);
				else
					iderr = 1;
			}
		}
		else if (Vcfile->Estl.tid == 'd' && Day != Daytm->Day)
		{
			idend = tmdata(Vcfile, &Tmdt, Daytm, perio) ;
			if ( idend )
			{
				if (Daytm->Day == Tmdt.Day)
					esdatgt(Vcfile->fi, 0, Vcfile->Estl.Ndata, Vcfile->Tlist);
				else
					iderr = 1;
			}
		}
		else if (Vcfile->Estl.tid == 'h' && Time != Daytm->ttmm)
		{
			idend = tmdata(Vcfile, &Tmdt, Daytm, perio) ;
			if ( idend )
			{
				
			/*** printf("<<Vcfinput>> Daytm=%d  Tmdt=%d\n", Daytm->ttmm,Tmdt.Time);
				*****/
				
				
				if (Daytm->Mon == Tmdt.Mon && Daytm->Day == Tmdt.Day
					&& Daytm->ttmm == Tmdt.Time)
					esdatgt(Vcfile->fi, 0, Vcfile->Estl.Ndata, Vcfile->Tlist);
				else
					iderr = 1;
			}
		}
		if ( idend == 0 )
		{
			sprintf(E, "Vcfinput file-end: %s\n", Vcfile->fname);

			Eprint ( "<Vcfinput>", E );
		}
		
		if ( iderr )
		{
			sprintf(E,"Vcfinput xxx file=%s prog_MM/DD/TM=%d/%d/%d file_MM/DD/TM=%d/%d/%d\n",
				Vcfile->fname, Daytm->Mon, Daytm->Day, Daytm->ttmm,
				Tmdt.Mon, Tmdt.Day, Tmdt.Time);
			
			Eprint ( "<Vcfinput>", E ) ;
		}
	}
	Mon = Daytm->Mon;
	Day = Daytm->Day;
	Time = Daytm->ttmm;
}
