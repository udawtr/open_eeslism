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
 * @brief HCC 冷温水コイルの処理関数の定義
 */


#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "fesy.h"
#include "fnmcs.h"
#include "fnfio.h"
#include "fnlib.h"
#include "lib/u_psy.h"

#include "mc/eqptyp.h"



/*  機器仕様入力 */

int Hccdata(char *s, HCCCA *Hccca)
{
	char  *st;
	double dt;
	int   id=0;
	
	if ((st=strchr(s,'=')) == 0)
	{
		Hccca->name = stralloc(s);
		Hccca->eh = 0.0;
		Hccca->et = -999.0 ;
		Hccca->KA = -999.0 ;
	}
	else
	{ 
		*st = '\0';
		
        dt=atof(st+1);
		
        if (strcmp(s,"et") == 0)
			Hccca->et = dt;
        else if (strcmp(s,"eh") == 0)
			Hccca->eh = dt;
		else if (strcmp(s,"KA") == 0)
			Hccca->KA = dt;
        else 
			id=1;      
	}
	return (id);
}	
