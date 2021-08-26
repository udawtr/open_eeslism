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

/*  eesfiles.c  */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "fesy.h"
#include "fnfio.h"
#include "winerror.h"
#include "winerror.h"
#include "fnlib.h"

/**
 * @file
 * @brief ファイルポインタの管理
 */


/* ----------------------------------------------------- */

/**
 * @brief ファイルを開く
 * @details
 * 読み／書きする全てのファイルを開き、ファイルポインタを取得する。
 * ※読込ファイルはHASP形式を使用する場合のみ
 */
void eeflopen(SIMCONTL *Simc, int Nflout, FLOUT *Flout)
{
	FLOUT *fl;
	char  Fname[SCHAR], Err[SCHAR] ; 
	
	sprintf(Err, ERRFMT, "(eeflopen)");

	//
	// 1) 入力ファイルを全て開く
	//

	//気象データをHASP形式で読み取る場合
	if (Simc->wdtype == 'H')
	{
		if ((Simc->fwdata = fopen(Simc->wfname, "r")) == 0)
		{
			Eprint ( "<eeflopen>", Simc->wfname ) ;
            //getch() ;
			preexit ( ) ;
			exit(EXIT_WFILE);
		}
		if ((Simc->fwdata2 = fopen(Simc->wfname, "r")) == 0)
		{
			Eprint ( "<eeflopen>", Simc->wfname ) ;
            //getch() ;
			preexit ( ) ;
			exit(EXIT_WFILE);
		}
		if ((Simc->ftsupw = fopen("supw.efl", "r")) == 0)
		{
			Eprint ( "<eeflopen>", "supw.efl" ) ;
            //getch() ;
			preexit ( ) ;
			exit(EXIT_SUPW);
		}
	}
	
	//strcat ( strcpy ( Fname, Simc->ofname ), ".log" ) ;
	//flog = fopen ( Fname, "w" ) ;


	//
	// 2) 出力ファイルを全て開く
	//

	for (fl = Flout; fl < Flout+Nflout; fl++)
	{
		strcat(strcpy(Fname, Simc->ofname), fl->idn);      
		fl->f = fopen(strcat(Fname, ".es"), "w");
	}
}
/* ----------------------------------------------------- */


void eeflclose(int Nflout, FLOUT *Flout)
{
	FLOUT *fl;
	
	//   fclose(Simc->fwdata);
	//   fclose(Simc->ftsupw);
	
	if ( LOG_ENABLED )
		fclose ( flog ) ;
	for (fl = Flout; fl < Flout+Nflout; fl++)
	{
		fprintf(fl->f, "-999\n");
		fflush(fl->f);
		fclose(fl->f);
	}
	  	//_fcloseall() ;  
		//higuchi
}
