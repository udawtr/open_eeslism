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

/* control.h */

#pragma once

/*
 * @brief <入力データファイル>システム経路のモデルについて構造体の定義
 * @details
 *
 * 2.7 制御データ (EESLISM7.2入力データ作成マニュアル.pdf)
 *
 * モデルの関連図
 *
 * *- CONTL
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 * CONTL:
 *
 * @sa Eeinput
 */

/**
 * @file
 * @brief 制御、スケジュール設定 
 * @sa Compodata, Contrldata
 */


#define   VAL_CTYPE   'v'
#define   SW_CTYPE    's'
#define   MAIN_CPTYPE  'M'
#define   LOCAL_CPTYPE 'L'


/*
 * @brief  
 * @sa Contlschdlr
 */
typedef struct contl
{
    ///! 制御種別(条件付き 'c'、無条件 ' ')
    char  type;

    ///! 制御情報(True:1、False:0)
    int   lgv;
    struct ctlif *cif;

    ///! ANDで2条件の場合
    struct ctlif* andcif;

    ///! ANDで3条件の場合
    struct ctlif *andandcif;

    ///! or条件の場合
    struct ctlif *orcif ;
    struct ctlst *cst;
} CONTL;


typedef union ctltyp
{
   double *v;
   char  *s;
} CTLTYP;


///@brief 制御条件項目データ
typedef struct ctlif
{
    ///! 'v', 's'
    char  type;
    char op;
    int   Nlft;
    union ctltyp  lft1, lft2, rgt;
} CTLIF;


typedef struct ctlst
{
    char  type;

    ///! 'M', 'L'
    char pathtype;

    void  *path;

    union ctltyp  lft, rgt;
} CTLST;


/**
 * @brief 
 * @sa VPTRinit
 */
typedef struct vptr
{
   char  type;
   void  *ptr;
} VPTR;

