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

/*  refas.c */

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include "fesy.h"
#include "fnmcs.h"
#include "fnesy.h"
#include "fnfio.h"
#include "fnlib.h"
#include "winerror.h"
#include <stdio.h>
#include "esize.h"
#include "lib/u_psy.h"
#include <math.h>

/**
 * @file
 * @brief REFA 圧縮式冷凍機の処理関数の定義
 */

//For RFCMP, REFA
#include "mc/eqptyp.h"

//------ プライベート関数の宣言 ------//

void _Refcmpdat(FILE* frf, int* Nrfcmp, RFCMP* Rfcmp);
void _Compca(double* e, double* d, double EGex, double* Teo, double Ta,
	double* Ho, double* He);
void _Compha(double* e, double* d, double EGex, double* Tco, double Ta,
	double* Ho, double* He);
double _Refpow(REFA* Rf, double QP);


//------ パブリック関数の実装 ------//


/*  冷凍機／ヒ－トポンプの圧縮機特性設定   */

void Refaint(int Nrefa, REFA *Refa, WDAT *Wd, int Ncompnt, COMPNT *Compnt)
{
	RFCMP	*Cmp;
	double	Teo=0.0, Tco=0.0, cGex=0.0,  Qeo=0.0, Qco=0.0;
	double  Qes=0.0, Qcs=0.0, Ws=0.0, ke=0.0, kc=0.0, kw=0.0, E=0.0;
	int		i, k, m;
	//char	Err[SCHAR] ;
	
	for (k = 0; k < Nrefa; k++, Refa++)
	{   
		Refa->Ta = &Wd->T;
		
		if (Refa->cat->awtyp != 'a')
			printf("Refcfi   awtyp=%c\n",Refa->cat->awtyp); 
		if ( Refa->cmp->roomname != NULL )
		{
			Refa->room = roomptr ( Refa->cmp->roomname, Ncompnt, Compnt ) ;
			printf ( "RefaRoom=%s\n", Refa->cmp->roomname ) ;
		}
		
		/*****************************
		sprintf ( Err, "Name=%s  Ph=%.4g", Refa->cmp->name, Refa->cat->Ph ) ;
		if ( Refa->cat->Ph < 0.0 )
			Eprint ( "Refaint", Err ) ;
			************************************/

		for (m = 0; m < Refa->cat->Nmode; m++)
		{
			if (Refa->cat->mode[m] == COOLING_SW)
			{
				cGex = CONST_CA * Refa->cat->cool->Gex;
				E=(1.0- Refa->cat->cool->eo)/ Refa->cat->cool->eo; 
				Qeo= Refa->cat->cool->Qo,  Qco= Refa->cat->cool->Qex;
				Teo= Qeo * E /(CONST_CW * Refa->cat->cool->Go) + Refa->cat->cool->Two;
				Tco= Qco/(Refa->cat->cool->eex * cGex) + Refa->cat->cool->Tex;             
			}       
			else if (Refa->cat->mode[m] == HEATING_SW)
			{ 
				cGex = CONST_CA * Refa->cat->heat->Gex;
				E=(1.0- Refa->cat->heat->eo)/ Refa->cat->heat->eo;
				Qeo= Refa->cat->heat->Qex;
				Qco= Refa->cat->heat->Qo;
				Tco= Qco * E /(CONST_CW * Refa->cat->heat->Go) + Refa->cat->heat->Two;
				Teo= Qeo/(Refa->cat->heat->eex * cGex) + Refa->cat->heat->Tex;      
			}
			
			Cmp = Refa->cat->rfc;
			Qes= Cmp->e[0] + Cmp->e[1]*Teo + Cmp->e[2]*Tco + Cmp->e[3]*Teo*Tco;
			Qcs= Cmp->d[0] + Cmp->d[1]*Teo + Cmp->d[2]*Tco + Cmp->d[3]*Teo*Tco;
			Ws= Cmp->w[0] + Cmp->w[1]*Teo + Cmp->w[2]*Tco + Cmp->w[3]*Teo*Tco;
			ke = Qeo /Qes;
			kc = Qco /Qcs; 
			if(Refa->cat->mode[m] == COOLING_SW)
				kw = Refa->cat->cool->Wo /Ws;
			else if(Refa->cat->mode[m] == HEATING_SW)
				kw = Refa->cat->heat->Wo /Ws;
			
			
				/**************************
				printf("Teo=%lf  Tco=%lf  Qes=%lf  Qcs=%lf   Ws=%lf\n",Teo,Tco,Qes,Qcs,Ws);
				printf("ke=%lf  kc=%lf   kw=%lf\n",ke,kc,kw);
			********************************************/
			if (Refa->cat->mode[m] == COOLING_SW)
			{
				for (i=0; i<4; i++)
				{ 
					Refa->c_e[i] = ke * Cmp->e[i];
					Refa->c_d[i] = kc * Cmp->d[i];
					Refa->c_w[i] = kw * Cmp->w[i];
				}
			}
			else if (Refa->cat->mode[m] == HEATING_SW)
			{
				for (i=0; i<4; i++)
				{ 
					Refa->h_e[i] = ke * Cmp->e[i];
					Refa->h_d[i] = kc * Cmp->d[i];
					Refa->h_w[i] = kw * Cmp->w[i];
				} 
			}
		}
		if (Refa->cat->Nmode == 1)
			Refa->chmode = Refa->cat->mode[0];
	}
}
/* -------------------------------------------- */

/*  冷凍機／ヒ－トポンプのシステム方程式の係数  */


void Refacfv(int Nrefa, REFA *Refa)
{
	ELOUT	*Eo;
	double	cG;
	int		i, err;
	char	s[SCHAR] ;
	
	for (i = 0; i < Nrefa; i++, Refa++)
	{
	/*****
	printf("xxx Refacfv xxx  i=%d chmode=%c cmp->contro=%c Eo->contro=%c E->sysld=%c\n", 
	i, Refa->chmode, Refa->cmp->control, Refa->cmp->elouts->control,
	Refa->cmp->elouts->sysld);
		*****/
		
		if (Refa->cmp->control != OFF_SW)
		{
			Eo = Refa->cmp->elouts;
			
			Refa->cG = cG = spcheat(Eo->fluid) * Eo->G;   
			
			Eo->coeffo = cG;
			
			/****if ( Eo->control == ON_SW) *****/
			if ( Eo->control != OFF_SW)
			{
				if (Eo->sysld == 'y')
				{
					Eo->Co = 0.0;
					*(Eo->coeffin) = -cG;
				}
				else
				{
					refacoeff(Refa, &err);
					if (err == 0)
					{
						Eo->Co = Refa->Do;
						*(Eo->coeffin) = Refa->D1 - cG; 
					}
					else
					{
						sprintf( s, "xxxxx refacoeff xxx stop xx  %s chmode=%c  monitor=%s",
							Refa->name, Refa->chmode, Refa->cmp->elouts->emonitr->cmp->name);
						Eprint ( "<Refacfv>", s ) ;

						preexit ( ) ;
						exit(EXIT_REFA);
					}
				}
			}			 
		}
	}
}
/* ------------------------------------------------------------- */

/*    冷凍機／ヒ－トポンプの能力特性一次式の係数  */

void refacoeff(REFA *Refa, int *err)
{
	double E=0.0, EGex=0.0, Px=0.0;
	
	*err = 0;
	
	if (Refa->chmode == COOLING_SW)
	{
		if (Refa->cat->cool != NULL)
		{
			EGex = Refa->cat->cool->eex * CONST_CA * Refa->cat->cool->Gex ;
			_Compca(Refa->c_e, Refa->c_d, EGex, Refa->cat->rfc->Teo, *Refa->Ta, 
				&Refa->Ho, &Refa->He);
			E = Refa->cG * Refa->cat->cool->eo;
		}
		else 
			*err = 1;
	}
	else if (Refa->chmode == HEATING_SW)
	{
		if (Refa->cat->heat != NULL)
		{
			EGex = Refa->cat->heat->eex * CONST_CA * Refa->cat->heat->Gex ;	
			_Compha(Refa->h_e, Refa->h_d, EGex, Refa->cat->rfc->Tco, *Refa->Ta, 
				&Refa->Ho, &Refa->He);
			E = Refa->cG * Refa->cat->heat->eo;
		}
		else
			*err = 1;
	}
	
	/***************** 
	printf("xxx Refacfv xxx   EGex=%lf Ho=%lf  Hx=%lf\n",
	EGex, Refa->Ho, Refa->He);
	*******************/
	
	if (*err == 0)
	{
		Px= E/(E + Refa->He);
		Refa->Do = Refa->Ho * Px;
		Refa->D1 = Refa->He * Px;
	}
	else
	{
		Refa->Do = 0.0;
		Refa->D1 = 0.0;
	}
}

/* ------------------------------------------------------------- */

/*   冷却熱量/加熱量、エネルギーの計算 */

void Refaene(int Nrefa, REFA *Refa, int *LDreset)
{
	int i, err, reset;
	double  Emax;
	ELOUT *Eo;
	
	for (i = 0; i < Nrefa; i++, Refa++)
	{
		Refa->Tin = Refa->cmp->elins->sysvin;
		Eo = Refa->cmp->elouts;
		Refa->E = 0.0;
		
		/*****
		printf("xxx Refaene xxx  i=%d chmode=%c cmp->contro=%c Eo->contro=%c E->sysld=%c\n", 
		i, Refa->chmode, Refa->cmp->control, Refa->cmp->elouts->control,
		Refa->cmp->elouts->sysld);
		*****/
		
		if (Eo->control != OFF_SW)
		{
		/*** Refa->Q = Refa->Do - Refa->D1 * Refa->Tin;
			************/
			Refa->Ph = Refa->cat->Ph;
			Refa->Q = Refa->cG * (Eo->sysv - Refa->Tin);
			
			if (Eo->sysld == 'n')
			{
				Refa->Qmax = Refa->Q;
				
				if (Refa->cat->Nmode > 0)
					Refa->E = _Refpow(Refa, Refa->Q) / Refa->cat->rfc->Meff;
				
			}
			else
			{
			/***** printf("xxx Refaene xxx  i=%d  Refa->chmode=%c\n",
				i, Refa->chmode); *****/
				
				reset = chswreset(Refa->Q, Refa->chmode, Eo);
				
				/***** printf("xxx Refaene xxx  cw-reset=%d\n", reset);
				*****/
				
				if (reset)
				{
					(*LDreset)++;
					Refa->cmp->control = OFF_SW;
				}
				else
				{
					if (Refa->cat->Nmode > 0)
					{
						refacoeff(Refa, &err); 		  		 
						
						if (err == 0)
						{
							Refa->Qmax =  Refa->Do - Refa->D1 * Refa->Tin;
							Emax = _Refpow(Refa, Refa->Qmax) / Refa->cat->rfc->Meff;	 
							Refa->E = (Refa->Q / Refa->Qmax) * Emax;
							
							if (Refa->cat->unlimcap == 'n')
								reset = maxcapreset(Refa->Q, Refa->Qmax, Refa->chmode, Eo);
							if (reset)
							{
								Refacfv(1, Refa);
								(*LDreset)++;
							}
						}
					}
					else
						Refa->Qmax = Refa->Q;
					
				}
			}
			/*****   
			printf("xxx Refaene xxx i=%d Do=%lf D1=%lf Q=%lf Qmax=%lf Emax=%lf E=%lf\n", 
			i, Refa->Do, Refa->D1, Refa->Q, Refa->Qmax, 
			Emax, Refa->E);
			*****/
		}
		else
			Refa->Q = Refa->Ph = 0.0;      
	}
}

void Refaene2(int Nrefa, REFA *Refa)
{
	int  i ;
	
	for ( i = 0; i < Nrefa; i++, Refa++ )
	{
		if ( Refa->room != NULL )
		{
			Refa->room->Qeqp += ( Refa->Q * Refa->cmp->eqpeff ) ;
			
			/****************
			printf ( "Roomname=%s  Q=%lf Qeqp=%lf\n", Refa->room->name,
			Refa->Q, Refa->room->Qeqp ) ;
			*******************/
		}
	}
}

/* ------------------------------------------------------------- */

/* 負荷計算指定時の設定値のポインター */

int refaldptr(char *load, char **key, REFA *Refa, VPTR *vptr)
{
	int err = 0;
	
	if (strcmp(key[1], "Tout") == 0)
	{
		vptr->ptr = &Refa->Toset;
		vptr->type = VAL_CTYPE;
		Refa->load = load;
	}
	else
		err = 1;
	return err;
}
/* ------------------------------------------------------------- */

/* 冷暖運転切換のポインター */

int refaswptr(char **key, REFA *Refa, VPTR *vptr)
{
	int err = 0;
	
	if (strcmp(key[1], "chmode") == 0)
	{
		vptr->ptr = &Refa->chmode;
		vptr->type = SW_CTYPE;
		/*****
		printf("xxxxx refaswptr   Refa->chmode=%c\n", Refa->chmode);
		*****/
	}
	else
		err = 1;
	return err;
}

/* --------------------------- */

/* 負荷計算指定時のスケジュール設定 */

void refaldschd(REFA *Refa)
{
	ELOUT *Eo;
	
	
	if (Refa->load != NULL)
	{
		Eo = Refa->cmp->elouts; 
		if (Eo->control != OFF_SW)
		{
			if (Refa->Toset > TEMPLIMIT)
			{
				Eo->control = LOAD_SW;
				Eo->sysv = Refa->Toset;
			}
			else
				Eo->control = OFF_SW;
		}	 
	}
}
/* --------------------------- */

void refaprint(FILE *fo, int id, int Nrefa, REFA *Refa)
{
	int i;
	
	switch (id)
	{
	case 0:
		if (Nrefa > 0)       
            fprintf(fo, "%s %d\n", REFACOMP_TYPE, Nrefa);
		for (i = 0; i < Nrefa; i++, Refa++)
			fprintf(fo, " %s 1 7\n",Refa->name); 
		break;
		
	case 1:
		for (i = 0; i < Nrefa; i++, Refa++)
		{
			fprintf(fo,"%s_c c c %s_G m f %s_Ti t f %s_To t f ",
				Refa->name, Refa->name, Refa->name, Refa->name);
			fprintf(fo,"%s_Q q f  %s_E e f %s_P e f\n",
				Refa->name, Refa->name, Refa->name);
		}
		break;	    
		
	default:	 
		for (i = 0; i < Nrefa; i++, Refa++)
            fprintf(fo, "%c %6.4g %4.1lf %4.1lf %3.0lf %3.0lf %2.0lf\n",
			Refa->cmp->elouts->control, Refa->cmp->elouts->G,
			Refa->Tin, Refa->cmp->elouts->sysv, Refa->Q, Refa->E, Refa->Ph);
		break;
	}
}

/* --------------------------- */

/* 日積算値に関する処理 */

void refadyint(int Nrefa, REFA *Refa)
{
	int i;
	
	for (i = 0; i < Nrefa; i++, Refa++)
	{
		svdyint(&Refa->Tidy);
		qdyint(&Refa->Qdy);
		edyint(&Refa->Edy);
		edyint(&Refa->Phdy);
	}
}

void refamonint(int Nrefa, REFA *Refa)
{
	int i;
	
	for (i = 0; i < Nrefa; i++, Refa++)
	{
		svdyint(&Refa->mTidy);
		qdyint(&Refa->mQdy);
		edyint(&Refa->mEdy);
		edyint(&Refa->mPhdy);
	}
}



/**
 * @brief 日集計、月集計
 */
void refaday(int Mon, int Day, int ttmm, int Nrefa, REFA *Refa, int Nday, int SimDayend)
{
	int i;
	int Mo, tt ;
	
	Mo = Mon - 1 ;
	tt = ConvertHour(ttmm) ;
	for (i = 0; i < Nrefa; i++, Refa++)
	{
		// 日集計
		svdaysum(ttmm, Refa->cmp->control, Refa->Tin, &Refa->Tidy);
		qdaysum(ttmm, Refa->cmp->control, Refa->Q, &Refa->Qdy);
		edaysum(ttmm, Refa->cmp->control, Refa->E, &Refa->Edy);
		edaysum(ttmm, Refa->cmp->control, Refa->Ph, &Refa->Phdy);

		// 月集計
		svmonsum(Mon, Day, ttmm, Refa->cmp->control, Refa->Tin, &Refa->mTidy, Nday, SimDayend);
		qmonsum(Mon, Day, ttmm, Refa->cmp->control, Refa->Q, &Refa->mQdy, Nday, SimDayend);
		emonsum(Mon, Day, ttmm, Refa->cmp->control, Refa->E, &Refa->mEdy, Nday, SimDayend);
		emonsum(Mon, Day, ttmm, Refa->cmp->control, Refa->Ph, &Refa->mPhdy, Nday, SimDayend);

		// 月・時刻のクロス集計
		emtsum(Mon, Day, ttmm, Refa->cmp->control, Refa->E, &Refa->mtEdy[Mo][tt]);
		emtsum(Mon, Day, ttmm, Refa->cmp->control, Refa->E, &Refa->mtPhdy[Mo][tt]);
	}
}

void refadyprt(FILE *fo, int id, int Nrefa, REFA *Refa)
{
	int i;
	
	
	switch (id)
	{
	case 0:
		if (Nrefa > 0)       
            fprintf(fo, "%s %d\n", REFACOMP_TYPE, Nrefa );
		for (i = 0; i < Nrefa; i++, Refa++)
			fprintf(fo," %s 1 22\n", Refa->name);
		break;
		
	case 1:
		for (i = 0; i < Nrefa; i++, Refa++)
		{
			fprintf(fo,"%s_Ht H d %s_T T f ", Refa->name, Refa->name);
			fprintf(fo,"%s_ttn h d %s_Tn t f %s_ttm h d %s_Tm t f\n",
				Refa->name, Refa->name, Refa->name, Refa->name);
			fprintf(fo, "%s_Hh H d %s_Qh Q f %s_Hc H d %s_Qc Q f\n",
				Refa->name, Refa->name, Refa->name, Refa->name);
			fprintf(fo, "%s_th h d %s_qh q f %s_tc h d %s_qc q f\n",
				Refa->name, Refa->name, Refa->name, Refa->name);
			fprintf(fo, "%s_He H d %s_E E f %s_te h d %s_Em e f\n",
				Refa->name, Refa->name, Refa->name, Refa->name);
			fprintf(fo, "%s_Hp H d %s_P E f %s_tp h d %s_Pm e f\n\n",
				Refa->name, Refa->name, Refa->name, Refa->name);
		}
		break;
		
	default:
		for (i = 0; i < Nrefa; i++, Refa++)
		{
            fprintf(fo, "%1ld %3.1lf %1ld %3.1lf %1ld %3.1lf ", 
				Refa->Tidy.hrs, Refa->Tidy.m, 
				Refa->Tidy.mntime, Refa->Tidy.mn, 
				Refa->Tidy.mxtime, Refa->Tidy.mx);
			
            fprintf(fo, "%1ld %3.1lf ", Refa->Qdy.hhr, Refa->Qdy.h);
            fprintf(fo, "%1ld %3.1lf ", Refa->Qdy.chr, Refa->Qdy.c);
            fprintf(fo, "%1ld %2.0lf ", Refa->Qdy.hmxtime, Refa->Qdy.hmx);
            fprintf(fo, "%1ld %2.0lf ", Refa->Qdy.cmxtime, Refa->Qdy.cmx);
			
            fprintf(fo, "%1ld %3.1lf ", Refa->Edy.hrs, Refa->Edy.d);
            fprintf(fo, "%1ld %2.0lf ", Refa->Edy.mxtime, Refa->Edy.mx);
			
            fprintf(fo, "%1ld %3.1lf ", Refa->Phdy.hrs, Refa->Phdy.d);     
            fprintf(fo, "%1ld %2.0lf\n", Refa->Phdy.mxtime, Refa->Phdy.mx); 
		}
		break;
	}
}

void refamonprt(FILE *fo, int id, int Nrefa, REFA *Refa)
{
	int i;
	
	
	switch (id)
	{
	case 0:
		if (Nrefa > 0)       
            fprintf(fo, "%s %d\n", REFACOMP_TYPE, Nrefa );
		for (i = 0; i < Nrefa; i++, Refa++)
			fprintf(fo," %s 1 22\n", Refa->name);
		break;
		
	case 1:
		for (i = 0; i < Nrefa; i++, Refa++)
		{
			fprintf(fo,"%s_Ht H d %s_T T f ", Refa->name, Refa->name);
			fprintf(fo,"%s_ttn h d %s_Tn t f %s_ttm h d %s_Tm t f\n",
				Refa->name, Refa->name, Refa->name, Refa->name);
			fprintf(fo, "%s_Hh H d %s_Qh Q f %s_Hc H d %s_Qc Q f\n",
				Refa->name, Refa->name, Refa->name, Refa->name);
			fprintf(fo, "%s_th h d %s_qh q f %s_tc h d %s_qc q f\n",
				Refa->name, Refa->name, Refa->name, Refa->name);
			fprintf(fo, "%s_He H d %s_E E f %s_te h d %s_Em e f\n",
				Refa->name, Refa->name, Refa->name, Refa->name);
			fprintf(fo, "%s_Hp H d %s_P E f %s_tp h d %s_Pm e f\n\n",
				Refa->name, Refa->name, Refa->name, Refa->name);
		}
		break;
		
	default:
		for (i = 0; i < Nrefa; i++, Refa++)
		{
            fprintf(fo, "%1ld %3.1lf %1ld %3.1lf %1ld %3.1lf ", 
				Refa->mTidy.hrs, Refa->mTidy.m, 
				Refa->mTidy.mntime, Refa->mTidy.mn, 
				Refa->mTidy.mxtime, Refa->mTidy.mx);
			
            fprintf(fo, "%1ld %3.1lf ", Refa->mQdy.hhr, Refa->mQdy.h);
            fprintf(fo, "%1ld %3.1lf ", Refa->mQdy.chr, Refa->mQdy.c);
            fprintf(fo, "%1ld %2.0lf ", Refa->mQdy.hmxtime, Refa->mQdy.hmx);
            fprintf(fo, "%1ld %2.0lf ", Refa->mQdy.cmxtime, Refa->mQdy.cmx);
			
            fprintf(fo, "%1ld %3.1lf ", Refa->mEdy.hrs, Refa->mEdy.d);
            fprintf(fo, "%1ld %2.0lf ", Refa->mEdy.mxtime, Refa->mEdy.mx);
			
            fprintf(fo, "%1ld %3.1lf ", Refa->mPhdy.hrs, Refa->mPhdy.d);     
            fprintf(fo, "%1ld %2.0lf\n", Refa->mPhdy.mxtime, Refa->mPhdy.mx); 
		}
		break;
	}
}

void refamtprt(FILE *fo, int id, int Nrefa, REFA *Refa, int Mo, int tt)
{
	int i;
	
	switch (id)
	{
	case 0:
		if (Nrefa > 0)
            fprintf(fo, "%s %d\n", REFACOMP_TYPE, Nrefa);
		for (i = 0; i < Nrefa; i++, Refa++)
			fprintf(fo, " %s 1 2\n", Refa->name);
		break;
		
	case 1:
		for (i = 0; i < Nrefa; i++, Refa++)
		{	 
			fprintf(fo,"%s_E E f %s_Ph E f \n", Refa->name, Refa->name);
		}
		break;
		
	default:
		for (i = 0; i < Nrefa; i++, Refa++)
		{
			fprintf(fo, " %.2lf %.2lf\n", Refa->mtEdy[Mo-1][tt-1].d * cff_kWh, Refa->mtPhdy[Mo-1][tt-1].d * cff_kWh);
		}
		break;
	}
}

//@brief 検討用出力
void refaxprint(int Nrefa, REFA* Refa)
{
	int i;

	if (Nrefa > 0)
	{
		printf("%s N=%d\n", REFACOMP_TYPE, Nrefa);

		for (i = 0; i < Nrefa; i++, Refa++)
		{
			printf("[%d] %-10s Do=%6.3lf D1=%6.3lf Tin=%5.2lf Tout=%5.2lf Ta=%4.1lf\n",
				i, Refa->name, Refa->Do, Refa->D1, Refa->Tin,
				Refa->cmp->elouts->sysv, *Refa->Ta);
			printf("     Te=%5.2lf  Tc=%5.2lf  Q=%6.0lf E=%6.0lf Ph=%3.0lf\n",
				Refa->Te, Refa->Tc, Refa->Q, Refa->E, Refa->Ph);
		}
	}
}

//------ プライベート関数の実装 ------//


/*  圧縮式冷凍機定格特性入力    */

void _Refcmpdat(FILE* frf, int* Nrfcmp, RFCMP* Rfcmp)
{
	RFCMP* rfc;
	char   s[SCHAR];
	int i;

	rfc = Rfcmp;

	while (fscanf(frf, "%s", s), s[0] != '*')
	{
		Rfcmp->name = stralloc(s);

		fscanf(frf, "%s", s);
		Rfcmp->cname = stralloc(s);

		for (i = 0; i < 4; i++)
			fscanf(frf, "%lf", &Rfcmp->e[i]);
		for (i = 0; i < 4; i++)
			fscanf(frf, "%lf", &Rfcmp->d[i]);
		for (i = 0; i < 4; i++)
			fscanf(frf, "%lf", &Rfcmp->w[i]);
		fscanf(frf, "%lf %lf %lf %lf", &Rfcmp->Teo[0], &Rfcmp->Teo[1],
			&Rfcmp->Tco[0], &Rfcmp->Tco[1]);
		fscanf(frf, "%lf", &Rfcmp->Meff);

		Rfcmp++;
	}
	*Nrfcmp = (int)(Rfcmp - rfc);
	if (*Nrfcmp >= RFCMPLSTMX)
		printf("xxxxxxxxx Refcfi   reflist=%d [max=%d]\n", *Nrfcmp, RFCMPLSTMX);
}
/* ----------------------------------- */

/*  冷凍機の蒸発温度と冷凍能力の一次式の係数  */

void _Compca(double* e, double* d, double EGex, double* Teo, double Ta,
	double* Ho, double* He)
{
	double  Tc, Te, Qo[2];
	int    i;

	for (i = 0; i < 2; i++)
	{
		Te = Teo[i];
		Tc = (d[0] + d[1] * Te + EGex * Ta)
			/ (EGex - d[2] - d[3] * Te);
		Qo[i] = e[0] + e[1] * Te + (e[2] + e[3] * Te) * Tc;

		/* ---------
		printf("xxxx _Compca xxx Te=%lf  Tc=%lf   Qo[i]=%lf\n", Te,Tc,Qo[i]);
		---------- */
	}
	*He = (Qo[0] - Qo[1]) / (Teo[1] - Teo[0]);
	*Ho = Qo[0] + *He * Teo[0];
}
/* ------------------------------------------------------------ */

/*  ヒ－トポンプの凝縮温度と冷凍能力の一次式の係数  */

void _Compha(double* e, double* d, double EGex, double* Tco, double Ta,
	double* Ho, double* He)
{
	double  Tc, Te, Qo[2];
	int    i;

	for (i = 0; i < 2; i++)
	{
		Tc = Tco[i];
		Te = (e[0] + e[2] * Tc + EGex * Ta)
			/ (EGex - e[1] - e[3] * Tc);
		Qo[i] = d[0] + d[2] * Tc + (d[1] + d[3] * Tc) * Te;
		/* -----
		printf("xxx _Compha xxx Te=%lf  Tc=%lf   Qo[i]=%lf\n", Te,Tc,Qo[i]);
		------------- */
	}
	*He = (Qo[0] - Qo[1]) / (Tco[1] - Tco[0]);
	*Ho = Qo[0] + *He * Tco[0];
}
/* --------------------------------------- */

/*  冷凍機／ヒ－トポンプの軸動力の計算　　 */


double _Refpow(REFA* Rf, double QP)
{
	double  W = 0.0, Te = 0.0, Tc = 0.0;

	/****   Tx = (Rf->Ho - QP)/Rf->He; ****/

	if (fabs((double)QP) > 1.0)
	{
		if (Rf->chmode == COOLING_SW)
		{
			Te = QP / (Rf->cat->cool->eo * Rf->cG) + Rf->Tin;;
			Tc = (QP - Rf->c_e[0] - Rf->c_e[1] * Te) / (Rf->c_e[2] + Rf->c_e[3] * Te);
			W = Rf->c_w[0] + Rf->c_w[1] * Te + Rf->c_w[2] * Tc + Rf->c_w[3] * Te * Tc;
		}
		else if (Rf->chmode == HEATING_SW)
		{
			Tc = QP / (Rf->cat->heat->eo * Rf->cG) + Rf->Tin;
			Te = (QP - Rf->h_d[0] - Rf->h_d[2] * Tc) / (Rf->h_d[1] + Rf->h_d[3] * Tc);
			W = Rf->h_w[0] + Rf->h_w[1] * Te + Rf->h_w[2] * Tc + Rf->h_w[3] * Te * Tc;
		}

		/*****
		printf("xxx Refpow xxx Te=%lf  Tc=%lf   Qp=%lf\n", Te,Tc,QP);
		*****/

		Rf->Te = Te;
		Rf->Tc = Tc;
	}
	else
		W = 0.0;

	return(W);
}

