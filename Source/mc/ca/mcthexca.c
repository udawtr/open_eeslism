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

/* mcthex.c */

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "fesy.h"
#include "fnmcs.h"
#include "fnesy.h"
#include "fnfio.h"
#include "fnlib.h"
#include "lib/u_psy.h"


/**
 * @file
 * @brief THEX 全熱交換器の処理関数の定義
 */

 /*  全熱交換器  */

/*  仕様入力  */

int		Thexdata ( char *s, THEXCA *Thexca )
{
	char	*st ;
	double	dt ;
	int		id = 0 ;

	if (( st = strchr ( s, '=' )) == 0 )
		Thexca->name = stralloc ( s ) ;
	else
	{
		*st = '\0' ;
		dt = atof ( st + 1 ) ;

		if ( strcmp ( s, "et" ) == 0 )
			Thexca->et = dt ;
		else if ( strcmp ( s, "eh" ) == 0 )
			Thexca->eh = dt ;
		else
			id = 1 ;
	}

	return ( id ) ;
}
