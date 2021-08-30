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

/*  solrcol.c  */

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "fesy.h"
#include "fnmcs.h"
#include "fnbld.h"
#include "fnfio.h"
#include "fnlib.h"

/**
 * @file
 * @brief PV 太陽光発電システムの処理関数の定義
 */

 
 /*　

機器仕様入力　　　　*/

int PVcadata (char *s, PVCA *PVca)
{
	char  *st;
	double dt;
	int   id=0;

	if ((st=strchr(s,'=')) == 0)
	{
		PVca->name = stralloc(s);
		PVca->PVcap = PVca->Area = -999.0 ;
		PVca->KHD = 1.0 ;
		PVca->KPD = 0.95 ;
		PVca->KPM = 0.94 ;
		PVca->KPA = 0.97 ;
		PVca->effINO = 0.9 ;
		PVca->A = PVca->B = -999. ;
		PVca->apmax = -0.41 ;
	}
	else
	{ 
		*st = '\0';
		
        dt=atof(st+1);
        
		if (strncmp(s,"KHD",3) == 0)			// 日射量年変動補正係数
			PVca->KHD = dt ;
		else if (strncmp(s,"KPD",3) == 0)			// 経時変化補正係数
			PVca->KPD = dt ;
		else if (strncmp(s,"KPM",3) == 0)			// アレイ負荷整合補正係数
			PVca->KPM = dt ;
		else if (strncmp(s,"KPA",3) == 0)			// アレイ回路補正係数
			PVca->KPA = dt ;
		else if (strncmp(s,"EffInv",6) == 0)		// インバータ実行効率
			PVca->effINO = dt ;
		else if (strncmp(s,"apmax",5) == 0)			// 最大出力温度係数
			PVca->apmax = dt  ;
		else if (strcmp(s, "InstallType") == 0)
		{
			PVca->InstallType = *(st+1) ;

			switch(PVca->InstallType)
			{
			case 'A':
				PVca->A = 46., PVca->B = 0.41 ;
				break ;
			case 'B':
				PVca->A = 50.0, PVca->B = 0.38 ;
				break ;
			case 'C':
				PVca->A = 57.0, PVca->B = 0.33 ;
				break ;
			}
		}
		else if (strncmp(s,"PVcap",5) == 0)			// 太陽電池容量
			PVca->PVcap = dt  ;
		else if (strncmp(s,"Area",4) == 0)			// 太陽電池容量
			PVca->Area = dt  ;
        else 
			id=1;     
	}
	return (id);
}