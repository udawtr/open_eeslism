#pragma once

//For COMPNT
#include "model/eepath.h"

//For WDAT
#include "model/wthrd.h"

//For OMVAV, OMVAVCA
#include "model/eqptyp.h"

int OMVAVdata (char *ss, OMVAVCA *OMvavca) ;
double	OMflowcalc(OMVAV *OMvav, WDAT *Wd) ;
int colkey(char *s, char **key) ;
void	OMvavControl(OMVAV *OMvav, COMPNT *Compnt, int NCompnt) ;
int		strCompcount(char *st, char key) ;
