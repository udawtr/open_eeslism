#pragma once

#include <stdio.h>

//DEBUGフラグ
extern int DEBUG;

//エラー出力用ファイルポインタ
extern FILE	*ferr;

//円周率
extern double PI;

extern int	dayprn;

extern double Sgm;

extern double  cff_kWh;

extern double ca, ro;

extern double dTM, ro, ca;

extern double  ca, roa;

extern int	NSTOP;

extern double dTM;

extern int SETprint;

extern  double  dTM;

extern double  cff_kWh;

extern double g;

	extern double   dTM;	extern char* Fbmlist;
	extern int	dayprn;
	extern int	dayprn;
	extern FILE* ferr;

	extern double row;
	extern double ca, cw;
	extern double  R0, Ca, Cv, Rc, Cc, Cw, Pcnv, P;

	extern char* UNIT;
	extern double P;
	extern double Pcnv;
	double Tabs, Pws, Temp;
	extern char* UNIT;
	extern double Lat, Slat, Clat, Tlat, Isc;
	extern double Lon, Ls;
	extern double	ca,		// 乾き空気の比熱[J/kgK]
		ro,		// 水の蒸発潜熱[J/kg]
		cv;	// 水蒸気の低圧比熱[J/kgK]
	extern char	DAYweek[][4];
	extern int	VAV_Count_MAX;

// 月の末日かどうかをチェックする
int	isEndDay(int Mon, int Day, int Dayend, int SimDayend);



#define  SCHAR    1024
//#define  NCHAR	  128

//#define  IDCHRMX  51


#define NOP   -1
#define FNOP  -999.9
#define TEMPLIMIT -273.16

#define  ERRFMT  "xxxxx %s xxxxx : "



//#define  ERSTR   101
#define  ERRFMTA  "xxx %s xxx %s\n"
