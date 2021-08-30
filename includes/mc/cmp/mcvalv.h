#pragma once

#include <stdio.h>

//For VALV
#include "mc/eqptyp.h"

//For WDAT
#include "model/wthrd.h"

//For COMPNT, MPATH
#include "model/eepath.h"

//For SIMCONTL
#include "model/simcon.h"

//For SCHDL
#include "model/sched.h"

//For VPTR
#include "model/control.h"


void Valvcountreset(int Nvalv, VALV* Valv);
void Valvcountinc(int Nvalv, VALV* Valv);
void Valvene(int Nvalv, VALV* Valv, int* Valvreset);
void ValvControl(FILE* fi, int Ncompnt, COMPNT* Compnt, SCHDL* Schdl, SIMCONTL* Simc, WDAT* Wd, VPTR* vptr);
void Valvinit(int NValv, VALV* Valv, int NMpath, MPATH* Mpath);
