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

/*  mcstank.c */

/*  95/11/17 rev  */

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "common.h"
#include "fesy.h"
#include "fnmcs.h"
#include "fnesy.h"
#include "fnfio.h" 
#include "fnlib.h"
#include "waterandair.h"

/**
 * @file
 * @brief STANK 蓄熱槽仕様入力処理関数の定義
 */


/*　蓄熱槽仕様入力　　　　*/

int Stankdata(FILE *f, char *s, STANKCA *Stankca)
{
	int   id = 0;
	char  *st;
	
	Stankca->gxr = 0.0;
	
	if ((st = strchr(s, '=')) != 0)
	{
		*st='\0'; 
		if (strcmp(s, "Vol") == 0)
			Stankca->Vol = atof(st+1);
		else if (strcmp(s, "KAside") == 0)
			Stankca->KAside = atof(st+1);
		else if (strcmp(s, "KAtop") == 0)
			Stankca->KAtop = atof(st+1);
		else if (strcmp(s, "KAbtm") == 0)
			Stankca->KAbtm = atof(st+1);
		
		else if (strcmp(s, "gxr") == 0)
			Stankca->gxr = atof(st+1);
		
		else 
			id = 1;
	}
	else if (strcmp(s, "-S") == 0)
	{
		strcat(s, "  ");
		st = s + strlen(s);	   
		fscanf(f, "%[^*]*", st); 
		strcat(s, " *"); 	   
		Stankca->tparm = stralloc(s);
	}   
	else
	{
		Stankca->name = stralloc(s);
		Stankca->type = 'C';
		Stankca->tparm = NULL ;
		Stankca->Vol = Stankca->KAside = Stankca->KAtop = Stankca->KAbtm = -999.0 ;
		Stankca->gxr = 0.0 ;
	}
	return(id);
}

