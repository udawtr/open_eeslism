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

/*  mcstheat.c  */
/*  電気蓄熱式暖房器 */

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "fesy.h"
#include "fnmcs.h"
#include "fnesy.h"
#include "fnfio.h"
#include "fnlib.h"

/**
 * @file
 * @brief STHEAT 電気蓄熱式暖房器の処理関数の定義
 */

/* ------------------------------------------ */

/* 機器仕様入力　　　　　　*/

/*---- Satoh Debug 電気蓄熱式暖房器 2001/1/21 ----*/
int Stheatdata(char *s, STHEATCA *stheatca)
{
	char  *st;
	double dt;
	int   id=0;
	
	if ((st=strchr(s,'=')) == 0)
	{
		stheatca->name = stralloc(s);
		stheatca->eff = -999.0 ;
		stheatca->Q = -999.0 ;
		stheatca->Hcap = -999.0 ;
		stheatca->KA = -999.0 ;
	}
	else
	{ 
		*st = '\0';
		
		if (strcmp(s, "PCM") == 0)
			stheatca->pcmname = stralloc(st + 1);
		else
		{
			dt = atof(st + 1);

			if (strcmp(s, "Q") == 0)
				stheatca->Q = dt;
			else if (strcmp(s, "KA") == 0)
				stheatca->KA = dt;
			else if (strcmp(s, "eff") == 0)
				stheatca->eff = dt;
			else if (strcmp(s, "Hcap") == 0)
				stheatca->Hcap = dt;
			else
				id = 1;
		}
	}
	return (id);
}
