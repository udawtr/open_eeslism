#pragma once

#include <stdio.h>
#include "eqptyp.h"

//---------------------------------------------------------------
// 2.5.1 機器仕様（機器カタログデータ
// 機器カタログデータの読み込み
//---------------------------------------------------------------

/*
 * @brief 機器カタログデータの読み込み
 * @param[IN]  f     読込元ファイルポインタ
 * @param[IN]  dsn
 * @param[OUT] Eqcat 機器カタログデータの動的配列
 */
void Eqcadata (FILE *f, char *dsn, EQCAT *Eqcat);



