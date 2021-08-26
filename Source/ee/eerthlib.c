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

#include <math.h>

#include "common.h"
#include "fesy.h"
#include "fnfio.h"

/**
 * @file
 * @brief 地下の温度または地表面温度の計算
 */


/*
 * @brief 地中温度の計算
 * 
 * @param[IN] Z     地中深さ
 * @param[IN] n     通日
 * @param[IN] nmx   日平均気温の年最高気温が発生する日の通日(地中温度計算用) (VCFILE daymx)
 * @param[IN] Tgro  年平均気温 [℃] 
 * @param[IN] DTg   気温年較差 [℃]
 * @param[IN] a     土の熱拡散率 [m2/s]
 *
 * @return 地中温度 [℃]
 */
double Tearth (double Z, int n, int nmx, double Tgro, double DTg, double a)
{
	const double t = 31.536e+6 ;
	
	double Cz = Z * sqrt ( CONST_PI / ( a * t )) ;

	return ( Tgro + 0.5 * DTg * exp ( - Cz ) * cos (( n - nmx ) * 0.017214 - Cz ));
}


/*
 * @brief 地下の温度または地表面温度の計算
 * 
 * @param[IN]     day    通日
 * @param[IN]     daymx  日平均気温の年最高気温が発生する日の通日(地中温度計算用) (VCFILE daymx)
 * @param[IN]     Tgrav  年平均気温 [℃] 
 * @param[IN]     DTgr   気温年較差 [℃]
 * @param[IN,OUT] Exs    外表面方位データ
 * @param[IN]     Wd     気象データ
 * @param[IN]     tt     時
 */
void Exsfter (int day, int daymx, double Tgrav, double DTgr, EXSF *Exs, WDAT *Wd, int tt)
{
	int i, Ne ;

	if ( Exs != NULL )
	{
		Ne = Exs->end;
		
		for ( i = 0; i < Ne; i++, Exs++ )
		{
			if (Exs->typ == 'E')
			{
				//地下の温度
				Exs->Tearth = Tearth(Exs->Z, day, daymx, Tgrav, DTgr, Exs->erdff);
			}
			else if (Exs->typ == 'e')
			{
				//地表面の温度
				Exs->Tearth = Wd->EarthSurface[day * 24 + tt];
			}
		}
	}
}
