#pragma once

///@brief HCC 冷温水コイル


// --------------------------------------------
// HCC 冷温水コイル
// --------------------------------------------

///@brief 冷温水コイル(機器カタログデータ）
typedef struct hccca
{
	char* name;
	double   et,               /*定格温度効率　　　　　　*/
		KA,
		eh;               /*定格エンタルピ効率　　　*/
} HCCCA;


typedef struct acs
{
	double  w, t, x, C;
} ACS;


int Hccdata(char *s, HCCCA *Hccca);

