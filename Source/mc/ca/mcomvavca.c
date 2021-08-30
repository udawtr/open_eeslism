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

/*  mcomvav.c  */

/*  OM用変風量コントローラ */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
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
 * @brief OM用変風量コントローラの処理関数の定義
 */


/* ------------------------------------------ */

/* 機器仕様入力　　　　　　*/

/*---- Satoh OMVAV  2010/12/16 ----*/
int OMVAVdata (char *s, OMVAVCA *OMvavca)
{
	char *st;
	double dt;
	int   id=0;
	
	if ((st=strchr(s,'=')) == 0)
	{
		OMvavca->name = stralloc(s);
		OMvavca->Gmax = OMvavca->Gmin = -999.0 ;
	}
	else
	{ 
		*st = '\0';
		dt = atof(st+1) ;
		
		if ( strcmp(s, "Gmax") == 0)
			OMvavca->Gmax = dt;
		else if (strcmp(s, "Gmin") == 0)
			OMvavca->Gmin = dt ;
		else
			id=1;
    }
	return (id);
}

