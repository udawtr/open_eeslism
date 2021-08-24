#pragma once

void Pathdata (FILE *f, char *errkey, SIMCONTL *Simc, WDAT *Wd, int  Ncompnt,  COMPNT *Compnt, SCHDL *Schdl,
	       MPATH **Mpath, int *Nmpath, PLIST **Plist, PELM **Pelm, int *Npelm, int *Nplist, int ID, EQSYS *Eqsys ) ;
void	Elcount ( int N, COMPNT *C, int *Nelout, int *Nelin ) ;
