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

/* escntllb_s.c */

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "MODEL.h"   /*-----higuchi 070918---*/
#include "fesy.h"
#include "fnesy.h"
#include "fnmcs.h"
#include "fnlib.h"
#include "fnbld.h"
#include "fnfio.h"


/**
 * @file
 * @brief ポインター処理用関数の実装
 */

#define   NMKEYMX 50

//------ プライベート関数の宣言 ------//

int _strkey(char* s, char** key);


//------ 関数の実装 ------//


/**
 * @brief システム変数名、内部変数名、スケジュール名のポインター
 * @param[IN] s
 * @param[IN] Simc
 * @param[IN] Ncompnt
 * @param[IN] Compnt
 * @param[IN] Nmpath
 * @param[IN] Mpath
 * @param[IN] Wd
 * @param[IN] Exsf
 * @param[IN] Schdl
 * @param[IN] vptr
 * @param[IN] vpath
 */
int ctlvptr(char *s, SIMCONTL *Simc, int Ncompnt, COMPNT *Compnt, int Nmpath, MPATH *Mpath,
			WDAT *Wd, EXSFS *Exsf, SCHDL *Schdl, VPTR *vptr, VPTR *vpath)
{
	int i, err = 0;
	
	if ((i = idsch(s, Schdl->Sch, NULL))  >= 0)
	{	 
		vptr->ptr = Schdl->val + i;
		vptr->type = VAL_CTYPE;
		
		/*****
		printf("xxxxx ctlvptr xxxxx Sch-val i=%d  err=%d\n", i, err);
		*****/
	}
	else if ((i = idscw(s, Schdl->Scw, NULL)) >= 0)
	{
		vptr->ptr = Schdl->isw + i;
		vptr->type = SW_CTYPE;
		
		/*****
		printf("xxxxx ctlvptr xxxxx Scw-isw i=%d  err=%d\n", i, err);
		*****/
	}
	else
		err = kynameptr(s, Simc, Ncompnt, Compnt, Nmpath, Mpath, Wd, Exsf, vptr, vpath);
	
	Errprint(err, "<ctlvptr>", s);
	
	return err;
}


/**
 * @brief システム経路名、要素名、システム変数名、内部変数名の分離
 * 
 * ex) s = "A_B_C"
 *     => return 3
 *        key[] = {"A", "B", "C"}
 * 
 * @param[IN]  s   分離前の名前
 * @param[OUT] key 分離された名前の動的配列
 * @return 分離された名前の数
 */
int _strkey(char *s, char **key)
{
	char *st;
	int  i, nk;
	
	if ((i = (int)strlen(s)) == 0)
	{
		return 0;
	}
	else
	{  
		char ss[SCHAR];

		//TODO: 変数ssが局所変数にも関わらず、そのポインタが keyに返されるので、ポインタが破損している。
		strcpy(ss, s);
		
		key[0] = ss;
		nk = 1;
		for (st = ss + 1; st <ss + i; st++)
		{
			//区切り文字 `_` を見つけたら 終端文字を入れることで、文字列を分割。
			if (*st == '_')
			{
				*st = '\0';
				st++ ;
				key[nk] = st;
				nk++ ;
			}
		}
		/************* 
		printf("   strkey  nk=%d", nk);
		for (i = 0; i < nk; i++)
		printf(" key[%d]=%s",i, key[i]);
		printf("\n");
		****************/
		
		return nk;
	}
}


/**
 * @brief 経路名、システム変数名、内部変数名のポインター
 * 
 * 表 2.7.1 valkyname および ldsname で指定可能な項目
 * 
 * @param[IN] s
 * @param[IN] Simc
 * @param[IN] Ncompnt
 * @param[IN] Compnt
 * @param[IN] Nmpath
 * @param[IN] Mpath
 * @param[IN] Wd
 * @param[IN] Exsf
 * @param[IN] Schdl
 * @param[IN] vptr
 * @param[IN] vpath
 */
int kynameptr(char *s, SIMCONTL *Simc, int Ncompnt, COMPNT *Compnt, int Nmpath, MPATH *Mpath,
			  WDAT *Wd, EXSFS *Exsf, VPTR *vptr, VPTR *vpath)
{
	char *e, *key[NMKEYMX];
	int  nk, err = 0;
	
	nk = _strkey(s, key) ;
	if ( nk )
	{
		//************** 気象条件, 給水温度 **************//

		//外気温 [℃]
		if (strcmp(key[0], "Ta") == 0)
		{
			vptr->type = VAL_CTYPE;
			vptr->ptr = &Wd->T;
		}

		//外気絶対湿度 [kg/kg]
		else if (strcmp(key[0], "xa") == 0)
		{
			vptr->type = VAL_CTYPE;
			vptr->ptr = &Wd->x;
		}

		//外気相対湿度 [%]
		else if (strcmp(key[0], "RHa") == 0)
		{
			vptr->type = VAL_CTYPE;
			vptr->ptr = &Wd->RH;
		}

		//屋外エンタルピ [J/kg]
		else if (strcmp(key[0], "ha") == 0)
		{
			vptr->type = VAL_CTYPE ;
			vptr->ptr = &Wd->h ;
		}

		//給水温度[℃]
		else if (strcmp(key[0], "Twsup") == 0)
		{
			vptr->type = VAL_CTYPE;
			vptr->ptr = &Wd->Twsup;
		}

		//水平面全日射   [W/m2]
		else if (strcmp(key[0], "Ihol") == 0)
		{
			vptr->type = VAL_CTYPE;
			vptr->ptr = &Wd->Ihor;
		}
		else 
		{
			//************** 窓 **************//

			// 傾斜面名称の検索
			// 
			// `<ename>_Idre` : 傾斜面入射直達日射
			// `<ename>_Idf`  : 傾斜面入射拡散日射
			// `<ename>_Iw`   : 傾斜面入射全日射
			// 
			// ※ <ename> = 外表面名
			//
			if ( Exsf != NULL )
			{
				EXSF* Exs = Exsf->Exs ;
				for ( int i = 0; i < Exsf->Nexs; i++, Exs++)
				{
					if (strcmp(key[0], Exs->name ) == 0)
					{
						// 傾斜面への入射直達日射量
						if(strcmp(key[1], "Idre") == 0)
						{
							vptr->type = VAL_CTYPE ;
							vptr->ptr = &Exs->Idre ;
							return 0 ;
						}
						// 傾斜面への入射拡散日射量
						else if(strcmp(key[1], "Idf") == 0)
						{
							vptr->type = VAL_CTYPE ;
							vptr->ptr = &Exs->Idf ;
							return 0 ;
						}
						// 傾斜面への入射全日射量
						else if(strcmp(key[1], "Iw") == 0)
						{
							vptr->type = VAL_CTYPE ;
							vptr->ptr = &Exs->Iw ;
							return 0 ;
						}
					}
				}
			}

			if (Nmpath > 0)
			{
				//************** 蓄熱槽,ボイラー,仮想熱源,仮想空調機,一般機器 **************//

				// #蓄熱槽,ボイラー,仮想熱源,仮想空調機
				// `<elmname>_Ts_x` : 槽内水温
				// `<elmname>_Tin`  : 入口水温
				// `<elmname>_Tout` : 出口水温
				// `<elmname>_xout` : 出口絶対湿度
				// 
				// #一般機器
				// `<elmname>_Twout` : 出口水温
				// `<elmname>_Taout` : 出口空気湿度
				// `<elmname>_xaout` : 出口空気絶対湿度
				// 
				// ※ <elmname> = 外表面名

				err = pathvptr(nk, key, Nmpath, Mpath, vptr, vpath);
			}
			else
			{
				err = 1;
			}

			if (err)
			{
				if (Simc->Nvcfile > 0)
					err = vcfptr(key, Simc, vptr);
				else
					err =1;
			}

			if (err)
			{	 
				for (int i = 0; i < Ncompnt; i++, Compnt++)
				{	    
					if (strcmp(key[0], Compnt->name) == 0)
					{
						//printf("%s\n", Compnt->name) ;
						err = compntvptr(nk, key, Compnt, vptr) ;
						if ( err )
						{
							e = Compnt->eqptype;
							if (strcmp(e, ROOM_TYPE) == 0)
							{
								/*** if (nk>1) ****/
								err = roomvptr(nk, key, (ROOM*)Compnt->eqp, vptr);
							}
							else if (strcmp(e, REFACOMP_TYPE) == 0)
							{
							/*****
							printf("xxxx kynameptr xxxx key[0]=%s key[1]=%s err=%d\n",
								key[0], key[1], err); *****/
								err = refaswptr(key, (REFA *)Compnt->eqp, vptr);
								/*****
								printf("xxxx kynameptr xxxx key[0]=%s key[1]=%s err=%d\n",
								key[0], key[1], err); *****/
							}
							else if (strcmp(e, HCLOAD_TYPE) == 0 ||
								strcmp(e, HCLOADW_TYPE) == 0 || strcmp(e, RMAC_TYPE) == 0 || strcmp(e, RMACD_TYPE) == 0 )
								err = hcldswptr(key, (HCLOAD *)Compnt->eqp, vptr) ;
							/* VAV Satoh Debug 2001/1/19 */
							else if (strcmp(e, VAV_TYPE) == 0 || strcmp(e, VWV_TYPE) == 0)
								err = vavswptr(key, (VAV *)Compnt->eqp, vptr) ;
							else if (strcmp(e, COLLECTOR_TYPE) == 0)
								err = collvptr(key, (COLL *)Compnt->eqp, vptr);
							else if (strcmp(e, STANK_TYPE) == 0)
								err = stankvptr(key, (STANK *)Compnt->eqp, vptr);
							else if (strcmp(e, STHEAT_TYPE) == 0)
								err = stheatvptr(key, (STHEAT *)Compnt->eqp, vptr, vpath);
							// Satoh追加　デシカント槽　2013/10/23
							else if (strcmp(e, DESI_TYPE) == 0)
								err = Desivptr(key, (DESI *)Compnt->eqp, vptr);
							else if (strcmp(e, PIPEDUCT_TYPE) == 0)
								err = pipevptr(key, (PIPE *)Compnt->eqp, vptr) ;
							else if (strcmp(e, RDPANEL_TYPE) == 0)
								err = rdpnlvptr(key, (RDPNL *)Compnt->eqp, vptr) ;
							else
								Eprint ( "CONTL", Compnt->name ) ;
						}
						break;
					}
				}
				
			}
		}
	}
	else
		err = 1;
	
	Errprint(err, "<kynameptr>", s);
	
	return err;
}


/**
 * @brief 経路名のポインター
 * @param[IN]  nk     分割後の名前の分割数
 * @param[IN]  key    分割後の名前の文字列の配列
 * @param[IN]  Nmpath SYSPTHにおける';'で区切られる経路の配列の要素数
 * @param[IN]  Mpath  SYSPTHにおける';'で区切られる経路の配列
 * @param[OUT] vptr   経路名へのポインタを出力先(refer to MPATH.control)
 * @param[OUT] vpath  経路名へのポインタを出力先(refer to MPATH)
 */
int pathvptr(int nk, char **key, int Nmpath, MPATH *Mpath,  VPTR *vptr, VPTR *vpath)
{
	int i, err = 0;
	MPATH *Mp, *Mpe;
	PLIST *Plist, *Plie;
	
	Mp = Mpath;
	
	//
	// 1) 経路名の探索
	//

	for (i = 0; i < Nmpath; i++, Mpath++)
	{      
		if (strcmp(key[0], Mpath->name) == 0)
		{
			vpath->type = MAIN_CPTYPE;
			vpath->ptr = Mpath;
			
			//制御情報への参照を取得
			if (nk == 1 || strcmp(key[1], "control") == 0)
			{
				vptr->type = SW_CTYPE;
				vptr->ptr = &Mpath->control;
			}
			break;
		}
	}

	// 経路名を探索して見つからなかったら...
	// 2) 経路要素の探索
	//

	err = (i == Nmpath) ;

	if ( err )
	{
		//TODO: 手抜きして全経路の要素を探そうとしているように見える。
		//      しかし、実際には探索すべきではない領域も含めて探索しており危険なコードに見える。
		//
		Mpe = Mp + Nmpath - 1;
		Plie = Mpe->plist + Mpe->Nlpath;
		
		//経路要素を順に確認していく
		for (Plist = Mp->plist; Plist < Plie; Plist++)
		{
			if (Plist->name != NULL)
			{
			/***********
			printf("<< pathvptr >> Key=%s, Plist->name=%s\n",
			key[0], Plist->name);
				*****************/
				
				if (strcmp(key[0], Plist->name) == 0)
				{
					vpath->type = LOCAL_CPTYPE;
					vpath->ptr = Plist;
					
					//制御情報への参照を取得
					if (nk == 1 || strcmp(key[1], "control") == 0)
					{
						vptr->type = SW_CTYPE;
						vptr->ptr = &Plist->control;
					}

					//負荷計算用設定値の参照を取得
					else if(strcmp(key[1], "G") == 0)
					{
						vptr->type = VAL_CTYPE;
						vptr->ptr = &Plist->G;
					}
					break;
				}
			}
		}
		if (Plist == Plie)
			err = 1;     
	}

	//見つかれば0
	return err;
}


/**
 * @brief COMPNTの配列から指定の名前の要素への参照を取得
 * @param[IN] name   探索する名前
 * @param[IN] N      COMPNT配列の要素数
 * @param[IN] Compnt COMPNT配列
 * @return COMPNTへの参照。見つからなかった場合はNULL
 */
COMPNT	*Compntptr ( char *name, int N, COMPNT *Compnt )
{
	COMPNT	*C = NULL ;
	for ( int i = 0; i < N; i++, Compnt++ )
	{
		if ( strcmp ( name, Compnt->name ) == 0 )
			C = Compnt ;
	}

	return C ;
}


/**
 * @brief システム要素出口温度、湿度のポインター
 */
int compntvptr(int nk, char **key, COMPNT *Compnt, VPTR *vptr)
{
	int err = 0;
	
	// 制御情報へのポインタを取得
	// (温水弁の場合はバルブ開度)
	if (nk == 1 || strcmp(key[1], "control") == 0)
	{
		//機器タイプ
		char* etype = Compnt->eqptype ;

		if ( strcmp ( etype, VALV_TYPE ) != 0 && strcmp ( etype, TVALV_TYPE ) != 0 )
		{
			// -- 温水弁の制御ではない --

			// ボイラなど機器自体の停止ではなく、燃焼の停止とする
			//vptr->ptr = &Compnt->control;
			ELOUT* Eo = Compnt->elouts ;
			if (strcmp(etype, STHEAT_TYPE) == 0)
			{
				vptr->ptr = &Compnt->control;
			}
			else
			{
				vptr->ptr = &Eo->control;
			}
			vptr->type = SW_CTYPE;
		}
		else
		{
			// -- 温水弁の制御である --

			//バルブ開度へのポインタを返す

			VALV* v = ( VALV * ) Compnt->eqp ;
			vptr->ptr = &v->x ;
			vptr->type = VAL_CTYPE ;
			v->org = 'y' ;
		}
	}
	else
	{
		int i;
		ELOUT* Eo = Compnt->elouts;

		for (i = 0; i < Compnt->Nout; i++, Eo++)
		{
			if ((Eo->fluid == AIRa_FLD && strcmp(key[1], "Taout") == 0)
				|| (Eo->fluid == AIRx_FLD && strcmp(key[1], "xout") == 0)
				|| (Eo->fluid == WATER_FLD && strcmp(key[1], "Twout") == 0))
			{
				vptr->ptr = &Eo->sysv;
				vptr->type = VAL_CTYPE;
				break;
			}
		}
		if (i == Compnt->Nout)
			err = 1;
	}   
	return err;
}


/**
 * @brief 負荷計算を行うシステム要素の設定システム変数のポインター
 */
int loadptr(COMPNT *loadcmp, char *load, char *s, int Ncompnt, COMPNT *Compnt,
			VPTR *vptr)
{
	ROOM *Room;
	char *key[NMKEYMX], idmrk=' ';
	int  i, nk, err=0;
	ELOUT  *Eo, *eold;
	RMLOAD	*R ;
	RDPNL	*Rdpnl ;
	
	nk = (_strkey(s, key)) ;

	if ( nk )
	{
		for (i = 0; i < Ncompnt; i++, Compnt++)
		{
			if (strcmp(key[0], Compnt->name) == 0)
			{
				if (strcmp(Compnt->eqptype, BOILER_TYPE) == 0)
				{
					err = boildptr(load, key, (BOI *)Compnt->eqp, vptr);
					idmrk = 't';
					/*** break;***/
				}
				
				if (strcmp(Compnt->eqptype, REFACOMP_TYPE) == 0)
				{
					err = refaldptr(load, key, (REFA *)Compnt->eqp, vptr);
					idmrk = 't';
				}
				else if (strcmp(Compnt->eqptype, HCLOAD_TYPE) == 0
					|| strcmp(Compnt->eqptype, RMAC_TYPE) == 0|| strcmp(Compnt->eqptype, RMACD_TYPE) == 0)
				{
					err = hcldptr(load, key, (HCLOAD *)Compnt->eqp, vptr, &idmrk);
					/***break;***/
				}
				else if (strcmp(Compnt->eqptype, PIPEDUCT_TYPE) == 0)
					err = pipeldsptr(load, key, (PIPE *)Compnt->eqp, vptr, &idmrk);
				
				else if (strcmp(Compnt->eqptype, RDPANEL_TYPE) == 0)
				{
					Rdpnl = ( RDPNL * ) Compnt->eqp ;
					err = rdpnlldsptr(load, key, (RDPNL *)Compnt->eqp, vptr, &idmrk);
					if (loadcmp != NULL && strcmp(loadcmp->eqptype, OMVAV_TYPE) == 0)
					{
						Rdpnl->OMvav = ( OMVAV * ) loadcmp->eqp ;
						Rdpnl->OMvav->omwall = Rdpnl->sd[0] ;
					}
				}

				else if (strcmp(Compnt->eqptype, ROOM_TYPE) == 0)
				{
					Room = (ROOM *)Compnt->eqp;
					if (Room->rmld == NULL)
					{
						if ((Room->rmld = (RMLOAD *)malloc(1 * sizeof(RMLOAD))) == NULL)
							Ercalloc(1, "roomldptr");

						//原因不明だがkeyの内容が失われるので無理矢理復活させる処理//E.Togashi 2008.09.06*****
						_strkey(s, key);
						//************************************************************************************

						R = Room->rmld ;
						R->loadt = R->loadx = NULL ;
						R->FOTN = R->FOPL = NULL ;

						if (loadcmp != NULL && strcmp(loadcmp->eqptype, VAV_TYPE) == 0)
							Room->VAVcontrl = (VAV *) loadcmp->eqp ;
					}
					err = roomldptr(load, key, Room, vptr, &idmrk);	       
					/***break;***/
				}

				if (err == 0)
				{
				/***************
				printf("<loadptr>   i=%d  %s\n", i, Compnt->name);
					*************************/
					
					if (loadcmp == NULL)
						loadcmp = Compnt;
					Eo = Compnt->elouts;
					eold = loadcmp->elouts;
					
					if (idmrk == 'x')
					{
						Eo++ ;
						eold++;
					}
					
					Eo->eldobj = eold;
					eold->emonitr = Eo;
					
					break;
				}
			}
			else
				err = 1;
		}
		return err;
	}
	else
		return 1;
}


