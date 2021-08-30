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

/*  solrcol.c  */

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "MODEL.h"   /*-----higuchi 070918---*/
#include "fesy.h"
#include "fnmcs.h"
#include "fnbld.h"
#include "fnfio.h"
#include "fnlib.h"

/**
 * @file
 * @brief COLCA 太陽熱集熱器の処理関数の定義
 */

/*　太陽熱集熱器

機器仕様入力　　　　*/

int Colldata (char *type,  char *s, COLLCA *Collca)
{
	char  *st;
	double dt;
	int   id=0;
	
	if ( strcmp(type, COLLECTOR_TYPE) == 0 )
		Collca->type = COLLECTOR_PDT ;
	else
		Collca->type = ACOLLECTOR_PDT ;

	if ((st=strchr(s,'=')) == 0)
	{
		Collca->name = stralloc(s);
		Collca->b0 = Collca->b1 = Collca->Ac = Collca->Ag = -999.0 ;
	}
	else
	{ 
		*st = '\0';
		
        dt=atof(st+1);
        if (strcmp(s,"b0") == 0)
			Collca->b0 = dt;
        else if (strcmp(s,"b1") == 0)
			Collca->b1 = dt;
        else if (strcmp(s,"Fd") == 0)
			Collca->Fd = dt;
        else if (strcmp(s, "Ac") == 0)
			Collca->Ac = dt;
        else if (strcmp(s, "Ag") == 0)
			Collca->Ag= dt;
        else 
			id=1;     
	}
	return (id);
}
