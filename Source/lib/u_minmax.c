﻿//This file is part of EESLISM.
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

/*  u_minmax.c  */

#include "lib/u_minmax.h"

/**
 * @file
 * @brief 最大最小
 */


/*  dmin(a,b), dmax(a,b)
======================= */
double dmin(double a, double b)
{ 
   if (a <= b)
     return (a);
   else
     return (b);
}
/* -------------------- */
double dmax(double a, double b)
{ 
   if (a >= b)
     return (a);
   else
     return (b);
}

int		imax ( int a, int b )
{
	return (( a > b ) ? a : b ) ;
}

int		imin ( int a, int b )
{
	return (( a < b ) ? a : b ) ;
}
