#pragma once


// --------------------------------------------
// OAVAV 屋根一体型空気集熱器の出口温度設定変風量制御ユニット
// --------------------------------------------
// Satoh OMVAV  2010/12/16

//@breif 屋根一体型空気集熱器の出口温度設定変風量制御ユニット(機器カタログデータ）
typedef struct omvavca
{
	char* name;
	double	Gmax,			// 最大風量[kg/s]
		Gmin;			// 最小風量[kg/s]
} OMVAVCA;


int    OMVAVdata (char *ss, OMVAVCA *OMvavca) ;
