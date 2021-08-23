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

/*     esidcode_s.c       */

#define _CRT_SECURE_NO_WARNINGS
#include "fesy.h"
#include "fnesy.h"
#include "fnlib.h"


/*  スケジュ－ル名からスケジュ－ル番号の検索   */
/* --------------------------------------------*/


/*
 * @brief 季節名から季節設定のインデックスを検索
 * @param[IN] code  季節名
 * @paran[IN] Seasn 季節設定の動的配列
 * @param[IN] err   見つからなかった場合に表示するエラーメッセージ
 * @return インデックス
 */
int idssn (char *code, SEASN *Seasn, char *err)
{
	//TODO: 見つからなかった場合の処理が弱い
	int j, N;
	
	N=Seasn->end;
	for (j=0; j<N; j++, Seasn++)
		if (strcmp(code, Seasn->name) == 0) break;
		if (j == N)
			printf("%s\n", err);
		return (j);
}


/*
 * @brief 曜日名から曜日設定のインデックスを検索
 * @param[IN] code  曜日名
 * @paran[IN] Seasn 曜日設定の動的配列
 * @param[IN] err   見つからなかった場合に表示するエラーメッセージ
 * @return インデックス
 */
int idwkd (char *code, WKDY *Wkdy, char *err)
{ 
	//TODO: 見つからなかった場合の処理が弱い
	int j, N;
	
	N=Wkdy->end;
	for (j=0; j<N; j++, Wkdy++)
		if (strcmp(code, Wkdy->name) == 0) break;
		if (j == N)
			printf("%s\n", err);
		return (j);
}


/*
 * @brief 設定値名から設定値スケジュール定義のインデックスを検索
 * @param[IN] code  設定名
 * @paran[IN] Seasn 設定値スケジュール定義の動的配列
 * @param[IN] err   見つからなかった場合に表示するエラーメッセージ
 * @return インデックス
 */
int iddsc (char *code, DSCH *Dsch, char *err)
{ 
	//TODO: 見つからなかった場合の処理が弱い
	int j, N;
	
	N=Dsch->end;
	for (j=0; j<N; j++, Dsch++)
		if (strcmp(code, Dsch->name) == 0) break;
		if (j == N)
			printf("%s\n", err);
		return (j);
}


/*
 * @brief 切替設定名から切替設定スケジュール定義のインデックスを検索
 * @param[IN] code  切替設定名
 * @paran[IN] Seasn 切替設定スケジュール定義の動的配列
 * @param[IN] err   見つからなかった場合に表示するエラーメッセージ
 * @return インデックス
 */
int iddsw (char *code, DSCW *Dscw, char *err)
{ 
	//TODO: 見つからなかった場合の処理が弱い
	int j, N;
	
	N=Dscw->end;
	for (j=0; j<N; j++, Dscw++)
		if (strcmp(code, Dscw->name) == 0) break;
		if (j == N)
			printf("%s\n", err);
		return (j);
}
/* ---------------------------------------- */

/* ---------------------------------------- */

int idsch (char *code, SCH *Sch, char *err)
{
	//TODO: 見つからなかった場合の処理が弱い
	int j, N;
	
	N=Sch->end;
	for (j=0; j<N; j++, Sch++)
		if (strcmp(code, Sch->name) == 0) break;
		if (j == N)
		{
			j = -1;
			
			if (err != NULL)
				Eprint("<idsch>", err);
		}
		return (j);
}
/* ---------------------------------------- */

int idscw (char *code, SCH *Scw, char *err)
{
	//TODO: 見つからなかった場合の処理が弱い
	int j, N;
	
	N=Scw->end;
	for (j=0; j<N; j++, Scw++)
		if (strcmp(code, Scw->name) == 0) break;
		if (j == N)
		{
			j = -1;
			
			if (err != NULL)
				Eprint("<idscw>", err);
		}
		return (j);
}
/* ---------------------------------------- */


int idroom (char *code, ROOM *Room, char *err)
{
	int		j, N;
	char	E[SCHAR] ;
	
	N = Room->end;
	for ( j = 0; j < N; j++, Room++ )
	{
		if ( strcmp ( code, Room->name ) == 0 )
			break;

		if ( j == N )
		{
			sprintf ( E, "Room=%s  %s", code, err ) ;
			Eprint ( "<idroom>", E ) ;
		}
	}

	return (j);
}

/* ---------------------------------------- */


/* ---------------------------------------- */
