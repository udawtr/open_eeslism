/*    bslib.c            */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

#include "common.h"
#include "fesy.h"
#include "esize.h"
#include "fnfio.h"
#include "fnlib.h"
#include "fnesy.h"

#define  ALO  23.0


//
// @brief 外表面
// @details
// 
// EXSFS -- EXSF
//


/*
 * @brief 外表面方位デ－タの入力
 * 
 * @param[IN]     fi
 * @param[IN]     dsn
 * @param[IN,OUT] Exsf   外表面リスト
 * @param[IN]     Schdl  スケジュール
 * @param[IN]     Simc
 */
void Exsfdata (FILE *fi, char *dsn, EXSFS *Exsf, SCHDL *Schdl, SIMCONTL *Simc )
{
	char	s[SCHAR], ename[SCHAR], *st ;
	double	dt;
	double dfrg = 0.0;	//前面地物の日射反射率 [-] 
	double	rad; 
	double	*vall ;
	int		i = -1, j, k ;
	double  wa, wb, swa, cwa, swb, cwb ;
	EXSF	*ex, *exj ;
	char	Err[SCHAR+128];

	//
	// 1) 外表面リストのメモリ確保
	//

	strcpy ( s, dsn ) ;
	int Nd = imax ( ExsfCount ( fi ), 1 ) ;

	vall = Schdl->val ;

	/****************/
	if ( Nd > 0 )
	{
		// 外表面総合熱伝達率の動的配列の作成
		sprintf(s, "%lf", ALO);
		Exsf->alosch = envptr(s,Simc,0,NULL,NULL,NULL) ;

		//外表面熱伝達率の設定方法の初期値⇒23.0固定
		Exsf->alotype = 'F' ;

		//メモリ確保
		Exsf->Exs = ( EXSF * ) malloc (( Nd + 1 ) * sizeof ( EXSF )) ;

		exj = Exsf->Exs ;
		if (exj == NULL)
		{
			//メモリ確保に失敗
			Ercalloc(Nd, "<Exsfdata> Exs");
		}
		else
		{
			// 外表面方位データの初期化
			Exsfinit(Nd + 1, exj);
		}
	}
	/**************************/


	//
	// 2) 外表面リストの読み込み
	//

	ex = Exsf->Exs - 1 ;
	
	while (fscanf(fi, "%s", s), s[0] != '*')
	{
		//printf ( "s=%s\n", s ) ;

		// 外表面総合熱伝達率 (`alo=xxx`)
		if (strncmp(s, "alo=", 4) == 0)
		{
			st = strchr(s, '=');
			if (strcmp(st + 1, "Calc") == 0)
			{
				//外表面熱伝達率の設定方法 ==> "風速から計算"
				Exsf->alotype = 'V';
			}
			else if ((k = idsch(st + 1, Schdl->Sch, NULL)) >= 0)
			{
				//外表面総合熱伝達率
				Exsf->alosch = &vall[k];

				//外表面熱伝達率の設定方法 ==> "スケジュール"
				Exsf->alotype = 'S';
			}
			else
			{
				//外表面総合熱伝達率
				Exsf->alosch = envptr(st + 1, Simc, 0, NULL, NULL, NULL);

				if (Exsf->alosch != NULL)
				{
					//外表面熱伝達率の設定方法 ==> "スケジュール"
					Exsf->alotype = 'S';
				}
			}
		}

		// 前面地物の日射反射率 [-] (指定しないとき 0.0) (`r=xxx`)
		else if (strncmp(s, "r=", 2) == 0)
		{
			//TODO: dfrgの値をどこにも保存していないように見える。

			st = strchr(s, '=');
			dfrg = atof(st + 1);

			if (dfrg<0. || dfrg>1.0)
			{
				sprintf(Err, "%s の設置値が不適切です", s);
				preexit();
			}
		}
		else 
		{
			ex++ ;
			i++ ;
			
			// 外表面名
			ex->name = stralloc( s);

			// 外表面熱伝達率の設定方法
			ex->alotype = Exsf->alotype;

			// 外表面総合熱伝達率
			ex->alo = Exsf->alosch;
				
			// 水平面
			if (strcmp(s, "Hor") ==0)
				ex->Wb=0.0;
			// 地表面
			else if(strcmp(s, "EarthSf") == 0)
			{
				Exsf->EarthSrfFlg = 'Y' ;
				ex->typ = 'e' ;
			}
			else
				ex->Wb=90.0, ex->Rg=dfrg;
		}
		
		while (fscanf(fi, " %s ", s), s[0] != ';')
		{ 
			//printf ( "s=%s\n", s ) ;

			// 方位角 [°] (`a=azmexpr`)
			if ( strncmp ( s, "a=", 2 ) == 0 )
			{
				if (sscanf(&s[2], "%lf", &dt) != 0)
				{
					ex->Wa = dt;
				}
				else
				{
					if (strchr(s, '+'))
						Nd = sscanf(&s[2], "%[^+]%lf", ename, &dt);
					else if (strchr(s, '-'))
						Nd = sscanf(&s[2], "%[^-]%lf", ename, &dt); 
					else
						Nd = sscanf(&s[2], "%s", ename);
					
					exj = Exsf->Exs ;
					for (j=0; j<i+1; j++, exj++)
					{
						if ((strcmp(exj->name, ename)) == 0)
						{ 
							ex->Wa = exj->Wa + (Nd == 2 ? dt : 0.0);
							break;
						}
					}
					if (j == i+1)
						Eprint( "<Exsfdata>", s ) ;
				}
			}

			else
			{
				// --------------------------------------------------------
				// TODO: 上のコードを確認。処理が重複しているように見える。
				// --------------------------------------------------------

				st = strchr(s,'=') ;
				// dt= atof(strchr(s,'=')+1);
				if (strncmp(s, "alo", 3) == 0)
				{
					//ex->alo = dt;
					if (strcmp(st+1, "Calc") == 0)
					{
						ex->alotype = 'V' ;
					}
					else if (( k = idsch ( st + 1, Schdl->Sch, NULL )) >= 0 )
					{
						ex->alo = &vall[k];
						ex->alotype = 'S' ;
					}
					else
					{
						ex->alo = envptr ( st + 1, Simc, 0, NULL, NULL, NULL ) ;
						ex->alotype = 'S' ;
					}
				}
				else
				{
					dt = atof(st+1) ;
					switch (s[0])
					{
					case 't':
						//傾斜角 (`t=xxxx`)
						ex->Wb =dt;
						break;

					case 'r':
						//前面の日射反射率 (`r=xxx`)
						ex->Rg =dt;
						break;

					case 'Z':
						//地中深さ[m] (`Z=xxx`)
						ex->Z =dt;
						ex->typ = 'E';
						break;

					case 'd': ex->erdff =dt;
						break;

					default :
						Eprint ( "<Exsfdata>", s ) ;
						break;
					}
				}
			}
			//ex++ ;
			if (strchr(s, ';')) break;
		}
	}
	
	i++ ;
	Exsf->Nexs = i ;
	Exsf->Exs->end = i;


	//
	// 3) 外表面リストの初期化
	//

	rad = CONST_PI/180.;
	
	ex = Exsf->Exs ;
	for ( i = 0; i < Exsf->Nexs; i++, ex++ )
	{
		//printf ( "i=%d\n", i ) ;

		if (ex->typ == 'S')
		{
			wa = ex->Wa*rad;
			wb = ex->Wb*rad;
			ex->cwa = cwa=cos(wa);
			ex->swa = swa=sin(wa);
			ex->Wz = cwb = cos(wb);
			ex->swb = swb = sin(wb);
			ex->Ww = swb*swa;

			//傾斜面の方向余弦
			ex->Ws = swb*cwa;

			ex->cbsa = cwb*swa;
			ex->cbca = cwb*cwa;
			
			//天空を見る形態係数
			ex->Fs = 0.5*(1.0+cwb);
		}
	}
}


/*
 * @brief 外表面入射日射量の計算
 *
 * @param[IN]     Nexs  外表面方位データのデータ数
 * @param[IN]     Wd    気象データ
 * @param[IN,OUT] Exs   外表面方位データ
 */
void Exsfsol(int Nexs, WDAT* Wd, EXSF* Exs)
{
	EXSF* ex = Exs;
	for (int i = 0; i < Nexs; i++, ex++)
	{
		//対象は一般外表面のみ(地下、地表は日射無し)
		if (ex->typ == 'S')
		{
			// 入射角のcos
			double cinc = Wd->Sh * ex->Wz + Wd->Sw * ex->Ww + Wd->Ss * ex->Ws;

			if (cinc > 0.0)
			{
				// プロファイル角のtan
				ex->tprof = (Wd->Sh * ex->swb - Wd->Sw * ex->cbsa - Wd->Ss * ex->cbca) / cinc;

				// プロファイル角の計算 [rad]
				ex->Prof = atan(ex->tprof);
				ex->tazm = (Wd->Sw * ex->cwa - Wd->Ss * ex->swa) / cinc;

				// 見かけの方位角の計算
				ex->Gamma = atan(ex->tazm);

				// 入射角のcos
				ex->cinc = cinc;
			}
			else
			{
				ex->Prof = 0.0;
				ex->Gamma = 0.0;
				ex->cinc = cinc = 0.0;
			}

			//直逹日射  [W/m2]
			ex->Idre = Wd->Idn * cinc;

			//拡散日射  [W/m2]
			ex->Idf = Wd->Isky * ex->Fs + ex->Rg * Wd->Ihor * (1.0 - ex->Fs);

			//全日射    [W/m2]
			ex->Iw = ex->Idre + ex->Idf;

			//夜間輻射  [W/m2]
			ex->rn = Wd->RN * ex->Fs;
		}
	}
}


/*
 * @brief ガラス日射熱取得の計算
 *
 * @param[IN]  Ag       面積
 * @param[IN]  tgtn     日射総合透過率
 * @param[IN]  Bn       吸収日射取得率
 * @param[IN]  cinc     入射角のcos
 * @param[IN]  Fsdw     影面積
 * @param[IN]  Idr      直達日射 [W/m2]
 * @param[IN]  Idf
 * @param[OUT] Qgt      透過日射熱取得 [W]
 * @param[OUT] Qga      吸収日射熱取得 [W]
 * @param[IN]  Cidtype  入射角特性のタイプ 'N':一般ガラス
 * @param[IN]  Profile  プロファイル角 [rad]
 * @param[IN]  Gamma    見かけの方位角
 */
void Glasstga(double Ag, double tgtn, double Bn, double cinc, double Fsdw,
	double Idr, double Idf, double* Qgt, double* Qga, char* Cidtype, double Profile, double Gamma)
{
	double    Cid, Cidf = 0.01;
	double	  Bid, Bidf = 0.0;
	double    Qt, Qb;

	Cid = Bid = 0.0;
	Qt = Qb = 0.0;

	// 標準
	if (strcmp(Cidtype, "N") == 0)
	{
		//printf("%lf\t", cinc);
		Cid = Glscid(cinc);
		Cidf = 0.91;

		Bid = Cid;
		Bidf = Cidf;
	}
	else
	{
		printf("xxxxx <eebslib.c  CidType=%s\n", Cidtype);
	}

	//if(cinc>0. && (Cid <= 0. || Cid > 1.0))
	//	printf("xxxxxxx Cid=%.3lf\n", Cid) ;
	//if(Cidf <= 0. || Cidf > 1.0)
	//	printf("xxxxxxx Cidf=%.3lf\n", Cidf) ;

	//if(cinc>0. && (Bid <= 0. || Bid > 2.5))
	//	printf("xxxxxxx Bid=%.3lf\n", Bid) ;

	// 透過日射量の計算
	Qt = Ag * (Cid * Idr * (1.0 - Fsdw) + Cidf * Idf);

	// 吸収日射量の計算
	Qb = Ag * (Bid * Idr * (1.0 - Fsdw) + Bidf * Idf);

	*Qgt = Qt * tgtn;
	*Qga = Qb * Bn;

	//printf("%lf\t%lf\n", Ag*(Cid*Idr*(1.0 - Fsdw)) * tgtn, Ag*(Cidf*Idf) * tgtn);
}


/*
 * @brief ガラスの直達日射透過率標準特性
 *
 * @param[IN] cinc
 *
 * @return 
 */
double Glscid(double cinc)
{
	return(dmax(0, cinc * (3.4167 + cinc * (-4.389 + cinc * (2.4948 - 0.5224 * cinc)))));
}


/*
 * @brief ガラスの直達日射透過率標準特性(普通複層ガラス)
 *
 * @param[IN] cinc
 *
 * @return
 */
double GlscidDG(double cinc)
{
	return(dmax(0, cinc * (0.341819 + cinc * (6.070709 + cinc * (-9.899236 + 4.495774 * cinc)))));
}


/*
 * @brief 外表面方位デ－タの動的配列の作成と初期化
 *
 * @param[OUT] E   外表面リストの動的配列
 * @param[IN]  N   外表面データのデータ数
 * @param[IN]  NN
 *
 * @return 成功した場合は1, 失敗した場合は0
 */
int	Exsfrealloc(EXSF** E, unsigned int N, unsigned int NN)
{
	int c = 1;
	unsigned int i = NN - N;

	EXSF* Buf = (EXSF*)malloc(i * sizeof(EXSF));

	if (Buf == NULL)
	{
		c = 0;
	}
	else
	{
		EXSF* B = Buf;

		for (i = N; i < NN; i++, B++)
		{
			B->name = NULL;
			B->typ = ' ';
			B->Wa = 0.0;
			B->Wb = 0.0;
			B->Rg = 0.0;
			B->Fs = 0.0;
			B->Wz = 0.0;
			B->Ww = 0.0;
			B->Ws = 0.0;
			B->swb = 0.0;
			B->cbsa = 0.0;
			B->cbca = 0.0;
			B->cwa = 0.0;
			B->swa = 0.0;
			B->Z = 0.0;
			B->erdff = 0.0;
			B->cinc = 0.0;
			B->tazm = 0.0;
			B->tprof = 0.0;
			B->Idre = 0.0;
			B->Idf = 0.0;
			B->Iw = 0.0;
			B->rn = 0.0;
			B->Tearth = 0.0;
			B->end = 0;
			B->alo = NULL;
		}

		for (i = 0; i < NN - N; i++)
			E[i + N] = &Buf[i];
	}

	return c;
}


/*
 * @brief 外表面方位デ－タのデータ数を調べる
 *
 * @param[IN] fi ファイルポインタ
 *
 * @return データ数
 */
int	ExsfCount(FILE* fi)
{
	int		N = 0;
	char	s[SCHAR];

	long ad = ftell(fi);

	while (fscanf(fi, " %s ", s), s[0] != '*')
	{
		/***********************
		if ( strncmp ( s, "r=", 2 ) == 0 )
		{
			fscanf ( fi, "%*[^;] " ) ;
			fscanf ( fi, " %*s " ) ;
		}
		else ****************/
		if (strchr(s, ';'))
			N++;
	}

	fseek(fi, ad, SEEK_SET);

	return (N);
}

