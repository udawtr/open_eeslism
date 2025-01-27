﻿#pragma once

/**
 * @fn
 * 入力データファイルの計算していGDATAの読み取り P.17
 * @param (wfname) 気象データファイル名
 */
void Gdata(FILE *fi, char *dsn, char *File, char **wfname, char **ofname,
	int *dtm, int *sttmm, int *dayxs, int *days, int *daye, double *Tini, int *pday,
	int *wdpri, int *revpri, int *pmvpri, char *helmkey, int *MaxIterate, DAYTM *Daytm, WDAT *Wd, char *perio);
