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

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MODEL.h"
#include "exs.h"
#include "fnlib.h"
#define SCHAR 1024


/**
 * @file
 * @brief  入力データの読み込み
 */

/*

							  入力データの読み込み
							  FILE=DATAIN.c
							  Create Date=1999.6.7
							  */

void	preexit(void);
int		InputCount(FILE *fi, char *key);
char	*stralloc(char *s);

char NAME[SCHAR];

/*
 * @brief SBLK - HISASHI の読み取り 
 */
void HISASHI(FILE *fi, sunblk *sb)
{
	// 庇の名前
	fscanf(fi, "%s", NAME);
	sb->snbname = stralloc(NAME);

	//TODO: 庇の反射率のデフォルト値の設定

	// 色の初期値
	sb->rgb[0] = 0.0;
	sb->rgb[1] = 0.2;
	sb->rgb[2] = 0.0;

	while (fscanf(fi, "%s", NAME), NAME[0] != ';'){

		//対象建物の正面左下隅を原点(0,0)として、高さ方向を軸、幅方向を x 軸とした２次元座標系における、
		// この庇の左隅の２次元座標(x, y)
		if (strcmp(NAME, "-xy") == 0){
			fscanf(fi, "%lf", &sb->x);
			fscanf(fi, "%lf", &sb->y);
		}

		//庇の幅 W [m]と突き出し長さ D [m]
		else if (strcmp(NAME, "-DW") == 0){
			fscanf(fi, "%lf", &sb->D);
			fscanf(fi, "%lf", &sb->W);
		}

		//庇の角度α[°]。壁面に対して垂直の場合は、90[°]
		else if (strcmp(NAME, "-a") == 0)
			fscanf(fi, "%lf", &sb->WA);

		//(マニュアル未記載)
		else if (strcmp(NAME, "-rgb") == 0){
			fscanf(fi, "%lf", &sb->rgb[0]);
			fscanf(fi, "%lf", &sb->rgb[1]);
			fscanf(fi, "%lf", &sb->rgb[2]);
		}

		else {
			printf("ERROR parameter----HISASI: %s\n", NAME);
			//getch();
			preexit();
			exit(1);
		}
	}
}


/*
 * @brief SBLK - BARUKONI の読み取り 
 */
void BARUKO(FILE *fi, sunblk *sb)
{
	//バルコニー床面の反射率のデフォルト値
	sb->ref = 0.0;

	// 色の初期値
	sb->rgb[0] = 0.0;
	sb->rgb[1] = 0.2;
	sb->rgb[2] = 0.0;

	// バルコニーの名前
	fscanf(fi, "%s", NAME);
	sb->snbname = stralloc(NAME);

	while (fscanf(fi, "%s", NAME), NAME[0] != ';'){

		//象建物の正面左下隅を原点(0,0)として、高さ方向をy 軸、幅方向を x 軸とした２次元座標系における、
		// このバルコニーの左上隅の２次元座標(x, y)
		if (strcmp(NAME, "-xy") == 0){
			fscanf(fi, "%lf", &sb->x);
			fscanf(fi, "%lf", &sb->y);
		}

		//突き出し長さ D [m]、高さ H [m]、幅 W [m]、フェンス高さ h[m]
		else if (strcmp(NAME, "-DHWh") == 0){
			fscanf(fi, "%lf", &sb->D);
			fscanf(fi, "%lf", &sb->H);
			fscanf(fi, "%lf", &sb->W);
			fscanf(fi, "%lf", &sb->h);
		}

		//バルコニー床面の反射率 ref [-]。デフォルトは 0。
		else if (strcmp(NAME, "-ref") == 0)
		{
			fscanf(fi, "%lf", &sb->ref);
		}

		//(マニュアル未記載)
		else if (strcmp(NAME, "-rgb") == 0){
			fscanf(fi, "%lf", &sb->rgb[0]);
			fscanf(fi, "%lf", &sb->rgb[1]);
			fscanf(fi, "%lf", &sb->rgb[2]);
		}

		else {
			printf("ERROR parameter----WBARUKONI: %s\n", NAME);
			//getch();
			preexit();
			exit(1);
		}
	}
}


/*
 * @brief SBLK - SODEKABE の読み取り
 */
void SODEK(FILE *fi, sunblk *sb)
{
	//TODO: 庇の反射率のデフォルト値の設定

	// 色の初期値
	sb->rgb[0] = 0.0;
	sb->rgb[1] = 0.2;
	sb->rgb[2] = 0.0;

	//袖壁の名前
	fscanf(fi, "%s", NAME);
	sb->snbname = stralloc(NAME);

	while (fscanf(fi, "%s", NAME), NAME[0] != ';'){
		//対象建物の正面左下隅を原点(0,0)として、高さ方向を y 軸、幅方向を x 軸とした２次元座標系における、
		//この袖壁の左隅の２次元座標(x, y)
		if (strcmp(NAME, "-xy") == 0){
			fscanf(fi, "%lf", &sb->x);
			fscanf(fi, "%lf", &sb->y);
		}

		//突き出し長さ D [m]と高さ H [m]
		else if (strcmp(NAME, "-DH") == 0){
			fscanf(fi, "%lf", &sb->D);
			fscanf(fi, "%lf", &sb->H);
		}
		
		//庇の角度α[°]。壁面に対して垂直の場合は、90[°]
		else if (strcmp(NAME, "-a") == 0)
			fscanf(fi, "%lf", &sb->WA);

		//******************************************************************
		//TODO: 袖壁の反射率の読み込み(マニュアルにはあるが読み取っていない) P.96
		//******************************************************************

		//(マニュアル未記載)
		else if (strcmp(NAME, "-rgb") == 0){
			fscanf(fi, "%lf", &sb->rgb[0]);
			fscanf(fi, "%lf", &sb->rgb[1]);
			fscanf(fi, "%lf", &sb->rgb[2]);
		}
		else {
			printf("ERROR parameter----SODEKABE: %s\n", NAME);
			//getch();
			preexit();
			exit(1);
		}
	}
}


/*
 * @brief SBLK - MADOHIYOKE の読み取り
 */
void SCREEN(FILE *fi, sunblk *sb)
{
	//TODO: 射率のデフォルト値の設定

	// 色の初期値
	sb->rgb[0] = 0.0;
	sb->rgb[1] = 0.2;
	sb->rgb[2] = 0.0;

	//ロールスクリーンのような窓に対して平行に設置する日よけの名前
	fscanf(fi, "%s", NAME);
	sb->snbname = stralloc(NAME);

	while (fscanf(fi, "%s", NAME), NAME[0] != ';'){

		//対象建物の正面左下隅を原点(0,0)として、高さ方向y 軸、幅方向を x 軸とした２次元座標系における、
		//このスクリーンの左上隅２次元座標(x, y)
		if (strcmp(NAME, "-xy") == 0){
			fscanf(fi, "%lf", &sb->x);
			fscanf(fi, "%lf", &sb->y);
		}

		//窓との間隔 D [m]、高さ H [m]、幅 W [m]
		else if (strcmp(NAME, "-DHW") == 0){
			fscanf(fi, "%lf", &sb->D);
			fscanf(fi, "%lf", &sb->H);
			fscanf(fi, "%lf", &sb->W);
		}

		//******************************************************************
		//TODO: 反射率の読み込み(マニュアルにはあるが読み取っていない) P.97
		//******************************************************************

		else if (strcmp(NAME, "-rgb") == 0){
			fscanf(fi, "%lf", &sb->rgb[0]);
			fscanf(fi, "%lf", &sb->rgb[1]);
			fscanf(fi, "%lf", &sb->rgb[2]);
		}

		else {
			printf("ERROR paramater---MADOHIYOKE: %s\n", NAME);
			//getch();
			preexit();
			exit(1);
		}
	}
}
/*----------------------------------------------------------------*/
void rmpdata(FILE *fi, RRMP *rp, MADO *wp){

	rp->ref = 0.0;
	rp->grpx = 1.0;

	rp->rgb[0] = 0.9;
	rp->rgb[1] = 0.9;
	rp->rgb[2] = 0.9;

	fscanf(fi, "%s", NAME);
	//printf("<rmpdata> 1 NAME=%s\n", NAME);
	rp->rmpname = stralloc(NAME);
	fscanf(fi, "%s", NAME);
	//printf("<rmpdata> 2 NAME=%s\n", NAME);
	rp->wallname = stralloc(NAME);

	while (fscanf(fi, "%s", NAME), NAME[0] != ';'){

		//printf("<rmpdata> 3 NAME=%s\n", NAME);
		if (strcmp(NAME, "-xyb") == 0){
			fscanf(fi, "%lf", &rp->xb0);
			fscanf(fi, "%lf", &rp->yb0);
		}

		else if (strcmp(NAME, "-WH") == 0){
			fscanf(fi, "%lf", &rp->Rw);
			fscanf(fi, "%lf", &rp->Rh);
		}

		else if (strcmp(NAME, "-ref") == 0)
			fscanf(fi, "%lf", &rp->ref);

		else if (strcmp(NAME, "-grpx") == 0)
			fscanf(fi, "%lf", &rp->grpx);

		else if (strcmp(NAME, "-rgb") == 0){
			fscanf(fi, "%lf", &rp->rgb[0]);
			fscanf(fi, "%lf", &rp->rgb[1]);
			fscanf(fi, "%lf", &rp->rgb[2]);
		}

		else {
			printf("ERROR parameter----RMP: %s\n", NAME);
			//getch();
			preexit();
			exit(1);
		}
	}

	rp->sumWD = 0;
	//wp = rp->WD;
	while (fscanf(fi, "%s", NAME), NAME[0] != ';'){

		//printf("<rmpdata> 4 NAME=%s\n", NAME);
		wp->ref = 0.0;
		wp->grpx = 1.0;

		wp->rgb[0] = 0.0;
		wp->rgb[1] = 0.3;
		wp->rgb[2] = 0.8;

		if (strcmp(NAME, "WD") != 0){
			printf("ERROR parameter----WD: %s\n", NAME);
			//getch();
			preexit();
			exit(1);
		}

		rp->sumWD = rp->sumWD + 1;

		fscanf(fi, "%s", NAME);
		//printf("<rmpdata> 5 NAME=%s\n", NAME);
		wp->winname = stralloc(NAME);

		while (fscanf(fi, "%s", NAME), NAME[0] != ';'){

			//printf("<rmpdata> 6 NAME=%s\n", NAME);
			if (strcmp(NAME, "-xyr") == 0){
				fscanf(fi, "%lf", &wp->xr);
				fscanf(fi, "%lf", &wp->yr);
			}

			else if (strcmp(NAME, "-WH") == 0){
				fscanf(fi, "%lf", &wp->Ww);
				fscanf(fi, "%lf", &wp->Wh);
			}

			else if (strcmp(NAME, "-ref") == 0)
				fscanf(fi, "%lf", &wp->ref);

			else if (strcmp(NAME, "-grpx") == 0)
				fscanf(fi, "%lf", &wp->grpx);

			else if (strcmp(NAME, "-rgb") == 0){
				fscanf(fi, "%lf", &wp->rgb[0]);
				fscanf(fi, "%lf", &wp->rgb[1]);
				fscanf(fi, "%lf", &wp->rgb[2]);
			}

			else {
				printf("ERROR parameter----WD: %s\n", NAME);
				//getch();
				preexit();
				exit(1);
			}
		}
		wp++;
	}
}
/*------------------------------------------------------------------*/
void rectdata(FILE *fi, OBS *obs){

	obs->ref[0] = 0.0;

	obs->rgb[0] = 0.7;
	obs->rgb[1] = 0.7;
	obs->rgb[2] = 0.7;

	fscanf(fi, "%s", NAME);
	obs->obsname = stralloc(NAME);

	while (fscanf(fi, "%s", NAME), NAME[0] != ';'){

		if (strcmp(NAME, "-xyz") == 0){
			fscanf(fi, "%lf", &obs->x);
			fscanf(fi, "%lf", &obs->y);
			fscanf(fi, "%lf", &obs->z);
		}

		else if (strcmp(NAME, "-WH") == 0){
			fscanf(fi, "%lf", &obs->W);
			fscanf(fi, "%lf", &obs->H);
		}

		else if (strcmp(NAME, "-WaWb") == 0){
			fscanf(fi, "%lf", &obs->Wa);
			fscanf(fi, "%lf", &obs->Wb);
		}

		else if (strcmp(NAME, "-ref") == 0)
			fscanf(fi, "%lf", &obs->ref[0]);

		else if (strcmp(NAME, "-rgb") == 0){
			fscanf(fi, "%lf", &obs->rgb[0]);
			fscanf(fi, "%lf", &obs->rgb[1]);
			fscanf(fi, "%lf", &obs->rgb[2]);
		}

		else {
			printf("ERROR parameter----OBS->rect: %s\n", NAME);
			//getch();
			preexit();
			exit(1);
		}
	}
}
/*------------------------------------------------------------------*/
void cubdata(FILE *fi, OBS *obs){

	int i;

	for (i = 0; i < 3; i++)
		obs->ref[i] = 0.0;

	obs->rgb[0] = 0.7;
	obs->rgb[1] = 0.7;
	obs->rgb[2] = 0.7;

	fscanf(fi, "%s", NAME);
	obs->obsname = stralloc(NAME);

	while (fscanf(fi, "%s", NAME), NAME[0] != ';'){

		if (strcmp(NAME, "-xyz") == 0){
			fscanf(fi, "%lf", &obs->x);
			fscanf(fi, "%lf", &obs->y);
			fscanf(fi, "%lf", &obs->z);
		}

		else if (strcmp(NAME, "-WDH") == 0){
			fscanf(fi, "%lf", &obs->W);
			fscanf(fi, "%lf", &obs->D);
			fscanf(fi, "%lf", &obs->H);
		}

		else if (strcmp(NAME, "-Wa") == 0)
			fscanf(fi, "%lf", &obs->Wa);

		else if (strcmp(NAME, "-ref0") == 0)
			fscanf(fi, "%lf", &obs->ref[0]);

		else if (strcmp(NAME, "-ref1") == 0)
			fscanf(fi, "%lf", &obs->ref[1]);

		else if (strcmp(NAME, "-ref2") == 0)
			fscanf(fi, "%lf", &obs->ref[2]);

		else if (strcmp(NAME, "-ref3") == 0)
			fscanf(fi, "%lf", &obs->ref[3]);

		else if (strcmp(NAME, "-rgb") == 0){
			fscanf(fi, "%lf", &obs->rgb[0]);
			fscanf(fi, "%lf", &obs->rgb[1]);
			fscanf(fi, "%lf", &obs->rgb[2]);
		}

		else {
			printf("ERROR parameter----OBS->cube: %s\n", NAME);
			//getch();
			preexit();
			exit(1);
		}
	}
}
/*-------------------------------------------------------------------*/
void tridata(FILE *fi, OBS *obs){

	obs->ref[0] = 0.0;

	obs->rgb[0] = 0.7;
	obs->rgb[1] = 0.7;
	obs->rgb[2] = 0.7;

	fscanf(fi, "%s", obs->obsname);

	while (fscanf(fi, "%s", NAME), NAME[0] != ';'){

		if (strcmp(NAME, "-xyz") == 0){
			fscanf(fi, "%lf", &obs->x);
			fscanf(fi, "%lf", &obs->y);
			fscanf(fi, "%lf", &obs->z);
		}

		else if (strcmp(NAME, "-WH") == 0){
			fscanf(fi, "%lf", &obs->W);
			fscanf(fi, "%lf", &obs->H);
		}

		else if (strcmp(NAME, "-WaWb") == 0){
			fscanf(fi, "%lf", &obs->Wa);
			fscanf(fi, "%lf", &obs->Wb);
		}

		else if (strcmp(NAME, "-ref") == 0)
			fscanf(fi, "%lf", &obs->ref[0]);

		else if (strcmp(NAME, "-rgb") == 0){
			fscanf(fi, "%lf", &obs->rgb[0]);
			fscanf(fi, "%lf", &obs->rgb[1]);
			fscanf(fi, "%lf", &obs->rgb[2]);
		}

		else {
			printf("ERROR parameter----OBS->triangle: %s\n", NAME);
			//getch();
			preexit();
			exit(1);
		}
	}
}
/*-------------------------------------------------------------------*/
// 20170503 higuchi add 
void dividdata(FILE *fi, int *monten, double *DE) {

	//if (strcmp(NAME, "DIVID") != 0) {
	//	printf("error DIVID\n", NAME);
	//	exit(1);
	//}

	while (fscanf(fi, "%s", NAME), NAME[0] != ';') {

		if (strcmp(NAME, "DE") == 0) {
			//printf("Name=%s\n", NAME);
			fscanf(fi, "%lf", DE);
		}
		else if (strcmp(NAME, "MONT") == 0)
			fscanf(fi, "%d", monten);

		else {
			printf("ERROR parameter----DIVID: %s\n", NAME);
			preexit();
			exit(1);
		}

	}

	fscanf(fi, "%s", NAME);

}
void treedata(FILE *fi, int *treen, TREE **tree){
	int i;
	int Ntree;
	TREE *tred;
	// BDPの数を数える
	Ntree = InputCount(fi, ";");
	printf("<treedata> Ntree=%d\n", Ntree);
	if (Ntree > 0)
	{
		*tree = (TREE *)malloc(sizeof (TREE)* Ntree);
		if (*tree == NULL)
			printf("<treedata> treeのメモリが確保できません\n");

		// 構造体の初期化
		tred = *tree;
		for (i = 0; i < Ntree; i++, tred++)
		{
			tred->treename = tred->treetype = NULL;
			tred->x = tred->y = tred->z = tred->W1 = tred->W2 = tred->W3 = tred->W4 = 0.;
			tred->H1 = tred->H2 = tred->H3 = 0.0;
		}
	}

	*treen = 0;
	tred = *tree;

	while (fscanf(fi, "%s", NAME), NAME[0] != '*'){

		tred->treetype = stralloc(NAME);

		fscanf(fi, "%s", NAME);
		tred->treename = stralloc(NAME);


		if (strcmp(tred->treetype, "treeA") == 0){
			while (fscanf(fi, "%s", NAME), NAME[0] != ';'){

				if (strcmp(NAME, "-xyz") == 0){
					fscanf(fi, "%lf", &tred->x);
					fscanf(fi, "%lf", &tred->y);
					fscanf(fi, "%lf", &tred->z);
				}

				else if (strcmp(NAME, "-WH1") == 0){
					fscanf(fi, "%lf", &tred->W1);
					fscanf(fi, "%lf", &tred->H1);
				}

				else if (strcmp(NAME, "-WH2") == 0){
					fscanf(fi, "%lf", &tred->W2);
					fscanf(fi, "%lf", &tred->H2);
				}

				else if (strcmp(NAME, "-WH3") == 0){
					fscanf(fi, "%lf", &tred->W3);
					fscanf(fi, "%lf", &tred->H3);
				}

				else if (strcmp(NAME, "-W4") == 0)
					fscanf(fi, "%lf", &tred->W4);

				else {
					printf("ERROR parameter----TREE: %s %s\n", tred->treename, NAME);
					//getch();
					preexit();
					exit(1);
				}
			}
		}

		else{
			printf("ERROR parameter----TREE: %s\n", tred->treetype);
			//getch();
			preexit();
			exit(1);
		}

		(*treen)++;
		tred++;
		/*--
		printf("treen=%d\n",*treen) ;
		--*/
	}
}

/*-------------------------*/
void polydata(FILE *fi, int *polyn, POLYGN **poly){

	int i;
	int	Npoly;
	void	matinit(double *A, int N);
	POLYGN *polyp;
	// BDPの数を数える
	Npoly = InputCount(fi, ";");
	printf("<polydata> Npoly=%d\n", Npoly);
	if (Npoly > 0)
	{
		*poly = (POLYGN *)malloc(sizeof (POLYGN)* Npoly);
		if (*poly == NULL)
			printf("<polydata> polyのメモリが確保できません\n");

		// 構造体の初期化
		polyp = *poly;
		for (i = 0; i < Npoly; i++, polyp++)
		{
			polyp->polyknd[0] = '\0';
			polyp->polyname = polyp->wallname = NULL;
			polyp->polyd = 0;
			polyp->ref = polyp->refg = polyp->grpx = 0.;
			polyp->P = NULL;
			matinit(polyp->rgb, 3);
		}
	}

	*polyn = 0;
	polyp = *poly;
	while (fscanf(fi, "%s", NAME), NAME[0] != '*'){

		polyp->grpx = 1.0;

		polyp->rgb[0] = 0.9;
		polyp->rgb[1] = 0.9;
		polyp->rgb[2] = 0.9;

		strcpy(polyp->polyknd, NAME);
		if ((strcmp(polyp->polyknd, "RMP") != 0) && (strcmp(polyp->polyknd, "OBS") != 0)){
			printf("ERROR parameter----POLYGON: %s  <RMP> or <OBS> \n", polyp->polyknd);
			//getch();
			preexit();
			exit(1);
		}

		fscanf(fi, "%d", &polyp->polyd);
		polyp->P = (XYZ *)malloc(sizeof(XYZ)*polyp->polyd);

		fscanf(fi, "%s", NAME);
		polyp->polyname = stralloc(NAME);
		fscanf(fi, "%s", NAME);
		polyp->wallname = stralloc(NAME);

		while (fscanf(fi, "%s", NAME), NAME[0] != ';'){
			if (strcmp(NAME, "-xyz") == 0){
				for (i = 0; i < polyp->polyd; i++){
					fscanf(fi, "%lf", &polyp->P[i].X);
					fscanf(fi, "%lf", &polyp->P[i].Y);
					fscanf(fi, "%lf", &polyp->P[i].Z);
				}
			}

			else if (strcmp(NAME, "-rgb") == 0){
				fscanf(fi, "%lf", &polyp->rgb[0]);
				fscanf(fi, "%lf", &polyp->rgb[1]);
				fscanf(fi, "%lf", &polyp->rgb[2]);
			}

			else if (strcmp(NAME, "-ref") == 0)
				fscanf(fi, "%lf", &polyp->ref);

			else if (strcmp(NAME, "-refg") == 0)
				fscanf(fi, "%lf", &polyp->refg);

			else if (strcmp(NAME, "-grpx") == 0)
				fscanf(fi, "%lf", &polyp->grpx);

			else{
				printf("ERROR parameter----POLYGON: %s\n", NAME);
				//getch();
				preexit();
				exit(1);
			}
		}
		(*polyn)++;
		polyp++;
		/*--
		printf("polyn=%d\n",*polyn) ;
		--*/
	}
}


/*
 * @brief BDP 方位別表面 の読み込み
 */
void bdpdata(FILE *fi, int *bdpn, BBDP **bp,EXSFS *Exsf){

	RRMP *rp;
	MADO *wp;
	sunblk *sb;
	int	Nbdp;
	BBDP *bbdp;

	//
	// 1-1) BDP メモリ確保、初期化
	//

	// BDPの数を数える
	Nbdp = InputCount(fi, "*");
	//printf("<bdpdata> Nbdp=%d\n", Nbdp);
	if (Nbdp > 0)
	{
		*bp = (BBDP *)malloc(sizeof (BBDP)* Nbdp);
		if (*bp == NULL)
			printf("<bdpdata> bpのメモリが確保できません\n");
		
		bbdp = *bp;
		int i;
		for (i = 0; i < Nbdp; i++, bbdp++)
		{
			bbdp->bdpname = NULL;
			bbdp->exh = bbdp->exw = 0.;
			bbdp->sumRMP = bbdp->sumsblk = 0;
			bbdp->x0 = bbdp->y0 = bbdp->z0 = 0.;
			bbdp->Wa = bbdp->Wb = 0.;
			bbdp->SBLK = NULL;
			bbdp->RMP = NULL;
			bbdp->exsfname = NULL;
		}
	}

	//
	// 1-2) BDP 読み込み
	//

	bbdp = *bp;
	//sb = bbdp->SBLK;
	//rp = bbdp->RMP;
	//wp = rp->WD;

	*bdpn = 0;

	while (fscanf(fi, "%s", NAME), NAME[0] != '*')
	{
		//printf("<bdpdata> 1 NAME=%s", NAME);
		if (strcmp(NAME, "BDP") != 0){
			printf("error BDP\n");
			exit(1);
		}
		//printf("<bdpdata> 2 NAME=%s", NAME);

		//1つの建築外表面名 (bdpname)
		fscanf(fi, "%s", NAME);
		bbdp->bdpname = stralloc(NAME);
		//printf("<bdpdata> 3 NAME=%s", NAME);

		while (fscanf(fi, "%s", NAME), NAME[0] != ';'){
			//printf("<bdpdata> 4 NAME=%s", NAME);

			if (strcmp(NAME, "-xyz") == 0){
				//-xyz x0 y0 z0
				// 対象建物の正面左下隅を原点とする３次元座標系(図2.10.8）における、
				// この外表面の左下隅の３次元座標(x0, y0, z0)
				fscanf(fi, "%lf", &bbdp->x0);
				fscanf(fi, "%lf", &bbdp->y0);
				fscanf(fi, "%lf", &bbdp->z0);
			}

			else if (strcmp(NAME, "-WA") == 0)
			{
				//-WA Wa
				//方位角 Wa [°]
				//真南を 0°、東向きを－、西向きを＋とし、真北を 180°または - 180°で表す。
				fscanf(fi, "%lf", &bbdp->Wa);
			}
			else if (strcmp(NAME, "-WB") == 0)
			{
				//-WB Wb
				//傾斜角 Wb [°]
				//水平面が 0°、垂直面が 90°として、0～180°の範囲で指定する。
				fscanf(fi, "%lf", &bbdp->Wb);
			}

			else if (strcmp(NAME, "-WH") == 0)
			{
				//WH exw exh
				//外表面の幅 exw [m]と高さ exh [m]
				fscanf(fi, "%lf", &bbdp->exw);
				fscanf(fi, "%lf", &bbdp->exh);
			}

			// Satoh修正（2018/1/23）
			else if (strcmp(NAME, "-exs") == 0)
			{
				fscanf(fi, "%s", NAME);
				bbdp->exsfname = stralloc(NAME);
				//外表面の検索
				EXSF *Exs;
				int id, i;
				id = 0;
				Exs = Exsf->Exs;
				for (i = 0; i < Exsf->Nexs; i++, Exs++)
				{
					if (strcmp(bbdp->exsfname, Exs->name) == 0)
					{
						bbdp->Wa = Exs->Wa;
						bbdp->Wb = Exs->Wb;
						id = 1;
						break;
					}
				}
				if (id == 0)
					printf("BDP<%s> %s is not found in EXSRF\n", bbdp->bdpname, bbdp->exsfname);
			}
			else {
				printf("ERROR parameter----BDP %s\n", NAME);
				//getch();
				preexit();
				exit(1);
			}
		}

		//
		// 2-1) SBLK メモリ確保と初期化
		//

		// SBLKの個数を数えてメモリを確保
		int Nsblk;
		int		SBLKCount(FILE *fi);
		Nsblk = SBLKCount(fi);
		//printf("<bdpdata> Nsblk=%d\n", Nsblk);
		// メモリの確保
		if (Nsblk > 0)
		{
			bbdp->SBLK = (sunblk *)malloc(sizeof(sunblk)*Nsblk);
			if (bbdp->SBLK == NULL)
				printf("<bdpdata> SBLKのメモリが確保できません\n");

			sb = bbdp->SBLK;
			int i;
			for (i = 0; i < Nsblk; i++, sb++)
			{
				sb->D = sb->H = sb->h = sb->ref = sb->W = sb->WA = sb->x = sb->y = 0.0;
				sb->sbfname = sb->snbname = NULL;
				matinit(sb->rgb, 3);
			}
		}

		//
		// 2-2) RMP メモリ確保と初期化
		//

		// RMPの個数を数えてメモリを確保
		int Nrmp;
		int		RMPCount(FILE *fi);
		Nrmp = RMPCount(fi);
		//printf("<bdpdata> Nrmp=%d\n", Nrmp);
		// メモリの確保
		if (Nrmp > 0)
		{
			bbdp->RMP = (RRMP *)malloc(sizeof(RRMP)*Nrmp);
			if (bbdp->RMP == NULL)
				printf("<bdpdata> RMPのメモリが確保できません\n");

			rp = bbdp->RMP;
			int i;
			for (i = 0; i < Nrmp; i++, rp++)
			{
				rp->rmpname = rp->wallname = NULL;
				rp->sumWD = 0;
				rp->ref = rp->xb0 = rp->yb0 = rp->Rw = rp->Rh = rp->grpx = 0.0;
				matinit(rp->rgb, 3);
				rp->WD = NULL;
			}
		}

		//
		// 2-3) SBLK, RMP の読み込み
		//

		sb = bbdp->SBLK;
		rp = bbdp->RMP;
		if (rp != NULL)
			wp = rp->WD;
		while (fscanf(fi, "%s", NAME), NAME[0] != '*'){

			//-----------------------------------------------------
			//SBLK 付設障害物
			//-----------------------------------------------------
			if (strcmp(NAME, "SBLK") == 0){
				// 反射率のデフォルト値の設定
				// TODO: 個別の初期化したほうが良い
				sb->ref = 0.0;

				fscanf(fi, "%s", NAME);
				sb->sbfname = stralloc(NAME);

				if (strcmp(sb->sbfname, "HISASI") == 0)
				{
					//SBLK - HISASH 庇
					HISASHI(fi, sb);
				}
				else if (strcmp(sb->sbfname, "BARUKONI") == 0)
				{
					//SBLK - BARUKONI バルコニー
					BARUKO(fi, sb);
				}
				else if (strcmp(sb->sbfname, "SODEKABE") == 0)
				{
					//SBLK - SODEKABE 袖壁
					SODEK(fi, sb);
				}
				else  if (strcmp(sb->sbfname, "MADOHIYOKE") == 0)
				{
					//SBLK - MADOHIYOKE ロールスクリーンのような窓に対して平行に設置する日よけ
					SCREEN(fi, sb);
				}
				else
				{
					printf("ERROR----\nhiyoke no syurui <HISASI> or <BARUKONI> or <SODEKABE> or <MADOHIYOKE> : %s \n", sb->sbfname);
					//getch();
					preexit();
					exit(1);
				}

				sb++;
				bbdp->sumsblk++;
			}

			//-----------------------------------------------------
			//RMP 建築室外壁面
			//-----------------------------------------------------
			else if (strcmp(NAME, "RMP") == 0)
			{
				// WDの数を数えてメモリを確保
				int Nwd;
				int		WDCount(FILE *fi);
				Nwd = WDCount(fi);
				//printf("<bdpdata> Nwd=%d\n", Nwd);
				if (Nwd > 0)
				{
					rp->WD = (MADO *)malloc(sizeof(MADO)*Nwd);
					if (rp->WD == NULL)
						printf("<bdpdata> rp->WDのメモリが確保できません\n");
					wp = rp->WD;
					int i;
					for (i = 0; i < Nwd; i++, wp++)
					{
						wp->winname = NULL;
						matinit(wp->rgb, 3);
						wp->grpx = wp->ref = wp->Wh = wp->xr = wp->yr = 0.0;
					}
				}
				rp->ref = 0.0;
				wp = rp->WD;
				bbdp->sumRMP++;
				rmpdata(fi, rp, wp);

				rp++;
				wp = rp->WD;
			}
			else
			{
				printf("ERROR----<SBLK> or <RMP> : %s \n", NAME);
				//getch();
				preexit();
				exit(1);
			}
		}

		(*bdpn)++;
		bbdp++;

		//rp = bbdp->RMP;
		//if (rp != NULL)
		//	wp = rp->WD;
		//sb = bbdp->SBLK;

	}
}
/*--------------------------------------------------------------------------*/
void obsdata(FILE *fi, int *obsn, OBS **obs)
{

	int i;
	int	Nobs;
	OBS	*obsp;

	// BDPの数を数える
	Nobs = InputCount(fi, ";");
	//printf("<obsdata> Nobs=%d\n", Nobs);
	if (Nobs > 0)
	{
		*obs = (OBS *)malloc(sizeof (OBS)* Nobs);
		if (*obs == NULL)
			printf("<obsdata> obsのメモリが確保できません\n");

		obsp = *obs;
		for (i = 0; i < Nobs; i++, obsp++)
		{
			obsp->fname = obsp->obsname = NULL;
			obsp->x = obsp->y = obsp->z = obsp->H = obsp->D = obsp->W = obsp->Wa = obsp->Wb = 0.0;
			matinit(obsp->ref, 4);
			matinit(obsp->rgb, 3);
		}
	}

	*obsn = 0;
	obsp = *obs;
	while (fscanf(fi, "%s", NAME), NAME[0] != '*'){
		// OBS名称
		obsp->fname = stralloc(NAME);

		for (i = 0; i < 4; i++)
			obsp->ref[i] = 0.0;

		if (strcmp(obsp->fname, "rect") == 0)
			rectdata(fi, obsp);

		else if (strcmp(obsp->fname, "cube") == 0)
			cubdata(fi, obsp);

		else if (strcmp(obsp->fname, "r_tri") == 0)
			tridata(fi, obsp);

		else if (strcmp(obsp->fname, "i_tri") == 0)
			tridata(fi, obsp);

		else {
			printf("ERROR parameter----OBS : %s\n", obsp->fname);
			//getch();
			preexit();
			exit(1);
		}

		obsp++;
		(*obsn)++;
	}
}

int		InputCount(FILE *fi, char *key)
{
	int		N;
	long	ad;
	char	s[SCHAR]; // ss[SCHAR] ;

	N = 0;
	ad = ftell(fi);

	while (fscanf(fi, "%s", s) != EOF && *s != '*')
	{
		N++;

		while (fscanf(fi, "%s", s) != EOF)
		{
			if (strcmp(s, key) == 0)
				break;
		}
	}

	fseek(fi, ad, SEEK_SET);
	return (N);
}

int		SBLKCount(FILE *fi)
{
	int		N;
	long	ad;
	char	s[SCHAR]; // ss[SCHAR] ;

	N = 0;
	ad = ftell(fi);

	while (fscanf(fi, "%s", s) != EOF && *s != '*')
	{
		if (strcmp(s, "SBLK") == 0)
			N++;
	}

	fseek(fi, ad, SEEK_SET);
	return (N);
}

int		RMPCount(FILE *fi)
{
	int		N;
	long	ad;
	char	s[SCHAR]; // ss[SCHAR] ;

	N = 0;
	ad = ftell(fi);

	while (fscanf(fi, "%s", s) != EOF && *s != '*')
	{
		if (strcmp(s, "RMP") == 0)
			N++;
	}

	fseek(fi, ad, SEEK_SET);
	return (N);
}

int		WDCount(FILE *fi)
{
	int		N;
	long	ad;
	char	s[SCHAR]; // ss[SCHAR] ;

	N = 0;
	ad = ftell(fi);

	int Flg;
	Flg = 0;
	while (fscanf(fi, "%s", s) != EOF)
	{
		if (strcmp(s, "WD") == 0)
			N++;

		if (strcmp(s, ";") == 0)
		{
			if (Flg == 1) // ;が2つ連続したら
				break;
			else
				Flg = 1;
		}
		else
			Flg = 0;
	}

	fseek(fi, ad, SEEK_SET);
	return (N);
}

int	OPcount(int Nbdp, BBDP *Bdp, int Npoly, POLYGN *poly)
{
	// 初期化
	int Nop = 0;

	int i;
	for (i = 0; i < Nbdp; i++, Bdp++)
	{
		Nop += Bdp->sumRMP;
		RRMP *RMP;
		RMP = Bdp->RMP;
		int j;
		for (j = 0; j < Bdp->sumRMP; j++, RMP++)
			Nop += RMP->sumWD;
	}
	
	for (i = 0; i < Npoly; i++, poly++)
	{
		if (strcmp(poly->polyknd, "RMP") == 0)
			Nop++;
	}

	return(Nop);
}

int LPcount(int Nbdp, BBDP *Bdp, int Nobs, OBS *Obs, int Ntree, int Npoly, POLYGN *poly)
{
	// 初期化
	int Nlp = 0;
	int i;
	for (i = 0; i < Nbdp; i++, Bdp++)
	{
		int j;
		sunblk *snbk;
		snbk = Bdp->SBLK;
		for (j = 0; j < Bdp->sumsblk; j++, snbk++)
		{
			if (strcmp(snbk->sbfname, "BARUKONI") == 0)
				Nlp += 5;
			else
				Nlp++;
		}
	}

	for (i = 0; i < Nobs; i++, Obs++)
	{
		if (strcmp(Obs->fname, "cube") == 0)
			Nlp += 4;
		else
			Nlp++;
	}

	// 樹木用
	Nlp += Ntree * 20;

	// ポリゴン
	for (i = 0; i < Npoly; i++, poly++)
	{
		if (strcmp(poly->polyknd, "RMP") == 0 || strcmp(poly->polyknd, "OBS") == 0)
			Nlp++;
	}

	return(Nlp);
}