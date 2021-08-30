#pragma once

#include <stdio.h>

////@brief カロリーメータ
typedef struct qmeas
{
	char	fluid;
	int		id;
	char* name;
	COMPNT* cmp;
	double* Th, * Tc, * G, * xh, * xc;
	PLIST* PlistG, * PlistTh, * PlistTc, * Plistxh, * Plistxc;
	double	Qs, Ql, Qt;
	SVDAY	Thdy, Tcdy, xhdy, xcdy;
	QDAY	Qdys, Qdyl, Qdyt;
	SVDAY	mThdy, mTcdy, mxhdy, mxcdy;
	QDAY	mQdys, mQdyl, mQdyt;
	//	PELM	*Pelmh, *Pelmc ;
	char	idh, idc;
	//	COMPNT	*cmph, *cmpc ;
	int		Nelmh, Nelmc;
	//PLIST	*Plist ;
} QMEAS;

void	Qmeasene (int Nqmeas, QMEAS *Qmeas ) ;
void	Qmeaselm ( int Nqmeas, QMEAS *Qmeas ) ;
void	Qmeasprint(FILE *fo, int id, int Nqmeas, QMEAS *Qmeas ) ;
void	Qmeasdyint(int Nqmeas, QMEAS *Qmeas ) ;
void	Qmeasmonint(int Nqmeas, QMEAS *Qmeas ) ;
void	Qmeasday(int Mon, int Day, int ttmm, int Nqmeas, QMEAS *Qmeas, int Nday, int SimDayend) ;
void	Qmeasdyprt(FILE *fo, int id, int Nqmeas, QMEAS *Qmeas) ;
void	Qmeasmonprt(FILE *fo, int id, int Nqmeas, QMEAS *Qmeas) ;
