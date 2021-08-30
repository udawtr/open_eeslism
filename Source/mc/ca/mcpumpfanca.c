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

/*  pump.c  */

/*  ポンプ   */

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "common.h"
#include "fesy.h"
#include "fnmcs.h"
#include "fnfio.h"
#include "fnlib.h"

/**
 * @file
 * @brief PUMP ポンプの処理関数の定義
 */

/* 機器仕様入力　　　　　　*/

int Pumpdata (char *cattype, char *s, PUMPCA *Pumpca, int Npfcmp, PFCMP *pfcmp)
{
	char *st;
	double dt;
	int   id=0, i;
	PFCMP	*pfc ;
	
	if ((st=strchr(s,'=')) == 0)
	{
		Pumpca->name = stralloc(s);
		Pumpca->type = NULL ;
		Pumpca->Wo = Pumpca->Go = Pumpca->qef = -999.0 ;
		Pumpca->val = NULL ;
		
		if ( strcmp ( cattype, PUMP_TYPE ) == 0 )
			Pumpca->pftype = PUMP_PF ;
		else if (strcmp(cattype, FAN_TYPE) == 0)
			Pumpca->pftype = FAN_PF ;
		else
			Pumpca->pftype = OFF_SW ;
	}
	else
	{ 
		*st = '\0';
		if ( strcmp(s, "type") == 0)
		{
			Pumpca->type = stralloc(st+1);
			if ( strcmp(Pumpca->type, "P") == 0)
				Pumpca->val = dcalloc(4, "Pumpdata");

			pfc = pfcmp ;
			for (i = 0; i < Npfcmp; i++, pfc++)
			{
				if (Pumpca->pftype == pfc->pftype
					&& strcmp(Pumpca->type, pfc->type) == 0)
				{
					Pumpca->pfcmp = pfc ;
					break ;
				}
			}
		}
		else
		{ 
			dt=atof(st+1);
			if (strcmp(s,"qef") == 0)
				Pumpca->qef= dt;
			else
			{
				if (strcmp(Pumpca->type, "P") != 0)
				{
					if (strcmp(s, "Go") == 0)
						Pumpca->Go =dt;
					else if (strcmp(s, "Wo") == 0)
						Pumpca->Wo = dt;
					else 
						id = 1;
				}
				else
				{
					if (strcmp(s, "a0") == 0)
						Pumpca->val[0] = dt;
					else if (strcmp(s, "a1") == 0)
						Pumpca->val[1] = dt;
					else if (strcmp(s, "a2") == 0)
						Pumpca->val[2] = dt;
					else if (strcmp(s, "Ic") == 0)
						Pumpca->val[3] = dt;
					else
						id = 1;
				}
			}
		}
	}
	return (id);
}

