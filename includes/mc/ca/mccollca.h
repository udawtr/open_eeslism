#pragma once

//COL 太陽熱集熱器


// --------------------------------------------
// COL 太陽熱集熱器
// --------------------------------------------

///@brief 太陽熱集熱器(機器カタログデータ）
typedef struct collca
{
	char* name;

	//! 水熱源：w、空気熱源：a
	char type;

	double   b0, b1;

	//! 集熱器効率係数(=Kc / Ko）
	double Fd;

	//! 総合熱損失係数[W/(m2･K)]
	double Ko;

	double Ac;

	double Ag;
} COLLCA;

int    Colldata (char *type, char *s, COLLCA *Collca);
