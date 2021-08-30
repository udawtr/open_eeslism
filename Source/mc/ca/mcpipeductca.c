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

/*  pipe.c  */

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

/**
 * @file
 * @brief PIPE 配管・ダクトの処理関数の定義
 */


/*  配管・ダクト 仕様入力 */

int Pipedata(char *cattype, char *s, PIPECA *Pipeca)
{
	char  *st;
	double dt;
	int   id=0;
	
	if (strcmp(cattype, DUCT_TYPE) == 0)
		Pipeca->type = DUCT_PDT;
	else
		Pipeca->type = PIPE_PDT;
	
	if ((st=strchr(s,'=')) == 0)
	{
		Pipeca->name = stralloc(s);
		Pipeca->Ko = -999.0 ;
	}
	else
	{ 
		*st = '\0';
		
        dt=atof(st+1);
		
        if (strcmp(s,"Ko") == 0)
			Pipeca->Ko = dt;
		
        else 
			id=1;      
	}
	return (id);
}
