#pragma once

void Contrldata(FILE *fi, CONTL **Ct, int *Ncontl, CTLIF **Ci, int *Nctlif,
				CTLST **Cs, int *Nctlst, 
				SIMCONTL *Simc, int Ncompnt, COMPNT *Compnt,
				int Nmpath, MPATH *Mpath, WDAT *Wd, EXSFS *Exsf, SCHDL *Schdl);
void ctifdecode(char *s, CTLIF *ctlif, 
				SIMCONTL *Simc, int Ncompnt, COMPNT *Compnt,
				int Nmpath, MPATH *Mpath, WDAT *Wd, EXSFS *Exsf, SCHDL *Schdl);
