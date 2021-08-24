﻿#pragma once

//EVAC 気化冷却器

#include <stdio.h>

//For EVACCA, EVAC
#include "model/eqptyp.h"

int		Evacdata ( char *s, EVACCA *Evacca ) ;
void	Evacint ( int Nevac, EVAC *Evac ) ;
void	LinearSatx(double Ts, double *a, double *b) ;
void	Evacelm(int Nevac, EVAC *Evac) ;
void	Evacelm(int Nevac, EVAC *Evac) ;
void	Evaccfv(int Nevac, EVAC *Evac) ;
void	Evacene(int Nevac, EVAC *Evac, int *Evacreset) ;
void Evacprint(FILE *fo, int id, int Nevac, EVAC *Evac) ;
void	Evaccountreset(int Nevac, EVAC *Evac) ;
double	Evacu(double G, double T, double H, double W, int N) ;
double Evachcc(double de, double L, double T, double H, double W, int N, double G, int Flg) ;
double	EvacNu(double AR, double Re) ;
