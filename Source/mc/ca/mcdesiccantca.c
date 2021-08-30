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
 * @brief DESI バッチ式デシカント空調機の処理関数の定義
 */


#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "fesy.h"
#include "fnmcs.h"
#include "fnesy.h"
#include "fnfio.h"
#include "fnlib.h"
#include "lib/u_psy.h"


/*---- Satoh追加 2013/10/20 ----*/
int Desiccantdata(char *s, DESICA *Desica)
{
	char  *st;
	double dt;
	int   id=0;
	
	if ((st=strchr(s,'=')) == 0)
	{
		Desica->name = stralloc(s);
		Desica->r = -999. ;
		Desica->rows = -999. ;
		Desica->Uad = -999. ;
		Desica->A = -999.0 ;
		Desica->Vm = 18. ;
		Desica->eps = 0.4764 ;
		Desica->P0 = 0.4 ;
		Desica->kp = 0.0012 ;
		Desica->cps = 710. ;
		Desica->ms = -999. ;
	}
	else
	{ 
		*st = '\0';
		
        dt=atof(st+1);
		
        if (strcmp(s,"Uad") == 0)			// シリカゲル槽壁面の熱貫流率[W/m2K]
			Desica->Uad = dt;
		else if (strcmp(s, "A") == 0)		// シリカゲル槽表面積[m2]
			Desica->A = dt ;
		else if (strcmp(s, "ms") == 0)		// シリカゲル質量[g]
			Desica->ms = dt ;
		else if (strcmp(s, "r") == 0)		// シリカゲル平均直径[cm]
			Desica->r = dt ;
		else if (strcmp(s, "rows") == 0)	// シリカゲル充填密度[g/cm3]
			Desica->rows = dt ;
        else 
			id=1;      
	}
	return (id);
}
