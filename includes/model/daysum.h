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

/* daysum.h */

#pragma once

/**
 * @file
 * @brief 日集計用の構造体の定義
 */

/**
 * @brief システム変数の日集
 */
typedef struct svday
{
    //!@brief 平均
    double m;
    
    //!@brief 最高
    double mn;

    //!@brief 最低
    double mx;

    //!@brief 平均値の母数
    long hrs;

    //!@brief 最高値発生時刻
    long mntime;

    //!@brief 最低値発生時刻
    long mxtime;
} SVDAY;


/**
 * @brief 積算壁体貫流熱取得
 */
typedef struct qday
{
    //!@brief 加熱積算値
    double h;

    //!@brief 冷却積算値
    double c;

    //!@brief 加熱最大値
    double hmx;

    //!@brief 冷却最大値
    double cmx;

    //!@brief 加熱時間回数
    long hhr;

    //!@brief 冷却時間回数
    long chr;

    long hmxtime;

    long cmxtime;
} QDAY;


/**
 * @brief
 */
typedef struct eday
{
    //!@brief 積算値
    double d;

    //!@brief 最大値
    double mx;
   
   //!@brief 運転時間回数
    long hrs;

    long mxtime;
} EDAY;

