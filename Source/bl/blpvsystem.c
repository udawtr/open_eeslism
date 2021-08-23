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

/*   bl_panel.c  */

#include <math.h>
#include "MODEL.h"
#include "fesy.h"
#include "fnfio.h"
#include "fnbld.h"
#include "fnmcs.h"
#include "fnlib.h"


//
//@brief 太陽電池の計算
//


/*
 * @brief 太陽電池の温度補正係数計算式
 * @param[IN] TPV    太陽電池温度
 * @param[IN] apmax
 * @return 太陽電池の温度補正係数
 */
double	FNKPT(double TPV, double apmax)
{
	return (1. + apmax * ( TPV - 25.) / 100. ) ;
}


/*
 * @brief 太陽電池パラメータの初期化
 * @param[IN,OUT] PVwallcat 太陽電池パラメータのポインタ
 */
void	PVwallcatinit(PVWALLCAT *PVwallcat)
{
	//PVwallcat->PVcap = -999. ;
	PVwallcat->type = 'C' ;
	PVwallcat->apmax = -0.41 ;
	PVwallcat->KHD = 1.0 ;
	PVwallcat->KPD = 0.95 ;
	PVwallcat->KPM = 0.94 ;
	PVwallcat->KPA = 0.97 ;
	PVwallcat->effINO = 0.9 ;
	PVwallcat->ap = 10.0 ;
	PVwallcat->Rcoloff = -999. ;
	PVwallcat->Kcoloff = -999. ;
}




/*
 * @brief 太陽電池の事前計算
 * @param[IN,OUT] PVwallcat 太陽電池パラメータのポインタ
 * @details
 * 温度補正係数以外は時々刻々変化しないので、最初に１度計算しておく
 */
void	PVwallPreCalc(PVWALLCAT *PVwallcat)
{
	//温度補正係数以外の補正係数の積（温度補正係数以外は時々刻々変化しない）
	PVwallcat->KConst = PVwallcat->KHD * PVwallcat->KPD * PVwallcat->KPM * PVwallcat->KPA * PVwallcat->effINO;
	//printf("KConst=%lf\n", PVwallcat->KConst);
}


/*
 * @brief 太陽電池温度の計算
 * @param[IN] Sd    壁体
 * @param[IN] Wd    気象データ
 * @param[IN] Exsfs
 * @return 太陽電池温度
 */
double	FNTPV(RMSRF *Sd, WDAT *Wd, EXSFS *Exsfs)
{
	//壁体
	WALL* wall = Sd->mw->wall;

	//外表面方位データ
	EXSF* Exs = &Exsfs->Exs[Sd->exs] ;

	//
	double Ipv = ( wall->tra - Sd->PVwall.Eff ) * Sd->Iwall ;

	double	TPV;	//太陽電池温度
	if ( Sd->rpnl->cG > 0.)
	{
		//printf("Tf=%lf\n", Sd->Tf ) ;
		TPV = (wall->PVwallcat.ap * Sd->Tf + *Exs->alo * Wd->T + Ipv) / (wall->PVwallcat.ap + *Exs->alo) ;
	}
	else
	{
		TPV = (wall->PVwallcat.Kcoloff * Sd->oldTx + *Exs->alo * Wd->T + Ipv)
			/ (wall->PVwallcat.Kcoloff + *Exs->alo) ;
	}

	return(TPV) ;
}



/*
 * @brief 発電量の計算
 * @param[IN]     Nsrf
 * @param[IN,OUT] Sd    壁体
 * @param[IN]     Wd    気象データ
 * @param[IN]     Exsfs
 */
void	CalcPowerOutput(int Nsrf, RMSRF *Sd, WDAT *Wd, EXSFS *Exsfs)
{
	int		i ;

	for (i = 0; i < Nsrf; i++, Sd++)
	{
		if (Sd->mw != NULL )
		{
			WALL *wall ;

			wall = Sd->mw->wall ;
			
			// 太陽電池が設置されているときのみ
			if (Sd->PVwallFlg == 'Y')
			{
				//EXSF	*Exs ;
				PVWALL	*pvwall ;
				//Exs = &Exsfs->Exs[Sd->exs] ;
				pvwall = &Sd->PVwall ;

				pvwall->TPV = FNTPV(Sd, Wd, Exsfs) ;
				//printf("TPV=%lf  ", pvwall->TPV) ;

				pvwall->KPT = FNKPT(pvwall->TPV, wall->PVwallcat.apmax) ;
				pvwall->KTotal = wall->PVwallcat.KConst * pvwall->KPT ;
				//printf("KConst=%lf  KPT=%lf  KTotal=%lf  ", wall->PVwallcat.KConst, pvwall->KPT, pvwall->KTotal) ;

				pvwall->Power = dmax(Sd->PVwall.PVcap * pvwall->KTotal * Sd->Iwall / 1000., 0.) ;
				//printf("Power=%lf\n", pvwall->Power ) ;

				// 発電効率の計算
				if(Sd->Iwall > 0.)
					pvwall->Eff = pvwall->Power / (Sd->Iwall * Sd->A) ;
				else
					pvwall->Eff = 0. ;
			}
		}
	}
}
