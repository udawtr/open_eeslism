#pragma once

//PV 太陽電池

// --------------------------------------------
// PV 太陽電池
// --------------------------------------------

///@brief 太陽電池(機器カタログデータ）
typedef struct pvca
{
	char* name;
	double	PVcap,					// 太陽電池容量[W]
		Area,					// アレイ面積[m2]
		KHD,					// 日射量年変動補正係数[-]
		KPD,					// 経時変化補正係数[-]
		KPM,					// アレイ負荷整合補正係数[-]
		KPA,					// アレイ回路補正係数[-]
		effINO;				// インバータ実行効率[-]
	double	apmax;					// 最大出力温度係数[-]
	double	ap;					// 太陽電池裏面の熱伝達率[W/m2K]
	char	type;					// 結晶系：'C'  アモルファス系：'A'
	double	A, B;					// 設置方式別の太陽電池アレイ温度計算係数
	char	InstallType;			// 太陽電池パネル設置方法
									// 'A':架台設置形、'B':屋根置き形、'C':屋根材形(裏面通風構造があるタイプ）
	//double	PVcap ;					// 太陽電池設置容量[W]
} PVCA;


int  PVcadata (char *s, PVCA *PVca) ;
