#pragma once

#include <stdio.h>

int DEBUG();
void EnterDebugMode();

//エラー出力用ファイルポインタ
extern FILE	*ferr;


extern int	dayprn;

extern double  cff_kWh;

int NSTOP();
void NSTOPOn();
int DISPLAY_DELAY();
void DISPLAY_DELAY_On();

extern double dTM;

int SETprint();

extern  double  dTM;

extern double  cff_kWh;

	extern double   dTM;	extern char* Fbmlist;
	extern int	dayprn;
	extern int	dayprn;
	extern FILE* ferr;

	extern double  Ca, Cv, Rc, Cc, Cw, Pcnv, P;

	extern double P;
	extern double Pcnv;
	double Tabs, Pws, Temp;

extern double  Lat, Slat, Clat, Tlat, Lon, Ls;

	extern char	DAYweek[][4];
	extern int	VAV_Count_MAX;

#define CONST_PI 3.141592654
#define CONST_SGM 5.67e-8
#define CONST_CA 1005.0		// 乾き空気の比熱[J/kgK]
#define CONST_CV 1846.0		// 水蒸気の低圧比熱[J/kgK]
#define CONST_ROA 1.29
#define CONST_CW 4186.0
#define CONST_ROW 1000.0
#define CONST_RO 2501000.	// 水の蒸発潜熱[J/kg]
#define CONST_G 9.8

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
