#pragma once


//HEX 熱交換器

//For HEX, HEXCA
#include "mc/eqptyp.h"


// --------------------------------------------
// HEX 熱交換器
// --------------------------------------------

///@brief 熱交換器 (システム構成要素)
typedef struct hex
{
	int		id;
	char* name;

	//! 温度効率の入力方法 e:et  k:KA
	char	etype;

	struct hexca* cat;
	struct compnt* cmp;
	double  eff,
		eCGmin,
		CGc, CGh,
		Tcin,
		Thin,
		Qci, Qhi;
	struct svday  Tcidy, Thidy;
	struct qday   Qcidy, Qhidy;
	struct svday  mTcidy, mThidy;
	struct qday   mQcidy, mQhidy;
} HEX;

void Hexcfv(int Nhex, HEX *Hex);
void Hexene(int Nhex, HEX *Hex);
void hexprint(FILE *fo, int id, int Nhex, HEX *Hex);
void hexdyint(int Nhex, HEX *Hex);
void hexmonint(int Nhex, HEX *Hex);
void hexday(int Mon, int Day, int ttmm, int Nhex, HEX *Hex, int Nday, int SimDayend);
void hexdyprt(FILE *fo, int id, int Nhex, HEX *Hex);
void hexmonprt(FILE *fo, int id, int Nhex, HEX *Hex);
