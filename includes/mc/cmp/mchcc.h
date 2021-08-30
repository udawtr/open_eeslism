#pragma once

///@brief HCC 冷温水コイル

//For HCCCA, HCC
#include "mc/eqptyp.h"


// --------------------------------------------
// HCC 冷温水コイル
// --------------------------------------------

///@brief 冷温水コイル(システム構成要素)
typedef struct hcc
{
	char* name,
		wet;
	char	etype;			/* 温度効率の入力方法
							　　e:et
								k:KA	*/
	struct hccca* cat;
	struct compnt* cmp;
	double   et,               /*温度効率　　　　　　*/
		eh;               /*エンタルピ効率　　　*/
	struct  acs  Et,
		Ex,
		Ew;
	double   cGa,
		Ga,
		cGw,
		Gw,
		Tain,
		Taout,
		xain,
		Twin,
		Twout,
		Qs,
		Ql,
		Qt;
	struct svday  Taidy, xaidy, Twidy;
	struct qday   Qdys, Qdyl, Qdyt;
	struct svday  mTaidy, mxaidy, mTwidy;
	struct qday   mQdys, mQdyl, mQdyt;
} HCC;

void Hccdwint(int Nhcc, HCC *Hcc);
void Hcccfv(int Nhcc, HCC *Hcc);
void Hccdwreset(int Nhcc, HCC *Hcc, int *DWreset);
void Hccene(int Nhcc, HCC *Hcc);
void hccprint(FILE *fo, int id, int Nhcc, HCC *Hcc);
void hccdyint(int Nhcc, HCC *Hcc);
void hccmonint(int Nhcc, HCC *Hcc);
void hccday(int Mon, int Day, int ttmm, int Nhcc, HCC *Hcc, int Nday, int SimDayend);
void hccdyprt(FILE *fo, int id, int Nhcc, HCC *Hcc);
void hccmonprt(FILE *fo, int id, int Nhcc, HCC *Hcc);
double	FNhccet ( double Wa, double Ww, double KA ) ;
void hccxprint(int Nhcc, HCC* Hcc);