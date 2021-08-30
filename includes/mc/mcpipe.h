﻿#pragma once

//PIPE 配管

#include <stdio.h>

//For COMPNT
#include "model/eepath.h"

//For PIPE, PIPECA
#include "model/eqptyp.h"

//For WDAT
#include "model/wthrd.h"

//For VPTR
#include "model/control.h"


int  Pipedata(char *cattype, char *s, PIPECA *Pipeca);
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