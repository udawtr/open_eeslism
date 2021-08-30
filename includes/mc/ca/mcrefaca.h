#pragma once


// --------------------------------------------
// REFA チラー、ヒートポンプチラー(空気熱源
// --------------------------------------------

///@brief 標準圧縮機特性
typedef struct rfcmp
{
	//! 名称
	char* name;

	//! 圧縮機タイプ説明
	char* cname;

	//! 蒸発器係数
	double e[4];

	//! 凝縮器係数
	double d[4];

	//! 軸動力係数
	double w[4];

	//! 蒸発温度範囲
	double Teo[2];

	//! 凝縮温度範囲
	double Tco[2];

	//! モ－タ－効率
	double Meff;
} RFCMP;

///@brief ヒートポンプ定格能力
typedef struct hpch
{
	//! 定格冷却能力(加熱能力）
	double  Qo;

	//! 定格冷(温）水量、風量
	double	Go;

	//! 定格冷(温）水出口温度(チラ－）
	double	Two;

	//! 定格水冷却(加熱）器、空調機コイル温度効率
	double	eo;

	//! 定格排出(採取）熱量
	double	Qex;

	//! 定格冷却風量、水量
	double	Gex;

	//! 定格外気温(冷却水入口水温）
	double	Tex;

	//! 定格凝縮器(蒸発器）温度効率
	double	eex;

	//! 定格軸動力
	double	Wo;
} HPCH;

///@brief ヒートポンプ(機器カタログデータ）
typedef struct refaca
{
	//! 名称
	char* name;

	//! 空冷(空気熱源）=a、冷却塔使用=w
	char awtyp;

	//! 部分負荷特性コ－ド
	char plf;

	//! エネルギー計算で機器容量上限無いとき 'y'
	char unlimcap;

	//! 冷房運転: C、暖房運転時: H
	char mode[2];

	//! mode[]の数。1 のとき冷房専用または暖房専用。2 のとき冷・暖 切換運転。
	int Nmode;

	struct rfcmp* rfc;

	//! 定格冷温水ポンプ動力 [W]
	double Ph;

	//! 冷房運転時定格能力
	struct hpch* cool;

	//! 暖房運転時定格能力
	struct hpch* heat;
} REFACA;


int  Refadata (char *s, REFACA *Refaca, int Nrfcmp, RFCMP *Rfcmp);
