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

/*   sun.c 
-------------------     */
#include <string.h>
#include <math.h>
#include "common.h"
#include "lib/u_sun.h"

/* ================================================================

 SUNLIB
 
  太陽位置および日射量計算用ライブラリ－
  （宇田川、パソコンによる空気調和計算法、プログラム4.1の C 言語版, ANSI C 版）
  
---------------------------------------------------------------- */


#define CONST_ISC 1370.

double _Slat, _Clat, _Tlat, _Lon, _Ls;

void Sunint(double Lat, double Lon, double Ls)
{
	const double Rd = CONST_PI/180.;
	_Slat=sin(Lat*Rd);
	_Clat=cos(Lat*Rd);
	_Tlat=tan(Lat*Rd);
	_Lon = Lon;
	_Ls = Ls;
}
/* --------------------------------------------- */
int FNNday(int Mo, int Nd)
{
	return( (153*(Mo-1)+2*(Mo<3)-9*(Mo>=3))/5 + Nd);
}
/*  -------------------------------------------- */
double FNDecl(int N)
{
    return( asin(.397949*sin(2.*CONST_PI*(N-81.)/365.)) );
}
/*  -------------------------------------------- */
double FNE(int N)
{
	double B;
	B=2.*CONST_PI*(N-81.)/365.;
	return( .1645*sin(2.*B)-.1255*cos(B)-.025*sin(B) );
}
/*  -------------------------------------------- */
double FNSro(int N)
{
	return( CONST_ISC*(1.0+.033*cos(2.*CONST_PI*N/365.)) );
}
/*  -------------------------------------------- */
double FNTtas(double Tt, double E)
{
	return( Tt+E+(_Lon-_Ls)/15. );
}
/*  -------------------------------------------- */
double FNTt(double Ttas, double E)
{
	return( Ttas-E-(_Lon-_Ls)/15. );
}
/*  -------------------------------------------- */
double FNTtd(double Decl)
{
	double Cws, Ttd;
	Cws= -_Tlat*tan(Decl);
	if ( 1. > Cws && Cws > -1. )
		Ttd=7.6394*acos(Cws); 
	else
    {
		if (Cws >= 1.) 
			Ttd=0.;
		else
			Ttd=24.;
    }
	return ( Ttd );
}
/* -------------------------------------------- */
void Solpos(double Ttas, double Decl, double *Sh, double *Sw, double *Ss, double *solh, double *solA)
{
	static double  Sdecl, Sld, Cld, Ttprev=25.;
	double  Ch, Ca, Sa, W;
	
	if (Ttas < Ttprev) 
	{
		Sdecl=sin(Decl);
		Sld=_Slat*Sdecl;
		Cld=_Clat*cos(Decl);
	}
	W=(Ttas-12.)*.2618;
	*Sh = Sld + Cld*cos(W);
	*solh = asin(*Sh) / CONST_PI*180.;
	if (*Sh > 0.) 
	{
		Ch=sqrt(1.-*Sh * *Sh);
		Ca=(*Sh * _Slat - Sdecl)/(Ch * _Clat);
		*solA = (W > 0. ? 1.0 : -1.0)* acos(Ca) / CONST_PI*180.;
		Sa=(W/fabs(W))*sqrt(1.-Ca*Ca);
		*Sw=Ch*Sa;
		*Ss=Ch*Ca;
	}  
	else
	{
		*Sh=0.;
		*Sw=0.;
		*Ss=0.;    
		*solh = 0.;
		*solA = 0.;
	}
	Ttprev=Ttas;
}
/* -------------------------------------------- */
void Srdclr(double Io, double P, double Sh, double *Idn, double *Isky)
{
	if ( Sh>.001 ) 
	{
		*Idn=Io*pow(P,(1./Sh));
		*Isky=Sh*(Io - *Idn)*(.66-.32*Sh)*(.5+(.4-.3*P)*Sh);
	}
	else
	{
		*Idn=0.;
		*Isky=0.; 
	}
}
/* -------------------------------------------- */
void Dnsky(double Io, double Ihol, double Sh, double *Idn, double *Isky)
{ 
	double Kt; 
	if ( Sh>.001 ) 
	{
		Kt=Ihol/(Io*Sh);
		if ( Kt >= .5163+(.333+.00803*Sh)*Sh )  
			*Idn=(-.43+1.43*Kt)*Io;
		else
			*Idn=(2.277+(-1.258+.2396*Sh)*Sh)*(Kt*Kt*Kt)*Io;
		
		*Isky=Ihol - *Idn * Sh; 
	}
	else
	{
		*Idn=0.;
		*Isky=Ihol; 
	} 
}  
/* ------------------------------------------- */
