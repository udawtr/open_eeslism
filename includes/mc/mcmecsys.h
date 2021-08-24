#pragma once

//For COMPNT
#include "model/eepath.h"

//For EQSYS
#include "model/eqptyp.h"

//For WDAT
#include "model/wthrd.h"

//For RMVLS
#include "model/build.h"

//For EXFS
#include "exs.h"

//For SIMCONTL
#include "model/simcon.h"

void Mecsinit(double dTM, EQSYS *Eqsys,
	      SIMCONTL *Simc, int Ncompnt,COMPNT *Compnt,
		  int Nexsf, EXSF *Exsf, WDAT *Wd, RMVLS *Rmvls);
void	Mecscf(EQSYS *Eqsys);
void Mecsene(EQSYS *Eqsys);
