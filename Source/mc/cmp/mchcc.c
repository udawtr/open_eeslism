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

/**
 * @file
 * @brief HCC 冷温水コイルの処理関数の定義
 */


#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "fesy.h"
#include "fnmcs.h"
#include "fnfio.h"
#include "fnlib.h"
#include "lib/u_psy.h"

//------ プライベート関数の宣言 ------//

#include "mc/eqptyp.h"

void _wcoil(char Air_SW, char Water_SW, char wet, double Gaet, double Gaeh,
	double xai, double Twi, ACS* Et, ACS* Ex, ACS* Ew);
double _Qcoils(ACS* Et, double Tai, double xai, double Twi);
double _Qcoill(ACS* Ex, double Tai, double xai, double Twi);
void _hstaircf(double Tw1, double Tw2, double* a, double* b);


//------ パブリック関数の実装 ------//


void Hccdwint(int Nhcc, HCC *Hcc)
{
	int i;
	
	for (i = 0; i < Nhcc; i++, Hcc++)
	{
		/* 乾きコイルと湿りコイルの判定 */
		if (Hcc->cat->eh > 1.0e-10)
			Hcc->wet = 'w';
		else
			Hcc->wet = 'd';

		/* 温度効率固定タイプと変動タイプの判定 */
		if (Hcc->cat->et > 0.0)
			Hcc->etype = 'e' ;
		else if (Hcc->cat->KA > 0.0)
			Hcc->etype = 'k' ;
		else
		{
			printf ("Hcc %s  Undefined Character et or KA\n",
				Hcc->name ) ;
			Hcc->etype = '-' ;
		}

		// 入口水温、入口空気絶対湿度を初期化
		//Hcc->Twin = 5. ;
		//Hcc->xain = FNXtr(25., 50. ) ;
	}
}

/* ------------------------------------------ */      
/*  特性式の係数  */

void Hcccfv(int Nhcc, HCC *Hcc)
{
	int i;
	
	for (i = 0; i < Nhcc; i++, Hcc++)
	{   
		Hcc->Ga = Hcc->Gw = 0.0 ;
		Hcc->et = Hcc->eh = 0.0 ;
		if (Hcc->cmp->control != OFF_SW)
		{
			ELOUT	*Eo;
			double	*cfin;
			char	AirSW, WaterSW ;

			Eo = Hcc->cmp->elouts;
			Hcc->Ga = Eo->G;
			Hcc->cGa = spcheat(Eo->fluid) * Hcc->Ga;

			AirSW = OFF_SW ;
			if ( Hcc->Ga > 0. ) AirSW = ON_SW ;

			Eo += 2 ;
			Hcc->Gw = Eo->G ;
			Hcc->cGw = spcheat(Eo->fluid) * Hcc->Gw ;

			WaterSW = OFF_SW ;
			if ( Hcc->Gw > 0. ) WaterSW = ON_SW ;

			//Eo -= 2 ;
			Eo = Hcc->cmp->elouts;

			if (Hcc->etype == 'e')
				Hcc->et = Hcc->cat->et;
			else if (Hcc->etype == 'k')
				Hcc->et = FNhccet ( Hcc->cGa, Hcc->cGw, Hcc->cat->KA ) ;

			//printf ( "<Hcccfv> et=%.2lf Ga=%.3lf Gw=%.3lf\n",
			//	Hcc->et, Hcc->Ga, Hcc->Gw ) ;
			Hcc->eh = Hcc->cat->eh;
            
			//printf ( "Air_SW=%c  Water_SW=%c\n", AirSW, WaterSW ) ;

			_wcoil(AirSW, WaterSW, Hcc->wet,  Hcc->Ga * Hcc->et,  Hcc->Ga * Hcc->eh, 
				Hcc->xain, Hcc->Twin, &Hcc->Et, &Hcc->Ex, &Hcc->Ew);
			

			// 空気の温度
			Eo->coeffo = Hcc->cGa;
			Eo->Co = -(Hcc->Et.C);
			cfin = Eo->coeffin;
			*cfin = Hcc->Et.t - Hcc->cGa;
			cfin++ ;
			*cfin = Hcc->Et.x;
			cfin++ ;
			*cfin = -(Hcc->Et.w);
			
			// 空気の絶対湿度
			Eo++;
			Eo->coeffo = Hcc->Ga;
			Eo->Co = -(Hcc->Ex.C);
			cfin = Eo->coeffin;
			*cfin = Hcc->Ex.t;
			cfin++ ;
			*cfin = Hcc->Ex.x - Hcc->Ga;
			cfin++ ;
			*cfin = -(Hcc->Ex.w);
			
			// 水の温度
			Eo++;
			Eo->coeffo = Hcc->cGw;
			Eo->Co = Hcc->Ew.C;
			cfin = Eo->coeffin;
			*cfin = -(Hcc->Ew.t);
			cfin++ ;
			*cfin = -(Hcc->Ew.x);
			cfin++ ;
			*cfin = Hcc->Ew.w - Hcc->cGw;
		}
	}
}
/* ------------------------------------------ */

/* 供給熱量の計算 */ 

void Hccdwreset(int Nhcc, HCC *Hcc, int *DWreset)
{
	int i, reset;
	double xain;
	double  Twin, Tdp;
	ELIN  *eli;
	
	for (i = 0; i < Nhcc; i++, Hcc++)
	{
		eli = Hcc->cmp->elins;
		eli++;
		xain = eli->sysvin;
		eli++;
		Twin = eli->sysvin;
		
		/*****
		printf("xxxx Hccdwreset xxxx  i=%d  wet=%c\n", i, Hcc->wet);
		/*****/
		
		reset = 0;
		if (Hcc->cat->eh > 1.0e-10)
		{
			Tdp = FNDp(FNPwx(xain));
			if (Hcc->wet == 'w' && Twin > Tdp)
			{
				Hcc->wet = 'd';
				reset = 1;
			}
			else if (Hcc->wet == 'd' && Twin < Tdp)
			{
				Hcc->wet  = 'w';
				reset = 1;
			}
			
			/*****
			printf("xxxx Hccdwreset xxxx    Twin=%lf Tdp=%lf wet=%c reset=%d\n",
			Twin, Tdp,Hcc->wet, reset);
			/*****/
			
			if (reset)
			{
				(*DWreset)++;
				Hcccfv(1, Hcc);
			}
		}
	}
}
/* ------------------------------------------ */

/* 供給熱量の計算 */ 

void Hccene(int Nhcc, HCC *Hcc)
{
	int i;
	ELIN  *eli;
	ELOUT *elo;
	
	for (i = 0; i < Nhcc; i++, Hcc++)
	{
		eli = Hcc->cmp->elins;
		Hcc->Tain = eli->sysvin;
		eli++;
		Hcc->xain = eli->sysvin;
		eli++;
		Hcc->Twin = eli->sysvin;
		
		if (Hcc->cmp->control != OFF_SW)
		{
			elo = Hcc->cmp->elouts;
			Hcc->Taout = elo->sysv ;
			Hcc->Qs = Hcc->cGa * (elo->sysv - Hcc->Tain);
			elo++;
			Hcc->Ql = CONST_RO * Hcc->Ga * (elo->sysv - Hcc->xain);
			elo++;
			Hcc->Twout = elo->sysv ;
			Hcc->Qt = Hcc->cGw * (elo->sysv - Hcc->Twin);
			
			/***************
			Hcc->Qs = Qcoils(&Hcc->Et, Hcc->Tain, Hcc->xain, Hcc->Twin);
			Hcc->Ql = Qcoill(&Hcc->Ex, Hcc->Tain, Hcc->xain, Hcc->Twin);
			Hcc->Qt = Hcc->Qs + Hcc->Ql;
			***************/
		}
		else
			Hcc->Qs = Hcc->Ql = Hcc->Qt = 0.0;
	}
}

/* ------------------------------------------ */

void hccprint(FILE *fo, int id, int Nhcc, HCC *Hcc)
{
	int i;
	ELOUT *el;
	
	switch (id)
	{
	case 0:
		if (Nhcc >0)
            fprintf(fo, "%s %d\n", HCCOIL_TYPE, Nhcc);
		for (i = 0; i < Nhcc; i++, Hcc++)
			fprintf(fo, " %s 1 16\n", Hcc->name);
		break;
		
	case 1:
		for (i = 0; i < Nhcc; i++, Hcc++)
		{
			fprintf(fo, "%s_ca c c %s_Ga m f %s_Ti t f %s_To t f %s_Qs q f\n",
				Hcc->name,  Hcc->name,  Hcc->name,  Hcc->name,  Hcc->name);
			fprintf(fo, "%s_cx c c %s_xi x f %s_xo x f %s_Ql q f\n",
				Hcc->name,  Hcc->name,  Hcc->name,  Hcc->name);
			fprintf(fo, "%s_cw c c %s_Gw m f %s_Twi t f %s_Two t f %s_Qt q f\n",
				Hcc->name,  Hcc->name,  Hcc->name,  Hcc->name,  Hcc->name);
			fprintf(fo, "%s_et m f %s_eh m f\n\n",
				Hcc->name,  Hcc->name);
		}
		break;
		
	default:
		for (i = 0; i < Nhcc; i++, Hcc++)
		{
            el = Hcc->cmp->elouts;
            fprintf(fo, "%c %6.4g %4.1lf %4.1lf %2.0lf ",
				el->control, Hcc->Ga, Hcc->Tain, el->sysv, Hcc->Qs);
            el++;
            fprintf(fo, "%c %5.3lf %5.3lf %2.0lf ",
				el->control, Hcc->xain, el->sysv, Hcc->Ql);
            el++;
            fprintf(fo, "%c %6.4g %4.1lf %4.1lf %2.0lf ",
				el->control, Hcc->Gw, Hcc->Twin, el->sysv, Hcc->Qt);
			
            fprintf(fo, "%6.4g %6.4g\n",
				Hcc->et, Hcc->eh);
		}
		break;
	}
} 

/* ------------------------------ */

/* 日積算値に関する処理 */   

void hccdyint(int Nhcc, HCC *Hcc)
{
	int i;
	
	for (i = 0; i < Nhcc; i++, Hcc++)
	{
		svdyint(&Hcc->Taidy);
		svdyint(&Hcc->xaidy);
		svdyint(&Hcc->Twidy);      
		qdyint(&Hcc->Qdys);
		qdyint(&Hcc->Qdyl);
		qdyint(&Hcc->Qdyt);
	}
}

void hccmonint(int Nhcc, HCC *Hcc)
{
	int i;
	
	for (i = 0; i < Nhcc; i++, Hcc++)
	{
		svdyint(&Hcc->mTaidy);
		svdyint(&Hcc->mxaidy);
		svdyint(&Hcc->mTwidy);      
		qdyint(&Hcc->mQdys);
		qdyint(&Hcc->mQdyl);
		qdyint(&Hcc->mQdyt);
	}
}


/**
 * @brief 日集計、月集計
 */
void hccday(int Mon, int Day, int ttmm, int Nhcc, HCC *Hcc, int Nday, int SimDayend)
{
	int i;
	
	for (i = 0; i < Nhcc; i++, Hcc++)
	{ 
		// 日集計
		svdaysum(ttmm, Hcc->cmp->control, Hcc->Tain, &Hcc->Taidy);
		svdaysum(ttmm, Hcc->cmp->control, Hcc->xain, &Hcc->xaidy);
		svdaysum(ttmm, Hcc->cmp->control, Hcc->Twin, &Hcc->Twidy);
		qdaysum(ttmm, Hcc->cmp->control, Hcc->Qs, &Hcc->Qdys);
		qdaysum(ttmm, Hcc->cmp->control, Hcc->Ql, &Hcc->Qdyl);
		qdaysum(ttmm, Hcc->cmp->control, Hcc->Qt, &Hcc->Qdyt);

		// 月集計
		svmonsum(Mon, Day, ttmm, Hcc->cmp->control, Hcc->Tain, &Hcc->mTaidy, Nday, SimDayend);
		svmonsum(Mon, Day, ttmm, Hcc->cmp->control, Hcc->xain, &Hcc->mxaidy, Nday, SimDayend);
		svmonsum(Mon, Day, ttmm, Hcc->cmp->control, Hcc->Twin, &Hcc->mTwidy, Nday, SimDayend);
		qmonsum(Mon, Day, ttmm, Hcc->cmp->control, Hcc->Qs, &Hcc->mQdys, Nday, SimDayend);
		qmonsum(Mon, Day, ttmm, Hcc->cmp->control, Hcc->Ql, &Hcc->mQdyl, Nday, SimDayend);
		qmonsum(Mon, Day, ttmm, Hcc->cmp->control, Hcc->Qt, &Hcc->mQdyt, Nday, SimDayend);
	}
}

void hccdyprt(FILE *fo, int id, int Nhcc, HCC *Hcc)
{
	int i;
	
	switch (id)
	{
	case 0:
		if (Nhcc >0)         
            fprintf(fo, "%s %d\n", HCCOIL_TYPE, Nhcc);
		for (i = 0; i < Nhcc; i++, Hcc++)
			fprintf(fo, "%s 4 42 14 14 14\n", Hcc->name);
		break;
		
	case 1:
		for (i = 0; i < Nhcc; i++, Hcc++)
		{
			fprintf(fo,"%s_Ht H d %s_T T f ", Hcc->name, Hcc->name);
			fprintf(fo,"%s_ttn h d %s_Tn t f %s_ttm h d %s_Tm t f\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);	 
			fprintf(fo, "%s_Hsh H d %s_Qsh Q f %s_Hsc H d %s_Qsc Q f\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);
			fprintf(fo, "%s_tsh h d %s_qsh q f %s_tsc h d %s_qsc q f\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);
			
			fprintf(fo,"%s_Hx H d %s_x X f ", Hcc->name, Hcc->name);
			fprintf(fo,"%s_txn h d %s_xn x f %s_txm h d %s_xm c f\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);	 
			fprintf(fo, "%s_Hlh H d %s_Qlh Q f %s_Hlc H d %s_Qlc Q f\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);
			fprintf(fo, "%s_tlh h d %s_qlh q f %s_tlc h d %s_qlc q f\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);
			
			fprintf(fo,"%s_Htw H d %s_Tw T f ", Hcc->name, Hcc->name);
			fprintf(fo,"%s_ttwn h d %s_Twn t f %s_ttwm h d %s_Twm t f\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);	 
			fprintf(fo, "%s_Hth H d %s_Qth Q f %s_Htc H d %s_Qtc Q f\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);
			fprintf(fo, "%s_tth h d %s_qth q f %s_ttc h d %s_qtc q f\n\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);
			
		}
		break;
		
	default:
		for (i = 0; i < Nhcc; i++, Hcc++)
		{
            fprintf(fo, "%1ld %3.1lf %1ld %3.1lf %1ld %3.1lf ", 
				Hcc->Taidy.hrs, Hcc->Taidy.m, 
				Hcc->Taidy.mntime, Hcc->Taidy.mn,
				Hcc->Taidy.mxtime, Hcc->Taidy.mx);
            fprintf(fo, "%1ld %3.1lf ", Hcc->Qdys.hhr, Hcc->Qdys.h);
            fprintf(fo, "%1ld %3.1lf ", Hcc->Qdys.chr, Hcc->Qdys.c);
            fprintf(fo, "%1ld %2.0lf ", Hcc->Qdys.hmxtime, Hcc->Qdys.hmx);
            fprintf(fo, "%1ld %2.0lf ", Hcc->Qdys.cmxtime, Hcc->Qdys.cmx);
			
            fprintf(fo, "%1ld %5.4lf %1ld %5.4lf %1ld %5.4lf ",
				Hcc->xaidy.hrs, Hcc->xaidy.m, 
				Hcc->xaidy.mntime, Hcc->xaidy.mn, 
				Hcc->xaidy.mxtime, Hcc->xaidy.mx);
            fprintf(fo, "%1ld %3.1lf ", Hcc->Qdyl.hhr, Hcc->Qdyl.h);
            fprintf(fo, "%1ld %3.1lf ", Hcc->Qdyl.chr, Hcc->Qdyl.c);
            fprintf(fo, "%1ld %2.0lf ", Hcc->Qdyl.hmxtime, Hcc->Qdyl.hmx);
            fprintf(fo, "%1ld %2.0lf ", Hcc->Qdyl.cmxtime, Hcc->Qdyl.cmx);
			
            fprintf(fo, "%1ld %3.1lf %1ld %3.1lf %1ld %3.1lf ", 
				Hcc->Twidy.hrs, Hcc->Twidy.m, 
				Hcc->Twidy.mntime,Hcc->Twidy.mn, 
				Hcc->Twidy.mxtime, Hcc->Twidy.mx);
            fprintf(fo, "%1ld %3.1lf ", Hcc->Qdyt.hhr, Hcc->Qdyt.h);
            fprintf(fo, "%1ld %3.1lf ", Hcc->Qdyt.chr, Hcc->Qdyt.c);
            fprintf(fo, "%1ld %2.0lf ", Hcc->Qdyt.hmxtime, Hcc->Qdyt.hmx);
            fprintf(fo, "%1ld %2.0lf\n", Hcc->Qdyt.cmxtime, Hcc->Qdyt.cmx);  
		}
		break;
	}
}

void hccmonprt(FILE *fo, int id, int Nhcc, HCC *Hcc)
{
	int i;
	
	switch (id)
	{
	case 0:
		if (Nhcc >0)         
            fprintf(fo, "%s %d\n", HCCOIL_TYPE, Nhcc);
		for (i = 0; i < Nhcc; i++, Hcc++)
			fprintf(fo, "%s 4 42 14 14 14\n", Hcc->name);
		break;
		
	case 1:
		for (i = 0; i < Nhcc; i++, Hcc++)
		{
			fprintf(fo,"%s_Ht H d %s_T T f ", Hcc->name, Hcc->name);
			fprintf(fo,"%s_ttn h d %s_Tn t f %s_ttm h d %s_Tm t f\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);	 
			fprintf(fo, "%s_Hsh H d %s_Qsh Q f %s_Hsc H d %s_Qsc Q f\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);
			fprintf(fo, "%s_tsh h d %s_qsh q f %s_tsc h d %s_qsc q f\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);
			
			fprintf(fo,"%s_Hx H d %s_x X f ", Hcc->name, Hcc->name);
			fprintf(fo,"%s_txn h d %s_xn x f %s_txm h d %s_xm c f\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);	 
			fprintf(fo, "%s_Hlh H d %s_Qlh Q f %s_Hlc H d %s_Qlc Q f\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);
			fprintf(fo, "%s_tlh h d %s_qlh q f %s_tlc h d %s_qlc q f\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);
			
			fprintf(fo,"%s_Htw H d %s_Tw T f ", Hcc->name, Hcc->name);
			fprintf(fo,"%s_ttwn h d %s_Twn t f %s_ttwm h d %s_Twm t f\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);	 
			fprintf(fo, "%s_Hth H d %s_Qth Q f %s_Htc H d %s_Qtc Q f\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);
			fprintf(fo, "%s_tth h d %s_qth q f %s_ttc h d %s_qtc q f\n\n",
				Hcc->name, Hcc->name, Hcc->name, Hcc->name);
			
		}
		break;
		
	default:
		for (i = 0; i < Nhcc; i++, Hcc++)
		{
            fprintf(fo, "%1ld %3.1lf %1ld %3.1lf %1ld %3.1lf ", 
				Hcc->mTaidy.hrs, Hcc->mTaidy.m, 
				Hcc->mTaidy.mntime, Hcc->mTaidy.mn,
				Hcc->mTaidy.mxtime, Hcc->mTaidy.mx);
            fprintf(fo, "%1ld %3.1lf ", Hcc->mQdys.hhr, Hcc->mQdys.h);
            fprintf(fo, "%1ld %3.1lf ", Hcc->mQdys.chr, Hcc->mQdys.c);
            fprintf(fo, "%1ld %2.0lf ", Hcc->mQdys.hmxtime, Hcc->mQdys.hmx);
            fprintf(fo, "%1ld %2.0lf ", Hcc->mQdys.cmxtime, Hcc->mQdys.cmx);
			
            fprintf(fo, "%1ld %5.4lf %1ld %5.4lf %1ld %5.4lf ",
				Hcc->mxaidy.hrs, Hcc->mxaidy.m, 
				Hcc->mxaidy.mntime, Hcc->mxaidy.mn, 
				Hcc->mxaidy.mxtime, Hcc->mxaidy.mx);
            fprintf(fo, "%1ld %3.1lf ", Hcc->mQdyl.hhr, Hcc->mQdyl.h);
            fprintf(fo, "%1ld %3.1lf ", Hcc->mQdyl.chr, Hcc->mQdyl.c);
            fprintf(fo, "%1ld %2.0lf ", Hcc->mQdyl.hmxtime, Hcc->mQdyl.hmx);
            fprintf(fo, "%1ld %2.0lf ", Hcc->mQdyl.cmxtime, Hcc->mQdyl.cmx);
			
            fprintf(fo, "%1ld %3.1lf %1ld %3.1lf %1ld %3.1lf ", 
				Hcc->mTwidy.hrs, Hcc->mTwidy.m, 
				Hcc->mTwidy.mntime,Hcc->mTwidy.mn, 
				Hcc->mTwidy.mxtime, Hcc->mTwidy.mx);
            fprintf(fo, "%1ld %3.1lf ", Hcc->mQdyt.hhr, Hcc->mQdyt.h);
            fprintf(fo, "%1ld %3.1lf ", Hcc->mQdyt.chr, Hcc->mQdyt.c);
            fprintf(fo, "%1ld %2.0lf ", Hcc->mQdyt.hmxtime, Hcc->mQdyt.hmx);
            fprintf(fo, "%1ld %2.0lf\n", Hcc->mQdyt.cmxtime, Hcc->mQdyt.cmx);  
		}
		break;
	}
}

/* 温水コイルの温度効率計算関数　計算モデルは向流コイル */
double	FNhccet ( double Wa, double Ww, double KA )
{
	double	NTU, B, Ws, Wl, exB, C ;

	//Ws = min ( Wa, Ww ) ;
	//Wl = max ( Wa, Ww ) ;
	Ws = Wa ;
	Wl = Ww ;

	NTU = KA / Ws ;
	C = Ws / Wl ;
	B = ( 1.0 - C ) * NTU ;

	if ( fabs ( Ws - Wl ) < 1.0e-5 )
		return ( NTU / ( 1.0 + NTU )) ;
	else
	{
		if (( exB = exp ( - B )) == HUGE_VAL )
		{
			//printf ( "B=%lf  ----  Wa=%lf >> Ww=%lf\n", B, Ws, Wl ) ;
			return ( 1. / C ) ;
		}
		else
			return (( 1.0 - exB ) / ( 1.0 - C * exB )) ;
	}
}


void hccxprint(int Nhcc, HCC* Hcc)
{
	int i;
	ACS   E;
	ELOUT* el;

	if (Nhcc > 0)
	{
		printf("%s N=%d\n", HCCOIL_TYPE, Nhcc);

		for (i = 0; i < Nhcc; i++, Hcc++)
		{
			printf("[%d] %-10s et=%5.3lf eh=%5.3lf\n", i, Hcc->name, Hcc->et, Hcc->eh);
			E = Hcc->Et;
			printf("     Et w=%7.3lf t=%7.3lf x=%7.3lf C=%7.3lf\n", E.w, E.t, E.x, E.C);
			E = Hcc->Ex;
			printf("     Et w=%7.3lf t=%7.3lf x=%7.3lf C=%7.3lf\n", E.w, E.t, E.x, E.C);
			E = Hcc->Ew;
			printf("     Et w=%7.3lf t=%7.3lf x=%7.3lf C=%7.3lf\n", E.w, E.t, E.x, E.C);
			el = Hcc->cmp->elouts;
			printf("     Tain=%5.2lf  Taout=%5.2lf  Qs=%4.0lf\n", Hcc->Tain, el->sysv, Hcc->Qs);
			el++;
			printf("     xain=%5.4lf  xaout=%5.4lf  Qs=%4.0lf\n", Hcc->xain, el->sysv, Hcc->Ql);
			el++;
			printf("     Wwin=%5.2lf  Twout=%5.4lf  Qt=%4.0lf\n", Hcc->Twin, el->sysv, Hcc->Qt);
		}
	}
}

/************ #include "cmpref.h"
*************/
/*  冷媒コイルの処理熱量計算用係数   */

/********************
void	dxcoil ( char wet, HPCH *Rf, double Toa, double Gaet, double Gaeh,
				double Tai, double xai, ACS *Et, ACS *Ex )
{ 
	double  EGex, cs, ae,be, Do,Dt,Dx,Dc,Ee;
	EGex= Rf->eex * ca *Rf->Gex;
	
	if (Rf->mode == 'C')
		_Compca(Rf->e, Rf->d, EGex, Rf->Teo, Toa, &Rf->Ho, &Rf->He);
	else
		_Compha(Rf->e, Rf->d, EGex, Rf->Tco, Toa, &Rf->Ho, &Rf->He);
	
	if (wet == 'd')
	{
		Do= ca*Gaet + Rf->He;
		Dt= ca*Gaet/Do;
		Dc= Rf->Ho /Do;
		Et->w = Et->x =0.0;
		Et->t = ca*Gaet*(1.0-Dt);
		Et->C = -ca*Gaet*Dc;
		Ex->w = Ex->t = Ex->x = Ex->C =0.0; }
	else
	{
		hstaircf(Rf->Teo[0]+3.0, Rf->Teo[1],&ae,&be);
		cs=ca+cv*xai;
		Do= Gaeh*be + Rf->He;
		Dt= Gaeh*cs/Do;
		Dx= Gaeh*ro/Do;
		Dc= (Rf->Ho - Gaeh*ae)/Do;
		
		Ee= (Gaeh*be -Gaet*ca)/ro;
		Et->w = 0.0;
		Et->t = ca*Gaet*(1.0-Dt);
		Et->x = -ca*Gaet*Dx;
		Et->C = -ca*Gaet*Dc;
		
		Ex->w = 0.0;
		Ex->t = (Gaeh*cs-Gaet*ca)/ro-Ee*Dt;
		Ex->x = Gaeh-Ee*Dx; 
		Ex->C = -(Gaeh*ae/ro + Ee*Dc); }
}
/**********************************/

/* ------------------------------------------ */



//------ プライベート関数の実装 ------//


/*  冷温水コイルの処理熱量計算用係数   */


void _wcoil(char Air_SW, char Water_SW, char wet, double Gaet, double Gaeh,
		   double xai, double Twi, ACS *Et, ACS *Ex, ACS *Ew)
{
	double  aw, bw, cs;
	if (wet == 'd' || Water_SW == OFF_SW || Air_SW == OFF_SW) 
	{
		// 片側系統が停止していたときに対応するように修正
		// Satoh Debug 2009/1/9
		if ( Water_SW != OFF_SW )
		{
			Et->w = Et->t = CONST_CA*Gaet;
			Et->x = Et->C =0.0;
		}
		else
			Et->w = Et->t = Et->x = Et->C = 0.0;
			
		Ex->w = Ex->t = Ex->x = Ex->C = 0.0; 

		if ( Air_SW != OFF_SW )
		{
			Ew->w = Ew->t = Gaet*CONST_CA;
			Ew->x = Ew->C = 0.0;
		}
		else
			Ew->w = Ew->t = Ew->x = Ew->C = 0.0;
	}
	else
	{
		_hstaircf(Twi, Twi+5.0, &aw, &bw);
		cs=CONST_CA+CONST_CV*xai;
		Et->w = Et->t = CONST_CA*Gaet;
		Et->x = Et->C =0.0;
		
		Ex->w = (Gaeh*bw-Gaet*CONST_CA)/CONST_RO;
		Ex->t = (Gaeh*cs-Gaet*CONST_CA)/CONST_RO;
		Ex->x = Gaeh;
		Ex->C = -Gaeh*aw/CONST_RO; 
		
		Ew->w = Gaeh*bw;
		Ew->t = Gaeh*cs;
		Ew->x = Gaeh*CONST_RO;
		Ew->C = -Gaeh*aw;
	}
}

/* ------------------------------------------ */

/*  コイル供給顕熱  */

double _Qcoils(ACS *Et, double Tai, double xai, double Twi)
{  
	return (Et->w * Twi - Et->t * Tai - Et->x * xai - Et->C);
}

/* ------------------------------------------ */

/*  コイル供給潜熱  */

double _Qcoill(ACS *Ex, double Tai, double xai, double Twi)
{ 
	return (CONST_RO * (Ex->w * Twi - Ex->t * Tai - Ex->x * xai - Ex->C));
}

/* ------------------------------------------ */

/*  水温に等しい飽和空気のエンタルピの一次式近似の係数 */

void _hstaircf(double Tw1, double Tw2, double *a, double *b)
{
	double  h1, h2;
	
	h1 = FNH((double) Tw1, FNXtr((double) Tw1, 100.0));
	h2 = FNH((double) Tw2, FNXtr((double) Tw2, 100.0));
	*b = (h2-h1)/(Tw2-Tw1);
	*a = h1 - *b * Tw1;
	
	/* -------------
    printf("== hstaircf  Tw1,Tw2=%lf  %lf    a=%lf   b=%lf\n",Tw1,Tw2,*a,*b);
	---------------- */
}
