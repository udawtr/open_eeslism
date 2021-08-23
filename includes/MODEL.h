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

/*

                         構造体の定義
                                    FILE=MODEL.h
                                    Create Date=1999.12.8

*/

#pragma once

//#define MAXSBLK 15             /*---一つのＢＤＰに対する日よけの最大数----*/
//#define MAXWD 10               /*---一つのＢＤＰに対する窓の最大数---*/ 
//#define MAXRMP 10              /*---一つのＢＤＰに対するＲＭＰの最大数---*/
#define M_pai 3.14159265             //PI と重複(値も少し違う)
#define M_rad M_pai/180.
#define pmax 200               


/*
 * @brief <入力データファイル>外部環境部分のモデルについて構造体の定義
 * @details
 * 
 * 2.10 外部障害物の入力方法 (EESLISM7.2入力データ作成マニュアル.pdf)
 * 
 * モデルの関連図
 * 
 * *- COORDNT --- BDP --+-- RMP ----- WD
 * |                    |
 * |                    +-- SBRK
 * +- OBS
 * +- TREE
 * +- POLYGON
 * +- SHDSCHTB
 * 
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * COORDNT : 外表面
 * BDP:      方位別表面 (exwall構造体)
 * RMP:      建築室外壁面 (exroomwall構造体)
 * WD:       窓 (madomen構造体)
 * SBLK:     付属障害物 (sunblk構造体)
 * OBS:      外部障害物 隣棟、構築物 etc
 * TREE:     樹木
 * POLYGON:  多角形
 * SHDSCHTB: 障害物の遮蔽率スケジュール設定
 * 
 * @sa Eeinput
*/


typedef struct bektle{
     double **ps ;
}bekt ;


//付設障害物
//ref: P.98 図 2.10.4 各種日よけの定義
typedef struct sunbreak{
    //! 庇/バルコニー/袖壁/スクリーンの分類
    char *sbfname ;  /*HISASI or BARUKONI or SODEKABE or MADOHIYOKE*/

    //! 名前
    char *snbname ;

    //! 色
    double rgb[3] ;

    //! 左隅の二次元座標(x,y)
    double x, y ;

    //! 突き出し長さ  [m]
    double D;
    
    //! 幅 [m]
    double W;
    
    //! 高さ [m]
    double H;
    
    //! フェンス高さ [m]
    double h;

    double WA ;

    //! 反射率
    double ref;
}sunblk ;

/*---窓---*/

/*
 * @brief 窓(WD)
 */
typedef struct madomen
{
    //! 名前
    char* winname;

    //! 左下頂点座標
    double xr, yr;

    //! 巾、高さ
    double Ww, Wh;

    //! 反射率
    double ref;

    //! 前面地面の代表点までの距離 初期値=1
    double grpx;

    //! 色
    double rgb[3];
} MADO ;


/*
 * @brief 室外表面(RMP)
 * @details
 * 室外表面(RMP)は任意の数の窓(WD)を持つ。
 */
typedef struct exroomwall
{
    // RMP名
    char* rmpname;


    char* wallname;

    //! 窓の数
    int sumWD;

    //! 反射率
    double ref;

    //! 左下頂点座標
    double xb0, yb0;

    //! 巾、高さ
    double Rw, Rh;

    //! 前面地面の代表点までの距離 初期値=1
    double grpx;

    //! 色
    double rgb[3];

    //! 窓(WD)の動的配列
    MADO  *WD ; 
}RRMP ;


/*
 * @brief BDP(方位別外表面)
 * @details
 * 方位別外表面(BDP)は、任意の数の室外表面(RMP)を持つ。
 */
typedef struct exwall{
    //! 室外壁面名(BDP名)
    char *bdpname;

    //! RMPの数
    int sumRMP;
    
    //! 日よけの数
    int sumsblk;

    //! 左下頂点座標
    double x0, y0, z0 ;

    //! 方位角、傾斜角
    double Wa, Wb ;

    //! 巾、高さ
    double exh, exw ;

    //! RMP
    RRMP *RMP ;

    //! SBLK
    sunblk *SBLK ;

    // Satoh修正（2018/1/23）
    char *exsfname;
}BBDP ;

/*---OBS 外部障害物---*/
typedef struct obs{
    char *fname ;            /*--rect or cube or r_tri or i_tri--*/
    char *obsname ;          /*--名前--*/     
    double x, y, z ;            /*--左下頂点座標--*/
    double H, D, W ;            /*--巾、奥行き、高さ--*/    
    double Wa ;                 /*--方位角--*/
    double Wb ;                 /*--傾斜角--*/
    double ref[4] ;             /*--反射率--*/
    double rgb[3] ;             /*--色--*/     
}OBS ;

/*---樹木---*/
typedef struct tree{
    char *treetype ;            /*--樹木の形Ａ，Ｂ，Ｃ--*/
    char *treename ;           /*--名前--*/
    double x, y, z ;              /*--幹部下面の中心座標--*/
    double W1, W2, W3, W4 ;       /*--W1=幹太さ,W2=葉部下面巾,W3=葉部中央巾,W4=葉部上面巾--*/
    double H1, H2, H3 ;           /*--H1=幹高さ,H2=葉部下側高さ,H3=葉部上側高さ--*/
}TREE ;

/*---日射遮蔽率---*/
typedef struct shadtb{
    char *lpname ;              /*--対象ＬＰ名--*/
    int  indatn ;                  /*--入力データの数--*/
    int  ndays[12],ndaye[12] ;     /*--スケジュール開始日と終了日--*/
    double shad[12] ;              /*--日射遮蔽率--*/
}SHADTB ;                                

/*--多角形の頂点座標--*/
typedef struct tyoutenn{        
   double X, Y, Z ;
}XYZ ;

/*--OPW:受照窓面--*/
typedef struct menn{
   char *opwname ;           /*--名前--*/
   XYZ *P ;                     /*--頂点--*/
   double ref ;                 /*--反射率--*/
   double grpx ;                /*--前面地面の代表点までの距離 初期値=1---*/
   double sumw ;                /*--窓面の影面積の割合--*/
   double rgb[3] ;              /*--色R,G,B--*/
   int polyd ;                  /*--何角形か？--*/
}WD_MENN ;

/*--OP（受照面）,LP（被受照面）,MP(OP+OPW)--*/
typedef struct opmenn{
   char   *opname ;          /*--名前--*/
   double rgb[3] ;              /*--色--*/
   int    wd,exs ;              /*--窓の数、方位番号--*/
   double grpx,                 /*--前面地面の代表点までの距離 初期値=1---*/
          faia,                 /*--天空に対する形態係数--*/ 
          faig,                 /*--地面に対する形態係数--*/ 
          faiwall[pmax],        /*--外部障害物に対する形態係数--*/ 
          grpfaia,              /*--前面地面代表点から見た天空の形態係数--*/
          sum,                  /*--壁面の影面積--*/
          ref,refg,             /*--反射率、前面地面の反射率--*/
          wa,                   /*--面の方位角--*/
          wb,                   /*--面の傾斜角--*/
          Ihor,Idre,Idf,Iw,     /*--日射量--*/  
          Reff,rn,              /*--大気放射量、夜間放射量--*/
          Te,Teg ;              /*--面の表面温度、前面地面の表面温度--*/   
  double  shad[365] ;           /*--面の日射遮蔽率--*/
  double  alo,as,Eo ;           /*--外表面総合熱伝達率、日射吸収率、放射率--*/  
  int	  Nopw;
  WD_MENN *opw ;         
  int     polyd ;               /*--何角形か--*/
  XYZ     *P, e, G, grp ;       /*--頂点座標、法線ベクトル、中心点、前面地面代表点--*/
  int     sbflg ;               /*--付設障害物フラグ　付設障害物の場合：１、その他：０--*/
  int     wlflg ;               /*--外表面の種類 窓：1 壁：0 --*/
}P_MENN ;
    
/*--LP(ポリゴン)直接入力用--*/
typedef struct polygon{
  char   polyknd[5] ;           /*--ポリゴン種類(RMP OBS WD)--*/
  char   *polyname ;         /*--名前--*/
  char   *wallname ;         /*--壁名称--*/
  int    polyd ;                /*--何角形か? 3,4,5,6--*/
  double ref,refg ;             /*--反射率、前面地面の反射率--*/
  XYZ    *P ;                   /*--頂点--*/
  double grpx ;                 /*--前面地面の代表点までの距離 初期値=1---*/
  double rgb[3] ;               /*--色--*/
}POLYGN ;

/*---Sdstr 影面積のストア 110413 higuchi add---*/
typedef struct Shadowsum{
    double *sdsum ;              /*--影面積--*/
}SHADSTR ;
/*--- 110413 higuchi end ----*/

typedef struct Noplpmp
{
	int	Nop, Nlp, Nmp;
}NOPLPMP;
