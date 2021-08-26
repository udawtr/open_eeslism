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

/*   wthrd.h    */

#pragma once

/**
 * @file
 * @brief 気象データに関する構造体の定義
 */

/**
 * @brief 気象データ
 * @sa Locinit, gtsupw
 */
typedef struct locat
{
	//! 地名
	char   *name;

	//! 緯度[deg] (VCFILE Lat)
	double  Lat;

	//! 経度[deg] (VCFILE Lon)
	double	Lon;

	//! 標準子午線[deg] (VCFILE Ls)
	double	Ls;
	
	//! 日平均気温の年最高気温が発生する日の通日(地中温度計算用) (VCFILE daymx)
	int    daymxert;

	//! 年平均気温 [℃] (VCFILE Tgrav)
	double  Tgrav;

	//! 気温年較差 [℃] (VCFILE DTgr)
	double DTgr;
	
	//!月毎の給水温度 (VCFILE -Twsup)
	double  Twsup[12];
} LOCAT ;


///@brief 気象デ－タ
typedef struct wdat
{
	//! 気温
	double   T;

	//! 絶対湿度  [kg/kg]
	double   x;

	//! 外気相対湿度 [%]
	double	RH;

	//! エンタルピ [J/kg]
	double	h;

	//! 法線面直逹日射 [W/m2]
	double	Idn;

	//! 水平面天空日射 [W/m2]
	double	Isky;

	//! 水平面全日射   [W/m2]
	double	Ihor;

	double	sunalt, sunazm;

	//! 太陽光線の方向余弦
	double	Sh, Sw, Ss;

	//! 太陽位置
	double	solh, solA; 

	//! 雲量
	double	CC;

	//! 夜間輻射 [W/m2]
	double            RN;

	//! 大気放射量[W/m2] higuchi 070918
	double            Rsky;

	//! 風速 [m/s]
	double	Wv;

	//! 風向　１６方位
	double	Wdre;

	//! 気象データ項目  C:雲量　R:夜間放射量[W/m2]  (GDATA FILE -skyrd) */
	char   RNtype;
	
	//! 給水温度を補完する場合は'Y'、しない場合は'N' (デフォルトは'N') (GDATA FILE -intgtsupw)
	char	Intgtsupw ;

	//! 給水温度 [℃]
	double  Twsup;

	//! 24*365日分の地表面温度[℃]
	double	*EarthSurface ;
} WDAT ;


///@brief 気象データ項目のポインター(VCFILEからの入力時)
typedef struct wdpt
{
	//! 気温 [℃]
	double* ta;

	//! 絶対温度 [kg/kg]
	double* xa;

	//! 相対湿度 [%]
	double* rh;

	//! 法線面直達日射 [W/㎡]
	double* idn;

	//! 水平面天空日射 [W/㎡]
	double* isky;

	//! 水平面全天日射 [W/㎡]
	double* ihor;

	//! 雲量 (0-10)
	double* cc;

	//! 夜間放射 [W/㎡]
	double* rn;

	//! 風速 [m/s]
	double* wv;

	//! 風向 (0-16)
	double* wdre;
} WDPT;
