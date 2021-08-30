#pragma once


// --------------------------------------------
// THEX 全熱交換器
// --------------------------------------------
/*---- Satoh Debug 熱交換換気  2001/8/22 ----*/

///@brief 全熱交換器(機器カタログデータ）
typedef struct thexca
{
	char* name;			/* カタログ名 */
//		type ;				/* t:顕熱交換型　h：全熱交換型 */
	double	et,				/* 温度効率 */
		eh;				/* エンタルピ効率 */
} THEXCA;


int		Thexdata ( char *s, THEXCA *Thexca ) ;
