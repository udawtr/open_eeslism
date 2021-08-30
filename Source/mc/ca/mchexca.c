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

/* hexchgr.c */

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>

#include "fesy.h"
#include "fnmcs.h"
#include "fnesy.h"
#include "fnfio.h"
#include "fnlib.h"


/**
 * @file
 * @brief HEX 熱交換器の処理関数の定義
 */


/*  仕様入力  */

int Hexdata(char *s, HEXCA *Hexca)
{
	char  *st;
	double dt;
	int   id=0;
	
	if ((st=strchr(s,'=')) == 0)
	{
		Hexca->name = stralloc(s);
		Hexca->eff = -999.0 ;
		Hexca->KA = -999.0 ;
	}
	else
	{ 
		*st = '\0';
		
        dt=atof(st+1);
		
        if (strcmp(s,"eff") == 0)
			Hexca->eff = dt;
		else if (strcmp(s,"KA") == 0)
			Hexca->KA = dt;
        else 
			id=1;      
	}
	return (id);
} 
