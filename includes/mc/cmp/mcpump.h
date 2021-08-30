#pragma once

//PUMP ポンプ

#include <stdio.h>

//For PUMP, PUMPCA
#include "mc/eqptyp.h"

//For EXFS
#include "exs.h"


// --------------------------------------------
// PUMP/FUN ポンプ・ファン
// --------------------------------------------


///@brief ポンプ・ファン (システム構成要素)
typedef struct pump
{
	char* name;
	struct pumpca* cat;
	struct compnt* cmp;
	//struct pfcmp  *pfcmp ;
	struct exsf* sol;
	double  Q,
		G,
		cG,
		Tin,
		E;
	double	PLC;		// 部分負荷特性を考慮した入力率
	struct eday Qdy, Gdy, Edy;
	EDAY		mtEdy[12][24];
	struct eday mQdy, mGdy, mEdy;
} PUMP;

void   Pumpint(int Npump, PUMP *Pump, int Nexsf, EXSF *Exs);
void   Pumpflow(int Npump, PUMP *Pump);
void   Pumpcfv(int Npump, PUMP *Pump);
double PumpFanPLC ( double XQ, PUMP *Pump ) ;
void   Pumpene(int Npump, PUMP *Pump);
void   pumpprint(FILE *fo, int id, int Npump, PUMP *Pump);
void   pumpdyint(int Npump, PUMP *Pump);
void   pumpmonint(int Npump, PUMP *Pump);
void   pumpday(int Mon, int Day, int ttmm, int Npump, PUMP *Pump, int Nday, int SimDayend);
void   pumpdyprt(FILE *fo, int id, int Npump, PUMP *Pump);
void   pumpmonprt(FILE *fo, int id, int Npump, PUMP *Pump);
void   pumpmtprt(FILE *fo, int id, int Npump, PUMP *Pump, int Mo, int tt) ;
void   PFcmpInit(int Npfcmp, PFCMP *Pfcmp) ;
void   PFcmpdata(FILE *fl, int *Npfcmp, PFCMP *pfcmp) ;
