#pragma once

//For COMPNT
#include "model/eepath.h"

//For WDAT
#include "model/wthrd.h"

//For OMVAV, OMVAVCA
#include "mc/eqptyp.h"


// --------------------------------------------
// OAVAV 屋根一体型空気集熱器の出口温度設定変風量制御ユニット
// --------------------------------------------
// Satoh OMVAV  2010/12/16

///@brief 屋根一体型空気集熱器の出口温度設定変風量制御ユニット(システム構成要素)
typedef struct omvav
{
	char* name;
	OMVAVCA* cat;
	RMSRF* omwall;		// 制御対象とする集熱屋根
	COMPNT* cmp;
	PLIST* Plist;
	double	G;
	RDPNL* rdpnl[4];
	int		Nrdpnl;
} OMVAV;

double OMflowcalc(OMVAV *OMvav, WDAT *Wd) ;
int    colkey(char *s, char **key) ;
void   OMvavControl(OMVAV *OMvav, COMPNT *Compnt, int NCompnt) ;
int	   strCompcount(char *st, char key) ;
