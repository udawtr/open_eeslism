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

/*   ee_print_s.c  */

#include "common.h"
#include "fesy.h"
#include "fnbld.h"
#include "fnfio.h"
#include "fnlib.h"


/**
 * @file
 * @brief 出力データファイルの書き込み制御
 */


/**
 * @brief 代表日の毎時計算結果のファイル出力
 */
void Eeprinth(DAYTM *Daytm, SIMCONTL *Simc, int Nflout, FLOUT *flout, 
			  RMVLS *Rmvls, EXSFS *Exsfst, 
			  int Nmpath, MPATH *Mpath, EQSYS *Eqsys, WDAT *Wd)
{
	if (Daytm->ddpri && Simc->dayprn[Daytm->day])
    {
		char*  title = Simc->title;
		int    Mon   = Daytm->Mon;
		int    Day   = Daytm->Day;
		double time  = Daytm->time;

		FLOUT* flo = flout;
		for (int i = 0; i < Nflout; i++, flo++)
		{
			if ( DEBUG())
				printf ( "Eeprinth MAX=%d flo[%d]=%s\n", Nflout, i, flo->idn ) ;
			
			if (strcmp(flo->idn, PRTHWD) == 0)
			{
				// 気象データの出力 `outfile_wd.es`

				if (DEBUG())
					printf("<Eeprinth> xprsolrd\n");
				//xprsolrd ( Exsfst->Nexs, Exsfst->Exs);
				Wdtprint(flo->f, title, Mon, Day, time, Wd, Exsfst);
			}
			else if (strcmp(flo->idn, PRTCOMP) == 0)
			{
				// 毎時出力／機器ごとのシミュレーション結果(入口・出口水温、各種熱量、エネルギー消費量など)
				// `outfile_sc.es`
				Hcmpprint(flo->f, PRTCOMP, Simc, Mon, Day, time, Eqsys, Rmvls->Nrdpnl, Rmvls->Rdpnl);
			}
			else if (strcmp(flo->idn, PRTPATH) == 0)
			{
				// システム経路の温湿度出力 `outfile_sp.es`
				Pathprint(flo->f, title, Mon, Day, time, Nmpath, Mpath);
			}
			else if (strcmp(flo->idn, PRTHRSTANK) == 0)
			{
				// 蓄熱槽内温度分布の出力 `outfile_tk.es`
				Hstkprint(flo->f, title, Mon, Day, time, Eqsys);
			}
			else if (strcmp(flo->idn, PRTREV) == 0)
			{
				// 毎時室温、MRTの出力 `outfile_re.es`
				Rmevprint(flo->f, title, Rmvls->Room, Mon, Day, time);
			}
			else if (strcmp(flo->idn, PRTHROOM) == 0)
			{
				// 放射パネルの出力 `outfile_rm.es`
				Rmpnlprint(flo->f, PRTHROOM, Simc, Mon, Day, time, Rmvls->Nroom, Rmvls->Room);
			}
			else if (strcmp(flo->idn, PRTHELM) == 0)
			{
				// ???
				Helmprint(flo->f, PRTHELM, Simc, Mon, Day, time, Rmvls->Nroom, Rmvls->Room, &Rmvls->Qetotal);
			}
			else if (strcmp(flo->idn, PRTHELMSF) == 0)
			{
				// ???
				Helmsurfprint(flo->f, PRTHELMSF, Simc, Mon, Day, time, Rmvls->Nroom, Rmvls->Room);
			}
			else if (strcmp(flo->idn, PRTPMV) == 0)
			{
				// PMV計算結果の出力  `outfile_pm.es`
				Pmvprint(flo->f, title, Rmvls->Room, Mon, Day, time);
			}
			else if (strcmp(flo->idn, PRTQRM) == 0)
			{
				// 室の熱取得要素の出力 `outfile_rq.es`
				Qrmprint(flo->f, title, Mon, Day, time, Rmvls->Room, Rmvls->Qrm);
			}
			else if (strcmp(flo->idn, PRTRSF) == 0)
			{
				// 室内表面温度の出力 `outfile_sf.es`
				Rmsfprint(flo->f, title, Mon, Day, time, Rmvls->Room, Rmvls->Sd);
			}
			else if (strcmp(flo->idn, PRTSHD) == 0)
			{
				// 日よけの影面積出力 `outfile_shd.es`
				Shdprint(flo->f, title, Mon, Day, time, Rmvls->Nsrf, Rmvls->Sd);
			}
			else if (strcmp(flo->idn, PRTWAL) == 0)
			{
				// 壁体内部温度の出力 `outfile_wl.es`
				Wallprint(flo->f, title, Mon, Day, time, Rmvls->Nsrf, Rmvls->Sd);
			}
			else if (strcmp(flo->idn, PRTPCM) == 0)
			{
				// PCM状態値の出力 `outfile_pcm.es`
				PCMprint(flo->f, title, Mon, Day, time, Rmvls->Nsrf, Rmvls->Sd);
			}
			else if (strcmp(flo->idn, PRTSFQ) == 0)
			{
				// 室内表面熱流の出力 `outfile_sfq.es`
				Rmsfqprint(flo->f, title, Mon, Day, time, Rmvls->Room, Rmvls->Sd);
			}
			else if (strcmp(flo->idn, PRTSFA) == 0)
			{
				// 室内表面熱伝達率の出力 `outfile_sfa.es`
				Rmsfaprint(flo->f, title, Mon, Day, time, Rmvls->Room, Rmvls->Sd);
			}
		}
	}  
}      


/**
 * @brief 日集計値出力
 * @details
 * 
 * 基本的には、 `outfile_d*.es` という名前のファイルへの出力を担う。
 */
void Eeprintd(DAYTM *Daytm, SIMCONTL *Simc, int Nflout, FLOUT *flout, 
			  RMVLS *Rmvls,  int Nexs, EXSF *Exs,
			  double *Soldy, EQSYS *Eqsys, WDAT *Wdd)
{ 
	static int	ic = 0 ;
	
	//日積算値出力の対象日か確認
	if (Daytm->ddpri)
	{
		char*  title = Simc->title;
		int    Mon   = Daytm->Mon;
		int    Day   = Daytm->Day;
		FLOUT* flo   = flout;
		
		for (int i = 0; i < Nflout; i++, flo++)
		{
			if (strcmp(flo->idn, PRTDWD) == 0)
			{
				// 気象データの出力 `outfile_dwd.es`
				Wdtdprint(flo->f, title, Mon, Day, Wdd, Nexs, Exs, Soldy);
			}
			else if (strcmp(flo->idn, PRTWK) == 0)
			{
				//初回出力時にはヘッダーを付与
				if ( ic == 0 )
				{
					fprintf ( flo->f, "Mo Nd Day Week\n" ) ;
					ic = 1 ;
				}
				
				fprintf(flo->f, "%2d %2d %3d %s\n", Mon, Day, Daytm->day, DAYweek(Simc->daywk[Daytm->day]));
				fflush(flo->f);
			}
			else if (strcmp(flo->idn, PRTDYCOMP) == 0)
			{
				// 機器ごとのシミュレーション結果(入口・出口水温、各種熱量、エネルギー消費量などの日集計値)の出力 `outfile_dc.es`
				Compodyprt(flo->f, PRTDYCOMP, Simc, Mon, Day, Eqsys, Rmvls->Nrdpnl, Rmvls->Rdpnl);
			}
			else if (strcmp(flo->idn, PRTDYRM) == 0)
			{
				// 建物シミュレーション結果(室温、湿度、室内表面温度、熱負荷日集計値)の出力 `outfile_dr.es`
				Rmdyprint(flo->f, PRTDYRM, Simc, Mon, Day, Rmvls->Nroom, Rmvls->Room);
			}
			else if (strcmp(flo->idn, PRTDYHELM) == 0)
			{
				// 要素別熱損失・熱取得の出力 `outfile_dqe`
				Helmdyprint(flo->f, PRTDYHELM, Simc, Mon, Day, Rmvls->Nroom, Rmvls->Room, &Rmvls->Qetotal);
			}
			else if (strcmp(flo->idn, PRTDQR) == 0)
			{
				// 建物シミュレーション結果(日射および室内発熱熱取得要素日積算値)の出力 `outfile_dqr.es`
				Dyqrmprint(flo->f, title, Mon, Day, Rmvls->Room, Rmvls->Trdav, Rmvls->Qrmd);
			}
			else if (strcmp(flo->idn, PRTDYSF) == 0)
			{
				// 日積算壁体貫流熱取得の出力 `outfile_dsf.es`
				Dysfprint(flo->f, title, Mon, Day, Rmvls->Room);
			}
		}
    }
}


/**
 * @brief 月集計値出力
 *
 * 基本的には、 `outfile_m*.es` という名前のファイルへの出力を担う。
 */
void Eeprintm(DAYTM *Daytm, SIMCONTL *Simc, int Nflout, FLOUT *flout, 
			  RMVLS *Rmvls,  int Nexs, EXSF *Exs,
			  double *Solmon, EQSYS *Eqsys, WDAT *Wdm)
{ 
	//日積算値出力の対象日か確認
	if (Daytm->ddpri)
	{
		char*  title = Simc->title;
		int    Mon   = Daytm->Mon;
		int    Day   = Daytm->Day;
		FLOUT* flo   = flout;

		for (int i = 0; i < Nflout; i++, flo++)
		{
			if (strcmp(flo->idn, PRTMWD) == 0)
			{
				// 気象データの出力  `outfile_mwd.es`
				Wdtmprint(flo->f, title, Mon, Day, Wdm, Nexs, Exs, Solmon);
			}
			else if (strcmp(flo->idn, PRTMNCOMP) == 0)
			{
				// 機器ごとのシミュレーション結果の出力 `outfile_mc.es`
				Compomonprt(flo->f, PRTMNCOMP, Simc, Mon, Day, Eqsys, Rmvls->Nrdpnl, Rmvls->Rdpnl);
			}
			else if (strcmp(flo->idn, PRTMNRM) == 0)
			{
				// 建物シミュレーション結果の出力 `outfile_mr.es`
				Rmmonprint(flo->f, PRTMNRM, Simc, Mon, Day, Rmvls->Nroom, Rmvls->Room);
			}
		}
    }
}


/**
 * @brief 月・時刻集計値出力
 */
void Eeprintmt(SIMCONTL *Simc, int Nflout, FLOUT *flout, EQSYS *Eqsys, int Nrdpnl, RDPNL *Rdpnl)
{ 
	FLOUT* flo   = flout;

	for (int i = 0; i < Nflout; i++, flo++)
	{
		if (strcmp(flo->idn, PRTMTCOMP) == 0)
		{
			// 機器ごとのシミュレーション結果（エネルギー消費量の月・時刻集計値） `outfile_mt.es`
			Compomtprt(flo->f, PRTMNCOMP, Simc, Eqsys, Nrdpnl, Rdpnl);
		}
	}
}
