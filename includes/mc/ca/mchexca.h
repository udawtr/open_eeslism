#pragma once


//HEX 熱交換器


// --------------------------------------------
// HEX 熱交換器
// --------------------------------------------

///@brief 熱交換器(機器カタログデータ）
typedef struct hexca
{
	char* name;

	//! 熱交換器有効率
	double  eff;

	double	KA;
} HEXCA;

int  Hexdata(char *s, HEXCA *Hexca);
