#pragma once

#include <stdio.h>

int DEBUG();
void EnterDebugMode();

/**
 * @brief ログ出力用ファイルポインタ
 * @sa Gdata
 */
extern FILE	*flog;


extern int	dayprn;


/**
 * @brief 計算時間間隔[s]
 */
extern  double  dTM;

/**
 * @brief kWhへの換算係数
 * cff_kWh = dTM / 3600. / 1000
 */
extern double  cff_kWh;

int NSTOP();
void NSTOPOn();
int DISPLAY_DELAY();
void DISPLAY_DELAY_On();

int SETprint();


//壁体の材料定義リストのファイル名を指定
void set_fbm_list_filename(char* fname);

//壁体の材料定義リストのファイル名を取得
const char* get_fbm_list_filename();

// 曜日名の配列 { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun", "Hol" }
const char* DAYweek(int i);

//VAV 計算回数の取得
int	VAV_Count_MAX();

//VAV 計算回数を設定
void set_VAV_Count_MAX(int count);

#define CONST_PI 3.141592654
#define CONST_SGM 5.67e-8

/**
 * @def CONST_CA
 * @brief 乾き空気の比熱[J/kgK].
 */
#define CONST_CA 1005.0

/**
 * @def CONST_CV
 * @brief 水蒸気の低圧比熱[J/kgK]
 */
#define CONST_CV 1846.0
#define CONST_ROA 1.29
#define CONST_CW 4186.0
#define CONST_ROW 1000.0

/**
 * @def CONST_RO
 * @brief 水の蒸発潜熱[J/kg]
 */
#define CONST_RO 2501000.

#define CONST_G 9.8

// 月の末日かどうかをチェックする
int	isEndDay(int Mon, int Day, int Dayend, int SimDayend);



#define  SCHAR    1024
//#define  NCHAR	  128

//#define  IDCHRMX  51


#define NOP   -1
#define FNOP  -999.9
#define TEMPLIMIT -273.16

#define  ERRFMT  "xxxxx %s xxxxx : "



//#define  ERSTR   101
#define  ERRFMTA  "xxx %s xxx %s\n"

//
/**
 * @def LOG_PRINT
 * @brief ログ出力用マクロ(printfと同じ形式で使用)
 */
#define LOG_PRINT(...) if(flog) { fprintf(flog, __VA_ARGS__); }

/**
 * @def LOG_ENABLED
 * @brief ログ出力が有効かどうかの真偽値
 */
#define LOG_ENABLED  (flog != NULL)
