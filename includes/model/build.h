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

/*   build.h  */

#pragma once

#include <string.h>
#include "exs.h"
#include "esize.h"
#include "daysum.h"

/**
 * @file
 * @brief <入力データファイル>建築データのモデルについて構造体の定義
 * @details
 * 
 * 2.4 建築データ (EESLISM7.2入力データ作成マニュアル.pdf)
 * 
 * モデルの関連図
 *
 * <PRE>
 * *- WALL
 * +- WINDOW
 * +- SUNBRK
 * +- ROOM
 * +- RESI
 * +- AAPL
 * +- VENT
 * </PRE>
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * WALL :    壁体構成：室構成データで使用する外壁、内壁、床、天井、屋根など材料構成の定義
 * WINDOW:   窓：室構成データで使用する窓の熱貫流率、日射透過率などの定義
 * SUNBRK:   日除け：室構成データで使用する日除けの定義
 * ROOM:     室構成：壁、天井、床など室構成部位の面積、方位、隣室との関係などにより建物を定義
 * RESI:     居住者：居住者の人数、在室スケジュールなどの指定
 * AAPL:     照明・機器：照明器具、機器の容量および使用スケジュールの指定
 * VENT:     換気量：換気量、隙間風量のスケジュールの指定 
 *
 * @sa Eeinput
 */


/**
 * @brief 壁材料リスト
 */
typedef struct bmlst
{
	//! 名称
	char* mcode;

	//! 熱伝導率  [W/mK]
	double   Cond;

	//! 容積比熱  [J/m3K]
	double Cro;
} BMLST;


/**
 * @brief 太陽電池一体型壁体カタログ
 * @sa PVwallcatinit, PVwallPreCalc
 */
typedef struct pvwallcat
{
	//double	PVcap,					// 太陽電池容量[W]

	//! 日射量年変動補正係数[-]
	double	KHD;

	//! 経時変化補正係数[-]
	double	KPD;

	//! アレイ負荷整合補正係数[-]
	double	KPM;

	//! アレイ回路補正係数[-]
	double	KPA;

	//! 温度補正係数以外の補正係数の積（温度補正係数以外は時々刻々変化しない）
	double	KConst;

	//! インバータ実行効率[-]
	double	effINO;

	//!  最大出力温度係数[-]
	double	apmax;

	//! 太陽電池裏面の熱伝達率[W/m2K]
	double	ap;

	//! 結晶系：'C'  アモルファス系：'A'
	char	type;

	//! 集熱ファン停止時の太陽電池から集熱器裏面までの熱抵抗[m2K/W]
	double	Rcoloff;
	double	Kcoloff;
} PVWALLCAT;


/**
 * @brief 太陽電池一体型壁体
 */
typedef struct pvwall
{
	double	KTotal;					// 太陽電池の総合設計係数[-]
	double KPT;					// 温度補正係数[-]
	double	TPV;					// 太陽電池温度[℃]
	double	Power;					// 発電量[W]
	double	Eff;					// 発電効率[-]
	double	PVcap;					// 太陽電池設置容量[W]
} PVWALL;

// エアフローウィンドウカタログ
//typedef struct airflowcat
//{
//	double	ti,						// 室内側ガラスの透過率
//			to,						// 室外側ガラスの透過率
//			ai, 					// 室内側ガラスの日射吸収率
//			ao,						// 屋外側ガラスの日射吸収率
//			aci,					// 室内側ガラスの中空層表面対流熱伝達率[W/m2K]
//			aco,					// 室外側ガラスの中空層表面対流熱伝達率[W/m2K]
//			acioff,					// 停止時室内側ガラスの中空層表面対流熱伝達率[W/m2K]
//			acooff,					// 停止時室外側ガラスの中空層表面対流熱伝達率[W/m2K]
//			alr ;					// 中空層の放射熱伝達率[W/m2K]
//} AIRFLOWCAT ;

// エアフローウィンドウ
//typedef struct airflow
//{
//	char	*name ;					// エアフローウィンドウ名称
//	char	*loadt ;
//	struct room		*rm ;			// 室のポインタ
//	struct rmsrf	*sd ;			// 表面のポインタ
//	struct compnt	*cmp ;			// 機器ポインタ
//	char	control ;				// 運転状態
//	double	Wh,						// =(aci+aco)/(ca*Ga)
//			Ew,						// =exp(-Wh)
//			EWh,					// =1-(1-Ew)/Wh
//			Toset,					// 出口設定温度
//			cG,						// =c*G
//			Twai,					// 入口温度
//			FP, FO, FI,				// 室熱取得計算時の係数
//			Epw, Ept, EPC,			// エアフローウィンドウの内部温度計算用係数
//			Q ;						// エアフローウィンドウの除去熱量[W]
//	struct svday	Twaidy ;		// 入口温度の日集計
//	struct qday		Qdy ;			// エアフローウィンドウの除去熱量日集計
//} AIRFLOW ;


/**
 * @brief PCMSTATE
 */
typedef struct pcmstate
{
	char	*name;

	//! PCM温度（左側節点）
	double	tempPCMNodeL;

	//! PCM温度（右側節点）
	double	tempPCMNodeR;

	//! PCM温度（平均温度）
	double	tempPCMave;

	//double capm;					// PCM比熱[J/kgK]
	//double lamda;					// PCM熱伝導率[W/mK]

	//! PCM見かけの比熱（左側）[J/kgK]
	double	capmL;

	//! PCM見かけの比熱（右側）[J/kgK]
	double	capmR;

	//! PCM熱伝導率（左側）[W/mK]
	double	lamdaL;

	//! PCM熱伝導率（右側）[W/mK]
	double	lamdaR;

	//! 前時刻PCM見かけの比熱（左側）
	double	oldcapmL;

	//! 前時刻PCM見かけの比熱（右側）
	double	oldcapmR;

	//! 前時刻PCM熱伝導率（左側）
	double	oldlamdaL;

	//! 前時刻PCM熱伝導率（右側）
	double	oldlamdaR;
} PCMSTATE;


/**
 * @brief 壁体　固定デ－タ
 */
typedef struct rmsrf
{
	//! 壁体名
	char	*name;

	//! RMP名 higuchi 070918
	char	*sname;

	//! 壁体内部温度出力指定 'p'
	char	wlpri;

	//! 日よけの影面積の出力指定 'p'
	char	shdpri;

	//! 要素別壁体表面温度出力指定 'y'
	char	sfepri;

	//! 部位コ－ド
	char	ble;

	//! 壁のとき'H'; 地中壁のとき'E'; 窓のとき'W'; 地表面境界の時'e'
	char	typ;

	//! 専用壁のとき'I';共用壁のとき'C'
	char	mwtype;     /**/

	//! 壁体 0 側のとき'i'; M 側のとき'M'
	char	mwside;

	//! '*' or '!'
	char	mrk;

	//! 表面への短波長放射基本吸収比率が定義されている場合'*' 未定義の場合'!'
	char	ffix_flg;

	//! PCMの有無の判定フラグ　毎時係数行列を計算するかどうかを決める
	char	PCMflg;

	//! PCMの状態値出力フラグ 'y'
	char	pcmpri;

	//! 窓変更設定用窓コ－ド
	char	fnmrk[10];

	struct room  *room,
		*nextroom;
	struct rmsrf *nxsd;

	//! 重量壁（差分による非定常計算）
	struct mwall* mw;

	//! 輻射パネル用
	struct rdpnl *rpnl;

	//! 窓
	struct window	*window;

	//! 動的に窓を切り替える場合'Y'
	int	dynamicwin;
	struct window	*ifwin;	// Trueの時の窓
	//*falsewin ;	// Falseの時の窓

	//! 動的窓の制御
	struct ctlif	*ctlif;	

	char		*dynamiccode;

	//AIRFLOW		*airflow ;

	//! 室番号
	int     rm;

	//! 室壁体番号
	int	n;

	//! 方位番号
	int	exs;

	//! 隣室番号
	int	nxrm;

	//! 隣室室壁体番号
	int	nxn;

	//! 壁体定義番号
	int	wd;

	//! 重量壁体番号
	int	rmw;
	int	lwd;

	//! ドア定義番号
	int	dr;
	//int		drd[4]; 

	//! 選択窓定義番号
	int	fn;

	//! 窓種類数
	int	Nfn;

	//! 窓定義番号
	int	fnd[10];

	//! 日射熱取得、窓部材熱抵抗を直接指定する場合の番号
	int	direct_heat_gain[10];
	
	//! 窓変更設定番号
	int	fnsw;

	//! 日除け定義番号
	int	sb;

	//! 面積
	double   A;

	//! 外表面輻射率
	double	Eo;

	//! 外表面日射吸収率
	double	as;

	//! 隣室温度係数
	double	c;

	//! 日射総合透過率
	double	tgtn;

	//! 吸収日射取得率
	double	Bn;

	/*壁体、窓熱抵抗　　　　 */

	//! 短波長放射の基本吸収比率
	double	*fsol;

	/*窓透過日射の吸収比率     */

	//! 1次入射比率（隣接室への透過やガラスから屋外への放熱は無視）
	double	srg;

	//! 最終的に室の日射熱取得の内の吸収比率
	double	srg2;

	//! 人体よりの輻射の吸収比率
	double	srh;

	//! 照明よりの輻射の吸収比率
	double	srl;

	//! 機器よりの輻射の吸収比率
	double	sra;
	double	alo;
	double	ali;
	double	alic;
	double	alir;

	//! 対流による熱取得 [W]
	double	Qc;

	//! 放射による熱取得 [W]
	double	Qr;

	//! 壁体貫流熱取得 [W]
	double	Qi;

	//! 透過日射熱取得[W]
	double	Qgt;

	//! 吸収日射熱取得[W]
	double	Qga;

	//! 夜間放射熱取得[W]
	double	Qrn;
	double	K;

	//! 熱抵抗[m2K/W] 表面熱伝達抵抗は除く
	double	Rwall;

	//! 単位面積当たり熱容量[J/m2K]
	double	CAPwall;
	double	*alicsch;
	double	*alirsch;
	double	FI;
	double	FO;
	double	FP;
	double	CF;
	double	WSR;
	double	*WSRN;
	double	*WSPL;
	double	WSC;

	//! SUNBRKで定義した日よけの影面積率
	double	Fsdworg;

	//! 影面積  higuchi 070918 */ // KAGE-SUN用
	double	Fsdw;

	//! higuchi 070918
	double	Ihor;

	//! higuchi 070918
	double	Idre;

	//! higuchi 070918
	double	Idf;

	//! higuchi 070918
	double	Iw;

	//! higuchi 070918
	double	rn;

	//! 室内表面に吸収される短波長輻射 [W/m2]
	double	RS;

	//! 室内表面に吸収される日射（短波長）[W/m2]
	double	RSsol;

	//! 室内表面に入射する日射（短波長）（隣接室への透過を考慮する前）
	double	RSsold;

	//! 室内表面に吸収される照明（短波長）[W/m2]
	double	RSli;
	double	RSin;
	double	TeEsol;

	//! 夜間放射熱取得 [W]
	double	TeErn;

	//! 外表面の相当外気温
	double	Te;

	//! 室内表面の平均輻射温度
	double	Tmrt;
	double	Ei;

	//! 表面温度[℃]
	double	Ts;

	//! 設備機器発熱
	double	eqrd;
	int     end;

	//! 建材一体型空気集熱器の相当外気温度[℃] 記号変更
	double	Tcole;
	//double	ColTe ;		// 建材一体型空気集熱器の相当外気温度[℃]

	double	Tcoleu, Tcoled;

	//! 建材一体型空気集熱器の熱媒平均温度[℃]
	double	Tf;

	//! 日積算壁体貫流熱取得
	QDAY	SQi;
	SVDAY	Tsdy;

	//! 太陽電池一体型壁体
	PVWALL	PVwall;
	QDAY	mSQi;
	SVDAY	mTsdy;

	// 集熱器一体型壁体用計算結果

	//! 流れ方向温度分布の分割数
	int		Ndiv;
	double	ColCoeff,
		// 建材一体型集熱器計算時の後退差分要素URM
		*Tc,
		//Scol,	// 放射熱取得量[W/m2]
		oldTx;	// 前時刻の集熱器と躯体の境界温度（集熱器相当外気温度計算用）

	// 太陽電池一体型
	double	Iwall;
	char	PVwallFlg;	// 太陽電池一体型なら'Y'
	double	dblWsu, dblWsd;

	// 屋根一体型空気集熱器の通気層上面、下面の幅[m]
	double	dblKsu, dblKsd, dblKc, dblfcu, dblfcd, dblKcu, dblKcd;
	double	dblb11, dblb12, dblb21, dblb22;
	double	dblacr, dblacc, dblao;
	double	dblTsu, dblTsd, dblTf;
	double	dblSG;
	double	ku, kd;
	double	ras, Tg;

	//! PCM状態値収録構造体
	PCMSTATE	*pcmstate;

	//! PCM設置レイヤー数
	int			Npcm;

	//! 当該部位への入射日射の隣接空間への日射分配（連続空間の隣室への日射分配）
	double	tnxt;

	//! 室内透過日射が窓室内側への入射日射を屋外に透過する場合'y'
	char	RStrans;
} RMSRF;


/**
 * @brief 壁体各層の熱抵抗と熱容量
 */
typedef struct welm
{
	char	*code;

	//! 各層の材料厚さ
	double	L;

	//double		res;				/*節点間の熱抵抗 [m2K/W]*/
	//double		cap;				/*節点間の熱容量 [J/m2K]*/

	//! 各層の内部分割数
	int		ND;

	//! 熱伝導率  [W/mK]
	double	Cond;

	//! 容積比熱  [J/m3K]
	double Cro;
} WELM;


///@brief PCM見かけの比熱計算用パラメータ
typedef struct pcmparam
{
	double	T; 
	double  B; 
	double  bs; 
	double  bl; 
	double  skew; 
	double  omega; 
	double  a; 
	double  b; 
	double  c; 
	double  d; 
	double  e; 
	double  f;
}PCMPARAM;


///@brief charttable
typedef struct chartable
{
	//! テーブル形式ファイルのファイル名
	char	*filename;

	//! E:エンタルピー、C:熱伝導率
	char	PCMchar;

	//! PCM温度[℃]
	double* T;

	//! 特性値（エンタルピー、熱伝導率）
	double	*Chara;

	//! h:見かけの比熱、e:エンタルピー
	char	tabletype;

	//! テーブルの下限温度、上限温度
	double	minTemp, maxTemp;

	//! テーブル形式の入力行数
	int		itablerow;

	FILE	*fp;

	//! 上下限温度範囲外の特性値計算用線形回帰式の傾きと切片
	double	lowA, lowB, upA, upB;

	//! 最低温度変動幅
	//! 前時刻からの温度変化がminTempChng以下の場合はminTempChngとして特性値を計算
	double	minTempChng;
}CHARTABLE;


///@brief 潜熱蓄熱材
typedef struct pcm
{
	char	*name;			// PCM名称
	char	spctype;		// 見かけの比熱　m:モデルで設定、t:テーブル形式
	char	condtype;		// 熱伝導率　m:モデルで設定、t:テーブル形式
	double	Ql,				// 潜熱量[J/m3]
		Condl,			// 液相の熱伝導率[W/mK]
		Conds,			// 固相の熱伝導率[W/mK]
		Crol,			// 液相の容積比熱[J/m3K]
		Cros;			// 固相の容積比熱[J/m3K]
	double	Ts,				// 固体から融解が始まる温度[℃]
		Tl;			// 液体から凝固が始まる温度[℃]
	double	Tp;			// 見かけの比熱のピーク温度
	char	iterate;	// PCM状態値を収束計算させる場合は'y'
	char	iterateTemp;	// 収束条件に温度も加える場合は'y'（通常は比熱のみ）
	int		DivTemp;	// 比熱の数値積分時の温度分割数
	int		Ctype;		// 比熱
	//	double	T, B, bs, bl, skew, omega, a, b, c, d, e, f;
	PCMPARAM	PCMp;		// 見かけの比熱計算用パラメータ
	char	AveTemp;	// PCM温度を両側の節点温度の平均で計算する場合は'y'（デフォルト）
	double	nWeight;	// 収束計算時の現在ステップの重み係数
	double	IterateJudge;	// 収束計算時の前ステップ見かけの比熱の収束判定[%]
	CHARTABLE chartable[2];		// 0:見かけの比熱またはエンタルピー、1:熱伝導率
} PCM;


///@brief 壁体　定義デ－タ
typedef struct wall
{
	//! 部位コ－ド
	char  ble;

	//! 名前
	char *name;

	//! 部材構成にPCMが含まれる場合は毎時係数行列を作成するのでPCMが含まれるかどうかのフラグ
	char	PCMflg;

	//! 材料層数≠節点数
	int    N;

	//! 発熱面のある層の番号
	int Ip;

	//char   code[12][5]; /*各層の材料コ－ド      */

	//! 節点間の材料厚さ
	double  *L;       /*        */

	//	int    *ND;      /*各層の内部分割数      */

	//! 室内表面輻射率
	double  Ei;

	//! 外表面輻射率
	double Eo;

	//! 外表面日射吸収率
	double as;

	//! 壁体熱抵抗   [m2K/W]
	double Rwall;

	//! 単位面積当たりの熱容量[J/m2K]
	double CAPwall;

	//! 登録された材料（≠節点）ごとの熱容量、熱抵抗
	double* CAP, * R;

	//! パネル効率
	double effpnl;

	//! 当該部位への入射日射の隣接空間への日射分配（連続空間の隣室への日射分配）
	double	tnxt;

	//! 節点数
	int    M;

	//! 発熱面のある節点番号
	int	mp;

	//! 節点間の熱抵抗 [m2K/W]
	double* res;

	//! 節点間の熱容量 [J/m2K]
	double *cap;

	int    end;

	WELM	welm[WELMMX];

	//! τα
	double	tra;

	//! 通気層上部から屋外までの熱貫流率[W/m2K]
	double Ksu; 

	//! 通気層下部から集熱器裏面までの熱貫流率[W/m2K]
	double Ksd;
	double fcu;
	double fcd;
	double	ku, kd;

	//!  通気層上部から屋外、通気層下部から集熱器裏面までの熱抵抗[m2K/W]
	double  Ru, Rd;
	double	Kc;
	double  Kcu;
	double  Kcd;
	double	Ko;
	double	air_layer_t;

	//! 通気層の厚さ[m]
	double	dblEsu, dblEsd;

	//! 通気層上面、下面の放射率
	double	ta, Eg, Eb, ag;

	//! 空気層の厚さ[m]、ガラスの放射率、集熱板放射率、ガラスの日射吸収率
	char	chrRinput;	// 熱抵抗が入力されている場合は'Y'
	// 熱貫流率が入力されている場合は'N'
	//double	ta,		// 建材一体型空気集熱器の透過体透過率[-]
	//				// 2009/01/19 Satoh Debug
	//		Kdd,	// 集熱媒体から集熱器裏面までの熱貫流率[W/m2K]
	//		Kud,	// 集熱媒体から集熱器表面までの熱貫流率[W/m2K]
	//		Ku,		// 建材一体型空気集熱器の集熱板から屋外までの熱貫流率[W/m2K]
	//		Kd,		// 　　　　　　　　〃　　　　　　　裏面までの熱貫流率[W/m2K]
	//		Ko,		// Ku + Kd
	//		KdKo,	// Kd / Ko
	//		//KcKu,	// Kc / Ku
	//		Kc ;	// 集熱器全体の熱貫流率[W/m2K] ( = 1 / αA + Ko )
	//				// 2009/01/26 Satoh Debug
	char	WallType;
	// 建材一体型空気集熱器の場合：'C'
	// 床暖房等放射パネルの場合：'P'
	// 一般壁体の場合：'N'
	//char	PVwall ;
	// 太陽電池一体型建材（裏面通気）：'Y'
	char	*ColType;
	// 集熱器タイプ　JSES2009大会論文（宇田川先生発表）のタイプ
	PVWALLCAT	PVwallcat;
	PCM		*PCM[WELMMX],
		**PCMLyr;		// 潜熱蓄熱材
	double	PCMrate[WELMMX], *PCMrateLyr;
} WALL;


/**
 * @brief 壁体定義番号既定値デ－タ
 */
typedef struct Dfwl
{
	//! 外壁
	int E;

	//! 屋根
	int R;

	//! 外部に接する床
	int F;

	//! 内壁
	int i;

	//! 天井
	int c;

	//! 隣室に接する床
	int f;
} DFWL;


/**
 * @brief 重量壁体デ－タ
 */
typedef struct mwall
{
	struct rmsrf  *sd, *nxsd;
	struct wall   *wall;

	//! 壁体通し番号
	int    ns;

	//! 室番号
	int rm;

	//! 室壁体番号
	int n;

	//! 隣室番号
	int nxrm;

	//! 隣室室壁体番号
	int nxn;
	
	//! [UX]の先頭位置
	double *UX;

	int    M, mp;
	double  *res, *cap;

	//! 室内表面のuo
	double uo;

	//! 外表面のum
	double um;

	//! 床パネル用係数
	double Pc;

	//! 壁体温度
	double* Tw;

	//! 以前の壁体温度
	double* Told;

	//! 現ステップの壁体内部温度
	double* Twd;
	
	//! PCM温度に関する収束計算過程における前ステップの壁体内温度
	double* Toldd;

	int    end;
} MWALL;


/**
 * @brief 窓およびドア定義デ－タ
 */
typedef struct window
{
	//! 名称
	char* name;

	//! 入射角特性のタイプ 'N':一般ガラス
	char *Cidtype;

	double  K, Rwall, Ei;

	//! 外表面輻射率（ドアのみ）
	double Eo;

	//! 日射総合透過率
	double tgtn;

	//! 吸収日射取得率
	double Bn;

	//! 日射吸収率（ドアのみ）
	double as;

	//! 窓ガラス面積
	double Ag;

	//! 開口面積
	double Ao;
	
	//! 巾、高さ
	double W, H;

	//! 室内透過日射が窓室内側への入射日射を屋外に透過する場合'y'
	char	RStrans;

	int    end;
	//char	AirFlowFlg ;	// エアフローウィンドウなら'Y'
	//AIRFLOWCAT	AirFlowcat ;
} WINDOW;


/**
 * @brief 日除けデータ
 * @sa Snbkdata
 * @detail ref: EESLISM7.2入力データ作成マニュアル.pdf P.31 図2.4.2 日除け入力方法
 */
typedef struct snbk
{
	//! 庇の名称
	char *name;

	//! 庇の種類 1=一般の庇, 2-4=袖壁, 5=長い庇, 6-8=長い袖壁, 9=格子ルーバー
	int type;

	//! 対象領域における日影部分と日照部分が逆の場合は1
	int ksi;

	//! 影の計算を行う対象領域 幅 (必須)
	double W;

	//! 影の計算を行う対象領域 高さ (必須)
	double H;

	//! 対象領域下部と日除けの距離 (必須)
	double D;

	//! 対象領域左と日除けの距離  (type=4,5,8では未入力)
	double W1;

	//! 対象領域右と日除けの距離 (type=3,5,7では未入力)
	double W2;

	//! 対象領域下部と日除けの距離 (type=6,7,8では未入力)
	double H1;

	//! 対象領域下部と日除けの距離 (type=1,5,6,7,8では未入力)
	double H2;

	//! 庇の数を格納。ただし、index=0にのみ格納され、あとは0である。
	int end;
} SNBK;

/* ---------------------------------------------------------- */

/**
 * @brief 日射、室内発熱熱取得
 */
typedef struct qrm
{
	//! 透過日射
	double tsol;

	//! 外表面吸収日射室内熱取得
	double asol;

	//! 外表面吸収長波長輻射熱損失
	double arn;

	//! 人体顕熱
	double hums;

	//! 照明
	double light;

	//! 機器顕熱
	double apls;

	//! 人体潜熱
	double huml;

	//! 機器潜熱
	double apll;

	//! 換気顕熱負荷[W]
	double Qinfs;

	//! 換気潜熱負荷[W]
	double Qinfl;

	//! 室内の顕熱蓄熱量[W]
	double Qsto;

	//! 室内の潜熱蓄熱量[W]
	double Qstol;

	//! 室内設置の配管、ボイラからの熱取得[W]
	double Qeqp;

	//! 外壁面入射日射量　W
	double solo;

	//! 窓面入射日射量 [W]
	double solw;

	//! 外表面吸収日射 W
	double asl;

	//! 室内発熱（顕熱）W
	double hgins;

	//! 消費電力[W]
	double AE;

	//! 消費ガス[W]
	double AG;
} QRM;

/* ---------------------------------------------------------- */

/**
 * @brief 室間相互換気
 */
typedef struct achir
{
	int   rm;
	int sch;
	struct room *room;
	double Gvr;
}  ACHIR;

/* ---------------------------------------------------------- */

/**
 * @brief 隣室
 */
typedef struct trnx
{
	struct room  *nextroom;

	//! room側からみたnextroomと接する表面のポインター
	struct rmsrf *sd;
} TRNX;

/* ---------------------------------------------------------- */

/**
 * @brief 室についての輻射パネル
 */
typedef struct rpanel
{
	struct rdpnl *pnl;
	struct rmsrf *sd;

	//! 放射パネルの入力要素のs先頭位置
	int  elinpnl;
} RPANEL;

/* ---------------------------------------------------------- */

/**
 * @brief 輻射パネル
 */
typedef struct rdpnl
{
	char         *name;
	char		 *loadt;
	char		 type;		// 建材一体型空気集熱器の場合：'C'
	// それ以外：'P'
	struct room  *rm[2];
	struct rmsrf *sd[2];
	struct compnt *cmp;	
	int          MC;      /*専用壁のとき MC=1; 共用壁のとき MC=2 */
	int	Ntrm[2];
	int	Nrp[2];
	int	elinpnl[2];
	int	eprmnx;  /*隣室EPRN[]の位置*/
	int	epwtw;   /*EPWの当該パネル入口水温の位置*/
	char         control;

	double        effpnl;
	double	Toset;
	double	Wp;
	double	Wpold;
	double	Tpi;
	double	Tpo;
	double	FIp[2]; 
	double FOp[2]; 
	double FPp;
	double	Epw;
	double	EPt[2];
	double	*EPR[2];
	double	*EPW[2];
	double	EPC;
	double	Q;
	// 2009/01/26 Satoh Debug
	double cG;				// 比熱×流量
	double Ec, FI, FO, FP;
	double Ew;

	/* 日集計 */
	SVDAY   Tpody;
	SVDAY   Tpidy;
	QDAY    Qdy;
	QDAY    Scoldy;
	QDAY    PVdy;
	SVDAY   TPVdy;

	// 月集計
	SVDAY	mTpody, mTpidy, mTPVdy;
	QDAY	mQdy, mScoldy, mPVdy;
	EDAY	mtPVdy[12][24];

	struct omvav	*OMvav;	// 吹出を制御する変風量ユニット

} RDPNL;

/* ---------------------------------------------------------- */

/**
 * @brief 室への冷温風供給熱量
 */
typedef struct airsup
{
	double Qs;
	double Ql;
	double Qt;
	double G;
	double Tin;
	double Xin;

	//! 日積算暖冷房
	QDAY Qdys;
	QDAY Qdyl;
	QDAY Qdyt;

	QDAY	mQdys;
	QDAY	mQdyl;
	QDAY	mQdyt;
} AIRSUP;

/* ---------------------------------------------------------- */

/**
 * @brief 室負荷パネル
 */
typedef struct rmload
{
	char   *loadt;
	char	*loadx;
	char	tropt;    /* 室温制御方法  'o': OT制御、'a': 空気温度制御 */
	char	hmopt;    /* 湿度制御設定値
	'x': 絶対湿度、'r': 相対湿度、 'd': 露点温度 */
	double  Tset;
	double	Xset;
	double	Qs;
	double	Ql;
	double	Qt;

	double	FOTr;
	double	*FOTN;
	double	*FOPL;
	double	FOC;

	struct qday  Qdys,   /* 日積算暖冷房 */
		Qdyl,
		Qdyt;
	struct qday  mQdys, mQdyl, mQdyt;
} RMLOAD;

/* ---------------------------------------------------------- */

/**
 * @brief ゾーン集計
 */
typedef struct rzone
{
	char  *name;
	int   Nroom;
	struct room **rm;
	double Afloor;
	double	Tr;
	double	xr;
	double	RH;
	double	Tsav;
	double	Qhs;
	double	Qhl;
	double	Qht;
	double	Qcs;
	double	Qcl;
	double	Qct;
	struct svday Trdy,
		xrdy,
		RHdy,
		Tsavdy;
	struct qday  Qsdy,
		Qldy,
		Qtdy;
} RZONE;

/* ---------------------------------------------------------- */
/* 要素別熱損失・熱取得計算用 */


/**
 * @brief
 */
typedef struct bhelm
{
	//! 貫流
	double trs;

	//! 外壁入射日射
	double so;

	//! 窓入射日射
	double sg;

	//! 大気放射
	double rn;

	//! 室内発熱
	double in;

	//! 放射暖・冷房パネル
	double pnl;
} BHELM;


/**
 * @brief
 */
typedef struct qhelm
{
	struct bhelm  qe;

	//! 外壁面入射日射量　W
	double slo;

	//! 窓面入射日射量　W
	double slw;

	//! 外壁面吸収日射量 W
	double asl;

	//! 窓透過日射量　W
	double tsol;

	//! 室内発熱（顕熱） W
	double hins;

	//! 室内発熱（潜熱）
	double hinl;

	//! 隣室熱損失
	double nx;

	//! 窓熱損失
	double gd;

	//! 外壁熱損失
	double ew;

	//! 窓熱損失
	double wn;

	//! 内壁熱損失
	double i;

	//! 天井、屋根
	double c;

	//! 床（内・外）
	double f;

	//! 換気
	double vo;

	//! 換気（潜熱）
	double vol;

	//! 室間換気
	double vr;

	//! 室間換気（潜熱）
	double vrl;

	//! 室内空気蓄熱
	double sto;

	//! 室内空気蓄熱（潜熱）
	double stol;
	double loadh;
	double loadhl;
	double loadc;
	double loadcl;
} QHELM;


/**
 * @brief
 */
typedef struct rmqelm
{
	struct rmsb   *rmsb;
	struct bhelm  *WSCwk;
	struct qhelm  qelm,
		qelmdy;
} RMQELM;


/**
 * @brief
 */
typedef struct rmsb
{
	//! 'E':外気に接する面、'G':地面に接する面、'i':内壁
	char          type;
	struct bhelm  Ts,
		*Tw,
		*Told;
} RMSB;


/**
 * @brief 
 */
typedef struct qetotal
{
	char          *name;
	struct qhelm  qelm,
		qelmdy;
} QETOTAL;


/**
 * @brief 室デ－タ
 */
typedef struct room
{
	//! 室名
	char    *name;

	//! 周壁数
	int     N;

	//! Sd[],S[]の先頭位置
	int brs;

	double	*MCAP, *CM, TM, oldTM, HM, QM;

	//! 家具の日射吸収割合
	double	*fsolm;

	//! 家具の最終的な日射吸収割合
	double	Srgm2;

	//! 家具の日射吸収量[W]
	double	Qsolm;

	//! PCM内臓家具の部材名称
	char	*PCMfurnname;

	//! PCM内臓家具の場合
	PCM		*PCM;

	//! PCM内臓家具の容積[m3]
	double	mPCM;

	//! PCM内臓家具の見かけの比熱[J/m3K]
	double	PCMQl;

	//! 家具の熱容量（顕熱とPCM内臓家具の合計）
	double	FunHcap;

	//! 室空気に加算したものは除く
	double	FMT, FMC;

	// 家具の計算用パラメータ

	//! 透過日射熱取得
	double	Qgt;

	int Nachr;

	//! 内壁を共有する隣室数
	int	Ntr;

	//! 輻射パネル数
	int	Nrp;

	//! 床の部位数
	int	Nflr;

	//! 短波長放射吸収比率が定義されている面数
	int	Nfsolfix;
	int	Nisidermpnl;
	int	Nasup;

	RMSRF		*rsrf;
	ACHIR		*achr;
	TRNX		*trnx;
	RPANEL		*rmpnl;
	//RAIRFLOW	*rairflow ;
	AIRSUP		*arsp;
	struct compnt	*cmp;
	struct elin	*elinasup,
		*elinasupx;
	RMLOAD		*rmld;
	RMQELM		*rmqe;

	double   *F,
		*alr;
	double  *XA,
		*Wradx;

	//! 隣室裏面の短波長放射考慮のとき 'y'　（床、天井のみ）
	char rsrnx;

	//! 形態係数 'F':外部入力、'A':面積率
	char fij;

	//! 表面温度出力指定 'p'
	char sfpri;

	//! 日射、室内発熱取得出力指定 'p'
	char eqpri;

	//! '*', 'C', '!'
	char mrk;

	//! 室容積
	double   VRM;

	//! 室内空気質量
	double GRM;

	//! 室空気熱容量
	double MRM;

	//! 室内表面総面積
	double Area;

	//! 床面積
	double FArea;

	//! 床に直接吸収される短波長放射の比率
	double* flrsr;

	//! 部位に直接吸収される短波長放射比率の既定値合計（Sd->fsol、Rm->flrsr、Rm->fsolmの合計）
	double tfsol;
	double alrbold;

	//! 室内熱容量   J/K
	double Hcap;

	//! 室内湿気容量 kg/(kg/kg)
	double Mxcap;


	//! 照明器具形式
	char    Ltyp;

	//! 人数
	double   Nhm;

	//! 照明器具容量
	double Light;

	//! 機器対流放熱容量
	double Apsc;

	//! 機器輻射放熱容量
	double Apsr;

	//! 機器潜熱放熱容量
	double Apl;

	//! 換気量
	double Gve;

	//! 隙間風量
	double Gvi;

	//! 消費電力容量[W]
	double AE;

	//! 消費ガス容量[W]
	double AG;

	//! 消費電力スケジュール
	double* AEsch;

	//! 消費ガススケジュール
	double* AGsch;
	double* Lightsch;
	double* Assch;
	double* Alsch;
	double* Hmsch;
	double* Metsch;
	double* Closch;
	double* Wvsch;
	double* Hmwksch;
	double* Vesc;
	double* Visc;

	//! 室内側対流熱伝達率のスケジュール設定値
	double *alc;

	//int     vesc,      /*換気設定番号*/
	//	visc ;      /*隙間風設定番号*/
	//lgtsc,     /*照明設定番号*/
	//hmnsc,     /*在室人数設定番号*/
	//hmwksc,    /*在室者作業強度設定番号*/
	//apssc,     /*機器顕熱発熱設定番号*/
	//aplsc,     /*機器潜熱発熱設定番号*/

	/*温熱環境指標計算用*/
	//metsc,     /*代謝量（met)設定番号*/
	//closc,     /*着衣量設定番号*/
	//wvsc;      /*室内風速設定番号*/

	/*室内発熱*/

	//! 人体よりの対流  [W]
	double Hc;

	//! 人体よりの輻射  [W]
	double Hr;

	//! 人体よりの潜熱　[W]
	double HL;

	//! 照明よりの対流  [W]
	double Lc;

	//! 照明よりの輻射  [W]
	double Lr;

	//! 機器よりの対流  [W]
	double Ac;

	//! 機器よりの輻射  [W]
	double Ar;

	//! 機器よりの潜熱  [W]
	double AL;

	/*設備機器発熱*/

	//! 設備機器発熱の対流成分比率
	double eqcv;

	//! 設備機器からの発熱[W]
	double Qeqp;

	double   Gvent;

	double   RMt;
	double	*ARN;
	double	*RMP;
	double	RMC;
	double	RMx;
	double	RMXC;

	double   Tr;
	double	Trold;
	double	xr;
	double	xrold;

	//! 室内空気相対湿度 [%]
	double	RH;

	//! 室内平均表面温度 [℃]
	double	Tsav;

	//! 室内作用温度の近似値[℃]
	//! (室温と室内平均表面温度の平均値)
	double	Tot;

	//! エンタルピー
	double	hr;

	//! PMV
	double	PMV;
	double	SET;
	int		setpri;

	struct svday  Trdy,
		xrdy,
		RHdy,
		Tsavdy;

	SVDAY	mTrdy, mxrdy, mRHdy, mTsavdy;
	int     end;
	struct vav	*VAVcontrl;

	//! 作用温度設定時の対流成分重み係数
	double	*OTsetCwgt;

	// デフォルトは0.5
	double	HGc, CA, AR;

	//! 吸収日射熱取得
	double	Qsab;

	//! 夜間放射による熱損失
	double Qrnab; 
} ROOM;

/* --------------------------------
室計算用データ
--------------------------------*/

/*
 * @brief 
 * @sa Rmvlsinit
 */
typedef struct rmvls
{
	double			Twallinit;
	int				Nroom;
	int Nrdpnl;
	int Nwall;
	int Nwindow;
	int Nmwall;
	int Nsrf;
	int				Npcm;
	//	char			Emrk[ROOMMX] ;
	char			*Emrk;
	struct wall		*Wall;
	struct window	*Window;
	struct snbk		*Snbk;
	PCM				*PCM;
	//	struct rmsrf   Sd[NSMX];
	RMSRF			*Sd;
	//	struct mwall	Mw[MWALLMX] ;
	struct mwall	*Mw;
	//	struct room    Room[ROOMMX];
	ROOM			*Room;
	struct rdpnl	*Rdpnl;
	//struct airflow	*airflow ;
	struct qrm		*Qrm, *Qrmd;
	struct qetotal	Qetotal;
	double			*Trdav;

	//! PCM建材を使用し、かつ収束計算を行う場合は'y'
	char			pcmiterate;
} RMVLS;
