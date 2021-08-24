//This file is part of EESLISM.
//
//Foobar is free software : you can redistribute itand /or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//Foobar is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with Foobar.If not, see < https://www.gnu.org/licenses/>.

/* exs.h */

#pragma once

//
// @brief 外表面
// @details
// 
// EXSFS -- EXSF
//


/*
 * @brief 外表面方位デ－タ
 * @sa Tearth, Exsfsol, Exsfinit
 */
typedef struct exsf
{
	//! 外表面名
	char* name;

	//! 外表面熱伝達率の設定方法
	//! V:風速から計算、F:23.0固定、S:スケジュール
	char alotype;

	//! 一般外表面'S',地下'E', 地表面'e'
	char typ;

	//! 方位角
	double  Wa;

	//! 傾斜角
	double	Wb;

	//! 前面の日射反射率
	double	Rg;

	//! 天空を見る形態係数
	double	Fs;
	double	Wz;
	double	Ww;

	//! 傾斜面の方向余弦
	double	Ws;
	double	swb;
	double	cbsa;
	double	cbca;

	//// ! 外表面の熱伝達率スケジュール
	//double *alosch;

	double	cwa;
	double	swa;

	//! 外表面総合熱伝達率
 	double	*alo;


	//------地中温度------/

	//! 地中深さ
	double	Z;

	//! 土の熱拡散率 [m2/s]
	double	erdff;

	//! 地中温度(または地表面温度; `typ`に応じる) [℃]
	double	Tearth;

	//------方位別日射関連デ－タ------/

	//! 入射角のcos
	double  cinc;

	//! 見掛けの方位角のtan
	double	tazm;

	//! プロファイル角のtan
	double	tprof;

	//! 見かけの方位角
	double	Gamma;

	//! プロファイル角  [rad]
	double	Prof;

	//! 直逹日射  [W/m2]
	double	Idre;

	//! 拡散日射  [W/m2]
	double	Idf;

	//! 全日射    [W/m2]
	double	Iw;

	//! 夜間輻射  [W/m2]
	double	rn;

	//--------------------/

	//!  外表面方位デ－タのデータ数(先頭の要素にのみ保存)
	int    end;
} EXSF; 


/*
 * @brief 外表面リスト
 * @details
 * 2.3.4 外表面リスト (EESLISM7.2入力データ作成マニュアル.pdf)
 */
typedef struct exsfst
{
	//! 外表面方位デ－タのデータ数
	int		Nexs ;

	//! 外表面方位デ－タの動的配列
	EXSF	*Exs ;

	//! 外表面総合熱伝達率の動的配列
	double	*alosch ;

	//! 外表面熱伝達率の設定方法
	//! V:風速から計算、F:23.0固定、S:スケジュール
	char	alotype ;

	//! 地表面境界がある場合'Y'
	char	EarthSrfFlg ;
} EXSFS ;
