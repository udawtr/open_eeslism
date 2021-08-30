#pragma once

//BOI ボイラー

#include "model/sched.h"
#include "model/control.h"
#include "model/simcon.h"
#include "mc/eqptyp.h"


// --------------------------------------------
// BOI ボイラー
// --------------------------------------------

///@brief ボイラ－(システム構成要素)
typedef struct boi
{
	char* name;

	//! 負荷制御以外での運転モード
	//! 最大能力：M  最小能力：m
	char mode;

	//! 冷房モート゛、暖房モード
	char HCmode;

	char* load;

	struct boica* cat;

	struct compnt* cmp;

	double  Do, D1;
	double cG;
	double Tin;
	double Toset;
	double  Q, E, Ph;

	//!@brief 日積算値
	struct svday  Tidy;

	//!@brief 日積算値
	struct qday   Qdy;

	//!@brief 日積算値
	struct eday   Edy;

	//!@brief 日積算値
	struct eday   Phdy;

	struct eday   mtEdy[12][24], mtPhdy[12][24];

	//!@brief 月積算値
	struct svday  mTidy;

	//!@brief 月積算値
	struct qday   mQdy;

	//!@brief 月積算値
	struct eday   mEdy;

	//!@brief 月積算値
	struct eday   mPhdy;
} BOI;


void Boicfv(int Nboi, BOI *Boi);
void Boiene(int Nboi, BOI *Boi, int *BOIreset);
int  boildptr(char *load, char **key, BOI *Boi, VPTR *vptr);
void boildschd(BOI *Boi);
void boiprint(FILE *fo, int id, int Nboi, BOI *Boi);
void boidyint(int Nboi, BOI *Boi);
void boimonint(int Nboi, BOI *Boi);
void boiday(int Mon, int Day, int ttmm, int Nboi, BOI *Boi, int Nday, int SimDayend);
void boidyprt(FILE *fo, int id, int Nboi, BOI *Boi);
void boimonprt(FILE *fo, int id, int Nboi, BOI *Boi);
void boimtprt(FILE *fo, int id, int Nboi, BOI *Boi, int Mo, int tt) ;
void boixprint(int Nboi, BOI* Boi);
