#pragma once

//PIPE 配管


// --------------------------------------------
// PIPE 配管
// --------------------------------------------

///@brief 配管・ダクト仕様
typedef struct pipeca
{
	char* name;

	//! 配管のとき P、ダクトのときD
	char type;

	double  Ko;
} PIPECA;

int  Pipedata(char *cattype, char *s, PIPECA *Pipeca);
