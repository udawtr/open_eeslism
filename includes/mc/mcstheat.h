#pragma once

//STHEAT 電気蓄熱式暖房器

#include <stdio.h>

//For STHEATCA, STHEAT
#include "model/eqptyp.h"

//For PCM
#include "model/build.h"

//For WDAT
#include "model/wthrd.h"

//For COMPNT
#include "model/eepath.h"

//For VPTR
#include "model/control.h"

//For SIMCONTL
#include "model/simcon.h"


int  Stheatdata(char *s, STHEATCA *stheatca) ;
void Stheatint(int Nstheat, STHEAT *stheat, SIMCONTL *Simc, int Ncompnt, COMPNT *Compnt, WDAT *Wd, int Npcm, PCM *PCM);
void Stheatcfv(int Nstheat, STHEAT *stheat) ;
void Stheatene(int Nstheat, STHEAT *stheat) ;
//void Stheatene2(int Nstheat, STHEAT *stheat);
int  stheatvptr(char **key, STHEAT *Stheat, VPTR *vptr, VPTR *vpath) ;
void stheatprint(FILE *fo, int id, int Nstheat, STHEAT *stheat) ;
void stheatdyint(int Nstheat, STHEAT *stheat) ;
void stheatmonint(int Nstheat, STHEAT *stheat) ;
void stheatday(int Mon, int Day, int ttmm, int Nstheat, STHEAT *stheat, int Nday, int SimDayend) ;
void stheatdyprt(FILE *fo, int id, int Nstheat, STHEAT *stheat) ;
void stheatmonprt(FILE *fo, int id, int Nstheat, STHEAT *stheat) ;
void stheatmtprt(FILE *fo, int id, int Nstheat, STHEAT *stheat, int Mo, int tt) ;
