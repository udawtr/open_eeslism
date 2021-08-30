#pragma once

//For REFACA, REFA
#include "mc/eqptyp.h"

//For WDAT
#include "model/wthrd.h"

//For COMPNT
#include "model/eepath.h"

//For VPTR
#include "model/control.h"


// --------------------------------------------
// REFA チラー、ヒートポンプチラー(空気熱源
// --------------------------------------------

///@brief ヒートポンプ (システム構成要素)
typedef struct refa
{
	//! 名称
	char* name;

	char* load;

	//! 冷房運転: C、暖房運転時: H
	char	chmode;

	struct refaca* cat;

	struct compnt* cmp;

	struct room* room;

	//! 冷房運転時蒸発器係数
	double c_e[4];

	//! 冷房運転時熱源側(凝縮器係数）
	double c_d[4];

	//! 冷房運転時軸動力係数
	double c_w[4];

	//! 暖房運転時凝縮器係数
	double	h_e[4];

	//! 暖房運転時熱源側(蒸発器係数）
	double	h_d[4];

	//! 暖房運転時軸動力係数
	double	h_w[4];

	//! 運転時能力特性式係数
	double	Ho, He;

	//! 外気温度
	double* Ta;
	double	Do, D1;
	double	cG;

	//! 運転時蒸発温度
	double	Te;

	//! 運転時凝縮温度
	double	Tc;

	double	Tin;
	double	Toset;
	double	Q;
	double	Qmax;
	double	E;

	//! 冷温水ポンプ動力 [W]
	double	Ph;

	struct svday  Tidy;
	struct qday   Qdy;
	struct eday   Edy, Phdy;
	EDAY		  mtEdy[12][24], mtPhdy[12][24];
	struct svday  mTidy;
	struct qday   mQdy;
	struct eday   mEdy, mPhdy;

} REFA;


void Refaint(int Nrefa, REFA *Refa, WDAT *Wd, int Ncompnt, COMPNT *Compnt);
void Refacfv(int Nrefa, REFA *Refa);
void refacoeff(REFA *Refa, int *err);
void Refaene(int Nrefa, REFA *Refa, int *LDreset); 
void Refaene2(int Nrefa, REFA *Refa);
int  refaldptr(char *load, char **key, REFA *Refa, VPTR *vptr);
int  refaswptr(char **key, REFA *Refa, VPTR *vptr);
void refaldschd(REFA *Refa);
void refaprint(FILE *fo, int id, int Nrefa, REFA *Refa);
void refadyint(int Nrefa, REFA *Refa);
void refamonint(int Nrefa, REFA *Refa);
void refaday(int Mon, int Day, int ttmm, int Nrefa, REFA *Refa, int Nday, int SimDayend);
void refadyprt(FILE *fo, int id, int Nrefa, REFA *Refa);
void refamonprt(FILE *fo, int id, int Nrefa, REFA *Refa);
void refamtprt(FILE *fo, int id, int Nrefa, REFA *Refa, int Mo, int tt) ;
void refaxprint(int Nrefa, REFA* Refa);