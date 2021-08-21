#pragma once

#include <stdio.h>

int DEBUG();
void EnterDebugMode();

//エラー出力用ファイルポインタ
extern FILE	*ferr;

//円周率
extern double CONST_PI;

extern int	dayprn;

extern double CONST_SGM;

extern double  cff_kWh;

extern double CONST_CA, CONST_RO;

extern double dTM, CONST_RO, CONST_CA;

extern double  CONST_CA, CONST_ROA;

int NSTOP();
void NSTOPOn();
int DISPLAY_DELAY();
void DISPLAY_DELAY_On();

extern double dTM;

int SETprint();

extern  double  dTM;

extern double  cff_kWh;

extern double CONST_G;

	extern double   dTM;	extern char* Fbmlist;
	extern int	dayprn;
	extern int	dayprn;
	extern FILE* ferr;

	extern double CONST_ROW;
	extern double CONST_CA, CONST_CW;
	extern double  R0, Ca, Cv, Rc, Cc, Cw, Pcnv, P;

	extern char* CONST_UNIT;
	extern double P;
	extern double Pcnv;
	double Tabs, Pws, Temp;
	extern char* CONST_UNIT;
	extern double Lat, Slat, Clat, Tlat, Isc;
	extern double Lon, Ls;
	extern double	CONST_CA,		// 乾き空気の比熱[J/kgK]
		CONST_RO,		// 水の蒸発潜熱[J/kg]
		CONST_CV;	// 水蒸気の低圧比熱[J/kgK]
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
