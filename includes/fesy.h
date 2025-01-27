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

/* fesy.h */

#pragma once

// TODO: 要説明
#include "esize.h"

// TODO: 要説明
#include "common.h"

// TODO: 要説明
#include "model/wthrd.h"

// 2.4 建築データ
// <入力データファイル>建築データのモデルについて構造体の定義
// WALL, WINDOW, SUNBRK, ROOM, RESI, AAPL, VENT
#include "model/build.h"

// 2.5 設備機器データ
// <入力データファイル>設備機器データのモデルについて構造体の定義
// EQPCAT, SYSCMP
#include "mc/eqptyp.h"

// 2.6 システム経路
// <入力データファイル>システム経路のモデルについて構造体の定義
// SYSPTH
#include "model/eepath.h"

// 2.7 制御データ
// <入力データファイル>システム経路のモデルについて構造体の定義
// CONTL
#include "model/control.h"

// 2.8 スケジュールデータ
// <入力データファイル>スケジュールのモデルについて構造体の定義
// SCHTB, SCHNM
#include "model/sched.h"

// 2.9 ファイル上のデータによる条件設定
// <入力データファイル>システム経路のモデルについて構造体の定義
// VCFILE
#include "model/simcon.h"

// シミュレーション結果の構造体の定義
#include "model/eps.h"

// TODO: 要説明
#include "model/daysum.h"
