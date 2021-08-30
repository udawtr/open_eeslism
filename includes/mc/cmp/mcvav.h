#pragma once

//VAV VAVユニット

#include <stdio.h>

//For VAV, VAVCA
#include "mc/eqptyp.h"

//For COMPNT
#include "model/eepath.h"

//For VPTR
#include "model/control.h"


// --------------------------------------------
// VAV VAV ユニット
// --------------------------------------------
/*---- Satoh Debug VAV  2000/10/30 ----*/

///@brief VAVユニット(システム構成要素)
typedef struct vav
{
	char	chmode;		/* 冷房用、暖房用の設定 */
	char* name;			/* 機器名 */
	char	mon;			/* 制御対象が
							　　コイルの時：c
							　　仮想空調機の時：h
							　　床暖房の時：f
							**************************/
	VAVCA* cat;			/* VAVカタログ構造体 */
	struct hcc* hcc;	/* VWVの時の制御対象コイル */
	struct hcload* hcld;	/* VWVの時の制御対象仮想空調機 */
	RDPNL* rdpnl;		/* VWVの時の制御対象放射パネル */
	//ROOM	*room ;			/* 制御室構造体 */
	double	G,				/* 風量 [kg/s] */
		cG,				/* 熱容量流量 [W/K] */
		Q,				/* 再熱計算時の熱量 [W] */
		Qrld,
		Tin, Tout;		/* 入口、出口空気温度 */
	int		count;			/* 計算回数 */
	COMPNT* cmp;
} VAV;

void   VAVcfv(int Nvav, VAV *vav) ;
void   VAVene(int Nvav, VAV *vav, int *VAVrest) ;
void   VAVcountreset ( int Nvav, VAV *VAV ) ;
int	   vavswptr(char **key, VAV *VAV, VPTR *vptr) ;
int    chvavswreset(double Qload, char chmode, VAV *VAV) ;
void   vavprint(FILE *fo, int id, int Nvav, VAV *VAV) ;
void   VAVcountinc ( int Nvav, VAV *VAV ) ;
void   VWVint(int Nvav, VAV *VAV, int Ncompnt, COMPNT *Compn) ;
double FNVWVG ( VAV *VWV ) ;
double FNFd ( double Wa, double Ww, double KA ) ;
