#pragma once

//PIPE 配管

#include <stdio.h>

//For COMPNT
#include "model/eepath.h"

//For PIPE, PIPECA
#include "mc/eqptyp.h"

//For WDAT
#include "model/wthrd.h"

//For VPTR
#include "model/control.h"


// --------------------------------------------
// PIPE 配管
// --------------------------------------------


///@brief システム使用配管・ダクト
typedef struct pipe
{
	char* name,
		* loadt,
		* loadx;
	//char	type ;
	struct pipeca* cat;
	struct compnt* cmp;
	struct room* room;
	double   L,
		Ko,
		* Tenv,
		ep,
		Do, D1,
		Tin,
		Q,
		Tout,
		hout,
		xout,
		RHout,

		Toset,
		Xoset;
	struct svday  Tidy;
	struct qday   Qdy;
	struct svday  mTidy;
	struct qday   mQdy;
} PIPE;

void Pipeint(int Npipe, PIPE *Pipe, SIMCONTL *Simc, int Ncompnt, COMPNT *Compnt, WDAT *Wd);
void Pipecfv(int Npipe, PIPE *Pipe);
void Pipeene(int Npipe, PIPE *Pipe);
int  pipeldsptr(char *load, char **key, PIPE *Pipe, VPTR *vptr, char *idmrk);
void pipeldsschd(PIPE *Pipe);
void pipeprint(FILE *fo, int id, int Npipe, PIPE *Pipe);
void pipedyint(int Npipe, PIPE *Pipe);
void pipemonint(int Npipe, PIPE *Pipe);
void pipeday(int Mon, int Day, int ttmm, int Npipe, PIPE *Pipe, int Nday, int SimDayend);
void pipedyprt(FILE *fo, int id, int Npipe, PIPE *Pipe);
void pipemonprt(FILE *fo, int id, int Npipe, PIPE *Pipe);
int  pipevptr(char **key, PIPE *Pipe, VPTR *vptr) ;
void pipexprint(int Npipe, PIPE* Pipe);