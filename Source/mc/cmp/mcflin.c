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


/* 境界条件・負荷仮想機器の要素機器データとしての入力処理 */

/*
 * @details
 * @see EESLISM7.2入力データ作成マニュアル.pdf P.57
 */
void flindat(FLIN *Flin)
{
	char s[SCHAR], *ss, *st;
	int  n = 0;
	char     Err[SCHAR];
	
	sprintf(Err, ERRFMT, "(flindat)");
	
	ss = Flin->cmp->tparm;
	while(sscanf(ss, "%s", s), strchr(s,'*') == NULL)
	{
		ss += strlen(s);
		while(isspace(*ss))
			ss++;
		
		if ((st = strchr(s, '=')) != NULL)
		{ 
			*st = '\0';
			if (strcmp(s, "t") == 0)
			{
				//変数名（温度、顕熱）
				Flin->namet = stralloc(st + 1);
				n++;
			}
			else if (strcmp(s, "x") == 0)
			{
				//変数名（湿度、潜熱）
				Flin->namex = stralloc(st + 1);
				n++;
			}
		}
		else
		{
			Eprint ( "<flindat>", s ) ;

			preexit ( ) ;
			exit(EXIT_FLIN);
		}
	}
	if (n == 1)
	{
		Flin->awtype = 'W';
		{
			Flin->cmp->idi = stralloc("W");
			Flin->cmp->ido = stralloc("W");
			Flin->cmp->airpathcpy = 'n'; 
		}
	}
	else
	{
		Flin->awtype = 'A';
		{
			Flin->cmp->idi = stralloc("tx");
			Flin->cmp->ido = stralloc("tx");
			Flin->cmp->airpathcpy = 'y'; 
		}
	}
	Flin->cmp->Nin = Flin->cmp->Nout = n;
	
	/***********
	printf("<<flindat>>  name=%s  t=%s  awtype=%c Nout=%d\n",
	Flin->cmp->name, Flin->namet,
	Flin->awtype, Flin->cmp->Nout);
	***************/
}
/* -------------------------------------------------- */	    

/* 境界条件・負荷仮想機器の要素機器データのポインター設定 */

void Flinint(int Nflin, FLIN *Flin, 
			 SIMCONTL *Simc, int Ncompnt, COMPNT *Compnt, WDAT *Wd)
{
	int i;
	
	for (i = 0; i < Nflin; i++, Flin++)
	{
	/***printf("<<Flinint>>  i=%d  namet=%s\n", i, Flin->namet);
		****/
		
		Flin->vart = envptr(Flin->namet, Simc, Ncompnt, Compnt, Wd, NULL);
		if (Flin->awtype == 'A')
			Flin->varx = envptr(Flin->namex, Simc, Ncompnt, Compnt, Wd, NULL);
	}
}


void	Flinprt ( int N, FLIN *Fl )
{
	FLIN	*F ;
	int		i ;

	F = Fl ;
	if ( DEBUG())
	{
		for ( i = 0; i < N; i++, F++)
		{
			printf("<< Flinprt >> Flin i=%d  %s %s = %.2g\n",
				i, F->name, F->namet, *F->vart);
		}
	}

	F = Fl ;
	if ( LOG_ENABLED )
	{
		for ( i = 0; i < N; i++, F++)
		{
			LOG_PRINT("<< Flinprt >> Flin i=%d  %s %s = %.2g\n",
				i, F->name, F->namet, *F->vart);
		}
	}

	LOG_PRINT("\n\n" ) ;
}
