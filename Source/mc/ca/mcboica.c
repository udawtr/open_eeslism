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


/**
 * @file
 * @brief BOICA ボイラーの処理関数の定義
 */

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "fesy.h"
#include "fnmcs.h"
#include "fnfio.h"
#include "fnlib.h"
#include "fnesy.h"

/* 機器仕様入力　　　　　　*/

int Boidata (char *s, BOICA *Boica)
{
	char *st;
	double dt;
	int   id=0;
	
	if ((st=strchr(s,'=')) == 0 && *s != '-' )
	{
		Boica->name = stralloc(s);
		Boica->unlimcap = 'n' ;
		Boica->ene = ' ' ;
		Boica->plf = ' ' ;
		Boica->Qo = NULL ;
		Boica->eff = 1.0 ;
		Boica->Ph = -999.0 ;
		Boica->Qmin = -999.0 ;
		//Boica->mode = 'n' ;
		Boica->Qostr = NULL ;
	}
	else if (( strcmp ( s, "-U" )) == 0 )
		Boica->unlimcap = 'y' ;
	else
	{ 
		*st = '\0';
		if ( strcmp(s, "p") == 0)
			Boica->plf = *(st+1);
		else if (strcmp(s, "en") == 0)
			Boica->ene = *(st+1);
		else if (strcmp(s, "blwQmin") == 0)
		{
			// 負荷が最小出力以下のときに最小出力でONとする
			if (strcmp(st+1, "ON") == 0)
				Boica->belowmin = ON_SW ;
			// 負荷が最小出力以下のときにOFFとする
			else if (strcmp(st+1, "OFF") == 0)
				Boica->belowmin = OFF_SW ;
			else
				id = 1 ;
		}
		else
		{
			dt=atof(st+1);
			if (strcmp(s,"Qo") == 0)
			{
				//Boica->Qo= dt;
				Boica->Qostr = stralloc(st+1) ;

				//if (Boica->Qo > 0. )
				//	Boica->mode = 'H' ;
				//else
				//	Boica->mode = 'C' ;
			}
			else if ( strcmp ( s, "Qmin" ) == 0 )
				Boica->Qmin = dt ;
			else if (strcmp(s, "eff") == 0)
				Boica->eff =dt;
			else if (strcmp(s, "Ph") == 0)
				Boica->Ph = dt;
			else
				id=1;
		}
    }
	return (id);
}

void	Boicaint(int NBoica, BOICA *Boica,  SIMCONTL *Simc, int Ncompnt, COMPNT *Compnt, WDAT *Wd, EXSFS *Exsf, SCHDL *Schdl)
{
	int	i ;

	for(i = 0; i < NBoica; i++, Boica++)
	{
		int i, err = 0;

		if (( i = idsch ( Boica->Qostr, Schdl->Sch, NULL )) >= 0 )
			Boica->Qo = Schdl->val + i;
		else
			Boica->Qo = envptr ( Boica->Qostr, Simc, 0, NULL, NULL, NULL ) ;
		
		//Errprint(err, "<ctlvptr>", Boica->Qostr);
	}
}