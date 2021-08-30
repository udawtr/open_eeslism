#pragma once

//COL 太陽熱集熱器

#include <stdio.h>

//For COLLCA. COLL
#include "mc/eqptyp.h"

//For WDAT
#include "model/wthrd.h"

//For VPTR
#include "model/control.h"


// --------------------------------------------
// COL 太陽熱集熱器
// --------------------------------------------


///@brief 太陽熱集熱器 (システム構成要素)
typedef struct coll
{
	char* name;

	struct collca* cat;
	struct  exsf* sol;
	struct compnt* cmp;
	double* Ta;
	double    Do, D1,
		ec,
		Te,					// 相当外気温度
		Tcb,				// 集熱板温度
		//Ko,					// 総合熱損失係数[W/(m2･K)]
		//Fd,					// 集熱器効率係数(=Kc / Ko）
		Tin,				// 入口温度
		Q,					// 集熱量[W]
		Ac,					// 集熱器面積
		Sol;				// 集熱面日射量[W](短波のみ）
	struct svday  Tidy;
	struct qday   Qdy;
	struct eday   Soldy;
	struct svday  mTidy;
	struct qday   mQdy;
	struct eday   mSoldy;
} COLL;

void   Collint(int Ncoll, COLL *Coll, int Nexsf, EXSF *Exs, WDAT *Wd);
void   Collcfv(int Ncoll, COLL *Coll);
void   Collene(int Ncoll, COLL *Coll);
void   collprint(FILE *fo, int id, int Ncoll, COLL *Coll);
double scolte (double rtgko, double cinc, double Idre, double Idf, double Ta);
int    collvptr(char **key, COLL *Coll, VPTR *vptr);
void   colldyint(int Ncoll, COLL *Coll);
void   collmonint(int Ncoll, COLL *Coll);
void   collday(int Mon, int Day, int ttmm, int Ncoll, COLL *Coll, int Nday, int SimDayend);
void   colldyprt(FILE *fo, int id, int Ncoll, COLL *Coll);
void   collmonprt(FILE *fo, int id, int Ncoll, COLL *Coll);
void   CalcCollTe(int Ncoll, COLL* Coll);
void   collxprint(int Ncoll, COLL* Coll);
