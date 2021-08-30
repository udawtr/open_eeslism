﻿#pragma once

//COL 太陽熱集熱器

#include <stdio.h>

//For COLLCA. COLL
#include "model/eqptyp.h"

//For WDAT
#include "model/wthrd.h"

//For VPTR
#include "model/control.h"


int Colldata (char *type, char *s, COLLCA *Collca);
void Collint(int Ncoll, COLL *Coll, int Nexsf, EXSF *Exs, WDAT *Wd);
void Collcfv(int Ncoll, COLL *Coll);
void Collene(int Ncoll, COLL *Coll);
void collprint(FILE *fo, int id, int Ncoll, COLL *Coll);
double scolte (double rtgko, double cinc, double Idre, double Idf, double Ta);
int collvptr(char **key, COLL *Coll, VPTR *vptr);
void colldyint(int Ncoll, COLL *Coll);
void collmonint(int Ncoll, COLL *Coll);
void collday(int Mon, int Day, int ttmm, int Ncoll, COLL *Coll, int Nday, int SimDayend);
void colldyprt(FILE *fo, int id, int Ncoll, COLL *Coll);
void collmonprt(FILE *fo, int id, int Ncoll, COLL *Coll);
void CalcCollTe(int Ncoll, COLL* Coll);
void collxprint(int Ncoll, COLL* Coll);
