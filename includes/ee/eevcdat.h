#pragma once

void Vcfdata(FILE *fi, SIMCONTL *Simcon);
int	VCFcount ( FILE *fi ) ;
int vcfptr(char **key, SIMCONTL *Simc, VPTR *vptr);
void Vcfinput(DAYTM *Daytm, int Nvcfile, VCFILE *Vcfile, char perio);
