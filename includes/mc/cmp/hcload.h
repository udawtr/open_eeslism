#pragma once


#include "mc/eqptyp.h"


///@brief 空調機負荷仮想機器
typedef struct hcload
{
	char* name,
		* loadt,
		* loadx,
		RMACFlg,		// ルームエアコンなら'Y'
		chmode,			// スケジュール等によって設定されている運転モード
//		opmode,			// 実際の運転時のモード
type,    /* 'D':直膨コイル想定
'W':冷温水コイル想定　*/
wetmode,	/* 実際のコイル状態 */
wet;     /*'y': wet coil  'n':dry coil */

	double   cGa,
		Ga,
		Tain,
		xain,
		Toset,
		Xoset,

		/*---- Roh Debug for a constant outlet humidity model of wet coil  2003/4/25 ----*/
		RHout,

		cGw,
		Gw,
		Twin,
		Twout,

		Qfusoku,
		Ele,
		COP,

		Qs,
		Ql,
		Qt;
	double	Qcmax, Qhmax, Qc, Qh, Qcmin, Qhmin,
		COPc, COPh,					// COP(定格）
		Ec, Eh, Ecmax, Ecmin,		// 消費電力[W]
		COPcmax, COPcmin,			// COP(最大能力時、最小能力時
		Gi, Go;					// 室内機、室外機風量[kg/s]
	double	COPhmax, COPhmin, Ehmin, Ehmax;
	double	Rc[3], Rh[3],			// 理論COPと実働COPの比の2次式回帰係数
		Pcc, Pch;					// ファン等消費電力[W]
	double	BFi, BFo;				// 室内機、室外機のバイパスファクタ
	double	rh, rc;	// 定格能力と最大能力の比
	struct svday  Taidy, xaidy;
	struct qday   Qdys, Qdyl, Qdyt;
	struct qday	  Qdyfusoku, Edy;
	EDAY		  mtEdy[12][24];
	struct svday  mTaidy, mxaidy;
	struct qday   mQdys, mQdyl, mQdyt;
	struct qday	  mQdyfusoku, mEdy;

	struct compnt* cmp;
} HCLOAD;


void   Hclelm(int Nhcload, HCLOAD *Hcload);
void   Hcldcfv(int Nhcload, HCLOAD *Hcload);
void   Hcldene(int Nhcload, HCLOAD *Hcload, int *LDrest, WDAT *Wd);
int    hcldptr(char *load, char **key, HCLOAD *Hcload, VPTR *vptr, char *idmrk);
void   hcldschd(HCLOAD *Hcload);
void   hcldprint(FILE *fo, int id, int Nhcload, HCLOAD *Hcload);
void   hclddyint(int Nhcload, HCLOAD *Hcload);
void   hcldmonint(int Nhcload, HCLOAD *Hcload);
void   hcldday(int Mon, int Day, int ttmm, int Nhcload, HCLOAD *Hcload, int Nday, int SimDayend);
void   hclddyprt(FILE *fo, int id, int Nhcload, HCLOAD *Hcload);
void   hcldmonprt(FILE *fo, int id, int Nhcload, HCLOAD *Hcload);
void   hcldmtprt(FILE *fo, int id, int Nhcload, HCLOAD *Hcload, int Mo, int tt);
int    hcldswptr (char **key, HCLOAD *Hcload, VPTR *vptr) ;
int    chhcldswreset(double Qload, double Ql, char chmode, ELOUT *Eo) ;
void   hcldwetmdreset (struct eqsys*Eqsys ) ;
void   hcldmodeinit (struct eqsys*Eqsys ) ;
double FNeffthc(double Tco, double Tci, double xci, double Qc, double Ec, double Go, double Gi, double cai, double cao) ;
double FNeffthh(double Tco, double Tci, double xco, double Qc, double Eh, double Go, double Gi, double cai, double cao) ;
void   rmacdat(HCLOAD *Hcld) ;
void   rmacddat(HCLOAD *Hcld) ;
double FNTcndc(double Tco, double Qc, double Ec, double cao, double Go) ;
double FNTevpc(double Tci, double Qc, double cai, double Gi, double xci) ;
double FNTcndh(double Tci, double Qc, double cai, double Gi) ;
double FNTevph(double Tco, double Qc, double Eh, double cao, double Go, double xco) ;