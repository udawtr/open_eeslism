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

/* mcevcooling.c */

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
#include "waterandair.h"

/**
 * @file
 * @brief EVAC 気化冷却器の処理関数の定義
 */


/*  気化冷却器  */

/*  仕様入力  */

int		Evacdata(char *s, EVACCA *Evacca)
{
	char	*st;
	int		id = 0;

	if ((st = strchr(s, '=')) == 0)
	{
		Evacca->name = stralloc(s);
		Evacca->N = -999;
		Evacca->Nlayer = -999;
		Evacca->Awet = Evacca->Adry = Evacca->hdry = Evacca->hwet = -999.;
	}
	else
	{
		*st = '\0';

		if (strcmp(s, "Awet") == 0)
			Evacca->Awet = atof(st + 1);
		else if (strcmp(s, "Adry") == 0)
			Evacca->Adry = atof(st + 1);
		else if (strcmp(s, "hwet") == 0)
			Evacca->hwet = atof(st + 1);
		else if (strcmp(s, "hdry") == 0)
			Evacca->hdry = atof(st + 1);
		else if (strcmp(s, "N") == 0)
			Evacca->N = atoi(st + 1);
		else if (strcmp(s, "Nlayer") == 0)
			Evacca->Nlayer = atoi(st + 1);
		else
			id = 1;
	}

	return (id);
}

