#pragma once



// --------------------------------------------
// 境界条件設定用仮想機器
// --------------------------------------------

///@brief 境界条件設定用仮想機器
//@sa Flinint, flindat,  Flinprt
typedef struct flin
{
	char* name;

	//! 変数名(温度、顕熱）
	char* namet;   /*  */

	//! 変数名(湿度、潜熱）
	char* namex;

	//! 'W':１変数のとき(nametの変数名のみ使用）
	//! 'A':２変数のとき(namexの変数も使用）
	char  awtype;

	//! nametで示された変数の値
	double* vart;

	//! namexで示された変数の値
	double* varx;

	struct compnt* cmp;
} FLIN;


void flindat(FLIN *Flin);
void Flinint(int Nflin, FLIN *Flin, 
	     SIMCONTL *Simc, int Ncompnt, COMPNT *Compnt, WDAT *Wdat);
void	Flinprt ( int N, FLIN *Fl ) ;
