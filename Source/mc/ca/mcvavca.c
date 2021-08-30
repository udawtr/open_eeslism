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

/*  mcvav.c  */

/*  VAVコントローラ */

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "fesy.h"
#include "fnmcs.h"
#include "fnfio.h"
#include "fnlib.h"
#include "lib/u_psy.h"
#include "fnesy.h"
#include "winerror.h"
#include "fnbld.h"

/**
 * @file
 * @brief VAV VAVコントローラの処理関数の定義
 */

/* ------------------------------------------ */

/* 機器仕様入力　　　　　　*/

/*---- Satoh Debug VAV  2000/10/30 ----*/
int VAVdata (char *cattype, char *s, VAVCA *vavca)
{
	char *st;
	double dt;
	int   id=0;
	
	if (strcmp(cattype, VAV_TYPE) == 0)
		vavca->type = VAV_PDT ;
	else if(strcmp(cattype, VWV_TYPE) == 0)
		vavca->type = VWV_PDT ;

	if ((st=strchr(s,'=')) == 0)
	{
		vavca->name = stralloc(s);
		vavca->Gmax = vavca->Gmin = vavca->dTset = -999.0 ;
	}
	else
	{ 
		*st = '\0';
		dt = atof(st+1) ;
		
		if ( strcmp(s, "Gmax") == 0)
			vavca->Gmax = dt;
		else if (strcmp(s, "Gmin") == 0)
			vavca->Gmin = dt ;
		else if (strcmp(s, "dTset") == 0)
			vavca->dTset = dt ;
		else
			id=1;
    }
	return (id);
}
