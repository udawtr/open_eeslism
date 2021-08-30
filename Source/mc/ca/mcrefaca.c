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

/*  refas.c */

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include "fesy.h"
#include "fnmcs.h"
#include "fnesy.h"
#include "fnfio.h"
#include "fnlib.h"
#include "winerror.h"
#include <stdio.h>
#include "esize.h"
#include "lib/u_psy.h"
#include <math.h>

/**
 * @file
 * @brief REFA 圧縮式冷凍機の処理関数の定義
 */

//For RFCMP, REFA
#include "mc/eqptyp.h"


/*  圧縮式冷凍機

機器仕様入力          */


int Refadata (char *s, REFACA *Refaca, int Nrfcmp, RFCMP *Rfcmp)
{ 
	RFCMP  *rfc;  
	static HPCH   *hpch;
	char   *st, c;
	double  dt;
	int    id=0, i;
	
	if ((st=strchr(s, '=')) == 0 && strchr(s, '-') == 0)
	{
		/***** printf("xxxx Refadata  %s\n", s); *****/
		
		Refaca->name = stralloc(s);
		Refaca->Nmode = 0;
		Refaca->unlimcap = 'n';
		Refaca->cool = Refaca->heat =  NULL;
		Refaca->awtyp = Refaca->plf = ' ' ;
		Refaca->rfc = NULL ;
		Refaca->Ph = -999.0 ;
	}
	else
	{ 	
		if (s[0] == 'a')
			Refaca->awtyp = *(st+1);
		
		else if (strcmp(s, "-U") == 0)
			Refaca->unlimcap = 'y';
		
		else if (s[0] == 'c')
		{
			rfc = Rfcmp;
			for (i = 0; i < Nrfcmp; i++, rfc++)
			{
				if (strcmp(st+1, rfc->cname) == 0)
				{
					Refaca->rfc = rfc;
					break;
				}
			}
			if (i == Nrfcmp)
				id = 1;
		}
		else if (s[0] == 'p')
			Refaca->plf = *(st+1);
		
		else if (s[0] == 'm')
		{
			Refaca->mode[Refaca->Nmode] = c = *(st+1);
			if (c == COOLING_SW)
			{	  
				if ((Refaca->cool = (HPCH *)malloc(1 * sizeof(HPCH))) == NULL)
					Ercalloc(1, "Refaca->cool");
				hpch = Refaca->cool;  
			}
			else if (c == HEATING_SW)
			{
				if ((Refaca->heat = (HPCH *)malloc(1 * sizeof(HPCH))) == NULL)
					Ercalloc(1, "Refaca->heat");
				hpch = Refaca->heat;
			}
			Refaca->Nmode++;
		}
		else
		{ 
			dt = atof(st + 1);
			
			if (strncmp(s, "Qo",2) == 0)
				hpch->Qo = dt;
			else if (strncmp(s,"Go",2) == 0)
				hpch->Go = dt;
			else if (strncmp(s,"Two",3) == 0)
				hpch->Two = dt;
			
			else if (strncmp(s,"eo",2) == 0)
				hpch->eo = dt;
			else if (strncmp(s,"Qex",3) == 0)
				hpch->Qex = dt;
			else if (strncmp(s,"Gex",3) == 0)
				hpch->Gex = dt;
			else if (strncmp(s,"Tex",3) == 0)
				hpch->Tex = dt;
			else if (strncmp(s,"eex",3) == 0)
				hpch->eex = dt;
			else if (s[0] == 'W')
				hpch->Wo = dt;
			
			else if (strncmp(s, "Ph", 2) == 0)
				Refaca->Ph = dt;
			
			else
				id=1;
		}
	}
	return (id);
}	
