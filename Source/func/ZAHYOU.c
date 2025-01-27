﻿//This file is part of EESLISM.
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


/**
 * @file
 * @brief モンテカルロ法を用いる際の座標変換
 */

/*

                      モンテカルロ法を用いる際の座標変換
                                 FILE=ZAHYOU.c
                                 Create Date=1999.6.7

*/


#include <stdio.h>
#include <math.h>
#include "model/wthrd.h"
#include "MODEL.h"
#include "exs.h"
#include "FUNC.h"
#include "func/ZAHYOU.h"

void ZAHYOU(XYZ Op,XYZ G,XYZ *op,double wa,double wb)
{
 double Cwa, Swa, Cwb, Swb ;
 XYZ p, q ;

 Cwa=cos(wa*M_rad) ;
 Swa=sin(wa*M_rad) ;
 Cwb=cos((-wb)*M_rad) ;
 Swb=sin((-wb)*M_rad) ;

 p.X=Op.X-G.X ;
 p.Y=Op.Y-G.Y ;
 p.Z=Op.Z-G.Z ;

  q.X=p.X*Cwa-p.Y*Swa ;
  q.Y=p.X*Swa+p.Y*Cwa ;
  q.Z=p.Z ;
 
 op->X=q.X ;
 op->Y=q.Y*Cwb-q.Z*Swb ;
 op->Z=q.Y*Swb+q.Z*Cwb ;

 CAT(&op->X,&op->Y,&op->Z) ;

 
}
/*------------------------------------------------------------------*/
void R_ZAHYOU(XYZ Op,XYZ G,XYZ *op,double wa,double wb)
{
 double Cwa, Swa, Cwb, Swb ;
 XYZ p, q ;

 Cwa=cos(-wa*M_rad) ;
 Swa=sin(-wa*M_rad) ;
 Cwb=cos(wb*M_rad) ;
 Swb=sin(wb*M_rad) ;


 p.X=Op.X ;
 p.Y=Op.Y*Cwb-Op.Z*Swb ;
 p.Z=Op.Y*Swb+Op.Z*Cwb ;

  q.X=p.X*Cwa-p.Y*Swa ;
  q.Y=p.X*Swa+p.Y*Cwa ;
  q.Z=p.Z ;

 op->X=q.X+G.X ;
 op->Y=q.Y+G.Y ;
 op->Z=q.Z+G.Z ;

 CAT(&op->X,&op->Y,&op->Z) ;
}
