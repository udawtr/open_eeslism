#pragma once

#include <stdio.h>

//For RFCMP, REFA
#include "model/eqptyp.h"

void Refcmpdat(FILE *frf, int *Nrfcmp, RFCMP *Rfcmp);
void Compca(double *e, double *d, double EGex, double *Teo, double Ta, 
	    double *Ho, double *He);
void Compha(double *e, double *d, double EGex, double *Tco, double Ta,
	    double *Ho, double *He);
double Refpow(REFA *Rf, double QP);
