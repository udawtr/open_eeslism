#pragma once

//VAV VAVユニット


// --------------------------------------------
// VAV VAV ユニット
// --------------------------------------------
/*---- Satoh Debug VAV  2000/10/30 ----*/

///@brief VAVユニット(機器カタログデータ）
typedef struct vavca
{
	char* name,			/* カタログ名 */
		type;				/* A:VAV  W:VWV */
	double	Gmax,			/* 最大風量 [kg/s] */
		Gmin,			/* 最小風量 [kg/s] */
		dTset;				/* VWV用設定温度差　[℃] */
} VAVCA;

int    VAVdata (char *s, char *ss, VAVCA *vavca) ;
